#include "Merkle Tree.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

node::node()
{
	parent = nullptr;
	children[0] = nullptr;
	children[1] = nullptr;
}

//���ù�ϣֵ
void node::setLeafHash(string hash_str)
{
	this->hash_str = sha256("0x00"+hash_str);
}
void node::setInternalHash(string hash_str)
{
	this->hash_str = sha256("0x01" + hash_str);
}
node* node::getParent()
{
	return parent;
}
void node::setParent(node* parent)
{
	this->parent = parent;
}
void node::setChildren(node* children_l, node* children_r)
{
	children[0] = children_l;
	children[1] = children_r;
}
node* node::getSibling() //�����ӵõ��Һ��ӣ����Һ��ӵõ�����
{
	node* parent = getParent();
	return parent->getChildren(0) == this ? parent->getChildren(1) : parent->getChildren(0);
}
node* node::getChildren(int index)
{
	return index <= 1 ? children[index] : nullptr;
}
string node::getHash()
{
	return hash_str;
}
int node::checkDir()
{
	//����丸�ڵ�������Ǹýڵ� ����0 �����򷵻�1
	return parent->getChildren(0) == this ? 0 : 1;
}

node::~node() {}

