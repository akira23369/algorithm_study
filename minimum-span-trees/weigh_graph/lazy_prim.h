#pragma once

#include <iostream>
#include "heap.h"
#include "edge.h"
#include <vector>
template<typename Graph, typename Weight>
class lazy_prim
{
    Graph &G;
    heap<edge<Weight>> pq;
    bool* is_in;    // 标记是否在最小生成树内
    std::vector<edge<Weight>> mst;
    Weight mst_weight;
    void visit(int v)
    {
        assert(!is_in[v]);
        is_in[v] = true;
        typename Graph::adj_iterator adj(G, v);
        for (edge<Weight>* it = adj.begin(); !adj.end(); it = adj.next())
        {
            if (!is_in[it->other(v)])
            {
                pq.insert(*it);
            }
        }
    }
public:
    lazy_prim(Graph &t) :G(t), pq(heap<edge<Weight>>(t.e()))
    {
        // pq(heap<edge<Weight>>(t.e()));
        is_in = new bool[t.v()];
        for (int i = 0; i < t.v(); i++) is_in[i] = false;
        mst.clear();

        // lazy_prim
        visit(0);
        while (!pq.is_empty())
        {
            edge<Weight> t = pq.extract();
            if (is_in[t.v()] == is_in[t.w()]) continue;
            mst.push_back(t);
            if (!is_in[t.v()]) visit(t.v());
            else visit(t.w());
        }
        for (int i = 0; i < mst.size(); i++)
            mst_weight += mst[i].wt();
    }
    ~lazy_prim() 
    {
        delete[] is_in;
    }
    std::vector<edge<Weight>> mst_edges() { return mst; }
    Weight result() { return mst_weight; }
};