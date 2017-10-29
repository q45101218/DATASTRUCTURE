/*************************************************************************
	> File Name: Vector.cpp
	> Author: Yangkun
	> Mail: yangkungetit@163.com
	> Created Time: Sat 28 Oct 2017 03:07:21 AM PDT
 ************************************************************************/

#include<iostream>
#include<assert.h>
using namespace std;


template<class T>
class Vector
{
public:
    Vector()
    :_a(NULL)
    ,_size(0)
    ,_capacity(0)
    {}

    Vector(const Vector<T>& v)
    {}

    ~Vector()
    {}

    Vector<T>& operator=(Vector<T> v)
    {
        return *this;
    }

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
                size_t i;
                for(i=0;i<_size;i++)
                {
                    tmp[i]=_a[i];
                }
                delete[] _a;
            }
            _a=tmp;
        }
    }

    void release()
    {}

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
        return 1;
    }

    bool Insert(size_t pos)
    {
        return false;
    }

    bool Erase(size_t pos)
    {
        return false;
    }

    void Print()
    {
        assert(_size>0);
        size_t index;
        for(index=0;index<_size;index++)
        {
            cout<<_a[index]<<endl;
        }
        cout<<endl;
    }
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

    cout<<v[5]<<endl;
    v.Print();
    return 0;
}
