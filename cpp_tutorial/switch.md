# `switch` 语句

`switch` 语句的开头，我们必须提供一个表达式，然后程序将遍历 `switch` 语句中的每个 `case`，如果找到与我们提供的表达式匹配的 `case`，它将执行那个 `case`。

如果上述过程不能匹配表达式，程序会跳出 switch 语句并执行 default 语句。

## 带有 `break` 的 `switch` 语句

C 和 C++ 中的 `break` 语句用于在 `switch` 语句的代码块中满足所需条件时停止循环迭代。

```c++
#include <iostream>
using namespace std;

int main() {
    int rating = 2;
    switch (rating) {
        case 1:
        cout << "Rated as 1. ";
        break;

        case 2:
        cout << "Rated as 2. ";
        break;

        case 3:
        cout << "Rated as 3. ";
        break;

        default:
        cout << "default . ";
        break;
   }
    return 0;
}
```

> 这里的表达式是 rating = 2。程序在这里所做的是它一个接一个地遍历每个 case 并检查提供的表达式的潜在匹配以停止进一步执行循环并终止它，给我们下面的输出。

```shell
Rated as 2.
```
 
## 不带 `break` 的 `switch` 语句

没有使用 `break` 语句，程序将继续执行，直到到达 `switch` 语句的末尾。

```c++
#include <iostream>
using namespace std;

int main() {
    int rating = 1;
    switch (rating) {
        case 1:
        cout << "Rated as 1. "
        
        case 2:
        cout << "Rated as 2. "
        
        case 3:
        cout << "Rated as 3. "
   }

    return 0;
}
```

没有 break 语句，即使在满足要求后，程序也会打印每个 case 的值。
break 语句用于循环应该迭代的次数未知或循环满足某个预定义条件的情况。

当语句体中没有 `default` 语句且没有 `case` 匹配时，不会执行 `switch` 语句体。`switch` 语句主体内的任何位置都只能有一个 `default` 语句。

