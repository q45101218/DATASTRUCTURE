/*************************************************************************
	> File Name: list.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 25 Oct 2017 05:14:07 AM PDT
 ************************************************************************/
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;


template<class T>
struct Node
{
    Node(const T& data)
    :_prev(NULL)
    ,_next(NULL)
    ,_data(data)
    {}

    Node<T>* _prev;
    Node<T>* _next;
    T _data;
};

template<class T,class Ref,class Ptr>
struct Iterator
{
    typedef Iterator<T,Ref,Ptr> Self;
    typedef Node<T> node;
    Iterator(node* p=NULL)
    :_ptr(p)
    {}


    node* _ptr;
}

template<class T>
class List
{
public:
    List()
    :_head(new node)
    {
        _head->_prev=_head;
        _head->_next=_head;
    }

    List(const List& l)
    :_head(NULL)
    {
        Node<T>* cur=l._head;
        while(cur->_next!=l._head)
        {
            Push_Back(cur->_data);
            cur=cur->_next;
        }
        Push_Back(cur->_data);
    }

    List& operator=(List l)
    {
        swap(_head,l._head);
        return *this;
    }

    void Push_Back(const T& data)
    {
        if(NULL==_head)
        {
            _head=new Node<T>(data);
            _head->_prev=_head;
            _head->_next=_head;
        }
        else
        {
            _head->_prev->_next=new Node<T>(data);
            _head->_prev->_next->_prev=_head->_prev;
            _head->_prev=_head->_prev->_next;
            _head->_prev->_next=_head;
        }
    }

    void Pop_Back()
    {
        assert(_head);
        if(_head->_prev==_head)
        {
            delete _head;
            _head=NULL;
        }
        else
        {
            _head->_prev=_head->_prev->_prev;
            delete _head->_prev->_next;
            _head->_prev->_next=_head;
        }
    }

    void Push_Front(const T& data)
    {
        if(NULL==_head)
        {
            _head=new Node<T>(data);
            _head->_prev=_head;
            _head->_next=_head;
        }

        else
        {
            _head->_prev->_next=new Node<T>(data);
            _head->_prev->_next->_prev=_head->_prev;
            _head->_prev->_next->_next=_head;
            _head->_prev=_head->_prev->_next;
            _head=_head->_prev;
        }
    }

    void Pop_Front()
    {
        assert(_head);
        if(_head->_next==_head)
        {
            delete _head;
            _head=NULL;
        }
        else
        {
            Node<T>* tmp=_head;
            _head->_prev->_next=_head->_next;
            _head->_next->_prev=_head->_prev;
            _head=_head->_next;
            delete tmp;
        }
    }

    ~List()
    {
        if(_head!=NULL)
        {
            Node<T>* del=_head;
            while(del->_next!=_head)
            {
                del=del->_next;
                delete del->_prev;
            }
            delete del;
            _head=NULL;
        }
    }

    void Print()
    {
        if(_head!=NULL)
        {
            Node<T>* tmp=_head;
            while(tmp->_next!=_head)
            {
                cout<<tmp->_data<<" ";
                tmp=tmp->_next;
            }
            cout<<tmp->_data;
        }
        cout<<endl;
    }
private:
    Node<T>* _head;
};


