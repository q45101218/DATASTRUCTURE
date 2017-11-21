/*************************************************************************
	> File Name: bubblesort.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Tue 21 Nov 2017 02:16:34 PM CST
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
void bubblesort(int* data,int size)
{
    Compare com;

    for(int i=0;i<size-2;i++)
    {
        for(int j=0;j<size-i-2;j++)
        {
            if(com(data[j],data[j+1]))
                swap(data[j],data[j+1]);
        }
    }
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
//    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0  };
//    bubblesort<Less>(data,sizeof(data)/sizeof(data[0]));
//    print(data,sizeof(data)/sizeof(data[0]));
//    bubblesort(data,sizeof(data)/sizeof(data[0]));
//    print(data,sizeof(data)/sizeof(data[0]));
//
//    return 0;
//
//}
