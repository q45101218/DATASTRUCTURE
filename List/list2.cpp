/*************************************************************************
	> File Name: list2.cpp
	> Author: Yangkun
	> Mail: yangkungetit@163.com
	> Created Time: Sat 28 Oct 2017 10:12:31 PM PDT
 ************************************************************************/

#include<iostream>
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
}
template<class T>
class List 
{
public:
    List()
    :_head(NULL)
    ,_tail(NULL)
    {}

    List(const List<T>& List)
    {}

    List& operator=(List<T> l)
    {}

    ~List()
    {}

    void Push_Back(const T& data)
    {}

    void Push_Front(const T& data)
    {}

    void Pop_Back()
    {}

    void Pop_Front()
    {}

    Node<T>* Find()
    {}

private: 
    Node<T>* _head;
    Node<T>* _tail;
}
