#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>

template<typename Graph, typename Weight>
class read_graph
{
public: 
    read_graph(Graph &g, const std::string &file)
    {
        std::fstream f(file);
        std::string line;
        int v, e;
        assert(f.is_open());
        assert(f >> v >> e);
        assert(g.v() == v);
        for (int i = 0; i < e; i++)
        {
            int a, b;
            Weight wt;
            f >> a >> b >> wt;
            assert(a >= 0 && a < v);
            assert(b >= 0 && b < v);
            g.add_edge(a, b, wt);
        }
    }

};