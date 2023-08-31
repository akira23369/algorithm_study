#include <iostream>
#include "sort_test.h"


template<typename T>
int _partition(T arr[], int l, int r)
{
    // srand(time(NULL));
    // std::swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];
    int j = l;  // j标记<的右边界
    for (int i = l + 1; i <= r; i++)
    {
        if (arr[i] < e) 
        {
            std::swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    // 这个是把arr[l]放到正确的位置
    std::swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void _quick_sort(T arr[], int l, int r)
{
    if (l >= r) return;
    int p = _partition(arr, l, r);  // 讲[l, r]区间给变成左小右大
    _quick_sort(arr, l, p - 1);
    _quick_sort(arr, p + 1, r);
}

template<typename T>
void quick_sort(T arr[], int n)
{
    _quick_sort(arr, 0, n - 1);
}
template<typename T>
void merge_sort(T arr[], int l, int r)
{
    if (l >= r) return;
    int mid = (l + r) / 2;
    merge_sort(arr, l, mid), merge_sort(arr, mid + 1, r);
    int i = l, j = mid + 1, tmp[r - l + 1], k = 0;
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
    merge_sort(arr, 0, n - 1);
}

int main()
{
    int n = 100000;
    int* arr = sort_test::generate_rand_array(n, 0, 100);
    int* arr2 = sort_test::generate_nearly_array(n, 0);
    quick_sort(arr, n);
    sort_test::test(merge_sort2, arr, n);
    sort_test::test(quick_sort, arr, n);
    // sort_test::print_array(arr, n);
    delete[] arr;
    delete[] arr2;
}