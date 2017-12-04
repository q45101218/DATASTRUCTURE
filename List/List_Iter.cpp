/*************************************************************************
	> File Name: List_Iter.cpp
	> Author:yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 04 Dec 2017 09:55:58 AM CST
 ************************************************************************/

#include<iostream>
#include<assert.h>

using namespace std;

template<class T>
struct Node
{
    Node(const T& data=T())
    :_data(data)
    ,_pre(NULL)
    ,_next(NULL)
    {}

    Node<T>* _pre;
    T _data;
    Node<T>* _next;
};

template<class T,class Ref,class Ptr>
class List_Iterator
{
    typedef List_Iterator<T,Ref,Ptr> self;
    typedef Node<T> node;
public:
    List_Iterator(node* p=NULL)
    :_p(p)
    {}

    T& operator*()
    {
        return _p->data;
    }

    T* operator->()
    {
        return _p;
    }

    self& operator++()
    {
        _p=_p->_next;
        return *this;
    }

    self operator++(int)
    {
        self tmp(*this);
        _p=_p->_next;
        return tmp;
    }

    self& operator--()
    {
        _p=_p->_pre;
        return *this;
    }

    self operator--(int)
    {
        self tmp(*this);
        _p=_p->_pre;
        return tmp;
    }

    node* _p;
};

template<class T>
class List
{
    typedef Node<T> node;
    typedef List<T> ListSelf;
public:
    typedef List_Iterator<T,T&,T*> Iterator;
    typedef List_Iterator<T,const T&,const T*> Const_Iterator;
public:
    List()
    :_head(new node)
    {
        _head->_next=_head;
        _head->_pre=_head;
    }

    List(const ListSelf& l)
    :_head(new node)
    {
        
    }

    ListSelf& operator=(ListSelf l)
    {}

    ~List()
    {}

    void PushBack(const T& data)
    {
        _head->_pre->_next=new node(data);
        _head->_pre->_next->_pre=_head->_pre;
        _head->_pre->_next->_next=_head;
        _head->_pre=_head->_pre->_next;
    }

    void PushFront()
    {}

    void PopBack(const T& data)
    {}

    void PopFront(const T& data)
    {}

    void Insert(Iterator& it,const T& data)
    {
    }

    Iterator Find(const T& data)
    {}

    Iterator Erase(Iterator& it)
    {
        assert(it!=End());
        Iterator tmp(it->_pre);
        tmp->_next=it->_next;
        it->_next->_pre=tmp._p;
        delete it._p;
        return tmp;
    }

    bool Empty()
    {
        return _head->next==_head;
    }

    Iterator Begin()
    {
        return _head->_next;
    }

    Iterator End()
    {
        return _head;
    }

    Const_Iterator Begin()const
    {
        return _head->next;
    }

    Const_Iterator End()const
    {
        return _head;
    }

private:
    node* _head;
};

int main()
{
    List<int> l;
    return 0;
}
