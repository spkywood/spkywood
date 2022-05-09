# 容器

## 线性容器

### `std::vector`

名称 | 说明 
---------|----------
 `assign` | 清除`vector`并将指定的元素复制到该空`vector`。
 `at` | 返回`vector`中指定索引的元素的引用。 
 `back` | 返回`vector`中最后元素的引用。
 `begin` | 返回`vector`中第一个元素返回迭代器`std::vector<TYPE>::iterator`。
 `end` | 返回`vector`中最后元素返回迭代器。
 `cbegin` | 返回`vector`中的 `const_iterator`。
 `cend` | 返回`vector`中的 `const_iterator`。
 `rbegin` | 返回`vector`中倒序首元素返回迭代器。
 `rend` |  `end` | 返回`vector`中倒序最后元素返回迭代器。
 `crbegin` | 返回`vector`中的 `const_iterator`。
 `crend` | 返回`vector`中的 `const_iterator`。

### `std::array`

- 为什么要引入 `std::array` 而不是直接使用 `std::vector`？

> 与 `std::vector` 不同，`std::array `对象的大小是固定的，如果容器大小是固定的，那么可以优先考虑使用 std::array 容器。 另外由于 `std::vector` 是自动扩容的，当存入大量的数据后，并且对容器进行了删除操作，容器并不会自动归还被删除元素相应的内存，这时候就需要手动运行 `shrink_to_fit()` 释放这部分内存。


```c++
#include <vector>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::vector<int> v;
    std::cout << "size:" << v.size() << std::endl;         // 输出 0
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0
    
    // 如下可看出 std::vector 的存储是自动管理的，按需自动扩张
    // 但是如果空间不足，需要重新分配更多内存，而重分配内存通常是性能上有开销的操作
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << "size:" << v.size() << std::endl;         // 输出 3
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 4
    
    // 这里的自动扩张逻辑与 Golang 的 slice 很像
    v.push_back(4);
    v.push_back(5);
    std::cout << "size:" << v.size() << std::endl;         // 输出 5
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8
    
    // 如下可看出容器虽然清空了元素，但是被清空元素的内存并没有归还
    v.clear();                                             
    std::cout << "size:" << v.size() << std::endl;         // 输出 0
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8
    
    // 额外内存可通过 shrink_to_fit() 调用返回给系统
    v.shrink_to_fit();
    std::cout << "size:" << v.size() << std::endl;         // 输出 0
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0
    return 0;
}
```

- 已经有了传统数组，为什么要用 `std::array`?

> 使用 `std::array` 能够让代码变得更加“现代化”，而且封装了一些操作函数，比如获取数组大小以及检查是否非空，同时还能够友好的使用标准库中的容器算法，比如 `std::sort`

```c++
template <class Ty, std::size_t N>
class array;
```

```c++
#include <array>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::array<int, 6> arr = {6, 3, 2, 5, 1, 4};
    arr.empty();
    arr.size();

    for (auto &&i : arr)
    {
        std::cout << i << " ";
    }

    // 用 lambda 表达式排序
    std::sort(arr.begin(), arr.end(), [](int a, int b) {return a < b;});
    
    // 将其兼容 C 风格的接口
    void foo(int *p, int len) {
        return;
    }
    // foo(arr, arr.size()); // 非法, 无法隐式转换
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());
    
    // 使用 `std::sort`
    std::sort(arr.begin(), arr.end());

    return 0;
}
```

### `std::list`


### `std::forward_list`

## 无序容器

- `std::map`
- `std::set`
- `std::unordered_map` 和 `std::unordered_multimap`
- `std::unordered_set` 和 `std::unordered_multiset`

## 元祖

- `std::tuple`

## 参考

- [现代C++教程 容器](https://changkun.de/modern-cpp/zh-cn/04-containers/)

- [array 类 (C++标准库)](https://docs.microsoft.com/zh-cn/cpp/standard-library/array-class-stl?view=msvc-170)