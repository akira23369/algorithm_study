#include <iostream>
#include <vector>
#include <cassert>

class sparse_graph
{
    int n, m;
    bool directed;
    std::vector<std::vector<int>> g;
public:
    sparse_graph(int n, bool dir)
    {
        this->n = n;
        m = 0;
        directed = dir;
        for (int i = 0; i < n; i++)
            g.push_back(std::vector<int>());
    }
    void add_edge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        g[v].push_back(w);
        if (v != w && !directed) g[w].push_back(v);
        m++;
    }
    bool has_edge(int a, int b)
    {
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        for (int i = 0; i < g[a].size(); i++)
        {
            if (g[a][i] == b) return true;
        }
        return false;
    }
    class adj_iterator
    {
        sparse_graph &G;
        int v;
        int index; // 访问到哪了
    public:
        adj_iterator(sparse_graph &t, int p) :G(t), v(p), index(0) {}
        int begin()
        {
            index = 0;
            if (G.g[v].size()) return G.g[v][0];
            return -1;
        }
        int next()
        {
            index++;
            if (index < G.g[v].size()) return G.g[v][index];
            return -1;
        }
        bool end() { return index >= G.g[v].size(); }
    };
};

int main()
{
    int n = 10, m = 100;
    srand(time(NULL));
    sparse_graph g(n, false);
    for (int i = 0; i < m; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        g.add_edge(a, b);
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << "V" << i << " :";
        sparse_graph::adj_iterator adj(g, i);
        for (auto it = adj.begin(); !adj.end(); it = adj.next()) 
            std::cout << it << " ";
        std::cout << "\n";
    }
}