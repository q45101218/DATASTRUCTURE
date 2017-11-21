/*************************************************************************
	> File Name: insertsort.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 20 Nov 2017 01:14:05 PM PST
 ************************************************************************/
#pragma once
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
void insertsort(int* data,size_t size)
{
    Compare com;
    int end;
    int tmp;
    for(size_t index=0;index<size-1;index++)
    {
        end=index;
        tmp=data[end+1];
        while(end>=0&&com(tmp,data[end]))
        {
            data[end+1]=data[end];
            end--;
        }
        data[end+1]=tmp;
    }
}


//int main()
//{
//    int data[]={2,5,4,9,3,6,8,7,1,0};
//    insertsort<Less>(data,sizeof(data)/sizeof(data[0]));
//    return 0;
//}
