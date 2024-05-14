
#算法/最短路 #算法/模板题 

[854. Floyd求最短路 - AcWing题库](https://www.acwing.com/problem/content/856/)


![[Pasted image 20240509212401.png]]


![[Pasted image 20240509212710.png]]


![[Pasted image 20240509212716.png]]


![[Pasted image 20240509212721.png]]

![[Pasted image 20240509212746.png]]


```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N = 210, M = 2e4 + 10, INF = 0x3f3f3f3f;
int g[N][N];
int p[N][N];
int n, m, k;

void floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (g[i][j] > g[i][k] + g[k][j]) g[i][j] = g[i][k] + g[k][j], p[i][j] = k;
}

void path(int i, int j)
{
    if (p[i][j] == 0) return;   // 如果点i，j之间没有桥直接返回
    int k = p[i][j];
    path(i, k);
    cout << k << " ";
    path(k, j);
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) 
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
    }
    floyd();
    while (k--)
    {
        int x, y;
        cin >> x >> y;
        if (g[x][y] < INF / 2) cout << g[x][y] << endl;
        else cout << "impossible" << endl;
    }
    return 0;
}
```



```cpp
#include<iostream>
#include<cstring>
using namespace std;

#define INF 0x3f3f3f3f
const int N = 210, M = 20010;
int d[N][N];
int n, m, k;



void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);      //松弛操作
}


int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) d[i][j] = 0;     //为了干掉自环
            else d[i][j] = INF;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = min(d[a][b], c);
    }
    floyd();
    while (k--)
    {
        int x, y;
        cin >> x >> y;
        if (d[x][y] > INF / 2) cout << "impossible" << endl;
        else cout << d[x][y] << endl;
    }
    return 0;
}
```