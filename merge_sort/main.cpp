#include <iostream>
#include <algorithm>
#include "sort_test.h"


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

template<typename T>
void insertion_sort(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        T tmp = arr[i];
        int j = i; 
        while (j > 0 && arr[j - 1] > tmp)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = tmp;
    }
}


int main()
{
    int n = 100000;
    int* arr = sort_test::generate_rand_array(n, 0, n);
    int* arr2 = sort_test::generate_nearly_array(n, 6);
    // merge_sort(arr, 0, n - 1);
    // sort_test::print_array(arr, n);
    sort_test::test(insertion_sort, arr2, n);
    sort_test::test(merge_sort2, arr2, n);
    delete[] arr;
    delete[] arr2;
}