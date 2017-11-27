/*************************************************************************
	> File Name: graph_Adjacency_List.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 27 Nov 2017 10:32:58 AM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<map>
using namespace std;

template<class V,class W>
struct GraphNode
{
    GraphNode<V,W>* _next;
    V _name;
    W _weight;

    GraphNode(const V& name,const W& weight)
    :_name(name)
    ,_weight(weight)
    {}
};

template<class V,class W>
class Graph
{
    typedef GraphNode<V,W> node;
public:
    Graph()
    {}

    
private:
    vector<V> _index;
    vector<node*> _adjacentlist;
    map<V,size_t> _findindex;
};

