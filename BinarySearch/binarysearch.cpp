/*************************************************************************
	> File Name: binarysearch.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Tue 14 Nov 2017 12:28:49 PM PST
 ************************************************************************/

#include<iostream>
using namespace std;

template<class T>
struct Treenode
{
    typedef Treenode<T> node;
    node* _left;
    node* _right;
    T _key;

    Treenode(const T& key)
    :_left(NULL)
    ,_right(NULL)
    ,_key(key)
    {}
};

template<class T>
class Binarysearch
{
    typedef Treenode<T> node;
public:
    Binarysearch()
    :_root(NULL)
    {}

    bool Insert(const T& key)
    {
        if(!_root)
        {
            _root=new node(key);
        }
        node* parent=_root;
        node* newchild=_root;
        while(newchild)
        {
            parent=newchild;
            if(newchild->_key<key)
            {
                newchild=newchild->_right;
            }
            else if(newchild->_key>key)
            {
                newchild=newchild->_left;
            }
            else
            {
                return false;
            }
        }
        if(parent->_key<key)
        {
            parent->_right=new node(key);
        }
        else
        {
            parent->_left=new node(key);
        }
        return true;
    }

    node* Find(const T& key)
    {
        node* cur=_root;
        while(cur)
        {
            if(cur==key)
            {
                return cur;
            }
            else if(cur->_key>key)
            {
                cur=cur->_left;
            }
            else
            {
                cur=cur->_right;
            }
        }
        return NULL;
    }

    void Inorder()
    {
        _Inorde(_root);
        cout<<endl;
    }

    void _Inorde(node* root)
    {
        if(!root)
            return;
        _Inorde(root->_left);
        cout<<root->_key<<" ";
        _Inorde(root->_right);
    }
private:
    node* _root;
};

int main()
{
    Binarysearch<int> bs;
    bs.Insert(5);
    bs.Insert(1);
    bs.Insert(4);
    bs.Insert(9);
    bs.Insert(7);
    bs.Insert(8);

    bs.Inorder();

    return 0;
}
