#include "Merkle Tree.h"
#include <iostream>
#include<vector>
#include <random>
#include<chrono>

string generate_random_string(size_t length) {
	static const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	static std::mt19937 rng(std::random_device{}());
	std::string result;
	for (size_t i = 0; i < length; ++i) {
		result.push_back(chars[rng() % chars.size()]);
	}
	return result;
}
int main()
{
	string check_str = "";
	cout << "输入数据:（输入//中止） " << endl;
	vector<string> v;
	//size_t num_strings = 100000;
	//size_t max_length = 100;
	//for (size_t i = 0; i < num_strings; ++i) {
	//	size_t length = 1 + rand() % max_length; // 生成随机长度
	//	std::string random_string = generate_random_string(length);
	//	v.push_back(random_string);
	//}
	while (1) //输入叶子节点
	{
		string str;
		cin >> str;
		if (str != "//")
		{
			v.push_back(str);
		}
		else
		{
			break;
		}
	}


	tree ntree;
	ntree.buildBaseLeafes(v);
	cout << "构建Merkle树过程:" << endl << endl;
	ntree.buildTree();
	ntree.show();

	auto start = std::chrono::high_resolution_clock::now();
	cout << "使用InclusionProof获得的根节点哈希值 " ;
	ntree.InclusionProof(3);
	auto end = std::chrono::high_resolution_clock::now();
	chrono::duration<double,milli> duration = end - start;
	cout << "InclusionProof用时: " << duration.count() << " 毫秒" << endl;
}

