/*************************************************************************
	> File Name: groph.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 27 Nov 2017 10:01:58 AM CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<string>
using namespace std;

template<class V,class W,bool undigraph=true>
class Graph
{
public:
    Graph(const V* name,size_t size)
    {
        _index.resize(size);
        _graph.resize(size);
        for(size_t i=0;i<size;i++)
        {
            _graph[i].resize(size);
            _index[i]=name[i];
            _findindex.insert(make_pair(name[i],i));
        }
    }

    void add(const V& src,const V& des,const W& weight)
    {
        size_t sindex=find(src);
        size_t dindex=find(des);

        _graph[sindex][dindex]=weight;
        if(undigraph)
            _graph[dindex][sindex]=weight;
    }

    size_t find(const V& name)
    {
        typename map<V,size_t>::iterator it=_findindex.find(name);
        if(_findindex.end()==it)
            perror("invaild parameter");
        else
        {
            return it->second;
        }
    }
private:
    vector<vector<W> > _graph;
    map<V,size_t> _findindex;
    vector<V> _index;
};

int main()
{
    string name[]={"a","b","c","d"};
    Graph<string,int> g(name,sizeof(name)/sizeof(name[0]));
    g.add("a","b",100);
    g.add("a","c",200);
    g.add("b","c",300);
    g.add("c","d",400);

    
    Graph<string,int,false> g1(name,sizeof(name)/sizeof(name[0]));
    g1.add("a","b",100);
    g1.add("a","c",200);
    g1.add("b","c",300);
    g1.add("c","d",400);
    return 0;
}
