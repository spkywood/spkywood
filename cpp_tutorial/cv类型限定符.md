# `const` 和 `volatile` 类型限定符

`const` `volatile`

- const ——定义类型为常量。
- volatile ——定义类型为易变。

C++ 类型系统中有另外三个独立的类型:

```c++
const T;
volatile T;
const volatile T;
```

## `const`

### `const` 的作用

1. 定义类型为常量，无法被程序修改。
2. 