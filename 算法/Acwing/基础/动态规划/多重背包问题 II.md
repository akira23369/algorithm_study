

#算法/DP/背包 #算法/模板题 

[5. 多重背包问题 II - AcWing题库](https://www.acwing.com/problem/content/5/)

![[Pasted image 20240511005448.png]]


![[Pasted image 20240511005450.png]]



```cpp
#include<iostream>
using namespace std;
int n, m, s;
const int N = 12 * 1000 + 10;       
int vv[N], ww[N];
int f[N];

int main()
{
    cin >> n >> m;
    int cnt = 1;    // 从1开始存
    for (int i = 1; i <= n; i++)
    {
        int v, w, s;    // 体积， 价值， 数量
        cin >> v >> w >> s;
        // 二进制拆分
        for (int j = 1; j <= s; j <<= 1)
        {
            vv[cnt] = j * v;
            ww[cnt++] = j * w;
            s -= j;
        }
        if (s)
        {
            vv[cnt] = s * v;
            ww[cnt++] = s * w;
        }
    }
    // i < cnt  因为上面已经++
    for (int i = 1; i < cnt; i++)
        for (int j = m; j >= vv[i]; j--)
            f[j] = max(f[j], f[j - vv[i]] + ww[i]);
    cout << f[m] << endl;
    return 0;
}

作者：爱不被爱的爱酱
链接：https://www.acwing.com/activity/content/code/content/4820640/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```