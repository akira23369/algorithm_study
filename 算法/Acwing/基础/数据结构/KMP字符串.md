#算法/KMP #算法/模板题 

[831. KMP字符串 - AcWing题库](https://www.acwing.com/problem/content/833/)
![[Pasted image 20240509185227.png]]


![[Pasted image 20240509185309.png]]
最大前后缀
每次匹配只要移动到最大后缀那里

![[Pasted image 20240509185325.png]]

将模式串中的每一个不匹配的字符所需要回退的下标保存起来就是next数组

![[Pasted image 20240509185351.png]]


```cpp
#include<stdio.h>
#include<malloc.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

void get_next(string T, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.size())
    {
        //如果j回溯到底 或者匹配成功
        if (j == 0 || T[i] == T[j])
        {
            i++, j++;
            next[i] = j;        //即next[j+1] == k + 1 == next[j] + 1。
        }
        else
            j = next[j];        //回溯前一重合部分子串的公共部分
    }
}


int KMP(string S, string T)
{
    int i = 1, j = 1;
    int* next = new int[T.size()]();
    while (i <= S.length() && j <= T.length())
    {
        if (j == 0 || T[j] == S[i])
        {
            i++, j++;
        }
        else j = next[j];
    }
    if (j > T.length()) return i - T.length();  //匹配成功
    else return 0;
}


int main() {

    return 0;
}
```

![[Pasted image 20240509185448.png]]


```cpp
#include<iostream>
using namespace std;

const int N = 1000010;
char s[N], p[N];
int n, m, ne[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;
    //处理next数组
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    for (int i = 1, j = 0; i <= m; i++) 
    {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (p[j + 1] == s[i]) j++;
        if (j == n)
        {
            //匹配成功后相关操作
            cout << i - n << " ";
            //成功后还要回溯
            j = ne[j];
        }
    }

    return 0;
}
```