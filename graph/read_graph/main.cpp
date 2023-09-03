#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cassert>
#include "read_graph.h"

// 邻接表
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
    int v() { return n; }
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
    void show()
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << "v" << i << " :";
            for (int j = 0; j < g[i].size(); j++)
                std::cout << g[i][j] << " ";
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


// 邻接矩阵
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
    void show() 
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                std::cout << g[i][j] << " ";
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

// 记录和判断联通分量
template<typename Graph>
class component
{
    Graph &G;
    bool* visited;
    int ccount;     // 连通分量
    int* id;        // 是否是在一个连通分量
    void dfs(int v)
    {
        visited[v] = true;
        id[v] = ccount;
        typename Graph::adj_iterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); i = adj.next())
        {
            if (!visited[i]) { dfs(i); }
        }
    }
public:
    component(Graph &g) :G(g)
    {
        visited = new bool[G.v()];
        ccount = 0;
        for (int i = 0; i < G.v(); i++) visited[i] = false, id[i] = -1;
        for (int i = 0; i < G.v(); i++)
        {
            if (!visited[i]) 
            {
                dfs(i);
                ccount++;
            }
        }
    }
    int count() { return ccount; }
    bool is_connected(int a, int b) 
    {
        assert(a >= 0 && a < G.v());
        assert(b >= 0 && b < G.v());
        return id[a] == id[b];
    }
    ~component() { delete[] visited; delete[] id; }
};


// 记录广度优先的路径
template<typename Graph>
class graph_path
{
    Graph &G;
    bool* visited;
    int* from;
    int s;  // 源点
    void dfs(int v)
    {
        visited[v] = true;
        typename Graph::adj_iterator adj(G, v);
        for (auto it = adj.begin(); !adj.end(); it = adj.next())
        {
            if (!visited[it]) 
            {
                from[it] = v;
                dfs(it);
            }
        }
    }
public:
    graph_path(Graph &g, int ss) :G(g), s(ss) 
    {
        visited = new bool[G.v()];
        from = new int[G.v()];
        for (int i = 0; i < G.v(); i++)
        {
            visited[i] = false;
            from[i] = -1;
        }
        dfs(s);
    }
    bool has_path(int v) 
    {
        assert(v >= 0 && v < G.v());
        return visited[v];
    }
    void path(int v, std::vector<int> &vec)
    {
        std::stack<int> s;
        int p = v;
        while (p != -1)
        {
            s.push(p);
            p = from[p];
        }
        vec.clear();
        while (s.size())
        {
            vec.push_back(s.top());
            s.pop();
        }
    }
    void show_path(int v)
    {
        std::vector<int> vec;
        path(v, vec);
        for (int i = 0; i < vec.size(); i++)
        {
            if (i != vec.size() - 1) std::cout << vec[i] << "->";
            else std::cout << vec[i];
        }
        std::cout << "\n";
    }
    ~graph_path() { delete[] visited; delete[] from; }
};

// 每个点的最短路径
template<typename Graph>
class shortes_path
{
    Graph &G;
    bool* visited;
    int* from;
    int* ord;   // 记录从s到每个节点的最短距离
    int s;      // 源点
public:
    shortes_path(Graph &g, int ss) :G(g), s(ss) 
    {
        visited = new bool[G.v()];
        from = new int[G.v()];
        ord = new int[G.v()];
        for (int i = 0; i < G.v(); i++)
        {
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }
        
        // 无向图最短路劲算法
        std::queue<int> q;
        q.push(s);
        visited[s] = true;
        ord[s] = 0;
        while (q.size())
        {
            int v = q.front();
            q.pop();
            typename Graph::adj_iterator adj(G, v);
            for (auto it = adj.begin(); !adj.end(); it = adj.next())
            {
                if (!visited[it]) 
                {
                    ord[it] = ord[v] + 1;
                    q.push(it);
                    from[it] = v;
                    visited[it] = true;
                }
            }
        }
    }
    bool has_path(int v) 
    {
        assert(v >= 0 && v < G.v());
        return visited[v];
    }
    void path(int v, std::vector<int> &vec)
    {
        std::stack<int> s;
        int p = v;
        while (p != -1)
        {
            s.push(p);
            p = from[p];
        }
        vec.clear();
        while (s.size())
        {
            vec.push_back(s.top());
            s.pop();
        }
    }
    void show_path(int v)
    {
        std::vector<int> vec;
        path(v, vec);
        for (int i = 0; i < vec.size(); i++)
        {
            if (i != vec.size() - 1) std::cout << vec[i] << "->";
            else std::cout << vec[i];
        }
        std::cout << "\n";
    }
    int length(int v)
    {
        assert(v >= 0 && v < G.v());
        return ord[v];
    }
    ~shortes_path() { delete[] visited; delete[] from; delete[] ord; }
};



int main()
{
    // int n = 10, m = 100;
    // srand(time(NULL));
    // sparse_graph g(n, false);
    // for (int i = 0; i < m; i++)
    // {
    //     int a = rand() % n;
    //     int b = rand() % n;
    //     g.add_edge(a, b);
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << "V" << i << " :";
    //     sparse_graph::adj_iterator adj(g, i);
    //     for (auto it = adj.begin(); !adj.end(); it = adj.next()) 
    //         std::cout << it << " ";
    //     std::cout << "\n";
    // }
    // std::string file = "test1.txt";
    // sparse_graph g(13, false);
    // read_graph<sparse_graph> r(g, file);
    // g.show();

    std::string file = "test1.txt";
    dense_graph g(13, false);
    read_graph<dense_graph> r(g, file);
    g.show();
    // component<dense_graph> com1(g);
    // std::cout << com1.count() << " \n";   
    // std::cout << com1.is_connected(3, 9) << "\n";

    graph_path<dense_graph> gp(g, 0);
    gp.show_path(3);

    shortes_path<dense_graph> bfs(g, 0);
    bfs.show_path(3);

}