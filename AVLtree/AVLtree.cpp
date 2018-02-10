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
        node* parent = _root;
        while(cur)
        {
            parent = cur;
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
        if( data < parent->_data )
        {
            parent->_left = new node(data);
            parent->_left._parent = parent;
        }
        else
        {
            parent->_right = new node(data);
            parent->_right = new node(data);
        }
        while()
        {}
    }


private:

    void _preorder(node*& root)
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

    void _midorder(node*& root)
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

    void _postorder(node*& root)
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

    void _LeftRote(node* cur)
    {
        node* parentR = cur->_right;
        node* parentRL = parentR->_left;
        cur->_right = parentRL;
        if(parentRL !=  NULL)
        {
            parentRL->_parent = cur;
        }
        parentR->_left = cur;
        node* grandp = cur->_parent;
        cur->_parent = parentR;
        if(grandp == NULL)
        {
            cur->_parent == NULL;
            _root = cur;
        }
        else if(grandp->_left == cur)
        {
            grandp->_left = parentR;
            parentR->_right = grandp;
        }
        else
        {
            grandp->_right = parentR;
            parentR->parent = grandp;
        }

    }

    void _RightRote(node* cur)
    {
        node* parentL = cur->_left;
        node* parentLR = parentL->_right;
        cur->_left = parentLR;
        if(parentLR)
        {
            parentLR->_parent = cur;
        }
        parentL->_right = cur;
        node* grandp = cur->_parent;
        cur->_parent = parentL;
        if(grandp == NULL)
        {
            parentL->_parent == NULL;
            _root = parentL;
        }
        else
        {
            grandp->_left == cur? grandp->_left = parentL : grandp->_right = parentL;
            parentL->_parent = grandp;
        }
}
private:
    node* _root;
};

int main()
{
    return 0;
}
