#include <iostream>
#include "sort_test.h"


// 将arr分成< = > 三部分 之后直接递归 < 和 > 部分就行
template<typename T>
void _quick_sort_3ways(T arr[], int l, int r)
{
    if (l >= r) return;
    std::swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];
    int lt = l;     // arr[l+1....lt] < e   一开始都为空
    int gt = r + 1; // arr[gt....r] > e
    int i = l + 1;  // 正在考查的元素

    while (i < gt)
    {
        if (arr[i] < e)
        {
            std::swap(arr[i], arr[lt + 1]);
            i++; lt++;
        }
        else if (arr[i] > e)
        {
            std::swap(arr[i], arr[gt - 1]);
            gt--;
        }
        else 
        {
            i++;
        }
    }
    std::swap(arr[l], arr[lt]);     // 这一步之后的lt没有--所以递归的是lt-1
    _quick_sort_3ways(arr, l, lt - 1);
    _quick_sort_3ways(arr, gt, r);
}

template<typename T>
void quick_sort_3ways(T arr[], int n)
{
    srand(time(NULL));
    _quick_sort_3ways(arr, 0, n - 1);
}

int main()
{
    int n = 100000;
    int* arr = sort_test::generate_rand_array(n, 0, 17);
    quick_sort_3ways(arr, n);
    sort_test::print_array(arr, n);
}