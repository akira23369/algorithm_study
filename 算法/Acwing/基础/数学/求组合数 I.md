

#算法/数学/组合数学 #算法/模板题 

[885. 求组合数 I - AcWing题库](https://www.acwing.com/problem/content/887/)
![[Pasted image 20240511003038.png]]


![[Pasted image 20240511003056.png]]



```cpp
// 求组合数 1 ： 递推式
#include<iostream>
using namespace std;

const int N = 2010, mod = 1e9 + 7;
int c[N][N];
// 预处理所有的组合数
void init()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
        {
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
}


int main()
{
    int n;
    cin >> n;
    init();
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        cout << c[a][b] << endl;
    }
    return 0;
}

作者：爱不被爱的爱酱
链接：https://www.acwing.com/activity/content/code/content/4757290/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```