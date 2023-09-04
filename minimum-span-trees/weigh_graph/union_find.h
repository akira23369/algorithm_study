#include <iostream>

class union_find
{
    int* parent;
    int* rank;  // 层数
    int count;
public:
    union_find(int n)
    {
        parent = new int[n];
        rank = new int[n];
        count = n;
        for (int i = 0; i < n; i++) parent[i] = i, rank[i] = 1;
    }
    ~union_find() { delete[] parent; delete[] rank; }
    int find(int p)
    {
        // while (p != parent[p]) 
        // {
        //     int pp = parent[p];
        //     parent[p] = parent[pp];
        //     p = parent[p];
        // }
        if (p != parent[p]) parent[p] = find(parent[p]);
        return parent[p];
    }
    bool is_connected(int p, int q) { return find(p) == find(q); }
    void my_union(int p, int q)
    {
        int pp = find(p);
        int qq = find(q);

        if (pp == qq) return;
        if (rank[pp] < rank[qq]) 
        {
            parent[pp] = qq;
        }
        else if (rank[pp] > rank[qq]) parent[qq] = pp;
        else 
        {
            parent[pp] = qq;
            rank[qq] += 1;
        }
    }
};