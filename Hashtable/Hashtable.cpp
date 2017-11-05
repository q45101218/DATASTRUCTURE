/*************************************************************************
	> File Name: Hashtable.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 05 Nov 2017 01:34:29 AM PDT
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

enum condition
{
    EMPTY,
    DELETE,
    EXIST,
};

template<class K,class V>
struct Hashnode
{
    pair<K,V> member;
    condition con;
};

template<class K,class V,class __HashFun=HashFun>
class Hashtable
{
public:
    typedef Hashnode<K,V> node;

private:
    vector<node> hashtable;
    size_t size;
};




















