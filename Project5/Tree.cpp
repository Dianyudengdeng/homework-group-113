#include "Merkle Tree.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


tree::tree() {}

node* tree::build(int start,int end) {//索引起始值和索引中止值前一位 [start,end)
	if (start == end-1) {//叶子结点
		string concatenated = to_string(start) + "-" + to_string(end);
		MTH[concatenated] = leaves[start]->getHash();
		return leaves[start];
	}
	else {
		int k = 1;
		while (k < end-start) {
			k <<= 1; // 等价于 k = k * 2
		}
		k >>= 1;
		//递归完成左右子树的构建
		node* left = build(start,start+k);
		node* right = build(start+k,end);

		node* new_parent = new node;
		left->setParent(new_parent);
		right->setParent(new_parent);
		new_parent->setInternalHash(left->getHash() + right->getHash());
		new_parent->setChildren(left, right);

		string concatenated = to_string(start) +"-" + to_string(end);
		MTH[concatenated] = new_parent->getHash();

		cout << left->getHash() << " 和 " << right->getHash() << " 父节点构建完成 " << endl << endl;
		cout << "得到的对应父节点的哈希值:" << endl;
		cout << new_parent->getHash() << endl << endl;
		return new_parent;
	}
}
node* tree::build_1(vector<node*> lowbase) {
	if (lowbase.size() == 1) {//叶子结点
		return lowbase[0];
	}
	else {
		int k = 1;
		while (k < lowbase.size()) {
			k <<= 1; // 等价于 k = k * 2
		}
		k >>= 1;
		//递归完成左右子树的构建
		vector<node*>subVectorleft(lowbase.begin(), lowbase.begin() + k);
		vector<node*>subVectorright(lowbase.begin() + k, lowbase.end());
		node* left = build_1(subVectorleft);
		node* right = build_1(subVectorright);

		node* new_parent = new node;
		left->setParent(new_parent);
		right->setParent(new_parent);
		new_parent->setInternalHash(left->getHash() + right->getHash());
		new_parent->setChildren(left,right);
		cout << left->getHash() << " 和 " << right->getHash() << " 父节点构建完成 " << endl << endl;

		cout << "得到的对应父节点的哈希值:" << endl ;
		cout << new_parent->getHash() << endl << endl;
		return new_parent;
	}
}

int tree::buildTree() //建造merkle tree
{
	merkleRoot = build(0,leaves.size());

	cout << "构建的MTH表：" << endl;
	for (const auto& pair : MTH) {
		std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
	}
	return 1;
}

void tree::buildBaseLeafes(vector<string> leafs) //建立叶子节点列表
{

	cout << "叶子结点及对应的哈希值: " << endl;

	for (auto leaf : leafs) //给每一个字符串创建对应节点，并通过这个字符串设置哈希值
	{
		node* new_node = new node;
		new_node->setLeafHash(leaf);
		cout << leaf << ":" << new_node->getHash() << endl;

		leaves.push_back(new_node);
	}

	cout << endl;
}

int tree::InclusionProof(int index) {
	string hash = Audit_Path(index, 0, leaves.size());
    cout << hash << endl;
	return hash == merkleRoot->getHash() ? 1 : 0;
}

int tree::ExclusionProof(int index) {
	string hash = Audit_Path(index, 0, leaves.size());
	cout << hash << endl;
	return hash == merkleRoot->getHash() ? 1 : 0;
}

string tree::Audit_Path(int index, int start, int end) {//递归构建审计路径
	if (start == end - 1) {
		string concatenated = to_string(start) + "-" + to_string(end);
		cout << "审计路径包含的内容:" << concatenated << endl;
		return MTH[concatenated];
	}
	else {
		int k = 1;
		while (k < end - start) {
			k <<= 1; 
		}
		k >>= 1;
		if (index < k) {
			string concatenated =to_string(start + k) + "-" + to_string(end-start);
			cout << "审计路径包含的内容:" << concatenated << endl;
			return sha256("0x01" + Audit_Path(index, start, start+k)+ MTH[concatenated]);
		}
		else {
			string concatenated = to_string(start) + "-" + to_string(start+k);
			cout << "审计路径包含的内容:" << concatenated << endl;
			return sha256("0x01"+MTH[concatenated]+ Audit_Path(index, start + k, end));
		}
	}
}

string tree::SUBPROOF(int index,int start,int end,bool TF) {
	int n = end - start;
	if (index == n) {
		if (TF)
			return this->merkleRoot->getHash();//根哈希已知
		else {
			string concatenated = to_string(0) + "-" + to_string(index);
			return MTH[concatenated];
		}
	}
	else {
		int k = 1;
		while (k < n) {
			k <<= 1;
		}
		k >>= 1;
		if (index <= k) {
			string concatenated = to_string(index) + "-" + to_string(n);
			return sha256("0x01" + SUBPROOF(index, 0, k, TF) + MTH[concatenated]);
		}
		else {
			string concatenated = to_string(0) + "-" + to_string(k);
			return sha256("0x01" + SUBPROOF(index-k, k, n, TF) + MTH[concatenated]);
		}
	}

}



tree::~tree() {}