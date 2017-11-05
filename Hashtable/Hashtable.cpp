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
    K key;
    V value;
    condition con;

    Hashnode(const K& k=0,const V& v=0)
    :key(k)
    ,value(v)
    ,con(EMPTY)
    {}
};

template<class K,class V>
struct HashFun
{
    size_t operator()(num,size)
    {
        return num%size;
    }
}

template<class K,class V,class __HashFun=HashFun>
class Hashtable
{
public:
    typedef Hashnode<K,V> node;

    Hashtable()
    :size(0)
    {}

    bool Insert(K& k,V& v)
    {
        Checkconflict();
        __HashFun HashFun;
        size_t index=HashFun(k,size);
        while()
        {
            if(table[index].con!=EXIST)
            {
                table[index].key=k;
                table[index].value=v;
                table[index].con=EXIST;
                break;
            }
            index++;
            if(index>table.size())
            {
                index=0;
            }
        }
    }

    void Checkconflict()
    {
        if(size=0||size*10%table.size()>=7)
        {
            size==0? table.resize(7):table.resize(size*2);
        }
    }


private:
    vector<node> table;
    size_t size;
};




















