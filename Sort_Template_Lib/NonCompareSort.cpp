/*************************************************************************
	> File Name: NonCompareSort.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sat 25 Nov 2017 01:08:05 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void NonCompareSort(int* data,int size)
{
    int max=0;
    int min=0;
    int i;
    for(i=0;i<size;i++)
    {
        if(data[i]<min)
            min=data[i];
        if(data[i]>max)
            max=data[i];
    }

    int range=max-min+1;


    vector<int> newspace;
    newspace.resize(range);

    for(i=0;i<size;i++)
    {
        newspace[data[i]-min]++;
    }

    int j=0;
    for(i=0;i<range;i++)
    {
        while(newspace[i]--)
        {
            data[j]=min+i;
            j++;
        }
    }
}

int main()
{
    int data[]={20, 300, 40, 5, 80, 12, 500, 43, 23, 56, 121, 33, 444, 555, 666, 112, 456, 234, 123, 124};
    NonCompareSort(data,sizeof(data)/sizeof(data[0]));
    return 0;
}

