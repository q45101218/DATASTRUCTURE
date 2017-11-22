/*************************************************************************
	> File Name: ptrsort.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Wed 22 Nov 2017 09:13:18 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

struct Greater
{
    bool operator()(int x,int y)
    {
        return x>=y;
    }
};

struct Less 
{
    bool operator()(int x,int y)
    {
        return x<=y;
    }
};

template<class Compare>
void ptrsort(int* data,int begin,int end)
{
    Compare com;
    int slow=begin-1;
    int fast=begin;

    while()
    {
        while(fast=<end && com(data[fast],))
        {
            fast++;
        }
        while()
        {
            slow++;
        }
        swap(data[fast],data[slow]);
    }

}

int main()
{
    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0  };
    ptrsort<Less>(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    ptrsort(data, 0, sizeof(data) / sizeof(data[0]) - 1);
    return 0;
}
