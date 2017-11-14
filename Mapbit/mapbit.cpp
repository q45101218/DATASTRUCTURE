/*************************************************************************
	> File Name: mapbit.cpp
	> Author:YangKun 
	> Mail:yangkungetit@163.com 
	> Created Time: Tue 14 Nov 2017 08:16:30 AM PST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

template<class T=char>
class mapbit
{
public:
    mapbit(size_t data)
    :range(sizeof(range)<<3)
    {
        _mapbit.resize(data/range+1);
    }

    void set(size_t data)
    {
        size_t pos=data/range;
        size_t num=data%range;
        _mapbit[pos] |=1<<num;
    }

    void reset(size_t data)
    {
        size_t pos=data/range;
        size_t num=data%range;
        _mapbit[pos] &=~(1<<num);
    }

    bool test(size_t data)
    {
        size_t pos=data/range;
        size_t num=data%range;
        return(_mapbit[pos]>>num)&1;
    }

private:
    vector<T> _mapbit;
    T range;
};

int main()
{
    mapbit<> m1(100);
    m1.set(1);
    m1.set(8);
    m1.set(9);
    m1.test(1);
    cout<<m1.test(8)<<endl;

    return 0;
}
