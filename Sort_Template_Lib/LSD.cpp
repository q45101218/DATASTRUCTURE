/*************************************************************************
	> File Name: LSD.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Sat 25 Nov 2017 01:44:52 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void LSD(int* data,int size)
{
    int digits=1;
    int count=10;
    for(int i=0;i<size;i++)
    {
        if(data[i]>count)
        {
            count*=10;
            digits++;
        }
    }

    int j=0;
    int i;
    int flag=1;
    for(j;j<digits;j++)
    {
        vector<int> bucket;
        bucket.resize(10);
        vector<int> postion;
        postion.resize(10);
        for(i=0;i<size;i++)
        {
            int index=(data[i]/flag)%10;
            bucket[index]++;
        }

        for(i=1;i<10;i++)
        {
            postion[i]=postion[i-1]+bucket[i-1];
        }

        vector<int> space;
        space.resize(size);
        for(i=0;i<size;i++)
        {
            int index=(data[i]/flag)%10;
            space[postion[index]++]=data[i];
        }

        for(i=0;i<size;i++)
        {
            data[i]=space[i];  
        }

        flag*=10;
    }
}

int main()
{
    int data[]={20, 300, 40, 5, 80, 12, 500, 43, 23, 56, 121, 33, 444, 555, 666, 112, 456, 234, 123, 124};
    LSD(data,sizeof(data)/sizeof(data[0]));
    return 0;
}
