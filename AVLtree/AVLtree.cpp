/*************************************************************************
	> File Name: AVLtree.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 13 Nov 2017 05:20:57 PM PST
 ************************************************************************/

#include<iostream>
using namespace std;


template<class T>
struct Treenode
{
    Treenode<T>* _right;
    Treenode<T>* _left;
    Treenode<T>* _parent;
    int _balance;
    T _data;

    Treenode(const T& data)
    :_data(data)
    {}
};

template<class T>
class AVLTree
{
    typedef Treenode<T> node;
public:
    AVLTree()
    :_root(NULL)
    {}

private:
    node* _root;
};

int main()
{
    return 0;
}
