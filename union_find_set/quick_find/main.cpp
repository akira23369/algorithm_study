#include <iostream>
#include <cassert>

class union_find
{
    int* id;
    int count;
public:
    union_find(int n) 
    {
        id = new int[n];
        for (int i = 0; i < n; i++) id[i] = i;
        count = n;
    }
    ~union_find() { delete[] id; }
    int find(int p) 
    {
        assert(p >= 0 && p < count);
        return id[p];
    }
    bool is_connected(int p, int q) 
    {
        assert((p >= 0 && p <= count) || (q >= 0 && q < count));
        return id[p] == id[q];
    }
    void my_union(int p, int q)
    {
        int p_id = find(p);
        int q_id = find(q);
        if (q_id == p_id) return;
        for (int i = 0; i < count; i++)
        {
            if (id[i] == q_id) id[i] = p_id;
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