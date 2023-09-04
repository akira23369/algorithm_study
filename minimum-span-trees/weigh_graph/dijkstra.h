#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "edge.h"
#include "heap.h"
#include "index_heap.h"

template<typename Graph, typename Weight>
class djkstra
{
    Graph &G;
    int s;
    Weight* dist;   // 存放源点到各个点的最短距离
    bool* state;    // 表示已经找到最短路的点
    std::vector<edge<Weight>*> from;    // 存放路径
public: 
    djkstra(Graph &t, int ss) :G(t), s(ss)
    {
        dist = new Weight[t.v()];
        state = new bool[t.v()];
        for (int i = 0; i < t.v(); i++)
        {
            dist[i] = Weight();     // 这个是模板的默认构造函数
            state[i] = false;
            from.push_back(nullptr);
        }
        index_heap<Weight> ipq(G.v());
        
        dist[s] = Weight();
        state[s] = true;
        ipq.insert(s, -dist[s]);
        while (!ipq.is_empty())
        {
            int v = ipq.extract_index();
            state[v] = true;
            typename Graph::adj_iterator adj(G, v);
            for (edge<Weight>* it = adj.begin(); !adj.end(); it = adj.next())
            {
                int otr = it->other(v);
                if (state[otr]) continue;
                if (dist[otr] > dist[v] + it->wt()) 
                {
                    dist[otr] = dist[v] + it->wt();
                    from[otr] = it;
                    if (ipq.contain(otr)) ipq.change(otr, -dist[otr]);
                    else ipq.insert(otr, -dist[otr]);
                }
            }
        }
    }
    Weight dist_at(int v) { return dist[v]; }
    bool has_path_to(int v) { return state[v]; }
    void path(int v, std::vector<edge<Weight>> &vec)
    {
        std::stack<edge<Weight>*> s;
        edge<Weight>* t = from[v];
        while (t != nullptr)
        {
            s.push(t);
            t = from[t->v()];
        }
        while (!s.empty())
        {
            t = s.top();
            vec.push_back(*t);
            s.pop();
        }
    }
    void show_path(int v)
    {
        assert(v >= 0 && v < G.v());
        std::vector<edge<Weight>> vec;
        path(v, vec);
        for (int i = 0; i < vec.size(); i++)
        {
            std::cout << vec[i].v() << "->";
            if (i == vec.size() - 1) std::cout << vec[i].w() << "\n";
        }
    }
    ~djkstra() 
    {
        delete[] dist;
        delete[] state;
    }
};