# 内联函数

`inline`

## 1. 为什么要使用内联 `inline` 函数

执行程序时，CPU 都会在函数调用之后存储指令的内存地址；它将参数复制到堆栈上并将控制权转移到指定的函数。

然后 CPU 执行代码，返回特定内存位置的值，并再次返回到被调用的函数。如果大部分时间都花在切换而不是执行功能上，它可能会产生额外的开销。

这种开销在执行复杂的 CPU 密集型任务的大型函数中是微不足道的，因为大部分时间只花在执行上。

但是，当我们有许多只执行基本任务的小功能时，这种开销会变得很大。大部分时间都花在切换上，几乎没有时间花在执行上。

因此，当我们有许多小功能以节省切换时间并提高效率时，内联的概念会很方便。

每当在编译时在代码中将任何函数声明为内联时，它不会在函数调用时分配地址，而是复制整个函数代码并将其放在该位置。

```c++
inline TYPE function_name(arguments)
{
    // ...
}
```

`inline` 函数只是对编译器的请求，因此编译器可以在以下情况下忽略它：

- 函数有静态变量；
- 函数有 `goto` 或 `switch` 语句；
- 函数是递归的；
- 函数有循环。
- `inline` 的概念通常与类一起使用。

## 2. 实现一个 `inline` 内联函数

下面的类声明中，`Account` 构造函数是内联函数。 

成员函数`GetBalanceDeposit`，`Withdraw`未指定为`inline`内联函数，但可以实现为内联函数。

```c++
// Inline_Member_Functions.cpp
class Account
{
public:
    Account(double initial_balance) { balance = initial_balance; }
    double GetBalance();
    double Deposit( double Amount );
    double Withdraw( double Amount );
private:
    double balance;
};

inline double Account::GetBalance()
{
    return balance;
}

inline double Account::Deposit( double Amount )
{
    return ( balance += Amount );
}

inline double Account::Withdraw( double Amount )
{
    return ( balance -= Amount );
}
int main()
{
}
```

> 在类声明中，未声明 inline 关键字的函数。 可以在 inline 类声明中指定关键字;结果相同。

给定的内联成员函数在每个编译单元中必须以相同的方式进行声明。 此约束会导致内联函数像实例化函数一样运行。 此外，必须有精确的内联函数的定义。

类成员函数默认为外部链接，除非该函数的定义包含 `inline` 说明符。 前面的示例显示，无需使用 `inline` 说明符显式声明这些函数。 在 `inline` 函数定义中使用会导致它是内联函数。 但是，不允许在调用该函数后重新声明函数 `inline` 。

## 3. 将 `constructor` 和 `destructor` 实现为 `inline` 函数


## 4. 实现 `inline` 函数的优缺点

## 5. 何时使用内联函数

- 内联函数最适用于小函数使用，例如访问私有数据成员。 这两个单行或两行“访问器”函数的主要用途是返回有关对象的状态信息。 短函数对函数调用的开销很敏感。较长的函数在调用和返回序列中花费的时间比例较低，并且从内联中受益更少。

```c++
// when_to_use_inline_functions.cpp
class Point
{
public:
    // Define "accessor" functions as
    //  reference types.
    unsigned& x();
    unsigned& y();
private:
    unsigned _x;
    unsigned _y;
};

inline unsigned& Point::x()
{
    return _x;
}
inline unsigned& Point::y()
{
    return _y;
}
int main()
{
}
```

假设坐标操作是此类客户端中相对常见的操作，因此 (指定两个访问器函数xy，并在前面的示例中) 通常inline节省开销：

- 函数调用（包括参数传递和在堆栈上放置对象地址）

- 保留调用者的堆栈帧

- 新的堆栈帧设置

- 返回值通信

- 还原旧堆栈帧

- 返回

## 内联函数与宏

内联函数类似于宏，因为函数代码在编译时调用时扩展。 但是，内联函数由编译器分析，宏由预处理器扩展。

- 内联函数遵循对正常函数强制执行的所有类型安全协议。

- 内联函数使用与除函数声明中包含 `inline` 关键字以外的任何其他函数相同的语法指定。

- 计算一次作为内联函数的参数传递的表达式。 在某些情况下，作为宏的自变量传递的表达式可计算多次。

> 示例演示了将小写字母转换为大写字母的宏：


```c++
// inline_functions_macro.c
#include <stdio.h>
#include <conio.h>

#define toupper(a) ((a) >= 'a' && ((a) <= 'z') ? ((a)-('a'-'A')):(a))

int main() {
   char ch;
   printf_s("Enter a character: ");
   ch = toupper( getc(stdin) );
   printf_s( "%c", ch );
}
//  Sample Input:  xyz
// Sample Output:  Z
```

表达式 toupper(getc(stdin)) 的意图是，应从控制台设备读取字符 (stdin) ，并在必要时转换为大写。

由于宏的实现， getc 执行一次以确定字符是否大于或等于“a”，一次用于确定字符是否小于或等于“z”。如果它位于该范围内， getc 则再次执行以将字符转换为大写。 这意味着程序等待两到三个字符，理想情况下，它应该只等待一个字符。

内联函数纠正了前面所述的问题：

```c++
// inline_functions_inline.cpp
#include <stdio.h>
#include <conio.h>

inline char toupper( char a ) {
   return ((a >= 'a' && a <= 'z') ? a-('a'-'A') : a );
}

int main() {
   printf_s("Enter a character: ");
   char ch = toupper( getc(stdin) );
   printf_s( "%c", ch );
}
```