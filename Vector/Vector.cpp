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

    Vector& operator=(Vector v)
    {}

    T& operator[]()
    {}

    void Push_Back(const T& data)
    {}

    void Pop_Back()
    {}

    size_t Find(const T& data)
    {}

    bool Insert(size_t pos)
    {}

    bool Erase(size_t pos)
    {}

private:
    T* _a;
    size_t _size;
    size_t _capacity;
}

