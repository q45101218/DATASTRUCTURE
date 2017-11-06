/*************************************************************************
	> File Name: Hashtablelink.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 05 Nov 2017 11:01:34 PM PST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

template<class K,class V>
struct Hashnode
{
    K _key;
    V _value;
    Hashnode<K,V> _next;

    Hashnode(const K& key=K(),const V& value=V())
    :_key(key)
    ,_value(value)
    ,_next(NULL)
    {}
};

template<class K>
struct HashFun
{
    size_t operator()(K key,size_t size)
    {
        return key%size;
    }
};

template<class K,class V,class __HashFun=HashFun<K> >
class Hashtable
{
    typedef Hashnode<K,V> node;
public:
    Hashtable()
    {}

    Hashtable(const Hashtable& h)
    {}

    Hash& operator=(Hashtable h)
    {}

    bool Insert(const K& key,const V& value)
    {}

    size_t Find(const K& key)
    {}

    bool Erase(const K& key)
    {}

private:
    vector<node*> table;
    size_t size;
};
