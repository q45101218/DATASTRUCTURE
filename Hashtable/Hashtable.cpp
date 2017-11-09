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
    size_t operator()(K k)
    {
        return k;
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
        size_t index=Hashfun(k);
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
        newtable.table.resize(GetNextPrime(table.size()));
        for(size_t index=0;index<table.size();index++)
        {
            if(table[index].con==EXIST)
            {
                newtable.Insert(table[index].key,table[index].value);
            }
        }
        table.swap(newtable.table);
    }

    size_t Hashfun(const K& k)
    {
        __HashFun hashfun;
        return hashfun(k)%table.size();
    }    
   
    node* Find(const K& k)
    {
        size_t index=Hashfun(k);
        while(table[index].con!=EMPTY)
        {
            if(table[index].key==k&&table[index].con==EXIST)
            {
                return &table[index];
            }

            index++;
            if(index>table.size())
            {
                index=0;
            }
        }
        return NULL;
    }
     
    bool Erase(const K& pos)
    {
        if(Find(pos)!=NULL)
        {
            Find(pos)->con=DELETE;
            size--;
            return true;
        }
        return false;
    }

    size_t GetNextPrime(size_t value)
    {
        const size_t _PrimeSize = 28;
        static const unsigned long _PrimeList [_PrimeSize] =
        {
            53ul,         97ul,         193ul,       389ul,       769ul,
            1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
            49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
            1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
            50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
            1610612741ul, 3221225473ul, 4294967291ul              
        };

        for (size_t i = 0; i < _PrimeSize; ++i)
        {
            if (_PrimeList[i] > value)
            {
                return _PrimeList[i];                
            }           
        }
                
        return _PrimeList[_PrimeSize-1];           
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
    h.Erase(4);
    h.Insert(11,1);
    h.Insert(14,1);
    h.Insert(10,1);
    h.Insert(28,1);
    h.Insert(40,1);

    return 0;
}


















