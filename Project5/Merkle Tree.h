#pragma once
#include<iostream>
#include<vector>
#include <unordered_map>
using namespace std;
string sha256(const string& message);

class node
{
private:
	string hash_str;
	node* parent;
	node* children[2];
public:
	node();
	string getHash();
	node* getParent();
	node* getChildren(int index);
	node* getSibling();
	int checkDir();
	void setLeafHash(string hash_str);
	void setInternalHash(string hash_str);
	void setParent(node* parent);
	void setChildren(node* children_l, node* children_r);
	virtual ~node();
};

class tree
{
private:
	node* merkleRoot;
	vector<node*>leaves; // Merkle Tree叶节点
	unordered_map<std::string, std::string> MTH;
public:
	tree();
	node* build(int start, int end);
	node* build_1(vector<node*> lowbase);
	int buildTree();
	void buildBaseLeafes(vector<string> leafs);
	string Audit_Path(int index, int start, int end);
	int InclusionProof(int index); //验证有无这个节点 树有无改变
	int ExclusionProof(int index);//验证这个结点是否在树中
	string SUBPROOF(int index, int start, int end, bool TF);
	virtual ~tree();
};