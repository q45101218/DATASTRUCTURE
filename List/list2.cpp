/*************************************************************************
	> File Name: list2.cpp
	> Author: Yangkun
	> Mail: yangkungetit@163.com
	> Created Time: Sat 28 Oct 2017 10:12:31 PM PDT
 ************************************************************************/

#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct Node
{
    Node<T>* _next;
    T _data;

    Node(const T& data)
    :_next(NULL)
    ,_data(data)
    {}
};

template<class T>
class List 
{
public:
    List()
    :_head(NULL)
    ,_tail(NULL)
    {}

    List(const List<T>& l)
    :_head(NULL)
    ,_tail(NULL)
    {
        Node<T>* tmp=l._head;
        while(tmp)
        {
            Push_Back(tmp->_data);
            tmp=tmp->_next;
        }
    }

    List& operator=(List<T> l)
    {
        swap(_head,l._head);
        swap(_tail,l._tail);
    }

    ~List()
    {
        if(_head!=NULL)
        {
            Node<T>* del=_head;
            Node<T>* tmp=_head;
            while(del)
            {
                tmp=del;
                del=del->_next;
                delete tmp; 
            }
        }
    }

    void Push_Back(const T& data)
    {
        if(_head==NULL)
        {
            _head=_tail=new Node<T>(data);
        }
        else
        {
            _tail->_next=new Node<T>(data);
            _tail=_tail->_next;
        }
    }

    void Push_Front(const T& data)
    {
        if(_head==NULL)
        {
            _head=_tail=new Node<T>(data);
        }
        Node<T>* tmp=new Node<T>(data);
        tmp->_next=_head;
        _head=tmp;
    }

    void Pop_Back()
    {
        assert(_head);
        if(_head==_tail)
        {
            delete _head;
            _head=_tail=NULL;
        }
        else
        {
            Node<T>* tmp=_head;
            while(tmp->_next!=_tail)
            {
                tmp=tmp->_next;
            }
            _tail=tmp;
            delete _tail->_next;
            _tail->_next=NULL;
        }
    }

    void Pop_Front()
    {
        assert(_head);
        if(_head==_tail)
        {
            delete _head;
            _head=_tail=NULL;
        }
        else
        {
            Node<T>* del=_head;
            _head=_head->_next;
            delete del;
        }
    }

   // Node<T>* Find()
   // {}

    void Print()
    {
        Node<T>* tmp=_head;
        while(tmp)
        {
            cout<<tmp->_data<<" ";
            tmp=tmp->_next;
        }
        cout<<endl;
    }

private: 
    Node<T>* _head;
    Node<T>* _tail;
};


int main()
{
    List<int> l;
    l.Push_Back(1);
    l.Push_Back(2);
    l.Push_Back(3);
    l.Push_Back(4);
    l.Push_Back(5);
    l.Print();
    l.Push_Front(0);
    l.Print();
    List<int> l2(l);
    l2.Pop_Back();
    l2.Print();
    List<int> l3;
    l3=l;
    l3.Pop_Front();
    l3.Print();
    return 0;
}

