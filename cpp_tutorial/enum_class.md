# 枚举类

在C++11新标准中推出了一种新的枚举定义办法叫做枚举类，也称作强类型枚举。

定义：

```c++
enum class 枚举类型名: 底层类型 
{
    枚举值列表
};
```

```c++
enum class Type { General, Light, Medium, Heavy};   //所有枚举常量都是int类型
enum class Type: char { General, Light, Medium, Heavy}; //所有枚举常量都是字符类型
enum class Category { General=1, Pistol, MachineGun, Cannon};   //后面的枚举常量值依次增加
```

如果不定义‘底层类型’它默认的枚举值都是int类型。

## 枚举类的优势

- 强作用域，其作用域限制在枚举类中。

> 从C语言继承过来的这个枚举类型[2]，在程序中是可以直接使用枚举值的，枚举类的强作用域就是把这个作用域限制在枚举类里面，就可以避免在不同枚举类型之间的枚举值重名的问题。

- 转换限制，枚举类对象不可以与整型隐式地互相转换。

> 对类型限制更为严格，语法对于这个程序的类型保障就更强。

- 可以指定底层类型

> 根据你要解决的问题的类型不同，可以选择合适的类型来作为枚举值。

```c++
enum class Type: char 
{ 
    General, 
    Light, 
    Medium, 
    Heavy
};
```

## 枚举类举例

```c++
#include<iostream>
using namespace std;

enum class Side{ Right, Left };
enum class Thing{ Wrong, Right };  //不冲突

int main()
{
    Side s = Side::Right;
    Thing w = Thing::Wrong;
    cout << (s == w) << endl;  //编译错误，无法直接比较不同枚举类
    return 0;
}
```

## 参考

```c++
enum class CalibrationAlgoType : int32_t
{
    kLEGACY_CALIBRATION = 0,
    kENTROPY_CALIBRATION = 1,
    kENTROPY_CALIBRATION_2 = 2,
    kMINMAX_CALIBRATION = 3,
};
```