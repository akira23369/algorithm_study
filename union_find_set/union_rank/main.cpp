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
        while (p != parent[p]) p = parent[p];
        return p;
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
    int n = 100000;
    test(n);

}