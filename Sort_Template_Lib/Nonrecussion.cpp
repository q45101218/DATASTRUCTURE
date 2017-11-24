/*************************************************************************
	> File Name: Nonrecussion.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Thu 23 Nov 2017 02:25:41 PM CST
 ************************************************************************/

#include<iostream>
#include<stack>
#include<assert.h>
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


template<template<class>class Compare=Greater>
void Nonrecussion(int* data,int begin,int end)
{
    assert(begin<end);
    Compare com;
    stack<int> s;
    s.push(end);
    s.push(begin);

    while(!s.empty())
    {
        begin=s.top();
        s.pop();
        end=s.top();
        s.pop();

        int fast=begin;
        int slow=begin-1;
        while(fast<end)
        {
            if(com(data[fast],data[end]))
            {
                swap(data[++slow],data[fast]);
            }
            fast++;
        }
        swap(data[end],data[++slow]);
        if(begin<slow-1)
        {
            s.push(slow-1);
            s.push(begin);
        }

        if(end>slow+1)
        {
            s.push(end);
            s.push(slow+1);
        }
    }
}

int main()
{
    int data[] = { 2, 5, 4, 9,5, 3, 6, 8, 7,5, 1, 0  };
    Nonrecussion(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    return 0;
}
