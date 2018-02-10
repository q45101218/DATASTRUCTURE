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
    ,_balance(0)
    ,_left(NULL)
    ,_right(NULL)
    ,_parent(NULL)
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

    void preorder()
    {
        _preorder( _root);
    }

    void midorder()
    {
        _midorder( _root);
    }

    void postorder()
    {
        _postorder( _root);
    }

    bool insert(T& data)
    {
        if(_root == NULL)
        {
            _root = new node(data);
            return true;
        }
        node* cur = _root;
        while(cur)
        {
            if(data < cur->_data)
            {
                cur = cur->_left;
            }
            else if(data > cur->_data)
            {
                cur = cur->_right;
            }
            else
            {
                return false;
            }
        }

    }


private:

    void _preorder(node*& const root)
    {
        if(root == NULL)
        {
            return;
        }
        cout << root->_data << endl;
        if( root->_left != NULL )
        {
            _preorder(root->_left);
        }
        
        if( root->_right != NULL )
        {
            _preorder(root->_right);
        }
    }

    void _midorder(node*& const root)
    {
        if(root == NULL)
        {
            return;
        }

        if(root->_left != NULL)
        {
            _midorder(root->_left);
        }
        cout << root->_data << endl;
        if(root->_right != NULL)
        {
            _midorder(root->_right);
        }
    }

    void _postorder(node*& const root)
    {
        if(root == NULL)
        {
            return;
        }
        if(root->_left != NULL)
        {
            _postorder(root->_left);
        }
        if(root->_right != NULL)
        {
            _postorder(root->_right);
        }
        cout << root->_data << endl;
    }

private:
    node* _root;
};

int main()
{
    return 0;
}
