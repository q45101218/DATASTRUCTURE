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
    HashtableIterator(node* ptr=NULL,hashtable* ht=NULL)
    :_ptr(ptr)
    ,_ht(ht)
    {}

    Ptr operator->()
    {
        return &(_ptr->_value);
    }

    Ref operator*()
    {
        return _ptr->_value;
    }

    Self& operator++()
    {
        Increase();
        return *this;
    }

    Self operator++(int)
    {
        Self tmp(*this);
        Increase();
        return tmp;
    }

    Self& operator--()
    {
        Decrease();
        return *this;
    }

    Self operator--(int)
    {
        Self tmp(*this);
        Decrease();
        return tmp;
    }

    bool operator!=(const Self& it)
    {
        return it._ptr!=_ptr; 
    }

    bool operator==(const Self& it)
    {
        return it._ptr==_ptr;
    }

    hashtable* _ht;
    node* _ptr;

private:
    void Increase()
    {
        assert(_ptr);
        if(_ptr->_next)
        {
            _ptr=_ptr->_next;
            return;
        }
        else
        {
            size_t index=_ht->Hashfun(_ptr->_value,_ht->_table.size())+1;
            for(index;index<_ht->_table.size();index++)
            {
                if(_ht->_table[index])
                {
                    _ptr=_ht->_table[index];
                    return;
                }
            }
            _ptr=NULL;
        }
    }

    void Decrease()
    {
        size_t index=_ht->Hashfun(_ptr->_value,_ht->_table.size());
        if(_ptr!=_ht->_table[index])
        {
            node* tmp=_ht->_table[index];
            while(tmp->_next!=_ptr)
            {
                tmp=tmp->_next;
            }
            _ptr=tmp;
        }
        else
        {
            if(index==0)
            {
                _ptr=NULL;
                return;
            }
            else
            {
                node* tmp=_ht->_table[index-1];
                while(tmp->_next!=NULL)
                {
                    tmp=tmp->_next;
                }
                _ptr=tmp;
            }
        }
    }
};

template<class K,class ValueType,class KofValueType,template<class> class __HashFun=_Hashfun >
class Hashtable
{
    typedef Hashnode<ValueType> node;
    typedef Hashtable<K,ValueType,KofValueType,__HashFun> hashtable;
    friend struct HashtableIterator<K,ValueType,ValueType&,ValueType*,KofValueType,__HashFun>;
public:
    typedef HashtableIterator<K,ValueType,ValueType&,ValueType*,KofValueType,__HashFun> Iterator;

public:
    Hashtable()
    :_size(0)
    {}

    Hashtable(const hashtable& h)
    :_size(0)
    {
        for(size_t index=0;index<_table.size();index++)
        {
            node* tmp=h._table[index];
            while(tmp)
            {
                node* next=tmp->_next;
                Insert(tmp->_value);
                tmp=next;
            }
        }
    }

    hashtable& operator=(hashtable h)
    {
        swap(_size,h._size);
        _table.swap(h._table);
        return *this;
    }

    ~Hashtable()
    {
        for(size_t index=0;index<_table.size();index++)
        {
            if(_table[index])
            {
                node* del=_table[index];
                node* next=del->_next;
                delete del;
                del=next;
            }
            _table[index]=NULL;
        }
    }

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
   
    bool Erase(Iterator& it)
    {
        assert(it);
        return Erase(*it);
    }

    bool Erase(ValueType& v)
    {
        size_t index=Hashfun(v,_table.size());
        node* del=_table[index];
        node* pre=del;
        if(del->_value==v)
        {
            _table[index]=del->_next;
        }
        while(del!=NULL)
        {
            if(del->_value==v)
            {
                pre->_next=del->_next;
                delete del;
                return true;
            }
            pre=del;
            del=del->_next;
        }
        return false;
    }


    Iterator Find(const ValueType& v)
    {
        size_t index=Hashfun(v,_table.size());
        node* tmp=_table[index];
        while(tmp)
        {
            if(tmp->_value==v)
            {
                break;
            }
            tmp=tmp->_next;
        }
        return Iterator(tmp,this);
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
                    tmp->_next=newtable[newindex];
                    newtable[newindex]=tmp;
                    tmp=next;
                }
            }
        }
        _table.swap(newtable);
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

    Iterator Begin()
    {
        for(size_t index=0;index<_table.size();index++)
        {
            if(_table[index])
            {
                return Iterator(_table[index],this);
            }
        }
        return Iterator(NULL,this);
    }

    Iterator End()
    {
        return Iterator(NULL,this);
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
    h.Insert(5);
    h.Insert(6);
    h.Insert(7);
    h.Insert(8);
    h.Insert(9);
    h.Insert(0);
    Hashtable<int,pair<int,int>,_KofKV<int,int> > h2;
    h2.Insert(pair<int,int>(1,1));
    h2.Insert(pair<int,int>(2,1));
    h2.Insert(pair<int,int>(3,1));
    h2.Insert(pair<int,int>(4,1));
    h2.Insert(pair<int,int>(5,1));
    h2.Insert(pair<int,int>(6,1));
    h2.Insert(pair<int,int>(7,1));
    h2.Insert(pair<int,int>(8,1));
    h2.Insert(pair<int,int>(9,1));
    h2.Insert(pair<int,int>(10,1));
    Hashtable<int,pair<int,int>,_KofKV<int,int> > h3(h2);
    return 0;   
}
