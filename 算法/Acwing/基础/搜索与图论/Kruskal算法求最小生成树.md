
#算法/最小生成树 #算法/模板题 

[859. Kruskal算法求最小生成树 - AcWing题库](https://www.acwing.com/problem/content/861/)

![[Pasted image 20240509212906.png]]


![[Pasted image 20240509212929.png]]


![[Prim vs Kruskal]]

```cpp
// kruskal算法具体步骤：
// 对所有边排序，
// 按排序顺序连接不在同一个联通块的边
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 200010;
int n, m;
int p[N];       //并查集的父亲节点

struct Edge
{
    int a, b, w;
    bool operator < (const Edge & val)const         //重载小于号sort排序
    {
        return w < val.w;
    }
} edges[N];

int find(int x)
{
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int kruskal()
{
    sort(edges, edges + m);
    for (int i = 1; i <= n; i++) p[i] = i;      //初始化并查集
    int res = 0, cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (p[a] != p[b])
        {
            p[a] = b;
            res += w;
            cnt++;
        }
    }
    if (cnt == n - 1) return res;
    else return 0x3f3f3f3f;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }
    int res = kruskal();
    if (res == 0x3f3f3f3f) cout << "impossible";
    else cout << res;
    return 0;
}
```

