/*************************************************************************
	> File Name: partsort.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Tue 21 Nov 2017 10:27:20 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

template<class T>
struct Less;

template<class T>
struct Greater
{
    typedef Less<T> other;

    bool operator()(const T& x,const T& y)
    {
        return x>=y;
    }
};

template<class T>
struct Less 
{
    typedef Greater<T> other;

    bool operator()(const T& x,const T& y)
    {
        return x<=y;
    }
};

template<template<class>class Compare=Greater,class T=int>
void partsort(int* data,int begin,int end)
{
    if(begin>=end)
        return;

    Compare<T> compareself;
    typename Compare<T>::other compareverse;

    int left=begin;
    int right=end;
    int tmp=data[end];

    while(left<right)
    {
        while(left<right && compareself(data[left],tmp))
        {
            left++;
        }
        data[right]=data[left];

        while(left<right && compareverse(data[right],tmp))
        {
            right--;
        }
        data[left]=data[right];
    }
    data[left]=tmp;

    partsort<Compare,T>(data,begin,left-1);
    partsort<Compare,T>(data,left+1,end);
}

int main()
{
    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0  };
    partsort<Less>(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    partsort(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    return 0;
}

