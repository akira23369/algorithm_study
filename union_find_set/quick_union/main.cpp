#include <iostream>
#include <cassert>
class union_find
{
    int* parent;
    int count;
    int* sz;
public:
    union_find(int n)
    {
        parent = new int[n];
        count = n;
        sz = new int[n];
        for (int i = 0; i < n; i++) parent[i] = i, sz[i] = 1;
    }
    ~union_find() { delete[] parent; delete[] sz; }
    int find(int p)
    {
        assert(p >= 0 && p < count);
        while (p != parent[p]) p = parent[p];
        return p;
    }
    bool is_connected(int p, int q) { return find(p) == find(q); }
    void my_union(int p, int q)
    {
        int p_root = find(p);
        int q_root = find(q);
        if (p_root == q_root) return;
        if (sz[p_root] < sz[q_root]) sz[p_root] = q_root, sz[q_root] += sz[p_root];
        else sz[q_root] = p_root, sz[p_root] += sz[q_root];
    }
};

void test(int n)
{
    union_find uf(n);
    time_t start = clock();
    for (int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.my_union(a, b);
    }
    for (int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        uf.is_connected(a, b);
    }
    time_t end = clock();
    std::cout << "用时: " << (end - start) * 1.0 / CLOCKS_PER_SEC << "\n";
}

int main()
{
    int n = 1000000;
    test(n);
}