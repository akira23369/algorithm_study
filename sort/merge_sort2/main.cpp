#include <iostream>
#include "sort_test.h"

template<typename T>
void merge(T arr[], int l, int mid, int r)
{
    int i = l, j = mid + 1, k = 0;
    T tmp[r - l + 1];
    while (i <= mid && j <= r)
    {
        if (arr[i] < arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= r) tmp[k++] = arr[j++];
    for (int i = 0, j = l; j <= r; j++) arr[j] = tmp[i++];
}

template<typename T>
void merge_sort2(T arr[], int n)
{
    for (int sz = 1; sz <= n; sz += sz)
        for (int i = 0; i + sz < n; i = i + 2 * sz)
            merge(arr, i, i + sz - 1, std::min(i + 2 * sz - 1, n - 1));
}

int main()
{
    int n = 10000;
    int* arr = sort_test::generate_rand_array(n, 0, n);
    merge_sort2(arr, n);
    // sort_test::test(merge_sort2, arr, n);
    sort_test::print_array(arr, n);
}