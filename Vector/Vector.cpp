/*************************************************************************
	> File Name: Vector.cpp
	> Author: Yangkun
	> Mail: yangkungetit@163.com
	> Created Time: Sat 28 Oct 2017 03:07:21 AM PDT
 ************************************************************************/

#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;

struct __FalseType{};
struct __TrueType{};

template<class T>
struct TypeTraits
{
    typedef __FalseType Type;
};

template<>
struct TypeTraits<int>
{
    typedef __TrueType Type;
};

template<>
struct TypeTraits<char>
{
    typedef __TrueType Type;
};

template<>
struct TypeTraits<double>
{
    typedef __TrueType Type;
};

template<>
struct TypeTraits<size_t>
{
    typedef __TrueType Type;
};

template<class T>
T* __Copy(T* des,T* src,size_t size,__FalseType)
{
    for(size_t index=0;index<size;index++)
    {
        des[index]=src[index];
    }
    return des;
}

template<class T>
T* __Copy(T* des,T* src,size_t size,__TrueType)
{
    return (T*)memcpy(des,src,size*(sizeof(T)));
}

template<class T>
T* Copy(T* des,T* src,size_t size)
{
    return __Copy<T>(des,src,size,typename TypeTraits<T>::Type());
}

template<class T>
class Vector
{
public:
    typedef T* Iterator;

    Vector()
    :_a(NULL)
    ,_size(0)
    ,_capacity(0)
    {}

    Vector(const Vector<T>& v)
    :_capacity(v._capacity)
    ,_size(0)
    ,_a(new T[_capacity])
    {
        int index=0;
        for(index;index<v._size;index++)
        {
            Push_Back(v._a[index]);
        }
    }

    ~Vector()
    {
        if(_a!=NULL)
        {
            delete[] _a;
            _size=0;
            _capacity=0;
        }
    
    }

    Vector<T>& operator=(Vector<T> v)
    {
        swap(_a,v._a);
        swap(_size,v._size);
        swap(_capacity,v._capacity);
        return *this;
    }
    /*
    Vector<T>& operator=(Vector<T>& v)
    {
        if(this!=&v)
        {
            release();
            _a=new T[_capacity];
            _size=v._size;
            _capacity=v._capacity;
            size_t index;
            for(index;index<_size;index++)
            {
                Push_Back(v._a[index]);
            }
        }
    }
    */

    T& operator[](size_t pos)
    {
        assert(pos<_size);
        return _a[pos];
    }

    void checkcapcity()
    {
        if(_size==_capacity)
        {
            _capacity=_capacity*2+1;
            T* tmp=new T[_capacity];
            if(_a!=NULL)
            {
                Copy(tmp,_a,_size);
                delete[] _a;
            }
            _a=tmp;
        }
    }

    void release()
    {
        if(_a!=NULL)
        {
            delete[] _a;
            _size=0;
            _capacity=0;
        }
    }

    void Push_Back(const T& data)
    {
        checkcapcity();
        _a[_size]=data;
        _size++;
    }

    void Pop_Back()
    {
        _size--;
    }

    size_t Find(const T& data)
    {
        size_t index=0;
        while(index!=_size)
        {
            if(_a[index]==data)
            {
               return index;
            }
            index++;
        }
        return -1;
    }
    

    bool Insert(size_t pos,const T data)
    {
        if(pos<1||pos>_size)
            return false;
        checkcapcity();
        size_t index;
        for(index=_size;index>pos-1;index--)
        {
            _a[index]=_a[index-1];
        }
        _size++;
        _a[pos-1]=data;
        return true;
    }

    bool Erase(size_t pos)
    {
        if(pos>_size||pos<1)
            return false;
        size_t index;
        for(index=pos-1;_size-1>index;index++)
        {
            _a[index]=_a[index+1];
        }
        _size--;
        return true;
    }

    void Reverse()
    {
        size_t index;
        size_t length=_size-1;
        for(index=0;index<_size>>1;index++)
        {
            swap(_a[index],_a[length]);
            length--;
        }
    }
    

    //void Print()
    //{
    //    assert(_size>0);
    //    size_t index;
    //    for(index=0;index<_size;index++)
    //    {
    //        cout<<_a[index]<<" ";
    //    }
    //    cout<<endl;
    //}
private:
    T* _a;
    size_t _size;
    size_t _capacity;
};


int main()
{
    Vector<int> v;
    v.Push_Back(1);
    v.Push_Back(2);
    v.Push_Back(3);
    v.Push_Back(4);
    v.Push_Back(5);
    v.Push_Back(6);
    v.Print();
    Vector<int> v2;
    v2.Push_Back(1);
    v2.Push_Back(2);
    v2.Push_Back(3);
    v2.Print();
    v2=v;
    v2.Print();
    Vector<int> v3(v);
    v3.Insert(3,6);
    v3.Print();
    v3.Erase(3);
    v3.Print();
    v3.Reverse();
    v3.Print();
    cout<<v[5]<<endl;
    return 0;
}
