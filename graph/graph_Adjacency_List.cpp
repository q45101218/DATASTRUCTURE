/*************************************************************************
	> File Name: graph_Adjacency_List.cpp
	> Author:Yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 27 Nov 2017 10:32:58 AM CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
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

template<class V,class W,bool undigraph=true>
class Graph
{
    typedef GraphNode<V,W> node;
public:
    Graph(const V* name,size_t size)
    {
        _index.resize(size);
        _adjacentlist.resize(size);
        for(size_t index=0;index<size;index++)
        {
            _index[index]=name[index];
            _findindex.insert(make_pair(name[index],index));
        }
    }

    void add(const V& src,const V& des,const W& weight)
    {
        size_t sindex=findindex(src);
        _add(sindex,des,weight);
        if(undigraph)
        {
            size_t dindex=findindex(des);
            _add(dindex,des,weight);
        }
    }

    void breath_first(const V& name)
    {
        findindex(name);
        queue<V> q;
        set<V> familiar;
        q.push(name);
        while(!q.empty())
        {
            V n=q.front();
            q.pop();
            if(familiar.end()==familiar.find(n))
            {
                cout<<n<<" ";
                size_t index=findindex(n);
                node* cur=_adjacentlist[index];
                while(cur)
                {
                    q.push(cur->_name);
                    cur=cur->_next;
                }
            }

            familiar.insert(n);
        }
        cout<<endl;
    }

    void depth_first(const V& name)
    {
        set<V> familiar;
        _depth_first(name,familiar);
    }



    void _depth_first(const V& name,set<V>& familiar)
    {
        if(familiar.end()!=familiar.find(name))
            return;
        size_t index=findindex(name);
        node* tmp=_adjacentlist[index];
        cout<<name<<" ";
        familiar.insert(name);
        while(tmp)
        {
            _depth_first(tmp->_name,familiar);
            tmp=tmp->_next;
        }
    }

    size_t findindex(const V& name)
    {
        typename map<V,size_t>::iterator it=_findindex.find(name);
        if(it==_findindex.end())
        {
            perror("invaild parameter");
        }
        else
        {
            return it->second;
        }
    }

    node* _add(size_t index,const V& des,const W& weight)
    {
        node* tmp=_adjacentlist[index];
        while(tmp)
        {
            if(tmp->_name==des)
                return tmp;
            tmp=tmp->_next;
        }
        tmp=creat(index,des,weight);
    }

    node* creat(const size_t index,const V& des,const W& weight)
    {
        node* tmp=new node(des,weight);
        tmp->_next=_adjacentlist[index];
        _adjacentlist[index]=tmp;
        return tmp;
    }

    ~Graph()
    {
        for(size_t index=0;index<_adjacentlist.size();index++)
        {
            node* del=_adjacentlist[index];
            node* tmp;
            while(del)
            {
                tmp=del->_next;
                delete del;
                del=tmp;
            }
        }
    }
    
private:
    vector<V> _index;
    vector<node*> _adjacentlist;
    map<V,size_t> _findindex;
};

int main()
{
    string name[]={"a","b","c","d"};
    Graph<string,int> g(name,sizeof(name)/sizeof(name[0]));
    g.add("a","b",100);
    g.add("a","c",200);
    g.add("d","a",300);
    g.add("c","d",400);
    g.add("b","d",599);
    g.breath_first("a");

    
    Graph<string,int,false> g1(name,sizeof(name)/sizeof(name[0]));
    g1.add("a","b",100);
    g1.add("a","c",200);
    g1.add("b","c",300);
    g1.add("c","d",400);
    return 0;
}
