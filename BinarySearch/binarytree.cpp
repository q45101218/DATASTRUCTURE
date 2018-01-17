/*************************************************************************
	> File Name: binarytree.cpp
	> Author:yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 24 Dec 2017 10:30:49 PM CST
 ************************************************************************/

#include<iostream>
#include<stack>
#include<queue>
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

    void preinterview_recursion()
    {
        _pre_interview_recursion(_root);
        cout<<endl;
    }

    void midinterview_recursion()
    {
        _midinterview_recursion(_root),cout<<endl;
    }

    void postinterview_recursion()
    {
        _postinterview_recursion(_root),cout<<endl;
    }
    
    void preinterview_nonrecursion()
    {
        _preinterview_nonrecursion(_root);
    }
private:
    void _pre_interview_recursion(node*& root)
    {
        if(root==NULL)
        {
            return;
        }
        cout<<root->_data<<" ";
        _pre_interview_recursion(root->_leftchild);
        _pre_interview_recursion(root->_rightchild);
    }

    void _midinterview_recursion(node*& root)
    {
        if(root==NULL)
        {
            return;
        }
        _midinterview_recursion(root->_leftchild);
        cout<<root->_data<<" ";
        _midinterview_recursion(root->_rightchild);
    }

    void _postinterview_recursion(node*& root)
    {
        if(!root)
            return;
        _postinterview_recursion(root->_leftchild);
        _postinterview_recursion(root->_rightchild);
        cout<<root->_data<<" ";
    }
    
    //first method
    //void _preinterview_nonrecursion(node*& root)
    //{
    //    if(!root)
    //        return;
    //    stack<node*> sbt;
    //    sbt.push(root);
    //    while(!sbt.empty())
    //    {
    //        node* tmp=sbt.top();
    //        sbt.pop();
    //        cout<<tmp->_data<<" ";
    //        
    //        if(NULL!=tmp->_rightchild)
    //        {
    //            sbt.push(tmp->_rightchild);
    //        }

    //        if(NULL!=tmp->_leftchild)
    //        {
    //            sbt.push(tmp->_leftchild);
    //        }
    //    }
    //    cout<<endl;
    //}
    
    //second method
    void _preinterview_nonrecursion(node*& root)
    {
        if(root==NULL)
            return;

        stack<node*> sbt;
        node* tmp=root;
        while(tmp||!sbt.empty())
        {
            while(tmp)
            {
                cout<<tmp->_data<<" ";
                sbt.push(tmp);
                tmp=tmp->_leftchild;
            }
            tmp=sbt.top();
            sbt.pop();
            tmp=tmp->_rightchild;
        }
        cout<<endl;
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
    bt.preinterview_recursion();
    bt.preinterview_nonrecursion();
    bt.midinterview_recursion();
    bt.postinterview_recursion();
}

int main()
{
    test();
    return 0;
}


