/*************************************************************************
	> File Name: ptrsort.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Wed 22 Nov 2017 09:13:18 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

template<class T>
struct Greater
{
    bool operator()(const T& x,const T& y)
    {
        return x>=y;
    }
};

template<class T>
struct Less 
{
    bool operator()(const T& x,const T& y)
    {
        return x<=y;
    }
};

template<template<class>class Compare=Greater,class T=int>
void ptrsort(int* data,int begin,int end)
{
    if(begin>=end)
        return;

    Compare<T> com;
    int slow=begin-1;
    int fast=begin;

    while(fast<end)
    {
        if(com(data[end],data[fast]))
        {
            swap(data[++slow],data[fast]);
        }
        fast++;
    }
    swap(data[end],data[++slow]);

    ptrsort<Compare,T>(data,begin,slow-1);
    ptrsort<Compare,T>(data,slow+1,end);

}

int main()
{
    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0  };
    ptrsort<Less,int>(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    ptrsort(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    return 0;
}
