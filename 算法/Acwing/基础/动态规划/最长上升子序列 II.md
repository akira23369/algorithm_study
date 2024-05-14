
#算法/贪心 #算法/模板题 #算法/DP/线性

[896. 最长上升子序列 II - AcWing题库](https://www.acwing.com/problem/content/898/)

![[Pasted image 20240513002110.png]]



![[Pasted image 20240513002118.png]]


```cpp
/ 最难理解的地方在于栈中序列虽然递增，但是每个元素在原串中对应的位置其实可能是乱的，那为什么这个栈还能用于计算最长子序列长度？
// 实际上这个栈【不用于记录最终的最长子序列】，而是【以stk[i]结尾的子串长度最长为i】
// 或者说【长度为i的递增子串中，末尾元素最小的是stk[i]】。
// 理解了这个问题以后就知道为什么新进来的元素要不就在末尾增加，要不就替代第一个大于等于它元素的位置。
// 这里的【替换】就蕴含了一个贪心的思想，对于同样长度的子串，我当然希望它的末端越小越好，这样以后我也有更多机会拓展。

#include<iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N], len;
int n;

int find(int a[], int l, int r, int x)
{
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    b[len++] = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] > b[len - 1]) b[len++] = a[i];
        else
        {
            int j = find(b, 0, len - 1, a[i]);
            b[j] = a[i];
        }
    }
    cout << len << endl;
    return 0;
}

作者：爱不被爱的爱酱
链接：https://www.acwing.com/activity/content/code/content/5339210/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```