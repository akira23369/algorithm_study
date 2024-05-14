#算法/DFS #算法/模板题 

[843. n-皇后问题 - AcWing题库](https://www.acwing.com/problem/content/845/)

![[Pasted image 20240509192233.png]]



![[Pasted image 20240509192315.png]]

```cpp
#include<iostream>
using namespace std;

const int N = 10;
// bool数组用来判断搜索的下一个位置是否可行
// col列，dg对角线，udg反对角线     用截距表示同一点的两条对角线
// g[N][N]用来存路径
bool col[N], dg[2 * N], udg[2 * N];
char g[N][N];
int n;
//从第u行开始搜索
void dfs(int u)
{
    if (u == n)
    {
        //输出每一行
        for (int i = 0; i < n; i++)
        {
            puts(g[i]);
        }
        cout << endl;
        return;
    }
    //找当前行中有哪个地方可以放皇后
    for (int i = 0; i < n; i++)
    {
        //如果可以放皇后
        if (!col[i] && !dg[i - u + N] && !udg[i + u])
        {
            g[u][i] = 'Q';
            col[i] = dg[i - u + N] = udg[i + u] = true;
            dfs(u + 1);
            col[i] = dg[i - u + N] = udg[i + u] = false;
            g[u][i] = '.';
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            g[i][j] = '.';
        }
    }
    dfs(0);
    return 0;
}
```