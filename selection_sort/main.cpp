#include <iostream>
#include "student.h"
#include "sort_test.h"

template<typename T>
void selection_sort(T a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[min_index]) min_index = j;
        std::swap(a[min_index], a[i]);
    }
}

int main()
{
    int n = 100000;
    int* a = sort_test::generate_rand_array(n, 0, n);
    Student c[3] = {{"zs", 50}, {"lisi", 20}, {"wangermazi", 66}};
    selection_sort(a, n);
    // sort_test::print_array(a, n);
    sort_test::test(selection_sort, a, n);
    delete[] a;
}