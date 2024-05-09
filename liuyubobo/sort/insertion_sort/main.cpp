#include <iostream>
#include "sort_test.h"

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
    int n = 100;
    int* arr = sort_test::generate_nearly_array(n, 6);
    insertion_sort(arr, n);
    sort_test::print_array(arr, n);
    sort_test::test(insertion_sort, arr, n);
}