/*************************************************************************
	> File Name: binarytree.cpp
	> Author:yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 24 Dec 2017 10:30:49 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

template<class T>
struct Treenode
{
    T _data;
    Treenode<T>* _leftchild;
    Treenode<T>* _rightchild;

    Treenode(const T& data)
    :_data(data)
    ,_leftchild(NULL)
    ,_rightchild(NULL)
    {}
};

template<class T>
class binarytree
{
    typedef Treenode<T> node;
public:
    binarytree(const T* data,int value)
    {
        int index=0;
        _root=createtree(data,index,value);
    }

    node* createtree(const T* data,int& index,int value)
    {
        if(data[index]==value)
            return NULL;
        else
        {
            node* tmp=new node(data[index]);
            tmp->_leftchild=createtree(data,++index,value);
            tmp->_rightchild=createtree(data,++index,value);
            return tmp;
        }
    }

    size_t height()
    {
        return _height(_root);
    }

    size_t size()
    {
        size_t size=0;
        _size(_root,size);
        return size;
    }

    size_t _height(node* root)
    {
        if(root==NULL)
            return 0;
        size_t left=_height(root->_leftchild);
        size_t right=_height(root->_rightchild);
        return left>right? left+1:right+1;
    }

    void _size(node* root,size_t& size)
    {
        if(root==NULL)
            return;
        size++;
        _size(root->_leftchild,size);
        _size(root->_rightchild,size);
    }

private:
    node* _root;
};


int test()
{
    int arry[]={1,2,3,'#','#',4,'#','#',5,6,'#','#','#'};
    binarytree<int> bt(arry,'#');
    cout<<bt.size()<<endl;
    cout<<bt.height()<<endl;
    int i;
    return i;
}

int main()
{
    test();
    return 0;
}

