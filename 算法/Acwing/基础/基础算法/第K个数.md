
#算法/模板题 #算法/快速排序 
[786. 第k个数 - AcWing题库](https://www.acwing.com/problem/content/788/)


![[Pasted image 20240509160130.png]]

```cpp
#include <iostream>
int n, k;
const int N = 1e5 + 10;
int a[N];

int quick_sort(int l, int r)
{
    if (l == r) return a[l];
    srand(time(NULL));
    std::swap(a[l], a[rand() % (r - l + 1) + l]);
    int i = l + 1, j = r;
    int e = a[l];
    while (true)
    {
        while (i <= r && a[i] < e) i++;
        while (j >= l + 1 && a[j] > e) j--;
        if (i > j) break;
        std::swap(a[i], a[j]);
        i++; j--;
    }
    std::swap(a[l], a[j]);
    if (k < j) quick_sort(l, j - 1);
    else if (k > j) quick_sort(j + 1, r);
    else return a[j];
}

int main()
{
    std::cin >> n >> k;
    k--;
    for (int i = 0; i < n; i++) std::cin >> a[i];
    std::cout << quick_sort(0, n - 1) << "\n";   
}
```



```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=100010;
int a[N];
int quickSort(int a[],int l,int r,int k)
{
    if(l>=r)return a[k];
    int x=a[l],i=l-1,j=r+1;
    while(i<j)
    {
        do i++;while(a[i]<x);
        do j--;while(a[j]>x);
        if(i<j)swap(a[i],a[j]);
    }
    if(k>j)return quickSort(a,j+1,r,k);
    return quickSort(a,l,j,k);
}

int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<quickSort(a,0,n-1,k-1)<<endl;
    return 0;
}
```