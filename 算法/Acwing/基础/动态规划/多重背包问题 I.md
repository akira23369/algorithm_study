

#算法/DP/背包 #算法/模板题 


[4. 多重背包问题 I - AcWing题库](https://www.acwing.com/problem/content/4/)
![[Pasted image 20240511005318.png]]


![[Pasted image 20240511005337.png]]

```cpp
// 将多重背包问题 转化为 01背包

// 01背包：第i种物品可以取     0，1件       f[j] = max(f[j], f[j - v[i]] + w[i])    分别对应取0和1
// 多重背包：第i种物品可以取   0，1, 2， 3，……件    f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);

#include<iostream>
using namespace std;
int n, m;
const int N = 100 * 100 + 10;
int v[N], w[N], s[N];
int f[N];


int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            for (int k = 0; k <= s[i] && k * v[i] <= j; k++)
                f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);
    cout << f[m] << endl;
    return 0;
}

作者：爱不被爱的爱酱
链接：https://www.acwing.com/activity/content/code/content/4820639/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```