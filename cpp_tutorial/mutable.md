# `mutable`

### `const` 和 `mutable`

- const意思是“这个函数不修改对象内部状态”。
- mutable意思是“这个成员变量不算对象内部状态”。

基于mutex的线程安全的队列。

```c++
class Queue
{
    //...

    mutable std::mutex mutex_;

    public:
        void push(int x);
        void pop(int& x);
        bool empty() const;

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mutex_); // require mutex_ mutable here
            // ...
        }
        // 使用empty这个const member function的时候肯定也要先获得内部的一个mutex
        // const函数时也会改变内部状态，于是就要把mutex_声明成mutable的。
};
```

### 类中的 mutable

- mutable 只能用来修饰类的数据成员。
- 而被 mutable 修饰的数据成员，可以在 const 成员函数中修改。

```c++
class HashTable {
 public:
    //...
    std::string lookup(const std::string& key) const
    {
        if (key == last_key_) {
            return last_value_;
        }

        std::string value{this->lookupInternal(key)};

        last_key_   = key;
        last_value_ = value;

        return value;
    }

 private:
    mutable std::string last_key_
    mutable std::string last_value_;
};
```

我们呈现了一个哈希表的部分实现。显然，对哈希表的查询操作，在逻辑上不应该修改哈希表本身。因此，`HashTable::lookup` 是一个 `const` 成员函数。在 `HashTable::lookup` 中，我们使用了 `last_key_` 和 `last_value_` 实现了一个简单的「缓存」逻辑。当传入的 `key` 与前次查询的 `last_key_` 一致时，直接返回 `last_value_`；否则，则返回实际查询得到的 value 并更新 `last_key_` 和 `last_value_`。

`last_key_` 和 `last_value_` 是 `HashTable` 的数据成员。按照一般的理解，`const` 成员函数是不允许修改数据成员的。但是，另一方面，`last_key_` 和 `last_value_` 从逻辑上说，修改它们的值，外部是无有感知的；因此也就不会破坏逻辑上的 `const`。为了解决这一矛盾，我们用 `mutable` 来修饰 `last_key_` 和 `last_value_`，以便在 `lookup` 函数中更新缓存的键值。


### `Lambda` 表达式中的 `mutable`

在 `Lambda` 表达式的设计中，捕获变量有几种方式；其中按值捕获（`Caputre by Value`）的方式不允许程序员在 `Lambda` 函数的函数体中修改捕获的变量。而以 `mutable` 修饰 `Lambda` 函数，则可以打破这种限制。

```c++
int x{0};
auto f1 = [=]() mutable {x = 42;};  // okay, 创建了一个函数类型的实例
auto f2 = [=]()         {x = 42;};  // error, 不允许修改按值捕获的外部变量的值
```

#### 参考

[C++ 中的 mutable 关键字](https://liam.page/2017/05/25/the-mutable-keyword-in-Cxx/)
[C++中mutable关键字存在的必要性是什么？](https://www.zhihu.com/question/64969053)