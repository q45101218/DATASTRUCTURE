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

    Hashnode(const K k=K(),const V v=V())
    :key(k)
    ,value(v)
    ,con(EMPTY)
    {}
};

template<class K>
struct HashFun
{
    size_t operator()(K num,size_t size)
    {
        return num%size;
    }
};

template<class K,class V,class __HashFun=HashFun<K> >
class Hashtable
{
public:
    typedef Hashnode<K,V> node;

    Hashtable()
    :size(0)
    {}

    Hashtable(const Hashtable& h)
    :size(0)
    {
        for(size_t index=0;index<h.table.size();index++)
        {
            Insert(h.table[index].key,h.table[index].value);
        }
    }

    Hashtable& operator=(Hashtable h)
    {
        table.swap(h.table);
        swap(size,h.size);
        return *this;
    }

    bool Insert(K k,V v)
    {
        Checkconflict();
        __HashFun HashFun;
        size_t index=HashFun(k,table.size());
        while(table[index].key=k||(table[index].key=k&&table[index].con!=EXIST))
        {
            if(table[index].con!=EXIST)
            {
                table[index].key=k;
                table[index].value=v;
                table[index].con=EXIST;
                size++;
                return true;
            }
            index++;
            if(index>table.size())
            {
                index=0;
            }
        }
        return false;
    }

    void Checkconflict()
    {
        if(table.size()==0||(size*10/table.size())>7)
        {
            table.size()==0? table.resize(7):Changecapacity();
        }
    }

    void Changecapacity()
    {
        Hashtable<K,V,__HashFun> newtable;
        newtable.table.resize(table.size()*2);
        for(size_t index=0;index<table.size();index++)
        {
            if(table[index].con==EXIST)
            {
                newtable.Insert(table[index].key,table[index].value);
            }
        }
        table.swap(newtable.table);
    }
    
    int Find(const K& k)
    {
        size_t index=__HashFun()(k,table.size());
        while(table[index].con!=EMPTY)
        {
            if(table[index].key==k&&table[index].con==EXIST)
            {
                return index;
            }

            index++;
            if(index>table.size())
            {
                index=0;
            }
        }
        return -1;
    }

    bool Erase(const K& pos)
    {
        if(Find(pos)!=-1)
        {
            table[Find(pos)].con=DELETE;
            size--;
        }
    }


private:
    vector<node> table;
    size_t size;
};

int main()
{
    Hashtable<int,int> h;
    h.Insert(1,1);
    h.Insert(2,1);
    h.Insert(8,1);
    h.Insert(9,1);
    h.Insert(4,1);
    int index=h.Find(4);
    h.Erase(4);
    int index2=h.Find(4);
    h.Insert(11,1);
    h.Insert(14,1);
    h.Insert(10,1);
    h.Insert(28,1);
    h.Insert(40,1);

    return 0;
}


















