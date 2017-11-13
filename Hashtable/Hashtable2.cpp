/*************************************************************************
	> File Name: Hashtable2.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 12 Nov 2017 05:31:33 PM PST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

template<class ValueType>
struct Hashnode
{
    Hashnode(const ValueType& v)
    :_value(v)
    ,_next(NULL)
    {}

    Hashnode<ValueType>* _next;
    ValueType _value;
};

template<class K>
struct _KofK
{
    K operator()(K key)
    {
        return key;
    }
};

template<class K,class V>
struct _KofKV
{
    K operator()(const pair<K,V>& value)
    {
        return value.first;
    }
};

template<class K>
struct _Hashfun
{
    K operator()(const K& key)
    {
        return key;
    }
};

template<class K,class ValueType,class KofValueType,template<class> class __HashFun>
class Hashtable;

template<class K,class ValueType,class Ref,class Ptr,class KofValueType,template<class> class __HashFun>
struct HashtableIterator
{
    typedef Hashtable<K,ValueType,KofValueType,__HashFun> hashtable;
    typedef HashtableIterator<K,ValueType,Ref,Ptr,KofValueType,__HashFun>  Self;
    typedef Hashnode<ValueType> node;
    HashtableIterator(node* ptr,hashtable* ht)
    :_ptr(ptr)
    ,_ht(ht)
    {}

    Ref operator->()
    {
        return &(*_ptr);
    }

    Ptr operator*()
    {
        return _ptr;
    }

    hashtable* _ht;
    node* _ptr;
};

template<class K,class ValueType,class KofValueType,template<class> class __HashFun=_Hashfun >
class Hashtable
{
    typedef Hashnode<ValueType> node;
    typedef Hashtable<K,ValueType,KofValueType,__HashFun> hashtable;
    friend HashtableIterator<K,ValueType,ValueType&,ValueType*,KofValueType,__HashFun> Iterator;
public:
    typedef HashtableIterator<K,ValueType,ValueType&,ValueType*,KofValueType,__HashFun> Iterator;

public:
    Hashtable()
    :_size(0)
    {}

    pair<Iterator,bool> Insert(const ValueType& v)
    {
        CheckLoadFactory();
        size_t index=Hashfun(v,_table.size());

        node* tmp=new node(v);
        tmp->_next=_table[index];
        _table[index]=tmp;
        _size++;
        return make_pair(Iterator(tmp,this),true);
    }

    void CheckLoadFactory()
    {
        if(_size==0||_size*10/_table.size()>10)
        {
            _size==0? _table.resize(7):Reallocate();
        }
    }

    void Reallocate()
    {
        vector<node*> newtable;
        newtable.resize(GetNextPrime(_table.size()));
        size_t newindex=0;
        for(size_t index=0;index<_table.size();index++)
        {
            if(_table[index])
            {
                node* tmp=_table[index];
                _table[index]=NULL;
                while(tmp)
                {
                    node* next=tmp->_next;
                    newindex=Hashfun(tmp->_value,newtable.size());
                    newtable[newindex]=
                }
            }
        }
    }

    size_t GetNextPrime(size_t pre)
    {
        const size_t _PrimeSize = 28;
        static unsigned long _PrimeList[_PrimeSize] =
        {
            53ul, 97ul, 193ul, 389ul, 769ul,
            1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
            49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
            1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
            50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
            1610612741ul, 3221225473ul, 4294967291ul
        };
        for (size_t index = 0; index<_PrimeSize; index++)
        {
            if (pre<_PrimeList[index])
                return _PrimeList[index];
        }
        return _PrimeList[_PrimeSize - 1];
    }

    size_t Hashfun(const ValueType& v,size_t size)
    {
        KofValueType _KofValueType;
        __HashFun<K> hashfun;
        return (hashfun(_KofValueType(v)))%size;
    }
private:
    vector<node*> _table;
    size_t _size;
};

int main()
{
    Hashtable<int,int,_KofK<int> > h;
    h.Insert(1);
    h.Insert(2);
    h.Insert(3);
    h.Insert(4);
    return 0;   
}
