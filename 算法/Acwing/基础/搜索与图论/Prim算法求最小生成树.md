
#算法/模板题 #算法/最小生成树

[858. Prim算法求最小生成树 - AcWing题库](https://www.acwing.com/problem/content/860/)

![[Pasted image 20240509212559.png]]

![[Pasted image 20240509212614.png]]


![[Pasted image 20240509212619.png]]

```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N = 510, M = 1e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[2 * M], ne[2 * M], w[2 * M], idx;
int n, m;
int d[N];       // d表示还没出圈的点与生成树的距离
bool st[N];     // 标记是否在生成树内
int ans;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool prim(int u)
{
    priority_queue<pair<int, int>> q;
    int cnt = 0;
    memset(d, INF, sizeof d);
    d[u] = 0;
    q.push({0, u});
    while (q.size())
    {
        auto t = q.top(); q.pop();
        int v = t.second;
        if (st[v]) continue;    // 如果已经是生成树的一份子
        st[v] = true;
        cnt++;
        ans += d[v];
        for (int i = h[v]; ~i; i = ne[i])
        {
            int j = e[i];
            if (d[j] > w[i])    // 这里注意体会与dijkstra的不同
            {
                d[j] = w[i];
                q.push({-d[j], j});
            }
        }
    }
    return cnt == n ? true : false;     // 如果!=n可能图不炼铜
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    bool flag = prim(1);
    if (flag) cout << ans << endl;
    else cout << "impossible" << endl;
    return 0;
}
```


```cpp
// S:当前已经在联通块中的所有点的集合
// 1. dist[i] = inf
// 2. for n 次
//     t<-S外离S最近的点
//     利用t更新S外点到S的距离
//     st[t] = true
// n次迭代之后所有点都已加入到S中
// 联系：Dijkstra算法是更新到起始点的距离，Prim是更新到集合S的距离

#include<iostream>
#include<cstring>
using namespace std;
const int N = 510, INF = 0x3f3f3f3f;
int g[N][N];
int dist[N];                //这里的dist表示离联通块的距离
bool st[N];                 //这里的st标记是否在联通块中
int n, m;

int prim()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;         //随便从那个点开始
    int res = 0;        //表示生成树的代价

    for (int i = 0; i < n; i++)
    {
        int t = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
            {
                t = j;
            }
        }
        //如果找到的距离最小的点是不可达的  (第一轮迭代要特判)
        if (dist[t] == INF) return INF;
        st[t] = true;
        res += dist[t];
        //更新联通块外的点
        for (int i = 1; i <= n; i++)
        {
            if (!st[i] && dist[i] > g[t][i])        //注意这里的1写法
            {
                dist[i] = g[t][i];                  //dist[i] = dist[t] + g[t][i];这是dijkstra
            }
        }
    }
    return res;
}

int main()
{
    cin >> n >> m;
    memset(g, 0x3f, sizeof(g));
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    int res = prim();
    if (res == INF) cout << "impossible" << " ";
    else cout << res << " ";
    return 0;
}
```