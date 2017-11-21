/*************************************************************************
	> File Name: quicksort.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 20 Nov 2017 04:49:32 PM PST
 ************************************************************************/

#include<iostream>
using namespace std;

int _quicksort(int* data,int begin,int end)
{
    int left=begin;
    int right=end;
    while(right>left)
    {
        while(right>left&&data[right]<=data[begin])
        {
            right--;
        }
        while(left<right&&data[left]>=data[begin])
        {
            left++;
        }
        if(left!=right)
            swap(data[left],data[right]);
    }
    swap(data[left],data[begin]);
    return left;
}

void quicksort(int* data,int begin,int end)
{
    if(begin>=end)
        return;

    int div=_quicksort(data,begin,end);
    quicksort(data,begin,div-1);
    quicksort(data,div+1,end);
}

int main()
{
    int data[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
    quicksort(data,0,sizeof(data)/sizeof(data[0])-1);
    return 0;
}
