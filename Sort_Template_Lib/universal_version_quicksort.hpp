/*************************************************************************
	> File Name: universal_version_quicksort.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Tue 21 Nov 2017 01:21:53 PM CST
 ************************************************************************/
#pragma once
#include<iostream>
using namespace std;


struct Less;

struct Greater
{
    typedef Less other;
    bool operator()(int x,int y)
    {
        return x>=y;
    }

};

struct Less
{
    typedef Greater other;
    bool operator()(int x,int y)
    {
        return x<=y;
    }
};

template<class Compare=Greater>
void quicksort(int* data,int begin,int end)
{
    if(begin>=end)
        return;
    int left=begin;
    int right=end;
    Compare com;
    typename Compare::other com1;

    while(right>left)
    {
        while(right>left && com(data[end],data[left]))
        {
            left++;
        }
        while(right>left && com1(data[end],data[right]))
        {
            right--;
        }
        if(right!=left)
            swap(data[left],data[right]);
    }
    swap(data[end],data[left]);
    quicksort<Compare>(data,begin,left-1);
    quicksort<Compare>(data,left+1,end);
}

//void print(int* data,size_t size)
//{
//    for(int index=0;index<size;index++)
//        cout<<data[index]<<" ";
//    cout<<endl;
//}
//
//int main()
//{
//    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
//    quicksort(data,0,sizeof(data)/sizeof(data[0])-1);
//    print(data,sizeof(data)/sizeof(data[0]));
//    quicksort<Less>(data,0,sizeof(data)/sizeof(data[0])-1);
//    print(data,sizeof(data)/sizeof(data[0]));
//    return 0;
//}
