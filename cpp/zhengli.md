# Table of Contents
- [Table of Contents](#table-of-contents)
- [清华郑莉](#清华郑莉)
  - [46\_constexpr函数](#46_constexpr函数)
  - [47\_带默认参数值的函数](#47_带默认参数值的函数)
  - [49\_函数重载](#49_函数重载)
  - [50\_c++系统函数](#50_c系统函数)
  - [55\_面向对象程序设计的基本特点](#55_面向对象程序设计的基本特点)
  - [58\_构造函数基本概念](#58_构造函数基本概念)
  - [61\_委托构造函数](#61_委托构造函数)
  - [62\_复制构造函数](#62_复制构造函数)
  - [65\_类的组合](#65_类的组合)
  - [70\_联合体](#70_联合体)
  - [71\_枚举类](#71_枚举类)
  - [76\_标识符的作用域与可见性](#76_标识符的作用域与可见性)
  - [77\_对象的生存期](#77_对象的生存期)
  - [80\_类的友元](#80_类的友元)
  - [81\_共享数据的保护](#81_共享数据的保护)
  - [91\_基于范围的for循环](#91_基于范围的for循环)
  - [93\_指针变量的初始化和赋值](#93_指针变量的初始化和赋值)
  - [97\_指针数组](#97_指针数组)
  - [98\_以指针作为函数参数](#98_以指针作为函数参数)
  - [99\_指针类型的函数](#99_指针类型的函数)
  - [100\_指向函数的指针](#100_指向函数的指针)
  - [101\_对象指针](#101_对象指针)
  - [102\_动态分配与释放内存](#102_动态分配与释放内存)
  - [103\_申请和释放动态数组01](#103_申请和释放动态数组01)
  - [104\_申请和释放动态数组02](#104_申请和释放动态数组02)
  - [105\_智能指针](#105_智能指针)
  - [106\_vector对象](#106_vector对象)
  - [108\_移动构造](#108_移动构造)
  - [109\_c风格字符串](#109_c风格字符串)
  - [110\_string类](#110_string类)
  - [116\_继承的基本概念和语法](#116_继承的基本概念和语法)
  - [117\_继承方式简介及公有继承](#117_继承方式简介及公有继承)
  - [118\_私有继承和保护继承](#118_私有继承和保护继承)
  - [119\_基类与派生类类型转换](#119_基类与派生类类型转换)
  - [120\_派生类的构造函数](#120_派生类的构造函数)
  - [122\_派生类的复制构造函数](#122_派生类的复制构造函数)
  - [123\_派生类的析构函数](#123_派生类的析构函数)
  - [124\_访问从基类继承的成员](#124_访问从基类继承的成员)
  - [125\_虚基类](#125_虚基类)
  - [130\_运算符重载的规则](#130_运算符重载的规则)
  - [131\_双目运算符重载为成员函数](#131_双目运算符重载为成员函数)
  - [134\_虚函数](#134_虚函数)
  - [136\_虚函数与动态绑定](#136_虚函数与动态绑定)
  - [137\_抽象类](#137_抽象类)
  - [138\_override与final](#138_override与final)
  - [161\_范性程序设计的基本概念](#161_范性程序设计的基本概念)
  - [162\_STL简介](#162_stl简介)
  - [163\_迭代器](#163_迭代器)
  - [STL库另作篇章，在此部分不再详谈。](#stl库另作篇章在此部分不再详谈)
  - [179\_I/O流的概念及流类库结构](#179_io流的概念及流类库结构)
  - [192\_异常处理的思想与程序实现](#192_异常处理的思想与程序实现)
  - [193\_异常处理中的构造与析构](#193_异常处理中的构造与析构)
  - [194\_标准程序库异常处理](#194_标准程序库异常处理)

# 清华郑莉

## 46_constexpr函数
如果参数为constexpt，承诺返回值为constexpr。
`constexpr int get_size(){return 20;}//该语句在编译阶段就可以解决`，`constexpr int foo = get_size();//由上一个cosntexpr函数来赋值，则foo必须为constexpr`

[![top] Goto Top](#table-of-contents)

## 47_带默认参数值的函数
有默认参数的形参必须列在形参列表的最后，即默认参数值的右面不能有无默认值的参数；
调用时实惨与形参的结合次序是从左向右
```cpp
int add(int x, int y = 5, int z = 6);//正确
int add(int x = 1, int y = 5, int z);//错误
int add(int x = 1, int y, int z = 6);//错误
```
默认参数值与函数的调用位置：如果一个函数有原型声明，且原型声明在定义之前，则默认参数值应在函数原型声明中给出；如果只有函数的定义，或函数定义在前，则默认参数可以在函数定义中给出。

[![top] Goto Top](#table-of-contents)

## 49_函数重载
注意事项：
1. 重载函数形参必须不同，个数不同或类型不同
2. 编译程序将根据实惨和形参的类型及个数最佳匹配来选择调用哪个函数
3. 不要将不同功能的函数声明为重载函数，以免出现调用结果的误解、混淆

[![top] Goto Top](#table-of-contents)

## 50_c++系统函数
cmath

[![top] Goto Top](#table-of-contents)

## 55_面向对象程序设计的基本特点
抽象、封装、继承、多态

多态是指同一名称，不同功能实现方式，目的是达到行为标识统一，减少程序中标示符的个数。

[![top] Goto Top](#table-of-contents)

## 58_构造函数基本概念
`= default`：
如果程序中已定义构造函数，默认情况下编译器就不再隐含生成默认构造函数。如果此时依然希望编译器隐含生成默认构造函数，可以使用`= default`
```cpp
class Clock {
public:
    Clock() = defalut;//指示编译器提供默认构造函数
    Clock(int newH, int newM, int newS);//构造函数

}
```

## 61_委托构造函数
委托构造函数使用类的其他构造函数执行初始化过程：
```cpp
Clock(int newH, int newM, int newS) :
        hour(newH), minute(newM), second(newS) {}

Clock() : Clock(0, 0, 0) {}
```
优势不仅仅是写代码简单省事，最大的好处是保持代码实现的一致性，如果未来想修改构造函数的算法的时候，你只要在一处修改，其他委托构造函数的算法也就同步修改。

[![top] Goto Top](#table-of-contents)

## 62_复制构造函数

用一个对象去复制一个新对象。利用已有对象的引用作为构造函数的参数。如果没有定义复制构造函数，编译器也会生成一个默认的复制构造函数，以实现两个对象数据成员的一一对应的复制。在默认复制构造函数不能满足我们需求的时候，我们需要去写自己的复制构造函数。

复制构造函数是一种特殊的构造函数，其形参为本类的对象引用，作用是用一个已存在的对象去初始化同类型的新对象。其形参必须是本类对象的引用，它的作用就是利用这个形参来构造新的对象。

```cpp
class 类名 {
public:
    类名(形参);//构造函数
    类名(const 类名 &对象名);//复制构造函数
    //...
}

类名::类(const 类名 &对象名)//复制构造函数的实现
{
    函数体
}
```
请一定注意const用法，我们不希望改变原有对象。


复制构造函数被调用的三种情况

1. 定义一个对象时，以本类另一个对象作为初始值，发生复制构造如果函数的形参是类的对象，调用函数时，将使用实参对象初始化形参对象，发生复制构造
2. 如果函数的返回值是类的对象，函数执行完成返回主调函数时将使用 returni 语句中的对象初始化一个临时无名对象，传递给主调函数，此时发生复制构造。
3. 这种情况也可以通过移动构造避免不必要的复制



如果不希望对象被复制构造：

C++98 做法：将复制构造函数声明为 private，并且不提供函数的实现。
C++11 做法：用`= delete`指示编译器不生成默认复制构造函数。

例：
```cpp
class Point{//Point类的定义
public:
    Point (int xx = O, int yy = O){x = xx; y = yy;}//构造函数，内联
    Point (const Pointe& p)= delete;//指示编译器不生成默认复制构造函数
private:
    int x, y;//私有数据 
}:
```

[![top] Goto Top](#table-of-contents)

## 65_类的组合

概念：
1. 类中的成员是另一个类的对象
2. 可以在已有抽象的基础上实现更复杂的抽象（类是抽象的）


类组合的构造函数设计：
原则：不仅要对本类中的基本类型成员数据初始化，也要对对象成员初始化

声明形式：
类名::类名(对象成员所需的形参, 本类成员形参):
    对象1(参数), 对象2(参数), ......
    {
        //函数体其他语句
    }


构造组合类对象时的初始化次序：
1. 首先对构造函数初始化列表中列出的成员（包括基本类型成员和对象成员）进行初始化，初始化次序是成员在类体中定义的次序。
- 成员对象构造函数调用顺序：按对象成员的定义顺序，先声明者先构造
- 初始化列表中未出现的成员对象，调用默认构造函数（即无形参的）初始化，这里提示了我们，为了使成员类更为通用，写构造函数时尽量写上不带参数的构造函数

2. 处理完初始化列表之后，再执行构造函数的函数体。

[![top] Goto Top](#table-of-contents)

## 70_联合体

union联合体可以看为一个数据结构而不是class或者struct，可放置在class中作为私有数据成员。

题外话：从书中的实例代码中看到，enum（枚举）类型虽说一般不要在声明时就创建对象，但是放在private成员时，不妨直接声明对象，`enum{...}mode`这样。见课本p132。

[![top] Goto Top](#table-of-contents)

## 71_枚举类

语法形式：
`enum class 枚举类型名: 底层类型{枚举值列表};`
例：
```cpp
enum class Type {General, Light, Medium, Heavy); //没有指定则为默认为int类型
enum class Type: char {General, Light, Medium, Heavy);
enum class Category {General=1, Pistol, MachineGun, Cannon);
```
枚举类的优势
- 强作用域
- 转换限制
- 可以指定底层类型

枚举类的优势

- 强作用域，其作用域限制在枚举类中。避免了重名问题
例：使用 Type 的枚举值 General:
`Type:: General`

- 转换限制，枚举类对象不可以与整型隐式地互相转换。

- 可以指定底层类型例：
`enum class Type: char General, Light, Medium, Heavy);`

示例代码：
```cpp
#include <iostream> using namespace std;

enum class Side {
    Right, Left
}

enum class Thing {
    Wrong, Right
};//不冲突

int main() {

    Side s
    Side::Right;
    Thing w
    Thing::Wrong;

    cout << (s == w) << endl;//编译错误，无法直接比较不同枚举类
    return 0;
}
```

[![top] Goto Top](#table-of-contents)

## 76_标识符的作用域与可见性
不同于`{}`等作用域，则具有文件作用域，其作用域开始于声明点，结束于文件尾。若是文件中有多个函数，则该文件中函数均可访问该标识符。

[![top] Goto Top](#table-of-contents)

## 77_对象的生存期
对象和变量的生存期分为静态生存期和动态生存期
静态生存期：
- 这种生存期与程序的运行期相同
- 在文件作用域中声明的对象具有这种生存期
- 在函数内部声明静态生存期对象，要冠以关键字static

动态生存期：
- 开始于程序执行到声明点时，结束于命名该标识符的作用域结束处
- 块作用域中声明的，没有用static修饰的对象是动态生存期的对象(习惯称局部生存期对象)

全局变量、静态全局变量、静态局部变量和局部变量的区别
- 变量可以分为：全局变量、静态全局变量、静态局部变量和局部变量。
- 按存储区域分，全局变量、静态全局变量和静态局部变量都存放在内存的静态存储区域，局部变量存放在内存的栈区。
- 按作用域分，全局变量在整个工程文件内都有效；静态全局变量只在定义它的文件内有效；静态局部变量只在定义它的函数内有效，并且程序仅分配一次内存，函数返回后，该变量不会消失；局部变量在定义它的函数内有效，但是函数返回后失效。

全局变量(外部变量)的说明之前再冠以static 就构成了静态的全局变量。全局变量本身就是静态存储方式， 静态全局变量当然也是静态存储方式。 这两者在存储方式上并无不同。这两者的区别在于非静态全局变量的作用域是整个源程序，当一个源程序由多个源文件组成时，非静态的全局变量在各个源文件中都是有效的。 而静态全局变量则限制了其作用域， 即只在定义该变量的源文件内有效， 在同一源程序的其它源文件中不能使用它。由于静态全局变量的作用域局限于一个源文件内，只能为该源文件内的函数公用， 因此可以避免在其它源文件中引起错误。
从以上分析可以看出，把局部变量改变为静态变量后是改变了它的存储方式即改变了它的生存期。把全局变量改变为静态变量后是改变了它的作用域，限制了它的使用范围。

static函数与普通函数作用域不同，只在定义该变量的源文件内有效。只在当前源文件中使用的函数应该说明为内部函数(static)，内部函数应该在当前源文件中说明和定义。对于可在当前源文件以外使用的函数，应该在一个头文件中说明，要使用这些函数的源文件要包含这个头文件。
static全局变量与普通的全局变量有什么区别：static全局变量只初使化一次，防止在其他文件单元中被引用;

static局部变量和普通局部变量有什么区别：static局部变量只被初始化一次，下一次依据上一次结果值；

static函数与普通函数有什么区别：static函数与普通函数作用域不同，只在定义该变量的源文件内有效；

全局变量和静态变量如果没有手工初始化，则由编译器初始化为0。局部变量的值不可知。

需要注意的是：静态数据成员不能在类中初始化，一般在类外和main()函数之前初始化，缺省时初始化为0。

1.static成员的所有者是类本身，但是多个对象拥有一样的静态成员。从而在定义对象是不能通过构造函数对其进行初始化。

2.静态成员不能在类定义里边初始化，只能在class body外初始化。
3.静态成员仍然遵循public，private，protected访问准则。
4.静态成员函数没有this指针，它不能返回非静态成员，因为除了对象会调用它外，类本身也可以调用


C++静态成员变量的初始化:
静态成员属于全局变量，是所有实例化以后的对象所共享的，而成员的初始化你可以想象成向系统申请内存存储数据的过程，显然这种共有对象。不能在任何函数和局部作用域中初始化。

```cpp
class point {
public:
    point() {};
//	...
private:
    static int x, y;
};

int point::x = 0;
int point::y = 0;

int main() {
//	...
}
```

[![top] Goto Top](#table-of-contents)

## 80_类的友元
友元函数在某些时候可以提高代码运行效率。比如在游戏中不断获取某两个点并计算距离，若不用友元函数时，就要每次get_x，get_y，然后计算，很麻烦。但是在类中public声明`friend float dist(Point &a, Point &b);`，则该函数可访问私有成员点的x、y坐标值，会提高效率，但该友元函数本身并不是类的成员。

也可以将类设置为友元以达到访问私有数据成员的目的：
```cpp
#include <iostream>

class A {
    friend class B;

public:
    void display() {
        std::cout << x << std::endl;
    }

private:
    int x;
};


class B {
public:
    void set(int i);

    void display();

private:
    A a;
};

void B::set(int i) {
    a.x = i;
}

void B::display() { a.display(); }
```
友元是单向的，且改行为破坏数据的封装，要慎用`friend`

[![top] Goto Top](#table-of-contents)

## 81_共享数据的保护

`A const a(2,3)` 常对象，不能被更新。

const也是区分重载函数的因素之一。

`const R b(20, 30);`意为该对象为`const`不可被修改，该对象只能调用常成员函数，非常对象也可以调用常成员函数。

类中含常数据成员：
```cpp
class A{
    private:
    const int a;
    static const int b;
}
```
常成员一旦初始化就无法修改。`b`的初始化在类外，`const int A::b=10;`，`a`在构建每个对象时初始化，必须在初始化列表中进行，`A::A(int i):a(i(){}`，如果不是常成员的话，既可以在初始化列表中初始化，也可以在函数体中进行赋值。

常引用：只读引用。`float dist(const Point &p1, const Point &p2){...}`

使用其他文件中定义的变量：extern关键字，外部变量，即不在本程序文件中定义的变量，

外部变量：
除了在定义它的源文件中可以使用外还能被其它文件使用。文件作用域中定义的变量默认情况下都是外部变量。在其它文件中如果需要使用需要用 `extern` 关键字声明。

外部函数：
在所有类之外声明的函数（也就是非成员函数），都是具有文件作用域的。这样的函数都可以在不同的编译单元中被调用
只要在调用之前进行引用性声明（即声明函数原型）即可。

[![top] Goto Top](#table-of-contents)

## 91_基于范围的for循环

一般for：
```cpp
int main() {
    int array[3] = {1, 3, 4};
    int *p;
    for (p = array; p < array + sizeof(array) / sizeof(int); ++p) {
        *p += 2;
        std::cout << *p << std::endl;
    }
    return 0;
}
```
c++11中：
```cpp
int main() {
    int array[3] = {1, 3, 4};
    for (int &e: array) {
        e += 2;
        std::cout << e << std::endl;
    }
    return 0;
}
```
这样避免了需要知道数组尺寸的不便。处理容器类更为便利。


[![top] Goto Top](#table-of-contents)

## 93_指针变量的初始化和赋值
注意事项：
- 用变量地址作为初值时，该变量必须在指针初始化之前已经声明过，且变量类型应与指针类型一直
- 可以用一个已有合法值的指针去初始化另一个指针变量
- 不要用一个内部非静态变量去初始化static指针

指针空值：nullptr

[![top] Goto Top](#table-of-contents)

## 97_指针数组
指针数组很多时候可以代替二维数组，而且很多时候更为好用，因为二维数组无法解决尺寸不规则的二维数组。cherno也讲过相同内容，不仅仅代码中好用，更多的是性能上的考虑。

```cpp

int main() {
    int line[] = {1, 0, 0};
    int line2[] = {0, 1, 0};
    int line3[]{0, 0, 1};

    int *pLine[3] = {line, line2, line3};
    std::cout << "Matrix :" << std::endl;

    for (int i = 0; i <3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout<<pLine[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
```

[![top] Goto Top](#table-of-contents)

## 98_以指针作为函数参数

为什么需要用指针做参数？
- 需要数据双向传递时（引用也可以达到此效果）
- 需要传递一组数据，只传首地址运行效率比较高

另外，在程序中不要比较两个浮点数是否相等，如`13.2`，在debug模式下可看到实际存储的是`13.2000002`，若需要比较两个浮点数，建议相减然后规定精确度如小数点后几个零来比较。

[![top] Goto Top](#table-of-contents)

## 99_指针类型的函数

不要将非静态局部地址用作函数的返回值。错误实例：
```cpp
int *function() {
    int local = 0;
    return &local;
}

int main() {

    int *ptr = function();
    *ptr = 5;//危险的操作
    return 0;
}
```

正确的例列子
1. 主函数中定义的数组，在子函数中对该数组元素进行某种操作后，返回其中一个元素的地址，这就是合法有效的地址
```cpp
int *search(int *a, int num) {
    for (int i = 0; i < num; ++i) {
        if (a[i] == 0)
            return &a[i];
    }
}//函数运行结束时，a[i]的地址仍有效

int main() {
    int array[10];

    for (int i = 0; i < 10; ++i)
        std::cin >> array[i];
    int *zeroptr = search(array, 10);
    return 0;
}
```

2. 在子函数中通过动态内存分配 new 操作取得的内存地址返回给主函数是合法有效的，但是内存分配和释放不在同一级别，要注意不能忘记释放，避免内存泄漏：
```cpp
int *newintvar() {
    int *p = new int();
    return p;//返回的地址指向的是动态分配的空间
}//函数运行结束时，p中地址仍有效

int main() {
    int *intptr = newintvar();
    *intptr = 5;
    delete intptr;//内存释放
    return 0;
}
```

[![top] Goto Top](#table-of-contents)

## 100_指向函数的指针
函数指针的定义：存储类型 数据类型 (*函数指针名)()
(*函数指针名)//说明在定义的是一个指针，如果没有括号则是指针类型的函数，返回值是指针，所以这个括号非常重要，存储类型是值函数返回值是什么类型
含义：函数指针指向的是程序代码存储区

为什么需要这样定义？为什么不直接通过函数名来访问函数？

- 函数指针的典型用途一实现函数回调通过函数指针调用的函数
    -例如将函数的指针作为参数传递给一个函数，使得在处理相似事件的时候可以灵活的使用不同的方法。
    
- 调用者不关心谁是被调用者
    - 需知道存在一个具有特定原型和限制条件的被调用函数。

函数指针举例：
- 编写一个计算函数 compute，对两个整数进行各种计算。有一个形参为指向具体算法函数的指针，根据不同的实参函数，用不同的算法进行计算。
- 编写三个函数：求两个整数的最大值、最小值、和。分别用这三个函数作为实参，测试 compute 函数。

```cpp

int compute(int a, int b, int(*func)(int, int)) { return func(a, b); }

int max(int a, int b) { return ((a > b) ? a : b); }

int min(int a, int b) { return ((a < b) ? a : b); }

int sum(int a, int b) { return a + b; }

int main() {
    int a, b, res;
    std::cout << "请输入整数a：";
    std::cin >> a;
    std::cout << "请输入整数b：";
    std::cin >> b;

    res = compute(a, b, &max);//只写函数名也是可以的，但是为了代码可读性写上更好
    std::cout << "Max of " << a << " and " << b << " is " << res << std::endl;
}
```

[![top] Goto Top](#table-of-contents)

## 101_对象指针

定义： 类名 *对象指针名
```cpp
Point a(5, 10);
Point *ptr;
ptr = &a;
```
访问成员：`prt->getx();`相当于`(*ptr).getx();`

This 指针：
- 隐含于类的每一个非静态成员函数中。
- 指出成员函数所操作的对象。
    - 当通过一个对象调用成员函数时，系统先将该对象的地址赋给 this 指针，然后调用成员函数，成员函数对对象的数据成员进行操作时就隐含使用了 this 指针。

- 例如，Point 类的 getX 函数中的语句：
return x;
相当于：
return this-> x;

在此之前错误的例子：
```cpp
class Fred;//向前引用声明
class Barney{
    Fred x;//错误，类Fred的声明尚不完善
};
class Fred{
    Barney y;
};
```
解决方案：
```cpp
class Fred;
class Barney{
    Fred *x;//错误，类Fred的声明尚不完善
};
class Fred{
    Barney y;
};
```
然后紧接着new一个Fred对象，将其收地址赋值给x指针，就可以达到在Bareny类中有Fred对象。其实这样需求很少，这段代码仅为了说明语法。

[![top] Goto Top](#table-of-contents)

## 102_动态分配与释放内存
delete操作符是删除指针所指向的内容，而不是删除指针自己，该指针仍可以继续赋值使用

[![top] Goto Top](#table-of-contents)

##  103_申请和释放动态数组01
```cpp
    char (*fp)[3] = new char[2][3];
    fp[0][2]='hell';
```

fp->    fp[0][0]
          [0][1]
          [0][2]
fp+1 -> fp[1][0]
          [1][1]
          [1][2]
        
可以看出fp指向每一行的首地址。三维数组较为麻烦，建议看cherno的方法。

[![top] Goto Top](#table-of-contents)

## 104_申请和释放动态数组02

将动态数组封装成类
- 更加简洁便于管理
- 可以在访问数组元素前检查下表是否越界

```cpp
#include <iostream>
#include <cassert>

class Point {
public:
    Point() : x(0), y(0) {
        std::cout << "Default Constructor called. " << std::endl;
    }

    Point(int x, int y) : x(x), y(y) {
        std::cout << "Constructor called. " << std::endl;
    }

    ~Point() { std::cout << "Destructor called. " << std::endl; }

    int getX() const { return x; }

    void move(int newX, int newY) {
        x = newX;
        y = newY;
    }

private:
    int x, y;

};


class ArrayOfPoints {
public:
    ArrayOfPoints(int size) : size(size) {
        points = new Point[size];
    }

    ~ArrayOfPoints() {
        std::cout << "Deleting..." << std::endl;
        delete[] points;
    }

    Point &element(int index) {//返回引用的意思
        assert(index >= 0 && index < size);
        return points[index];
    }

private:
    Point *points;
    int size;
};


int main() {
    int count;
    std::cout << "please enter the count of points: ";
    std::cin >> count;
    ArrayOfPoints points(count);
    points.element(0).move(5, 0);
    points.element(1).move(15, 20);
    return 0;

}
```
上例请注意为什么element函数返回对象的引用？
希望move点(对象)本身而不是点的副本。若是返回对象，则是副本。

[![top] Goto Top](#table-of-contents)

## 105_智能指针

- Unique_ptr
    不允许多个指针共享资源，可以用标准库中的 move 函数转移指针
- shared_ptr
    多个指针共享资源
- weak_ptr
    可复制 shared_ptr，但其构造或者释放对资源不产生影响

[![top] Goto Top](#table-of-contents)

## 106_vector对象

定义：`vector<double> arr(n)`，使用`arr[0]=1.2`，通过下标来访问数组是因为重载了下标运算符

基于范围的for循环:
```cpp
    std::vector<int> v = {1, 2, 3};
    for (auto i = v.begin(); i != v.end(); i++) {
        std::cout << *i << std::endl;
    }
    std::cout<<"-------------------"<<std::endl;
    for (auto e: v) {
        std::cout << e << std::endl;
    }
```

[![top] Goto Top](#table-of-contents)

## 108_移动构造
c++11引入移动语义：源对象资源的控制权全部交给目标对象
当临时对象在被复制后就不再被利用了，我们就把临时对象的资源直接移动，这样避免了多余的复制操作。

```cpp
#include <iostream>

class Point {
public:
    Point() : x(0), y(0) {
        std::cout << "Default Constructor called. " << std::endl;
    }

    Point(int x, int y) : x(x), y(y) {
        std::cout << "Constructor called. " << std::endl;
    }

    ~Point() { std::cout << "Destructor called. " << std::endl; }

    int getX() const { return x; }

    void move(int newX, int newY) {
        x = newX;
        y = newY;
    }

private:
    int x, y;

};


class ArrayOfPoints {
public:
    ArrayOfPoints(int size) : size(size) {
        points = new Point[size];
    }

    ~ArrayOfPoints() {
        std::cout << "Deleting..." << std::endl;
        delete[] points;
    }

    Point &element(int index) {//返回引用的意思
        assert(index >= 0 && index < size);
        return points[index];
    }

private:
    Point *points;
    int size;
};

class IntNum {
public:
    IntNum(int x = 0) : xptr(new int(x)) {
        //构造函数
        std::cout << "Calling constructor..." << std::endl;
    }

    IntNum(const IntNum &n) : xptr(new int(*n.xptr)) {
        //复制构造函数
        std::cout << "Calling copy constructor..." << std::endl;
    }


    //移动构造函数
    IntNum(IntNum &&n) : xptr(n.xptr) {//两个&&表示右值引用，表示即将消亡的值
        n.xptr = nullptr;//看似浅层复制，但是这里将指针置空，将来delete时不回出现问题
        std::cout << "Calling move constructor..." << std::endl;
    }


    ~IntNum() {
        //析构函数
        delete xptr;
        std::cout << "Destructing..." << std::endl;
    }

    int getInt() { return *xptr; }//返回指针所指内容

private:
    int *xptr;
};

IntNum getNum() {
    IntNum a;//这里会调用构造函数
    return a;//这里会调用复制构造函数
    //离开函数时释放内存，删除临时对象，调用析构函数
}

int main() {
    std::cout << getNum().getInt() << std::endl;//当没有移动构造函数时调用复制，否则调用移动
    return 0;
}
```

[![top] Goto Top](#table-of-contents)

## 109_c风格字符串

```cpp
    char str1[8]={'p','r','o','g','r','a','m','\0'};
    char str2[8]={"program"};
    char str3[]={'p','r','o','g','r','a','m'};
```
总之较为繁琐，不建议使用。

[![top] Goto Top](#table-of-contents)

## 110_string类

c++标准库里封装起来的字符串类，字符数组，较为好用。

常用操作很多，s + t，连接成新串之类，s == t，判断是否相等...

getline可以输入整行字符，要包含string头文件，如`getline(cin, s2)`，也可以从io流中读入，也可以设置第三个参数作为分隔符，如`getline(cin, s2, ',');`

[![top] Goto Top](#table-of-contents)

## 116_继承的基本概念和语法
继承与派生概述：
- 继承与派生是同一过程从不同的角度看
    - 保持已有类的特性而构造新类的过程称为继承。
    - 在已有类的基础上新增自己的特性而产生新类的过程称为派生。
- 被继承的已有类称为基类（或父类）。
- 派生出的新类称为派生类（或子类）
- 直接参与派生出某类的基类称为直接基类。
- 基类的基类甚至更高层的基类称为间接基类。

吸收基类成员：
- 默认情况下派生类包含了全部基类中除构造和析构函数之外的所有成员。（默认情况下不继承构造函数和析构函数）
- C++11 规定可以用 using 语句继承基类构造函数。


改造基类成员：
- 如果派生类声明了一个和某基类成员同名的新成员，派生的新成员就隐藏或覆盖了外层同名成员

添加新的成员：
- 派生类增加新成员使派生类在功能上有所发展

[![top] Goto Top](#table-of-contents)

## 117_继承方式简介及公有继承

不同继承方式的影响主要体现在
- 派生类成员对基类成员的访问权限
- 通过派生类对象对基类成员的访问权限。

[![top] Goto Top](#table-of-contents)

## 118_私有继承和保护继承

私有继承（private)
- 继承的访问控制
    - 基类的 public 和 protected成员：都以 orivate 身份出现在派生类中；
    - 基类的 private 成员：不可直接访问。

- 访问权限
- 派生类中的成员函数：可以直接访问基类中的 public 和protected 成员，但不能直接访问基类的 orivate 成员；
- 通过派生类的对象：不能直接访问从基类继承的任何成员。

用的不多，将基类所有接口都封装掉的效果


保护继承（protected)
- 继承的访问控制
    - 基类的 publici 和 protected，成员：都以 protected。身份出现在派生类中基类的
    - private 成员：不可直接访问。
- 访问权限
    - 派生类中的成员函数：可以直接访问基类中的 publici 和protected，成员，但不能直接访问基类的private 成员；
    - 通过派生类的对象：不能直接访问从基类继承的任何成员。

[![top] Goto Top](#table-of-contents)

## 119_基类与派生类类型转换

类型转换
- 公有派生类对象可以被当作基类的对象使用，反之则不可。
    - 派生类的对象可以隐含转换为基类对象；
    - 派生类的对象可以初始化基类的引用；
    - 派生类的指针可以隐含转换为基类的指针。
- 通过基类对象名、指针只能使用从基类继承的成员。

派生类地址可以初始化基类指针
```cpp
class Base1{};
class Base2:public Base1{};
class Base3:public Base2{};

void fun(Base1 *ptr){
    ...
}
```
直接定义继承而来的函数会导致无法访问等错误信息，所以不要重新定义继承而来的非虚函数。

[![top] Goto Top](#table-of-contents)

## 120_派生类的构造函数

默认情况下：
- 基类的构造函数不被继承
- 派生类需要定义自己的构造函数

C++11 规定（适用情况，派生来很少或者不增加新的数据成员，因为这样只能初始化基类继承来的数据成员）：
- 可用 using 语句继承基类构造函数；
- 但是只能初始化从基类继承的成员。
- 语法形式：·using B: B;
- 若新增成员，则要通过类内初始化

若不继承基类的构造函数：
- 派生类新增成员：派生类定义构造函数初始化；
- 继承来的成员：自动调用基类构造函数进行初始化；
- 派生类的构造函数需要给基类的构造函数传递参数。


单继承时构造函数语法：
```cpp
派生类名::派生类名(基类所需的形参, 本类成员所需的形参):
    基类名(参数表), 本类成员初始化列表 
    {
        //其他初始化
    }
```

多继承时构造函数的定义语法：
```cpp
派生类名:派生类名（参数表）:
    基类名 1(基类 1 初始化参数表)
    基类名 2(基类 2 初始化参数表),
    ...
    基类名 n(基类 n 初始化参数表)
本类成员初始化列表
{
    //其他初始化；
};
```

派生类与基类的构造函数：
- 当基类有默认构造函数时
  - 派生类构造函数可以不向基类构造函数传递参数。
  - 构造派生类的对象时，基类的默认构造函数将被调用。

- 如需执行基类中带参数的构造函数
    -派生类构造函数应为基类构造函数提供参数。

多继承且有对象成员时派生的构造函数定义语法:
```cpp
派生类名::派生类名(形参表):
    基类名1(参数)，基类名 2(参数),...,基类名 n(参数),
    本类成员(含对象成员)初始化列表
{
    //其他初始化
}
```

构造函数的执行顺序:
1. 调用基类构造函数。
- 顺序按照它们被继承时声明的顺序（从左向右）。
2. 对初始化列表中的成员进行初始化。
- 顺序按照它们在类中定义的顺序。
- 对象成员初始化时自动调用其所属类的构造函数。
    -由初始化列表提供参数。
3. 执行派生类的构造函数体中的内容。

若派生类定义复制构造函数
- 一般都要为基类的复制构造函数传递参数。
- 复制构造函数只能接受一个参数，既用来初始化派生类定义的成员，也将被传递给基类的复制构造函数。
- 基类的复制构造函数形参类型是基类对象的引用，实参可以是派生类对象的引用。
- 例如：`C:: C (const C &c1): B (c1) {... }`

[![top] Goto Top](#table-of-contents)

## 122_派生类的复制构造函数
若派生类没有声明复制构造函数：
- 编译器会在需要时生成一个隐含的复制构造函数
- 先调用基类的复制构造函数；
- 再为派生类新增的成员执行复制。


若派生类定义复制构造函数：
- 一般都要为基类的复制构造函数传递参数。
- 复制构造函数只能接受一个参数，既用来初始化派生类定义的成员，也将被传递给基类的复制构造函数。
- 基类的复制构造函数形参类型是基类对象的引用，实参可以是派生类对象的引用。
- 例如：C:: C (const C &c1): B (c1) {... }

[![top] Goto Top](#table-of-contents)

## 123_派生类的析构函数
- 析构函数不被继承，派生类如果需要要自行声明析构函数。
- 声明方法与无继承关系时类的析构函数相同。
- 不需要显式地调用基类的析构函数系统会自动隐式调用。(和构造函数执行顺序相反，析构先执行本类的析构函数，再调用基类的析构函数)
- 先执行派生类析构函数的函数体再调用基类的析构函数。

[![top] Goto Top](#table-of-contents)

## 124_访问从基类继承的成员
当派生类与基类中有相同成员时:
- 若未特别限定，则通过派生类对象使用的是派生类中的同名成员
- 如要通过派生类对象访问基类中被隐藏的同名成员，应使用基类名和作用域操作符(::)来限定。


二义性问题：
- 如果从不同基类继承了同名成员，但是在派生类中没有定义同名成员，“派生类对象名或引用名.成员名”、“派生类指针->成员名”访问成员存在二义性问题
- 解决方式：用类名限定。

个人感觉自找麻烦，少弄些重名函数不就完了，如果实在都是重名的，那就类名限定即可。

[![top] Goto Top](#table-of-contents)

## 125_虚基类

需要解决的问题：
- 当派生类从多个基类派生，而这些基类又有共同基类，则在访问此共同基类中的成员时，将产生冗余，并有可能因冗余带来不一致性。

虚基类声明：
- 以 virtuali 说明基类继承方式 例：`class B1: virtual public B`

作用：
- 主要用来解决多继承时可能发生的对同一基类继承多次而产生的二义性问题；
- 为最远的派生类提供唯一的基类成员，而不重复产生多次复制(冗余)。

注意：
- 在第一级继承时就要将共同基类设计为虚基类。

虚基类及其派生类构造函数
- 建立对象时所指定的类称为**最远派生类**。
- 虚基类的成员是由最远派生类的构造函数通过调用虚基类的构造函数进行初始化的
- 在整个继承结构中，直接或间接继承虚基类的所有派生类都必须在构造函数的成员初始化表中为虚基类的构造函数列出参数。如果未列出，则表示调用该虚基类的默认构造函数。
- 在建立对象时，只有最远派生类的构造函数调用虚基类的构造函数，其他类对虚基类构造函数的调用被忽略。

虚基类为了解决二义性和冗余问题。

```cpp
#include <iostream>

class Base0 {
public:
    Base0(int var) : var0(var) {}

    int var0;

    void fun0() { std::cout << "Member of Base0" << std::endl; }
};

class Base1 : virtual public Base0 {
public:
    Base1(int var) : Base0(var) {}

    int var1;
};

class Base2 : virtual public Base0 {
public:
    Base2(int var) : Base0(var) {}
};

class Derived : public Base1, public Base2 {
public:
    Derived(int var) : Base0(var), Base1(var), Base2(var) {}

    int var;

    void fun() { std::cout << "Member of Derived" << std::endl; }
};


int main() {
    Derived d(1);
    d.var0 = 2;//直接访问虚基类的数据成员
    d.fun0();//直接访问虚基类的函数成员

    return 0;
}
```
重点关注Derived类的构造函数的传参，Derived也就是所谓的最远的派生类。

[![top] Goto Top](#table-of-contents)

## 130_运算符重载的规则

不能重载的运算符:`.`、`.*`、`::`、`?:`

## 131_双目运算符重载为成员函数
语法:
```cpp
函数类型 operator 运算符(形参)
{
    ......
}
```
参数个数 = 原参数个数 - 1(后置++、--除外)

运算所需变量为两个的运算符叫做双目运算符，或者要求运算对象的个数是2的运算符称为双目运算符。

[![top] Goto Top](#table-of-contents)

## 134_虚函数

```cpp
class Base1 {
public:
    virtual void display() const;//虚函数
};

void Base1::display() const {
    std::cout << "Base1::display()" <<
              std::endl;
};
```
virtual在这里意为虚函数，告诉编译器，凡是遇到这样的原型函数，不要在编译的时候马上做决定要调用哪个函数的函数体，滞后，不要在编译阶段做静态绑定，要在运行阶段做动态绑定。所以virtual函数不能弄成内联函数，内联函数实现在静态编译时。


初识虚函数：
- 用 virtual 关键字说明的函数
- 虚函数是实现运行时多态性基础
- C++中的虚函数是动态绑定的函数
- 虚函数必须是非静态的成员函数，虚函数经过派生之后，就可以实现运行过程中的多态。

什么函数可以是虚函数：
- 一般成员函数可以是虚函数
- 构造函数不能是虚函数
- 析构函数可以是虚函数

一般虚函数成员
- 虚函数的声明:`virtual 函数类型 函数名(形参表)；`
- 虚函数声明只能出现在类定义中的函数原型声明中而不能在成员函数实现的时候。
- 在派生类中可以对基类中的成员函数进行覆盖。
- 虚函数一般不声明为内联函数，因为对虚函数的调用需要动态绑定，而对内联函数的处理是静态的。

Virtual 关键字小结：
- 派生类可以不显式地用 virtua 声明虚函数，这时系统就会用以下规则来判断派生类的一个函数成员是不是虚函数：
    - 该函数是否与基类的虚函数有相同的名称、参数个数及对应参数类型
    - 该函数是否与基类的虚函数有相同的返回值或者满足类型兼容规则的指针、引用型的返回值；
- 如果从名称、参数及返回值三个方面检查之后，派生类的函数满足上述条件，就会自动确定为虚函数。这时，派生类的虚函数便覆盖了基类的虚函数。
- 派生类中的虚函数还会隐藏基类中同名函数的所有其它重载形式。
- 一般习惯于在派生类的函数中也使用 virtual 关键字，以增加程序的可读性。

[![top] Goto Top](#table-of-contents)

## 136_虚函数与动态绑定

虚表
- 每个多态类有一个虚表（virtual table）
- 虚表中有当前类的各个虚函数的入口地址
- 每个对象有一个指向当前类的虚表的指针（虚指针 vptr)

动态绑定的实现
- 构造函数中为对象的虚指针赋值
- 通过多态类型的指针或引用调用成员函数时，通过虚指针找到虚表，进而找到所调用的虚函数的入口地址
- 通过该入口地址调用虚函数

[![top] Goto Top](#table-of-contents)

## 137_抽象类

纯虚函数
- 纯虚函数是一个在基类中声明的虚函数，它在该基类中没有定义具体的操作内容，要求各派生类根据实际需要定义自己的版本纯虚函数的声明格式为：`virtual 函数类型函数名(参数表)=O;`

语法：
```cpp
class 类名
{
    virtual 类型 函数名(参数表) = 0;
    //其他成员...
}
```

抽象类作用：
- 将有关的数据和行为组织在一个继承层次结构中，保证派生类具有要求的行为。
- 对于暂时无法实现的函数，可以声明为纯虚函数，留给派生类去实现。
注意：
- 抽象类只能作为基类来使用。
- 不能定义抽象类的对象。

[![top] Goto Top](#table-of-contents)

## 138_override与final

Override：
- 多态行为的基础：基类声明虚函数，派生类声明一个函数覆盖该虚函数；
- 覆盖要求：函数签名（signature）完全一致。
- 函数签名包括：`函数名 参数列表 const`


- C++11 引入显式函数覆盖，在编译期而非运行期捕获此类错误。
- 在虚函数显式重载中运用，编译器会检查基类是否存在一虚拟函数，与派生类中带有声明 override 的虚拟函数，有相同的函数签名（signature）；若不存在，则会回报错误。

```cpp
struct Base1 final {
};
struct Derived1 : Base1 {
};//编译错误，Base1为final，不允许被继承
```
`error: base 'Base1' is marked 'final'`

```cpp
struct Base2 {
    virtual void f() final;
};

struct Derived2 : Base2 {
    void f();//编译错误，Base2::f为final，不允许被覆盖
};
```
[![top] Goto Top](#table-of-contents)


## 161_范性程序设计的基本概念

泛型程序设计：
- 编写不依赖于具体数据类型的程序
- 将算法从特定的数据结构中抽象出来成为通用的
- C++的模板为泛型程序设计奠定了关键的基础

术语：概念
- 用来界定具备一定功能的数据类型。例如：
  - 将“可以比大小的所有数据类型（有比较运算符）”这一概念记为 Comparable
  - 将“具有公有的复制构造函数并可以用‘='赋值的数据类型”这一概，念记为 Assignable
  - 将“可以比大小、具有公有的复制构造函数并可以用'='赋值的所有数据类型”这个概念记作 Sortable
- 对于两个不同的概念 A 和 B，如果概念 A 所需求的所有功能也是概，念 B 所需求的功能，那么就说概念 B 是概念 A 的子概念。例如：
  - Sortablel 既是 Comparablel 的子概念，也是 Assignable 的子概，念


术语：模型
- 模型（mode!）：符合一个概念的数据类型称为该概念的模型，例如：
    - int 型是 Comparable 概念的模型
    - 静态数组类型不是 Assignablef 概念的模型（无法用“=”给整个静态数组赋值）

用概念做模版参数名：很多STL的实现代码就是使用概念来命名模版参数的

用概念做模板参数名：
- 为概念赋予一个名称，并使用该名称作为模板参数名
- 例如：表示 insertionSort 这样一个函数模板的原型：
    ```cpp
    template  <class Sortable>
    void insertionSort (Sortable a[], int n);
    ```

[![top] Goto Top](#table-of-contents)

## 162_STL简介

STL 简介：
- 标准模板库（Standard Template Library，简称 STL）定义了一套概念体系，为泛型程序设计提供了逻辑基础
- STL 中的各个类模板、函数模板的参数都是用这个体系中的概念来规定的。
- 使用 STL 的模板时，类型参数既可以是 C++标准库中已有的类型，也可以是自定义的类型一只要这些类型是所要求概念的模型。

STL 的基本组件
- 容器（container)
- 迭代器（iterator)
- 函数对象（function object）
- 算法（algorithms)

STL 的基本组件
- Iterators（迭代器）是算法和容器的桥梁
    - 将迭代器作为算法的参数、通过迭代器来访问容器而不是把容器直接作为算法的参数。
- 将函数对象作为算法的参数而不是将函数所执行的运算作为算法的一部分。
- 使用 STL 中提供的或自定义的迭代器和函数对象，配合 STL 的算法，可以组合出各种各样的功能。

STL 的基本组件—容器（container)
- 容纳、包含一组元素的对象。
- 基本容器类模板
    - 顺序容器
    array（数组）、vector（向量）、deque（双端队列）、forward list（单链表）、Iist（列表）
    - （有序）关联容器
    set（集合）、multiset（多重集合）、map（映射）、multimap（多重映射）
    - 无序关联容器
    unordered_set（无序集合）、unordered_multiset（无序多重集合）unordered_map（无序映射）、unorder_multimap（无序多重映射）

容器适配器(使用容器，需要包涵对应的头文件)
- stack（栈）
- queue（队列）
- priority_queue（优先队列）

STL 的基本组件一迭代器（iterator）
- 提供了顺序访问容器中每个元素的方法
- 可以使用”++”运算符来获得指向下一个元素的迭代器；
- 可以使用”*”运算符访问迭代器所指向的元素，如果元素类型是类或结构体，还可以使用”->”运算符直接访问该元素的一个成员
- 有些迭代器还支持通过”--”运算符获得指向上一个元素的
- 迭代器迭代器是泛化的指针：指针也具有同样的特性，因此指针本身就是一种迭代器；
- 使用独立于 STL 容器的迭代器，需要包含头文件<iterator>。


STL 的基本组件一函数对象（function object)
- 一个行为类似函数的对象，对它可以像调用函数一样调用。
- 函数对象是泛化的函数：任何普通的函数和任何重载了“()”运算符的类的对象都可以作为函数对像使用
- 使用 STL 的函数对象，需要包含头文件<functional>


STL 的基本组件一算法（algorithms）
- 可以广泛用于不同的对象和内置的数据类型。
- STL 包括 70 多个算法
    - 例如：排序算法，消除算法，计数算法，比较算法，变换算法，置换算法和容器管理等使用 STL 的算法，需要包含头文件<algorithm>

```cpp
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

int main(){
    const int N =5;
    std::vector<int>s(N);//n容器
    for (int i = 0; i < N; ++i) {
        std::cin>>s[i];
        std::transform(s.begin(),s.end(), std::ostream_iterator<int>(std::cout,""),std::negate<int>());
        //transform为算法，negate为函数对象，s.begin()、s.end()、ostream_iterator为迭代器
        std::cout<<std::endl;
        return 0;
    }
}
```
transrorm算法：
```cpp
template <class _InputIterator, class _OutputIterator, class _UnaryOperation>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
_OutputIterator
transform(_InputIterator __first, _InputIterator __last, _OutputIterator __result, _UnaryOperation __op)
{
    for (; __first != __last; ++__first, (void) ++__result)
        *__result = __op(*__first);
    return __result;
```
- Transform：算法顺序遍历 first 和 last 两个迭代器所指向的元素；
- 将每个元素的值作为函数对象 op 的参数；
- 将 op 的返回值通过迭代器 result 顺序输出
- 遍历完成后 result 迭代器指向的是输出的最后一个元素的下一个位置 transform 会将该迭代器返回

[![top] Goto Top](#table-of-contents)

## 163_迭代器

- 迭代器是算法和容器的桥梁
    - 迭代器用作访问容器中的元素
    - 算法不直接操作容器中的数据，而是通过迭代器间接操作
- 算法和容器独立
    - 增加新的算法，无需影响容器的实现
    - 增加新的容器，原有的算法也能适用

输入流迭代器和输出流迭代器
- 输入流迭代器：`istream iterator <T>`
    - 以输入流（如 cin）为参数构造
    - 可用* (p++）获得下一个输入的元素
- 输出流迭代器`ostream iterator <T>`
    - 构造时需要提供输出流（如 cout）
    - 可用（*p++) =x 将 x 输出到输出流
- 二者都属于适配器
    - 适配器是用来为已有对象提供新的接口的对象
    - 输入流适配器和输出流适配器为流对象提供了迭代器的接口


```cpp
#include <iostream>
#include <iterator>
#include <algorithm>
double square(double x) {
    return x * x;
}

int main() {
    //从标准输入读入若干实数，分别将平方输出
    std::transform(std::istream_iterator<double>(std::cin),
                   std::istream_iterator<double>(),
                   std::ostream_iterator<double>(std::cout, "\t"), square);
    return 0;
};
```

迭代器支持的操作:
- 迭代器是泛化的指针，提供了类似指针的操作(诸如++、*、->运算符)
- 输入迭代器
    - 可以用来从序列中读取数据，如输入流迭代器
- 输出迭代器
    - 允许向序列中写入数据，如输出流迭代器
- 前向迭代器
    - 既是输入迭代器又是输出迭代器，并且可以对序列进行单向的遍历
- 双向迭代器
    - 与前向迭代器相似，但是在两个方向上都可以对数据遍历
- 随机访问迭代器
    - 也是双向迭代器，但能够在序列中的任意两个位置之间进行跳转如指针、使用 vector 的 begin()、end() 函数得到的迭代器


迭代器的区间
- 两个迭代器表示一个区间：[p1, p2)
- STL 算法常以迭代器的区间作为输入，传递输入数据
- 合法的区间
  - p1 经过 n 次(n>0) 自增(++)操作后满足 p1==p2 区间包含 p1, 但不包含 p2

---
STL库另作篇章，在此部分不再详谈。
---

[![top] Goto Top](#table-of-contents)



## 179_I/O流的概念及流类库结构
流对象与文件操作
- 程序建立一个流对象
- 指定这个流对象与某个文件对象建立连接
- 程序操作流对象
- 流对象通过文件系统对所连接的文件对象产生作用

提取与插入
- 读操作在流数据抽象中被称为（从流中）提取
- 写操作被称为（向流中）插入

## 192_异常处理的思想与程序实现

- 若有异常则通过 throw 创建一个异常对象并抛掷
- 将可能抛出异常的程序段嵌在 try 块之中。通过正常的顺序执行到达 try 语句，然后执行 try 块内的保护段
- 如果在保护段执行期间没有引起异常，那么跟在 try 块后的 catch 子句就不执行。程序从 try 块后的最后一个 catch 子句后面的语句继续执
- catch 子句按其在 try 块后出现的顺序被检查。匹配的 catch 子句将捕获并处理异常(或继续抛掷异常)。
- 如果匹配的处理器未找到，则库函数 terminate 将被自动调用，其缺默认能是调用 abort 终止程序

异常处理语法：
- 抛掷异常的程序段
```cpp
.......
throw 表达式;
.......
```
- 捕获并处理异常的程序段
```cpp
try
    复合语句----保护段
catch(异常声明)
    复合语句----异常处理程序
catch(异常声明)
    复合语句
    ...
```
示例，处理除零异常

```cpp
#include <iostream>

int divide(int x, int y) {
    if (y == 0)
        throw x;
    return x / y;
}

int main() {
    try {
        std::cout << "5 / 2 = " << divide(5, 2) << std::endl;
        std::cout << "8 / 0 = " << divide(8, 0) << std::endl;
        std::cout << "7 / 1 = " << divide(7, 1) << std::endl;
    } catch (int e) {
        std::cout << e << "is divide by zere!" << std::endl;
    }
    std::cout << "That is ok." << std::endl;

    return 0;
};
```
运行结果：
```bash
5 / 2 = 2
8 / 0 = 8is divide by zere!
That is ok.
```

异常接口声明:
- 可以在函数的声明中列出这个函数可能抛掷的所有异常类型
- 例如：`void fun () throw (A B, C, D);`
- 若无异常接口声明，则此函数可以抛掷任何类型的异常。
- 不抛掷任何类型异常的函数声明如下：void fun () throw ();
- 列出异常主要为了方便处理异常信息

## 193_异常处理中的构造与析构

应当将易出问题的代码防在`try`块中，这样当代码出现问题时可以被catch捕获。

自动的析构
- 找到一个匹配的 catch 异常处理后
    - 初始化异常参数。
    - 将从对应的 try 块开始到异常被抛掷处之间构造(且尚未析构)的所有自动对象进行析构。
    - 从最后一个 catch 处理之后开始恢复执行。

```cpp
#include <iostream>
#include <string>


class MyException {
public:
    MyException(const std::string &message) : message(message) {}

    ~MyException() {}

    const std::string &getMessage() const { return message; }

private:
    std::string message;
};

class Demo {
public:
    Demo() { std::cout << "Constructor of Demo" << std::endl; }

    ~Demo() { std::cout << "Destructor of Demo" << std::endl; }
};

void func() throw(MyException) {
    Demo d;
    std::cout << "Throw MyException in func()" << std::endl;
    throw MyException("exception thrown by func()");
}

int main() {
    std::cout << "In main function" << std::endl;
    try {
        func();
    } catch (MyException &e) { std::cout << "Caught an exception" << e.getMessage() << std::endl; }
    std::cout << "Resume the execution of main()" << std::endl;

    return 0;
};
```
以上代码适用c++11，并不兼容c++17。以上代码可测试出，先析构，执行抛出异常、处理异常。

## 194_标准程序库异常处理

如有所需，请参照类库。

标准异常类的基础：
- exception：标准程序库异常类的公共基类。
- logic_error 表示可以在程序中被预先检测到的异常
  - 如果小心地编写程序，这类异常能够避免。
- runtime_error 表示难以被预先检测的异常。

[![top] Goto Top](#table-of-contents)