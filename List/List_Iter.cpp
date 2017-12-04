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


    bool operator==(self& it)
    {
        return it._p==_p;
    }

    bool operator!=(const self& it)
    {
        return it._p!=_p;
    }

    Ref operator*()
    {
        return _p->_data;
    }

    Ptr operator->()
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
    {
        node* tmp=_head->_next;
        while(_head!=tmp)
        {
            node* cur=tmp->_next;
            delete tmp;
            tmp=cur;
        }
        delete _head;
        cout<<"clear finised"<<endl;
    }

    void PushBack(const T& data)
    {
       // _head->_pre->_next=new node(data);
       // _head->_pre->_next->_pre=_head->_pre;
       // _head->_pre->_next->_next=_head;
       // _head->_pre=_head->_pre->_next;
        Insert(End(),data);
    }

    void PushFront(const T& data)
    {
        Insert(Begin(),data);
    }

    void PopBack()
    {
        Erase(--End());
    }

    void PopFront()
    {
        Erase(Begin());
    }

    void Insert(Iterator it,const T& data)
    {
        node* tmp=new node(data);
        it._p->_pre->_next=tmp;
        tmp->_pre=it._p->_pre;
        tmp->_next=it._p;
        it._p->_pre=tmp;
    }

    Iterator Erase(Iterator it)
    {
        assert(it!=End());
        Iterator tmp(it._p->_pre);
        tmp._p->_next=it._p->_next;
        it._p->_next->_pre=tmp._p;
        delete it._p;
        return tmp._p->_next;
    }

    bool Empty()
    {
        return _head->next==_head;
    }

    Iterator Begin()
    {
        return Iterator(_head->_next);
    }

    Iterator End()
    {
        return Iterator(_head);
    }

    Const_Iterator Begin()const
    {
        return Const_Iterator(_head->_next);
    }

    Const_Iterator End()const
    {
        return Const_Iterator(_head);
    }

private:
    node* _head;
};


void test(const List<int>& l)
{
    List<int>::Const_Iterator cit = l.Begin();
    while (cit != l.End())
    {
        cout << *cit++ << " ";
    }cout << endl;

}

int main()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);
    l.PushBack(5);
    l.PushBack(6);
    l.PushBack(7);
    l.PushBack(8);
    List<int>::Iterator it = l.Begin();
    while (it != l.End())
    {
        cout << *it++ <<" ";
    }cout << endl;

    l.PopFront();
    l.PopBack();
    l.PushFront(0);
    it = l.Begin();
    while (it != l.End())
    {
        cout << *it++ << " ";
    }cout << endl;

    test(l);
    return 0;
}

