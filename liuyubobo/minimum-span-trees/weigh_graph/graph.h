#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cassert>
#include "edge.h"

// 邻接表
template<typename Weight>
class sparse_graph
{
    int n, m;
    bool directed;
    std::vector<std::vector<edge<Weight>* >> g;
public:
    sparse_graph(int n, bool dir)
    {
        this->n = n;
        m = 0;
        directed = dir;
        for (int i = 0; i < n; i++)
            g.push_back(std::vector<edge<Weight>* >());
    }
    ~sparse_graph() 
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < g[i].size(); j++)
                delete g[i][j];
    }
    int v() { return n; }
    int e() { return m; }
    void add_edge(int v, int w, Weight wt)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        g[v].push_back(new edge<Weight>(v, w, wt));
        if (v != w && !directed) g[w].push_back(new edge<Weight>(w, v, wt));
        m++;
    }
    bool has_edge(int a, int b)
    {
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        for (int i = 0; i < g[a].size(); i++)
        {
            if (g[a][i]->other(a) == b) return true;
        }
        return false;
    }
    void show()
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << "v" << i << " :";
            for (int j = 0; j < g[i].size(); j++)
                std::cout << g[i][j]->wt() << " ";
            std::cout << "\n";
        }
    }
    class adj_iterator
    {
        sparse_graph &G;
        int v;
        int index; // 访问到哪了
    public:
        adj_iterator(sparse_graph &t, int p) :G(t), v(p), index(0) {}
        edge<Weight>* begin()
        {
            index = 0;
            if (G.g[v].size()) return G.g[v][0];
            return nullptr;
        }
        edge<Weight>* next()
        {
            index++;
            if (index < G.g[v].size()) return G.g[v][index];
            return nullptr;
        }
        bool end() { return index >= G.g[v].size(); }
    };
};


// 邻接矩阵
template<typename Weight>
class dense_graph
{
    int n, m;
    bool directed;  // 是否为有向图
    std::vector<std::vector< edge<Weight>* >> g;
public: 
    dense_graph(int n, bool dir)
    {
        this->n = n;
        m = 0;
        directed = dir;
        for (int i = 0; i < n; i++) g.push_back(std::vector<edge<Weight>*>(n, nullptr));
    }
    ~dense_graph() 
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (g[i][j] != nullptr)
                    delete g[i][j];
    }
    int v() { return n; }
    int e() { return m; }
    void add_edge(int v, int w, Weight wt)
    {
        // 和原来不同的是，如果有重复的边，就覆盖掉ta
        if (has_edge(v, w)) 
        {
            delete g[v][w];
            if (!directed) delete g[w][v];
            m--;    // 维护边数
        }
        g[v][w] = new edge<Weight>(v, w, wt);
        if (!directed) g[w][v] = new edge<Weight>(w, v, wt);   
        m++;
    }
    bool has_edge(int a, int b)
    {
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        return g[a][b] != nullptr;
    }
    void show() 
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (g[i][j]) std::cout << g[i][j]->wt() << "\t";
                else std::cout << "nullptr ";
            std::cout << "\n";
        }
    }
    class adj_iterator
    {
        dense_graph &G;
        int v;
        int index;
    public: 
        adj_iterator(dense_graph &t, int p) :G(t), v(p), index(-1) {}
        int begin() 
        {
            index = -1;
            return next();
        }
        // 原先next返回的是节点的序列号， 现在要返回edge<Weight>*
        edge<Weight>* next()
        {
            for (index += 1; index < G.v(); index++)
                if (G.g[v][index]) return G.g[v][index];
            return nullptr;
        }
        bool end() 
        {
            return index >= G.v();
        }
    };
};