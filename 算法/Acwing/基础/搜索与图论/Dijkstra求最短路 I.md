
#算法/最短路 #算法/模板题 

[849. Dijkstra求最短路 I - AcWing题库](https://www.acwing.com/problem/content/851/)

![[Pasted image 20240509210944.png]]


```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N = 510;
int dist[N];    //存源点到各点的距离
int g[N][N];    //稠密图用邻接矩阵
bool state[N];   //标记点是否有最短距
int n, m;


//默认从1点开始
int dijkstra()
{
    //初始化源点到各点的长度 dist   
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    //这里没有state[1] = true
    //迭代n次
    for (int i = 0; i < n; i++)
    {
        //每次找到边权最小的点
        int t = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!state[i] && (t == -1 || dist[t] > dist[i]))
            {
                t = i;
            }
        }
        state[t] = true;
        //更新距离
        for (int i = 1; i <= n; i++)
        {
            dist[i] = min(dist[i], dist[t] + g[t][i]);
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];
}


int main()
{
    cin >> n >> m;
    memset(g, 0x3f, sizeof(g));
    while (m--)
    {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);      //可以选出重边最小的一条边
    }
    cout << dijkstra() << endl;
    return 0;
}
```

