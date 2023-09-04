#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <memory>
using namespace std;

template <typename Item>
class index_heap
{
private:
    unique_ptr<Item[]> data;
    int count;
    int capacity;
    unique_ptr<int[]> indexes;   // index[第多少下标] = 源下标   data[第多少下标] = 排序后的第多少值
    unique_ptr<int[]> reverse;   // reverse[源下标] = 第多少下标    
    // 给传入的第k个up
    void up(int k)
    {
        while (k > 1 && data[indexes[k / 2]] < data[indexes[k]])
        {
            std::swap(indexes[k], indexes[k / 2]);
            reverse[indexes[k]] = k;
            reverse[indexes[k / 2]] = k;
            k = k / 2;
        }
    }
    void down(int k)
    {
        while (k * 2 <= count)
        {
            int j = k * 2;
            if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]]) j++;
            if (data[indexes[k]] > data[indexes[j]]) break;
            std::swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
    }

public:
    index_heap(int c) : count(0), capacity(c)
    {
        data = std::make_unique<Item[]>(c + 1); // 创建一个指向长度为c+1的Item数组的智能指针
        indexes = std::make_unique<int[]>(c + 1); // 创建一个指向长度为c+1的int数组的智能指针
        reverse = std::make_unique<int[]>(c + 1); // 创建一个指向长度为c+1的int数组的智能指针
        for (int i = 0; i <= c; i++) reverse[i] = 0;
    }
    // n是数组长度
    index_heap(Item arr[], int n) :index_heap(n)
    {
        count = n;
        capacity = n;
        for (int i = 0; i < n; i++)
        {
            data[i + 1] = arr[i];
            indexes[i + 1] = i + 1;
            reverse[i + 1] = i + 1;
        }
        for (int i = (n + 1) / 2; i >= 1; i--) down(i);
    }
    ~index_heap() { data.reset(); indexes.reset(); reverse.reset(); }
    int size() { return count; }
    bool is_empty() { return count == 0; }
    bool contain(int i) 
    {
        assert(i + 1 >= 1 && i + 1 <= capacity);
        return reverse[i + 1] != 0;
    }
    // 这个i是用户来看的数组下标，0...
    void insert(int i, Item item)
    {
        assert(i + 1 >= 1 && i + 1 <= capacity);
        // 没被用过
        assert(!contain(i));
        assert(count + 1 <= capacity);
        i++;
        data[i] = item;
        indexes[count + 1] = i;
        reverse[i] = count + 1;
        count++;
        up(count);
    }
    Item extract()
    {
        Item ret = data[indexes[1]];
        std::swap(indexes[count], indexes[1]);
        reverse[indexes[count]] = 0;
        reverse[indexes[1]] = 1;
        count--;
        down(1);
        return ret;
    }

    int extract_index()
    {
        assert(count > 0);
        int ret = indexes[1] - 1;
        std::swap(indexes[1], indexes[count]);
        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;
        count--;
        down(1);
        return ret;
    }

    Item get_intem(int i) 
    {
        assert(i + 1 >= 1 && i + 1 <= capacity);
        assert(contain(i));
        return data[i + 1];
    }
    // 原来的i位置修改
    void change(int i, Item it)
    {
        assert(contain(i));
        i++;
        data[i] = it;
        up(reverse[i]);
        down(reverse[i]);
    }
public:
    // 以树状打印整个堆结构
    void testPrint()
    {

        // 我们的testPrint只能打印100个元素以内的堆的树状信息
        if (size() >= 100)
        {
            cout << "This print function can only work for less than 100 int";
            return;
        }

        // 我们的testPrint只能处理整数信息
        if (typeid(Item) != typeid(int))
        {
            cout << "This print function can only work for int item";
            return;
        }

        cout << "The max heap size is: " << size() << endl;
        cout << "Data in the max heap: ";
        for (int i = 1; i <= size(); i++)
        {
            // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
            assert(data[i] >= 0 && data[i] < 100);
            cout << data[i] << " ";
        }
        cout << endl;
        cout << endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while (n > 0)
        {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level - 1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for (int level = 0; level < max_level; level++)
        {
            string line1 = string(max_level_number * 3 - 1, ' ');

            int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
            bool isLeft = true;
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++)
            {
                putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
                isLeft = !isLeft;
            }
            cout << line1 << endl;

            if (level == max_level - 1)
                break;

            string line2 = string(max_level_number * 3 - 1, ' ');
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
                putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
            cout << line2 << endl;

            cur_tree_max_level_number /= 2;
        }
    }

private:
    void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft)
    {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if (num >= 10)
        {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else
        {
            if (isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine(string &line, int index_cur_level, int cur_tree_width)
    {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
        assert(offset_left + 1 < line.size());
        int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert(offset_right < line.size());

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
};