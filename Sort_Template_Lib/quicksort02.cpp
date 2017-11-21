/*************************************************************************
	> File Name: quicksort02.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Tue 21 Nov 2017 12:12:38 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


int _quicksort(int* data,int begin,int end)
{
    int left=begin;
    int right=end;
    int tmp=data[end];
    while(left<right)
    {
        while(right>left&&tmp>=data[left])
        {
            left++;
        }
        while(right>left&&tmp<=data[right])
        {
            right--;
        }
        if(left!=right)
            swap(data[left],data[right]);
    }
//   data[end]=data[left];
//   data[left]=tmp;
    swap(data[end],data[left]);
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
