/*************************************************************************
	> File Name: Hashtablelink.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 05 Nov 2017 11:01:34 PM PST
 ************************************************************************/
nclude<iostream>
#include<vector>
using namespace std;

template<class K, class ValueType, class KofValueType, class __HashFun>
class Hashtable;

template<class ValueType>
struct Hashnode
{
    ValueType _value;
    Hashnode<ValueType>* _next;

    Hashnode(const ValueType& v)
        :_value(v)
        , _next(NULL)
    {}
};


template<class ValueType, class Ref,class Ptr, class K, class KofValueType, class __HashFun>
struct Iterator
{
    typedef Iterator<ValueType, Ref, Ptr, K, KofValueType, __HashFun> Self;
    typedef Hashtable<K, ValueType, KofValueType, __HashFun> Hashtable;
    typedef Hashnode<ValueType> node;


    Iterator(node* ptr=NULL, Hashtable* h=NULL)
        :_ptr(ptr)
        ,_ht(h)
    {}

    Iterator(const Iterator& it)
        :_ptr(it._ptr)
        , _ht(it._ht)
    {}

    Iterator& operator=(const Iterator it)
    {
        _ptr = it._ptr;
        _ht = it._ht;
        return *this;
    }

    Ref operator*()
    {
        return _ptr->_value;
    }

    Ptr operator->()
    {
        return &(_ptr->_value);
    }

    bool operator!=(const Iterator& it)
    {
        return it._ptr != _ptr;
    }

    bool operator==(const Iterator& it)
    {
        return it._ptr == _ptr;
    }

    Self& operator++()
    {}

    Self operator++(int)
    {}

    Self& operator--()
    {}

    Self operator--(int)
    {}

    node* _ptr;
    Hashtable* _ht;

private:
    Self& Increase()
    {
        if (_ptr->_next)
        {
            _ptr = _ptr->_next;
        }
        else
        {
            KofValueType _KofValueType;
            size_t index = _ht->Hashfun(_KofValueType(_ptr->_value), _ht->_table.size());
        }
    }
};


template<class K>
struct HashFun
{
    size_t operator()(K key)
    {
        return key;
    }
};

template<class K>
struct _KofK
{
    K operator()(K key)
    {
        return key;
    }
};

template<class K, class ValueType>
struct _KofKV
{
    K operator()(ValueType v/*const pair<K, V>& v*/)
    {
        return v.first;
    }
};

template<class K, class ValueType, class KofValueType, class __HashFun = HashFun<K> >
class Hashtable
{
    typedef Hashnode<ValueType> node;
    typedef Hashtable<K,ValueType, KofValueType, __HashFun> _Hashtable;
    typedef Iterator<ValueType, ValueType&, ValueType*, K, KofValueType, __HashFun> Iterator;

public:
    Hashtable()
        :_size(0)
    {}

    Hashtable(const _Hashtable& h)
        :_size(0)
    {
        _table.resize(h._table.size());
        for (size_t index = 0; index < h._table.size(); index++)
        {
            node* tmp = h._table[index];
            while (tmp)
            {
                Insert(tmp->_key, tmp->_value);
            }
        }
    }

    _Hashtable& operator=(_Hashtable h)
    {
        swap(_size, h._size);
        swap(_table, h._table);
        return *this;
    }

    ~Hashtable()
    {
        for (size_t index=0; index < _table.size(); index++)
        {
            node* del = _table[index];
            node* tmp = _table[index];
            while (del)
            {
                tmp = del->_next;
                delete del;
                del = tmp;
            }
        }
    }
    
    size_t Hashfun(const K& k, size_t size)
    {
        __HashFun _hashfun;
        return _hashfun(k)%size;
    }

    bool Insert(const ValueType& value)
    {
        CheckLoadFactory();
        KofValueType _KofValueType;

        size_t index = Hashfun(_KofValueType(value), _table.size());

        //if (!Find(_KofValueType(value)))
        //  return false;
        if (_table[index] == NULL)
        {
            _table[index] = new node(value);
        }
        else
        {
            node* tmp = new node(value);
            tmp->_next = _table[index];
            _table[index] = tmp;
        }
        _size++;
        return true;
    }

    bool Find(const K& key)
    {
        size_t index = Hashfun(key, _table.size());
        KofValueType _KofValueType;
        if (_table[index] == NULL)
            return false;
        else
        {
            node* cur = _table[index];
            while (cur != NULL)
            {
                if (_KofValueType(cur->_value) == key)
                    return true;
                cur = cur->_next;
            }
            return false;
        }
    }

    bool Erase(const K& key)
    {
        size_t index = Hashfun(ValueType, _table.size());

        assert(_table[index]);
        node* cur = _table[index];
        node* pre = _table[index];
        while (key != = cur->key)
        {
            prv = cur;
            cur = cur->_next;
        }
        prv->_next = cur->_next;
        delete cur;
        _size--;
        return true;
    }

    void CheckLoadFactory()
    {
        if (_size == 0 || _size*10 / _table.size()>10)
        {
            _size == 0 ? _table.resize(7) : Reallocate();
        }
    }

    void Reallocate()
    {
        vector<node*> newtable;
        newtable.resize(GetNextPrime(_table.size()));
 
        KofValueType _KofValueType;
        size_t i = 0;
        for (size_t index = 0; index<_table.size(); index++)
        {
            if (_table[index] != NULL)
            {
                node* next = _table[index];
                node* tmp = _table[index];
                _table[index] = NULL;
                while (tmp)
                {
                    i = Hashfun(_KofValueType(tmp->_value), newtable.size());
                    next = tmp->_next;
                    if (newtable[i] == NULL)
                    {
                        newtable[i] = tmp;
                    }
                    else
                    {
                        node* cur = newtable[i]->_next;
                        newtable[i] = tmp;
                        tmp->_next = cur;
                    }
                    tmp = next;
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

private:
    vector<node*> _table;
    size_t _size;
};

int main()
{
    Hashtable<int, pair<int,int>,_KofKV<int,int>> h;
    h.Insert(make_pair(2,2));
    /*h.Insert(9, 2);
    h.Insert(16, 2);
    h.Insert(23, 2);
    h.Insert(30, 2);
    h.Insert(37, 2);
    h.Insert(44, 2);
    h.Insert(51, 2);
    h.Insert(58, 2);
    h.Insert(65, 2);
*/
    //h.Insert(9,9);
    //h.Insert(1,1);
    //h.Insert(3,3);
    //h.Insert(16,16);
    //h.Insert(19,19);
    //h.Insert(59,59);
    //h.Insert(99,99);




    //h.Insert(88,88);
    return 0;
}
