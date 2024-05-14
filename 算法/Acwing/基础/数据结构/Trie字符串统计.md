
#算法/数据结构/Trie树 #算法/模板题 

[835. Trie字符串统计 - AcWing题库](https://www.acwing.com/problem/content/837/)

![[Pasted image 20240509185701.png]]


```cpp
#include<stdio.h>
#include<malloc.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
const int N = 100010;

int son[N][26], idx, cnt[N];

void insert(char* str)
{
    int p = 0;      //表示当前指向的节点   从头结点开始
    for (int i = 0; str[i]; i++)        //遍历str每个字符
    {
        int u = str[i] - 'a';
        //检查当前p指向的节点字符是否与str的中的字符相匹配
        //有就将p移动到其子节点 匹配后续字符
        //没有就用idx分配器创建
        if (son[p][u] != str[i]) son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++;
}

//查找操作 并且返回每个以所查找字符串以末尾字符 结尾的节点个数
int query(char* str)
{
    int p = 0;  //用于指向当前节点
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (son[p][u] != str[i]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}


int main()
{
    cin >> n;
    char ch;
    while (n--)
    {
        string s;
        cin >> ch >> s;
        if (ch == 'I') insert(s);
        else cout << query(s) << endl;
    }
    return 0;
}
```


