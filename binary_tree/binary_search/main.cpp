#include <iostream>

template<typename T>
int binary_search(T arr[], int n, int target)
{
    // [l ... r] 中找
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int main()
{
    int a[7] = {1, 2, 6, 6, 7, 9, 9};
    std::cout << binary_search(a, 7, 6);

}