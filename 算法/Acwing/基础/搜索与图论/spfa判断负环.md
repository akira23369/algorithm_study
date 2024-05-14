
#算法/模板题 #算法/最短路 

[852. spfa判断负环 - AcWing题库](https://www.acwing.com/problem/content/854/)

![[Pasted image 20240509211746.png]]


![[Pasted image 20240509211841.png]]




```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int n, m;
int dist[N];
bool st[N];     // 注意spfa的st数组表示是否在更新队列内
int cnt[N];

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

// true表示有负环
bool spfa(int u)
{
    memset(dist, INF, sizeof dist);
    dist[u] = 0;
    queue<int> q;
    // q.push(u);   只入一个点是不行滴
    // st[u] = true;
    for (int i = 1; i <= n; i++) q.push(i), st[i] = true;
    while (q.size())
    {
        int t = q.front(); q.pop(); st[t] = false;
        for (int i = h[t]; ~i; i = ne[i])   
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) 
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;    
                if (cnt[j] >= n) return true;   // 如果步数超过n表示有负环
                if (!st[j]) q.push(j), st[j] = true;
            }
        }
    }
    return false;

}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    bool flag = spfa(1);
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
```