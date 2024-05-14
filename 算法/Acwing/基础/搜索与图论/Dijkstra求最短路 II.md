
#算法/模板题 #算法/最短路 

![[Pasted image 20240509211142.png]]


![[Pasted image 20240509211151.png]]

![[Pasted image 20240509211156.png]]


![[Pasted image 20240509211204.png]]

```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N = 100010;
typedef pair<int, int> PII;
int n, m;
int e[N], ne[N], h[N], w[N], idx;
int dist[N];
bool state[N];  // 是否已经确定最短路
void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});      //这个顺序不能倒，pair排序时是先根据first，再根据second，这里显然要根据距离排序
    //获取dist最小的边
    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();
        //已找到的dist最小的点来做跳板来更新dist
        int ver = t.second, distance = t.first;     //distance是源点到t点距离
        if (state[ver]) continue;      //如果有重边会从这里出去，
        // 不写，continue答案也是正确的，但是会处理许多重复的数据。这样就和朴素的dijkstra一样了，反而还多了个维护堆的时间。
        //更新状态，dist
        state[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > distance + w[i])          
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    while (m--)
    {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
    }
    cout << dijkstra() << endl;
    return 0;
}
```

![[Pasted image 20240509211238.png]]

