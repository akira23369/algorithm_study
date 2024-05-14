
#算法/DP/状态压缩 #算法/模板题 

[91. 最短Hamilton路径 - AcWing题库](https://www.acwing.com/problem/content/93/)


![[Pasted image 20240513003154.png]]



```cpp
// 暴力枚举
// 0 -> 1 -> 2 -> 3  18wei √
// 0 -> 2 -> 1 -> 3  20wei ×    // 这种情况是可以去掉

// 上式规律：
// 1.只需要关心那些点被使用过，不关心顺序
// 2.目前停在哪个点上

// f[state][j] 来表示使用了那些点，终点为j的路径权值

// state用二进制来表示点是否被使用过
// eg：011 表示使用过0,1点

// 递推方程： 用k表示到j点之前那个点
// f[state][j] = min(f[state - j][k] + weight[k][j]);      ps: state - j 表示除去j点的集合的所有状态
// 初值：f[1][0] = 0;   只经过0，到0的的路径权值为0
// 目标值：f[(1 << n) - 1][n - 1]   走过所有店到n-1点的最小路径



#include<iostream>
#include<cstring>
const int N = 20, M = 1 << 20;
int f[M][N];
int weight[N][N];
int n;
int main()
{
    std::cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> weight[i][j];
    memset(f, 0x3f, sizeof(f));
    f[1][0] = 0;    
    for (int i = 0; i < 1 << n; i++)
        for (int j = 0; j < n; j++)
            if (i >> j & 1)     // i 这条路径是否走到过j点
                for (int k = 0; k < n; k++)
                    if (i >> k & 1) // i这条路径是否走到过k点
                    {
                        f[i][j] = std::min(f[i][j], f[i - (1 << j)][k] + weight[k][j]);     // i - (1 << j) 除去j点
                    }
    std::cout << f[(1 << n) - 1][n - 1] << std::endl;
    return 0;
}

作者：爱不被爱的爱酱
链接：https://www.acwing.com/activity/content/code/content/4866793/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```