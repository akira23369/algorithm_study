
#算法/数学/组合数学 #算法/数学/逆元 #算法/数学/快速幂 #算法/模板题 

[886. 求组合数 II - AcWing题库](https://www.acwing.com/problem/content/888/)



![[Pasted image 20240511003222.png]]


![[Pasted image 20240511003234.png]]

```cpp
// 直接用定义来求组合数
// 注意点 ：除法用乘法逆元来求 1e9 + 7是质数可直接我用快速幂来求逆元
// 先预处理出来所有要用到的阶乘fact
#include<iostream>
using namespace std;
typedef long long LL;
const int N = 100010;
const int mod = 1e9 + 7;

int fact[N], infact[N];     //fact[x] 表示x的阶乘

int qmi(int a, int k, int p)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL) res * a % p;
        a = (LL) a * a % p;
        k >>= 1;
    }
    return res;
}

int main()
{
    int n;
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        cout << (LL)fact[a] * infact[b] % mod * infact[a - b] % mod << endl;        //这里强转注意，md卡了劳资好久日
    }
    return 0;
}

作者：爱不被爱的爱酱
链接：https://www.acwing.com/activity/content/code/content/4763134/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

```