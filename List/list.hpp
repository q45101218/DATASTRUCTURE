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

template<class T>
class List
{
public:
    List()
    :_head(NULL)
    {}

    List(const List& l)
    {}

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
            _head->_prev=_head->_prev->_next->_next;
            _head=_head->prev;
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
            Node<T>* tail=_head->_prev;
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

private:
    Node<T>* _head;
};


