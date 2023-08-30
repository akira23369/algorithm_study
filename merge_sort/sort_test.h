#pragma once

#include <iostream>
#include <cassert>
#include <ctime>
namespace sort_test
{
    int* generate_rand_array(int n, int rangel, int ranger)
    {
        assert(rangel <= ranger);
        int* ptr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; i++)
        {
            ptr[i] = rand() % (ranger - rangel + 1) + rangel;
        }
        return ptr;
    }

    // 生成一个近乎有序的数组
    int* generate_nearly_array(int n, int swap_times)
    {
        int* arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = i;
        srand(time(NULL));
        for (int i = 0; i < swap_times; i++)
        {
            int x = rand() % n, y = rand() % n;
            std::swap(arr[x], arr[y]);
        }
        return arr;
    }

    template<typename T> 
    void print_array(T array[], int n)
    {
        for (int i = 0; i < n; i++)
            std::cout << array[i] << " ";
        std::cout << "\n";
    }

    // 测试排序性能
    template<typename T>
    void test(void(*sort_name)(T[], int), T arr[], int n)
    {
        clock_t start = clock();
        sort_name(arr, n);
        clock_t end = clock();
        std::cout << "总共耗时 : " << 1.0 * (end - start) / CLOCKS_PER_SEC << " s \n";
    }
    int* copy_int_array(int a[], int n)
    {
        int* arr = new int[n];
        std::copy(a, a + n, arr);
        return arr;
    }
}