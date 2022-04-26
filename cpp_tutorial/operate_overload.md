# 运算符重载

## `+` `-` `*` `/` 运算符重载

必须是**友元函数**


```c++
class Point
{
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);
    Point(const Point&);

    ~Point();

    friend const Point operator+(const Point& p1,const Point& p2);
    friend const Point operator-(const Point& p1,const Point& p2);
};
```

## 输入输出重载

必须是**友元函数**

```c++
friend ostream& operator<<(ostream& cout, const Point& p);
friend istream& operator>>(istream& cin, Point& p); 
```