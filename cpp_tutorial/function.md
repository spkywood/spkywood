# 函数

## 匿名函数 `lambda`

lambda表达式完整声明

```c++
[capture list] (params list) mutable exception-> return type { function body }
```

- `capture list`：捕获外部变量列表
- `params list`：形参列表
- `mutable`：用来说用是否可以修改捕获的变量
- `exception`：异常设定
- `return type`：返回类型
- `function body`：函数体

```c++
// 声明const类型的表达式，这种类型的表达式不能修改捕获列表中的值。
[capture list] (params list) -> return type {function body}
// 省略了返回值类型，编译器可以自动推断。
[capture list] (params list) {function body}
// 省略了参数列表，类似普通函数中的无参函数。
[capture list] {function body}
```

调用sort函数，旧式的做法如下

```c++
sort(myvec.begin(), myvec.end(), cmp);// myvec是一个int类型的无序变量
```

现在可以方便地利用Lambda表达式来简化代码

```c++
sort(myvec.begin(), myvec.end(),[](int a, int b)->bool {return a < b;});
```

如果我们需要修改捕获变量，这时需要利用mutable关键字

```c++
int a = 100;
auto f = [a]()mutable { cout << ++a; }; // 执行完后a=101
```

捕获形式 | 说明 
---------|----------
[] | 不捕获任何外部变量
[x, y…] | 默认以值的形式捕获指定的多个外部变量（用逗号分隔）
[this] | 以值的形式捕获this指针
[=] | 以值的形式捕获所有外部变量
[&] | 以引用形式捕获所有外部变量
[=, &x] | 变量x以引用形式捕获，其余变量以传值形式捕获
[&, x] | 变量x以值的形式捕获，其余变量以引用形式捕获


> 每个 `lambda` 的类型都是独一无二的。

```c++
#include <iostream>
#include <typeinfo>

template <typename T>
void printType(T obj) {
    std::cout << typeid(obj).name() << std::endl;
}

int main() {
    printType([](){});
    printType([](){});
    printType(0L);
    return 0;
}
```

### std::function

> Class template std::function is a general-purpose polymorphic function wrapper. Instances of std::function can store, copy, and invoke any CopyConstructible Callable target – functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.

> 类模板std::function是一种通用的多态函数封装，std::function的实例可以对任何CopyConstructible Callable目标进行存储、复制和调用操作，这些目标可以是普通函数、Lambda表达式、bind表达式，或者其它函数对象，和指向成员函数的指针和指向数据成员的指针。std::function对象可以看成是对C++中现有的可调用实体的一种类型安全的包裹（例如，函数指针这类可调用的实体，就是类型不安全的）。

比较通俗的理解就是，通过std::function对C++中各种可调用实体（普通函数、Lambda表达式、函数指针、以及其它函数对象等）的封装，可以形成一个新的可调用的std::function对象，让我们不需要再纠结那么多的可调用实体。