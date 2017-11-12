/*************************************************************************
	> File Name: Hashtablelink.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sun 12 Nov 2017 06:11:02 AM PST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<assert.h>
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

    Iterator(const Self& it)
        :_ptr(it._ptr)
        , _ht(it._ht)
    {}

    Iterator& operator=(const Self it)
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

    bool operator!=(const Self& it)
    {
        return it._ptr != _ptr;
    }

    bool operator==(const Self& it)
    {
        return it._ptr == _ptr;
    }

    Self& operator++()
    {
        Increase();
        return *this;
    }

    Self operator++(int)
    {
        Self it(*this);
        Increase();
        return it;
    }

    Self& operator--()
    {
        Decrease();
        return *this;
    }

    Self operator--(int)
    {
        Self it(*this);
        Decrease();
        return it;
    }

    node* _ptr;
    Hashtable* _ht;

private:
    void Increase()
    {
        if (_ptr->_next)
        {
            _ptr = _ptr->_next;
        }
        else
        {
            KofValueType _KofValueType;
            size_t index = _ht->Hashfun(_KofValueType(_ptr->_value), _ht->_table.size())+1;
            for (index; index < _ht->_table.size();index++)
            {
                if (_ht->_table[index] != NULL)
                {
                    _ptr = _ht->_table[index];
                    return;
                }
            }
            _ptr = NULL;
        }
    }

    void Decrease()
    {
        KofValueType _KofValueType;
        size_t index = _ht->Hashfun(_KofValueType(_ptr->_value), _ht->_table.size());
        if (_ht->_table[index] != _ptr)
        {
            node* cur = _ht->_table[index];
            while (cur)
            {
                if (cur->_next == _ptr)
                {
                    _ptr = cur;
                    return;
                }
                cur = cur->_next;
            }
        }
        else
        {
            for (index - 1; index >= 0; index--)
            {
                if (_ht->_table[index] != NULL)
                {
                    node* cur = _ht->_table[index];
                    while (cur)
                    {
                        if (cur->_next == NULL)
                        {
                            _ptr = cur;
                            return;
                        }
                        cur = cur->_next;
                    }
                }
            }
        }
        _ptr = NULL;
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

template<class K,class ValueType>
struct _KofK
{
    K operator()(K key)
    {
        return key;
    }
};

template<class K, class V>
struct _KofKV
{
    K operator()(const pair<K, V>& v)
    {
        return v.first;
    }
};


template<class K, class ValueType, class KofValueType, class __HashFun = HashFun<K> >
class Hashtable
{
    friend struct Iterator<ValueType, ValueType&, ValueType*, K, KofValueType, __HashFun>;

    typedef Hashnode<ValueType> node;
    typedef Hashtable<K,ValueType, KofValueType, __HashFun> _Hashtable;

public:
    typedef typename Iterator<ValueType, ValueType&, ValueType*, K, KofValueType, __HashFun> Iterator;

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
            _table[index] = NULL;
        }
    }
    
    Iterator Begin()
    {
        node* cur = NULL;
        for (size_t index = 0; index < _table.size(); index++)
        {
            if (_table[index])
            {
                cur = _table[index];
                return Iterator(cur, this);
            }
        }
    }

    Iterator End()
    {
        return Iterator(NULL, this);
    }

    size_t Hashfun(const K& k, size_t size)
    {
        __HashFun _hashfun;
        return _hashfun(k)%size;
    }

    pair<Iterator,bool> Insert(const ValueType& value)
    {
        CheckLoadFactory();
        KofValueType _KofValueType;

        size_t index = Hashfun(_KofValueType(value), _table.size());
        Iterator it = Find(_KofValueType(value));
        if (it!=NULL)
            return make_pair(it,false);
        else
        {
            node* tmp = new node(value);
            tmp->_next = _table[index];
            _table[index] = tmp;
            _size++;
            return make_pair(Iterator(tmp,this),true);
        }
    }

    Iterator Find(const K& key)
    {
        size_t index = Hashfun(key, _table.size());
        KofValueType _KofValueType;
        if (_table[index] == NULL)
            return End();
        else
        {
            node* cur = _table[index];
            while (cur != NULL)
            {
                if (_KofValueType(cur->_value) == key)
                    return Iterator(cur, this);
                cur = cur->_next;
            }
            return End();
        }
    }

    bool Erase(const K& key)
    {
        size_t index = Hashfun(key, _table.size());

        assert(_table[index]);
        node* cur = _table[index];
        node* prv = _table[index];
        while (key != cur->key)
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
    Hashtable<int,pair<int,int>,_KofKV<int,int> > h;
    h.Insert(make_pair(1, 2));
    h.Insert(make_pair(2, 2));
    h.Insert(make_pair(3, 2));
    h.Insert(make_pair(4, 2));
    h.Insert(make_pair(5, 2));
    h.Insert(make_pair(6, 2));
    Hashtable<int, pair<int, int>, _KofKV<int, int> >::Iterator it = h.Begin();
    while (it != h.End())
    {
        cout << (*it).second << " ";
        it++;
    }
    cout << endl;
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
