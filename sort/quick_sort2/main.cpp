#include <iostream>
#include "sort_test.h"


template<typename T>
int _patition(T arr[], int l, int r)
{
    srand(time(NULL));
    std::swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];
    // arr[l + 1....i] <= e ;   arr[j....r] >= e;
    int i = l + 1, j = r;
    while (true)
    {
        while (i <= r && arr[i] < e) i++;       // 从前往后看
        while (j >= l + 1 && arr[j] > e) j--;   // 从后往前看
        if (i > j) break;
        std::swap(arr[i], arr[j]);
        i++; j--;
    }
    // 上面循环完后j从后向前看第一个<=e的，i指从前往后看第一个>=e的， 所以a[l] 和 a[j] 交换
    std::swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void _quick_sort(T arr[], int l, int r)
{
    if (l >= r) return;
    // if (r - l <= 15) { insertion_sort(arr, l, r); return; }
    int p = _patition(arr, l, r);
    _quick_sort(arr, l, p - 1);
    _quick_sort(arr, p + 1, r);
}

template<typename T>
void quick_sort2(T arr[], int n)
{
    _quick_sort(arr, 0, n - 1);
}

int main()
{
    int n = 10000;
    int* arr = sort_test::generate_rand_array(n, 0, 17);
    quick_sort2(arr, n);
    sort_test::print_array(arr, n);
    delete[] arr;
}