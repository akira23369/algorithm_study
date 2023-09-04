#pragma once
#include <iostream>
#include <vector>
#include "heap.h"
#include "union_find.h"
#include "edge.h"

template<typename Graph, typename Weight>
class kruska
{
    std::vector<edge<Weight>> mst;
    Weight mst_weight;
public:
    kruska(Graph &t) 
    {
        heap<edge<Weight>> pq(t.e());
        for (int i = 0; i < t.v(); i++)
        {
            typename Graph::adj_iterator adj(t, i);
            for (edge<Weight>* it = adj.begin(); !adj.end(); it = adj.next())
            {
                if (it->v() > it->w()) pq.insert(-(*it));
            }
        }
        union_find uf(t.e());
        while (!pq.is_empty() && mst.size() < t.v() - 1) 
        {
            edge<Weight> t = pq.extract();
            if (uf.is_connected(t.v(), t.w())) continue;
            mst.push_back(t);
            uf.my_union(t.v(), t.w());
        }
    }

    ~kruska() 
    {

    }
    std::vector<edge<Weight>> mst_edges() { return mst; }
    Weight result() { return mst_weight; }
};