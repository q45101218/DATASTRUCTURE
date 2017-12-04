/*************************************************************************
	> File Name: vec_iter.cpp
	> Author:yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 04 Dec 2017 02:40:10 PM CST
 ************************************************************************/

#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
class Vector
{
public:
    typedef T* Iterator;
    Vector()
    :start(NULL)
    ,finish(NULL)
    ,endofstor(NULL)
    {}
    
    ~Vector()
    {
        Release();
        start=NULL;
        finish=NULL;
        endofstor=NULL;
    }

    void PushBack(const T& data)
    {
        CheckAllocate();
        *finish=data;
        finish++;
    }

    void PushFront(const T& data)
    {
        Insert(start,data);
    }

    Iterator Insert(Iterator it,const T& data)
    {
        Iterator po=Find(it);
        CheckAllocate();
        int end=finish-start-1;
        int time=finish-po;
        while(time--)
        {
            start[end+1]=start[end];
            end--;
        }
        *po=data;
        finish++;
        return po;
    }

    Iterator Find(Iterator& it)
    {
        Iterator tmp=it;
        Iterator pre=it;
        for(int index=0;index<(finish-start);index++)
        {
            if(tmp==start+index)
            {
                return tmp;
            }
            pre=tmp;
            tmp=tmp++;
        }
        return NULL;
    }

    Iterator Begin()
    {
        return start;
    }

    Iterator End()
    {
        return finish;
    }

    T& operator[](size_t pos)
    {
        assert(pos>0||pos<Size());
        return start[pos];
    }

    void CheckAllocate()
    {
        if(finish==(endofstor-1)||start==NULL)
        {
            size_t have=finish-start;
            size_t newspace=2*(endofstor-start)+3;
            Iterator tmp=new T[newspace];
            for(int index=0;index<(finish-start);index++)
            {
                tmp[index]=start[index];
            }
            
            Release();

            start=tmp;
            endofstor=start+newspace;
            finish=start+have;
        }
    }

    void Release()
    {
        if(start)
        {
            delete[] start;
        }
    }

    size_t Size()
    {
        return finish-endofstor;
    }

private:
    Iterator start;
    Iterator finish;
    Iterator endofstor;
};

int main()
{
    Vector<int> v;
    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);
    v.PushBack(4);
    v.PushBack(5);
    Vector<int>::Iterator it = v.Begin();
    while (it != v.End())
    {
        cout << *it++ << "  ";
    }
    return 0;
}
