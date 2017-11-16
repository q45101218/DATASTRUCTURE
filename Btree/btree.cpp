/*************************************************************************
	> File Name: btree.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Wed 15 Nov 2017 05:59:39 PM PST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct Treenode
{
    typedef Treenode<T> node;
    
    node* parent;
    vector<T> _key;
    vector<node*> _child;
    size_t _size;

};

template<class T>
class Btree
{
    typedef Treenode<T> node;
public:
    Btree()
    {}
private:
    node* _root;
};

int main()
{
    return 0;
}

