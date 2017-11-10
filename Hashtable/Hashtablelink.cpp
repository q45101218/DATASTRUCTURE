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
    Hashnode<K,V>* _next;

    Hashnode(const K& key=K(),const V& value=V())
    :_key(key)
    ,_value(value)
    ,_next(NULL)
    {}
};

template<class K>
struct HashFun
{
    size_t operator()(K key,int size)
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
    :size(0)
    {}

    Hashtable(const Hashtable& h)
    {}

    Hash& operator=(Hashtable h)
    {}

    bool Insert(const K& key,const V& value)
    {
        CheckLoadFactory();
        __HashFun hashfun;
        size_t index=hashfun(key,_table.size());
        Find(key);
        if(_table[index]==NULL)
        {
            _table[index]=new node(key,value);
        }
        else
        {
            node* tmp=new node(key,value);
            tmp->_next=_table[index];
            _table[index]=tmp;
        }
        return true;
    }

    size_t Find(const K& key)
    {
    }

    bool Erase(const K& key)
    {
        __HashFun hashfun;
        size_t index=hashfun(key,_table.size());
        assert(_table[index]);
        node* cur=_table[index];
        node* pre=_table[index];
        while(key!==cur->key)
        {
            prv=cur;
            cur=cur->_next;
        }
        prv->_next=cur->_next;
        delete cur;
        return true;
    }
    
    void CheckLoadFactory()
    {
        if(_size=0||_size*10/_table.size()>7)
        {
            _size==0? _table.resize(7):Reallocate();
        }
    }

    void Reallocate()
    {
        vector<node*> newtable;
        newtable.resize(GetNextPrime(_table.size()));
        __HashFun hashfun;
        size_t i=0;
        for(size_t index=0;index<_table.size();index++)
        {
            if(_table[index]!=NULL)
            {
                node* next=_table[index];
                node* tmp=_table[index];
                _table[index]=NULL;
                while(tmp)
                {
                    i=hashfun(tmp->key,newtable.size());
                    next=tmp->_next;
                    if(newtable[i]==NULL)
                    {
                        newtable[i]=tmp;
                    }
                    else
                    {
                        node* cur=newtable[i]->_next;
                        newtable[i]=tmp;
                        tmp->_next=cur;
                    }
                    tmp=next;
                }
            }
        }
    }
private:
    vector<node*> _table;
    size_t _size;
};
