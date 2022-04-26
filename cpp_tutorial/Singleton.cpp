class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton inst;
        return inst;
    }
    
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 其他数据函数
    // ...

private:
    Singleton() { /* ... */ }
    // 其他数据成员
    // ...
};