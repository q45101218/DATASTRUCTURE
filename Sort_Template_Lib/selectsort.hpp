/*************************************************************************
	> File Name: selectsort.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 20 Nov 2017 03:58:58 PM PST
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
void selectsort(int* data,size_t size)
{
    Compare com;
    int begin=0;
    int end=size-1;
    while(begin<end)
    {
        int min=begin;
        int max=end;
        for(int index=begin;index<=end;index++)
        {
            if(com(data[index],data[min]))
            {
                min=index;
            }
            if(com(data[max],data[index]))
            {
                max=index;
            }
        }
        swap(data[begin],data[min]);
        if(begin==max)
        {
            begin=min;
        }
        swap(data[end],data[max]);
        begin++;
        end--;
    }
}

//int main()
//{
//    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
//    selectsort<Less>(data,sizeof(data)/sizeof(data[0]));
//    return 0;
//}
