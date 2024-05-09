#include <iostream>
#include <cassert>
#include <vector>

class dense_graph
{
    int n, m;
    bool directed;  // 是否为有向图
    std::vector<std::vector<bool>> g;
public: 
    dense_graph(int n, bool dir)
    {
        this->n = n;
        m = 0;
        directed = dir;
        for (int i = 0; i < n; i++) g.push_back(std::vector<bool>(n, false));

    }
    int v() { return n; }
    int e() { return m; }
    void add_edge(int v, int w)
    {
        if (has_edge(v, w)) return;
        g[v][w] = true;
        if (!directed) g[w][v] = true;   
    }
    bool has_edge(int a, int b)
    {
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        return g[a][b];
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
        int next()
        {
            for (index += 1; index < G.v(); index++)
                if (G.g[v][index]) return index;
            return -1;
        }
        bool end() 
        {
            return index >= G.v();
        }
    };
};

int main()
{
    int n = 10, m = 100;
    srand(time(NULL));
    dense_graph g(n, false);
    for (int i = 0; i < m; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        g.add_edge(a, b);
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << "V" << i << " :";
        dense_graph::adj_iterator adj(g, i);
        for (auto it = adj.begin(); !adj.end(); it = adj.next()) 
            std::cout << it << " ";
        std::cout << "\n";
    }
}