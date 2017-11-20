/*************************************************************************
	> File Name: shellsort.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 20 Nov 2017 02:05:36 PM PST
 ************************************************************************/

#include<iostream>
using namespace std;

struct Greater
{
    bool operator()(int x,int y)
    {
        return x>y;
    }
};

struct Less
{
    bool operator()(int x,int y)
    {
        return x<y;
    }
};

template<class Compare=Greater>
void shellsort(int* data,size_t size)
{
    Compare com;
    int end;
    int tmp;
    int gap=size;
    while(gap>1)
    {
        gap=gap/3+1;
        for(size_t index=0;index<size-gap;index++)
        {
            end=index;
            tmp=data[end+gap];
            while(com(data[end],tmp)&&end>=0)
            {
                data[end+gap]=data[end];
                end-=gap;
            }
            data[end+gap]=tmp;
        }
    }
}


int main()
{
    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 }; 
    shellsort(data,sizeof(data)/sizeof(data[0]));
    return 0;
}


