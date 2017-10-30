/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 25 Oct 2017 06:13:46 AM PDT
 ************************************************************************/

#include<iostream>
#include"list.hpp"

int main()
{
    List<int> ls;
    ls.Push_Back(1);
    ls.Push_Back(2);
    ls.Push_Back(3);
    ls.Push_Back(4);
    ls.Print();
    ls.Pop_Back();
    ls.Print();
    ls.Push_Front(2);
    ls.Print();
    ls.Pop_Front();
    ls.Print();
    //List<int> ls1(ls);
    List<int> ls2;
    ls2.Push_Back(1);
    //ls2.Push_Back(2);
    //ls2.Push_Back(3);
    //ls2.Push_Back(4);
    //ls2.Push_Back(5);
    //ls2.Push_Back(6);
    //ls2.Push_Back(7);
    //ls2.Push_Back(8);
    //ls2.Print();
    //ls=ls2;
    //ls.Print();
    return 0;
}
