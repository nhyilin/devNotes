# Table of Contents
- [Table of Contents](#table-of-contents)
- [Cherno c++](#cherno-c)
  - [07. How the C++ Linker Works](#07-how-the-c-linker-works)
  - [08. Variables in C++](#08-variables-in-c)
  - [10. C++ Header Files](#10-c-header-files)
  - [11. How to DEBUG C++ in VISUAL STUDIO.mp4](#11-how-to-debug-c-in-visual-studiomp4)
  - [12. CONDITIONS and BRANCHES in C++ (if statements)](#12-conditions-and-branches-in-c-if-statements)
  - [13. BEST Visual Studio Setup for C++ Projects!](#13-best-visual-studio-setup-for-c-projects)
  - [14. Loops in C++ (for loops, while loops)](#14-loops-in-c-for-loops-while-loops)
  - [15. Control Flow in C++ (continue, break, return)](#15-control-flow-in-c-continue-break-return)
  - [16. POINTERS in C++](#16-pointers-in-c)
  - [17. REFERENCES in C++](#17-references-in-c)
  - [18. CLASSES in C++](#18-classes-in-c)
  - [19. CLASSES vs STRUCTS in C++](#19-classes-vs-structs-in-c)
  - [20. How to Write a C++ Class](#20-how-to-write-a-c-class)
  - [21. Static in C++](#21-static-in-c)
  - [22. Static for Classes and Structs in C++](#22-static-for-classes-and-structs-in-c)
  - [23. Local Static in C++](#23-local-static-in-c)
  - [24. ENUMS in C++](#24-enums-in-c)
  - [25. Constructors in C++](#25-constructors-in-c)
  - [26. Destructors in C++](#26-destructors-in-c)
  - [27. Inheritance in C++](#27-inheritance-in-c)
  - [28. Virtual Functions in C++](#28-virtual-functions-in-c)
  - [29. Interfaces in C++ (Pure Virtual Functions)](#29-interfaces-in-c-pure-virtual-functions)
  - [30. Visibility in C++](#30-visibility-in-c)
  - [31. Arrays in C++](#31-arrays-in-c)
  - [32. How Strings Work in C++ (and how to use them)](#32-how-strings-work-in-c-and-how-to-use-them)
  - [33. String Literals in C++](#33-string-literals-in-c)
  - [34. CONST in C++](#34-const-in-c)
  - [35. The Mutable Keyword in C++.srt](#35-the-mutable-keyword-in-csrt)
  - [36. Member Initializer Lists in C++ (Constructor Initializer List)](#36-member-initializer-lists-in-c-constructor-initializer-list)
  - [37. Ternary Operators in C++ (Conditional Assignment)](#37-ternary-operators-in-c-conditional-assignment)
  - [38. How to CREATE INSTANTIATE OBJECTS in C++](#38-how-to-create-instantiate-objects-in-c)
  - [39. The NEW Keyword in C++](#39-the-new-keyword-in-c)
  - [40. Implicit Conversion and the Explicit Keyword in C++](#40-implicit-conversion-and-the-explicit-keyword-in-c)
  - [41. OPERATORS and OPERATOR OVERLOADING in C++](#41-operators-and-operator-overloading-in-c)
  - [42. The 'this' keyword in C++](#42-the-this-keyword-in-c)
  - [43. Object Lifetime in C++ (Stack Scope Lifetimes)](#43-object-lifetime-in-c-stack-scope-lifetimes)
  - [44. SMART POINTERS in C++ (std  unique_ptr, std  shared_ptr, std  weak_ptr)](#44-smart-pointers-in-c-std--unique_ptr-std--shared_ptr-std--weak_ptr)
  - [45. Copying and Copy Constructors in C++](#45-copying-and-copy-constructors-in-c)
  - [46. The Arrow Operator in C++](#46-the-arrow-operator-in-c)
  - [47. Dynamic Arrays in C++ (std  vector)](#47-dynamic-arrays-in-c-std--vector)
  - [48. Optimizing the usage of std  vector in C++](#48-optimizing-the-usage-of-std--vector-in-c)
  - [49. Using Libraries in C++ (Static Linking)](#49-using-libraries-in-c-static-linking)
  - [50. Using Dynamic Libraries in C++](#50-using-dynamic-libraries-in-c)
  - [51. Making and Working with Libraries in C++ (Multiple Projects in Visual Studio](#51-making-and-working-with-libraries-in-c-multiple-projects-in-visual-studio)
  - [52. How to Deal with Multiple Return Values in C++](#52-how-to-deal-with-multiple-return-values-in-c)
  - [53. Templates in C++](#53-templates-in-c)
  - [54. Stack vs Heap Memory in C++](#54-stack-vs-heap-memory-in-c)
  - [55. Macros in C++](#55-macros-in-c)
  - [56. The 'auto' keyword in C++](#56-the-auto-keyword-in-c)
  - [57. Static Arrays in C++ (std  array)](#57-static-arrays-in-c-std--array)
  - [58. Function Pointers in C++](#58-function-pointers-in-c)
  - [59. Lambdas in C++](#59-lambdas-in-c)
  - [60. Why I don't 'using namespace std'](#60-why-i-dont-using-namespace-std)
  - [61. Namespaces in C++](#61-namespaces-in-c)
  - [62. Threads in C++](#62-threads-in-c)
  - [63. Timing in C++.](#63-timing-in-c)
  - [64. Multidimensional Arrays in C++ (2D arrays)](#64-multidimensional-arrays-in-c-2d-arrays)
  - [65. Sorting in C++](#65-sorting-in-c)
  - [66. Type Punning in C++](#66-type-punning-in-c)
  - [67. Unions in C++](#67-unions-in-c)
  - [68. Virtual Destructors in C++](#68-virtual-destructors-in-c)
  - [69. Casting in C++](#69-casting-in-c)
  - [70. Conditional and Action Breakpoints in C++](#70-conditional-and-action-breakpoints-in-c)
  - [71. Safety in modern C++ and how to teach it](#71-safety-in-modern-c-and-how-to-teach-it)
  - [72. Precompiled Headers in C++](#72-precompiled-headers-in-c)
  - [73. Dynamic Casting in C++](#73-dynamic-casting-in-c)
  - [74. BENCHMARKING in C++ (how to measure performance)](#74-benchmarking-in-c-how-to-measure-performance)
  - [75. STRUCTURED BINDINGS in C++](#75-structured-bindings-in-c)
  - [76. How to Deal with OPTIONAL Data in C++](#76-how-to-deal-with-optional-data-in-c)
  - [77. Multiple TYPES of Data in a SINGLE VARIABLE in C++](#77-multiple-types-of-data-in-a-single-variable-in-c)
  - [78. How to store ANY data in C++.mp4](#78-how-to-store-any-data-in-cmp4)
  - [79. How to make C++ run FASTER (with std  async)](#79-how-to-make-c-run-faster-with-std--async)
  - [80. How to make your STRINGS FASTER in C++!](#80-how-to-make-your-strings-faster-in-c)
  - [81. VISUAL BENCHMARKING in C++ (how to measure performance visually)](#81-visual-benchmarking-in-c-how-to-measure-performance-visually)
  - [82. SINGLETONS in C++](#82-singletons-in-c)
  - [83. Small String Optimization in C++](#83-small-string-optimization-in-c)
  - [84. Track MEMORY ALLOCATIONS the Easy Way in C++](#84-track-memory-allocations-the-easy-way-in-c)
  - [85. lvalues and rvalues in C++](#85-lvalues-and-rvalues-in-c)
  - [86. Continuous Integration in C++](#86-continuous-integration-in-c)
  - [87. Static Analysis in C++](#87-static-analysis-in-c)
  - [88. Argument Evaluation Order in C++](#88-argument-evaluation-order-in-c)
  - [89. Move Semantics in C++](#89-move-semantics-in-c)
  - [90. std  move and the Move Assignment Operator in C++](#90-std--move-and-the-move-assignment-operator-in-c)
  - [91. ARRAY - Making DATA STRUCTURES in C++](#91-array---making-data-structures-in-c)
  - [92. VECTOR DYNAMIC ARRAY -  Making DATA STRUCTURES in C++](#92-vector-dynamic-array----making-data-structures-in-c)
  - [93. ITERATORS in C++](#93-iterators-in-c)
  - [94. Writing an ITERATOR in C++](#94-writing-an-iterator-in-c)
  - [95. How to REALLY learn C++](#95-how-to-really-learn-c)
- [清华郑莉](#清华郑莉)
  - [46_constexpr函数](#46_constexpr函数)
  - [47_带默认参数值的函数](#47_带默认参数值的函数)
  - [49_函数重载](#49_函数重载)
  - [50_c++系统函数](#50_c系统函数)
  - [55_面向对象程序设计的基本特点](#55_面向对象程序设计的基本特点)
  - [58_构造函数基本概念](#58_构造函数基本概念)
  - [61_委托构造函数](#61_委托构造函数)
  - [62_复制构造函数](#62_复制构造函数)
  - [65_类的组合](#65_类的组合)
  - [70_联合体](#70_联合体)
  - [71_枚举类](#71_枚举类)
  - [76_标识符的作用域与可见性](#76_标识符的作用域与可见性)
  - [77_对象的生存期](#77_对象的生存期)
  - [80_类的友元](#80_类的友元)
  - [81_共享数据的保护](#81_共享数据的保护)
  - [91_基于范围的for循环](#91_基于范围的for循环)
  - [93_指针变量的初始化和赋值](#93_指针变量的初始化和赋值)
  - [97_指针数组](#97_指针数组)
  - [98_以指针作为函数参数](#98_以指针作为函数参数)
  - [99_指针类型的函数](#99_指针类型的函数)
  - [100_指向函数的指针](#100_指向函数的指针)
  - [101_对象指针](#101_对象指针)
  - [102_动态分配与释放内存](#102_动态分配与释放内存)
  - [103_申请和释放动态数组01](#103_申请和释放动态数组01)
  - [104_申请和释放动态数组02](#104_申请和释放动态数组02)
  - [105_智能指针](#105_智能指针)
  - [106_vector对象](#106_vector对象)
  - [108_移动构造](#108_移动构造)
  - [109_c风格字符串](#109_c风格字符串)
  - [110_string类](#110_string类)
  - [116_继承的基本概念和语法](#116_继承的基本概念和语法)
  - [117_继承方式简介及公有继承](#117_继承方式简介及公有继承)
  - [118_私有继承和保护继承](#118_私有继承和保护继承)
  - [119_基类与派生类类型转换](#119_基类与派生类类型转换)
  - [120_派生类的构造函数](#120_派生类的构造函数)
  - [122_派生类的复制构造函数](#122_派生类的复制构造函数)
  - [123_派生类的析构函数](#123_派生类的析构函数)
  - [124_访问从基类继承的成员](#124_访问从基类继承的成员)
  - [125_虚基类](#125_虚基类)
  - [130_运算符重载的规则](#130_运算符重载的规则)
  - [131_双目运算符重载为成员函数](#131_双目运算符重载为成员函数)
  - [134_虚函数](#134_虚函数)
  - [136_虚函数与动态绑定](#136_虚函数与动态绑定)
  - [137_抽象类](#137_抽象类)
  - [138_override与final](#138_override与final)
  - [161_范性程序设计的基本概念](#161_范性程序设计的基本概念)
  - [162_STL简介](#162_stl简介)
  - [163_迭代器](#163_迭代器)
  - [STL库另作篇章，在此部分不再详谈。](#stl库另作篇章在此部分不再详谈)
  - [179_I/O流的概念及流类库结构](#179_io流的概念及流类库结构)
  - [192_异常处理的思想与程序实现](#192_异常处理的思想与程序实现)

省略部分：
01. Welcome to C++
02. How to Setup C++ on Windows
03. How to Setup C++ on Mac
04. How to Setup C++ on Linux
05. How C++ Works
06. How the C++ Compiler Works

# Cherno c++

## 07. How the C++ Linker Works

链接可以简单这样理解：
1. build阶段编译器选择相信代码全部正确，所有声明的函数都在某处可找到
2. 链接是把这些函数定位。当产生obj后，需要某个函数对其进行处理，链接作用就是能准确找到需要的函数。
3. 总之`build = compile + link`

那么在`include`某一函数后，再次定义这个函数，就会造成链接错误（重复定义）。

math.cpp:
```cpp
#include <iostream>

using namespace std;

void Log(const char *message);//编译器认为某处有Log函数，但是这是链接阶段的工作来找到Log在哪里，编译并不负责

int Multiply(int a, int b) {
    Log("Multiply");
    return a * b;
}


int main() {
    cout << Multiply(5, 9) << endl;
    cout << "hello world";
}
```
1. 此时代码build报错，因为link不到main函数中调用的Multiply中的Log
2. 如果注释掉Multiply函数中的Log函数调用，则build通过，因为从不调Log函数，所以连接器不必链接次函数
3. 当注释掉main函数中的`Multiply`函数时，则build不通过，因为`Multiply`函数中存在`Log`函数，虽然在这个文件中没有用到`Log`，但是其他文件中可能会用到，所以链接起确实需要链接该文件。如果我们没有定义`Log`函数，那么就会报错
4. wait，我们在Multiply函数前加`static`声明，我们就可以告诉编译器，我们只在本文件中调用了`Multiply`函数，如果这里不调用，那么永远不会被调用，则build不会报错

继续，我们添加Log.h和Log.cpp
Log.h:
```cpp
#pragma once
void Log(const char* message){
    std::cout<<message<<std::endl;
}
```

Log.cpp:
```cpp
#include <iostream>
#include"Log.h
using namespace std;
void Log(const char* message){
    cout<<message<<endl;
}

void InitLog(){
    Log("initialized Log");
}
```
math.cpp:
```cpp
#include <iostream>
#include "Log.h"
using namespace std;

void Log(const char *message);

int Multiply(int a, int b) {
    Log("Multiply");
    return a * b;
}


int main() {
    cout << Multiply(5, 9) << endl;
    cout << "hello world";
}
```
可以看到，多次`include了Log.h`，那么一定会造成`LINK`错误，因为多次出现了`Log`函数定义（include相当于把代码复制过来）。
解决方案三个：
1. 在需要的地方声明`static`，比如，在`Log.h`中，可以告诉编译器，`Log`函数不论在哪里引用，只链接到此处
2. 换`static`为`inline`，可将所有调用部分直接将函数体拷贝，不会出现重复定义现象
3. 将所有定义写在`cpp`文件，声明出现在`h`文件，每次include头文件，只copy过来了声明，链接实际上还是到了`cpp`文件

[![top] Goto Top](#table-of-contents)

## 08. Variables in C++

一个字节存储8位无符号数，储存的数值范围为0-255。
数据存储是以“字节”（Byte）为单位，数据传输大多是以“位”（bit，又名“比特”）为单位，一个位就代表一个0或1（即二进制），每8个位（bit，简写为b）组成一个字节（Byte，简写为B），是最小一级的信息单位

1字节(Byte)=8位(bit)
1KB( Kilobyte，千字节)=1024B
1MB( Megabyte，兆字节)=1024KB
1GB( Gigabyte，吉字节，千兆)=1024MB
1TB( Trillionbyte，万亿字节，太字节)=1024GB
1PB( Petabyte，千万亿字节，拍字节)=1024TB
1EB( Exabyte，百亿亿字节，艾字节)=1024PB
1ZB(Zettabyte，十万亿亿字节，泽字节)=1024EB
1YB( Yottabyte，一亿亿亿字节，尧字节)=1024ZB
1BB( Brontobyte，千亿亿亿字节)=1024YB

[![top] Goto Top](#table-of-contents)


## 10. C++ Header Files

头文件：公共位置，用来存储只是声明而不是定义，因为，请记住：我们智能在一个通用的地方来存储函数的声明。只是声明，没有实际定义，没有函数体。

`void Log(const char* message)`称作函数的签名（signature）

在每次调用一个函数时，都需要将其声明提前体现在该文件，那总不能每次都复制粘贴这些签名吧，所以这就是头文件的意义

[![top] Goto Top](#table-of-contents)

## 11. How to DEBUG C++ in VISUAL STUDIO.mp4

调试是为了读取内存，最终你要记住，电脑永远是对的。

在内存视图中，输入地址后，变量内容显示全为`cccc`之类的，主要是`c`，意味着变量还未初始化。且在内存视图下，两个数字等于一个字节，也就是8位，这也是为什么我们用十六进制来看这个视图，因为如果我们那样做，每两个十六进制数与一个`byte`对齐，我们就能分辨，这8个十六进制数字是4字节的内存。

当我在一个函数或者`for`循环内，不再想继续观察时，在想让程序停止的地方打断点，然后`F5`，让debug继续，就可以进行到断点处了。

[![top] Goto Top](#table-of-contents)

## 12. CONDITIONS and BRANCHES in C++ (if statements)

优化过的代码一般没有if语句，因为这样会拖慢程序

[![top] Goto Top](#table-of-contents)

## 13. BEST Visual Studio Setup for C++ Projects!



主要讲解了Cherno本人vs的设置。

1. 将源代码和sln等文件分离开，Cherno通过vs的Solution Exporler窗口中上边的Show All Files视图来调整实际的文件目录，代码目录命名为`src`，默认的filter视图其实是筛选器，虚拟的组织方案，在磁盘上并不真实存在，即使删除也没有关系，和磁盘上的实际目录毫无关系。
2. 当想查看生成的exe文件时，vs默认在存放源代码的目录下生成debug文件夹，这里存放了中间文件。项目目录和实际的可执行二进制文件放入sln同级目录下。更改设置可以在项目属性中更改，`Configuration Properties`内的`General`设置，其路径都相对于项目路径而言，项目路径不是指`sln`而是`vcxproj`文件，其实`vcporj`是xml文件。与此同时，项目文件中建立本项目的`src`文件夹，也就是源码文件。
3. 重要的是：在修改设置时，记得按需将`Configuration`改为`All Configurations`，将`Platform`改为`All Platforms`。
    - 在其中，`outPut Directory`设置为`$(SolutionDir)bin\$(Platform)\$(configuration)\`，目的是将同一结局方案的所有项目二进制包括dll们存储在同一个文件夹下
    - 中间文件夹，`Intemediate Directory`设置为`$(SolutionDir)bin\intermediates\$(Platform)\$(configuration)\`
    - 前两条中，`SolutionDir`和`bin`文件夹中间没有反斜杠看，是因为宏定义时已经将反斜杠写了

[![top] Goto Top](#table-of-contents)

## 14. Loops in C++ (for loops, while loops)

for循环和while循环完全相同，选择哪个取决于是否需要变量:
```cpp
    for (int i = 0; i < 5; ++i) {
        cout << "i is:" << i << endl;
    }
    cout << "=================== " << endl;
    int i = 0;
    while (i < 5) {
        cout << "first i is:" << i << " ";
        ++i;
        cout << "second i is:" << i << endl;
    }
```
由此可见，i就是我所指的变量，比如在程序中，我们有一个叫`running`的变量，我可能想保留该变量，则我们选择`while`变量，我们只需要判断条件，而不需要每次迭代后更改条件。



`i++`和`++i`的区别：
1. 其中内容有很多，暂时不涉及深刻的左值右指的内容
2. 单独拿出来说`++i`和`i++`，意思都是一样的，就是`i = i + 1`。
3. 如果当做运算符来说，就是`a = i++`或者`a = ++i`这样的形式。情况就不一样了。先说`a = i++`。`++`的优先级高于赋值运算符`=`，无论是`++i`还是`i++`都是先自增，再赋值，所以先执行`i = i + 1`，再将自增前的`i`值赋值给`a`；而`a = ++i`，这个的意思是先执行`i = i + 1`，然后在把i的值赋予a
4. 举个例子来说，如果一开始`i = 4`。那么执行`a = i++`这条语句之后，`a = 4`，`i = 5`；那么执行`a = ++i`这条语句之后，`i = 5`，`a = 5`；同理，`i--`和`--i`的用法也是一样的。区别在于，`++i` 是先加`1`，然后返回加`1`之后的值；`i++`是先加`1`然后返回本来的值（没加`1`之前的`i`值）。


最后，do-while循环相对while循环，区别是一定会执行一遍body。anyway，很少用到。

[![top] Goto Top](#table-of-contents)

## 15. Control Flow in C++ (continue, break, return)


`return`效果和`break`很像，直接结束。区别是，break只会打断当前循环或函数体，但`return`则直接结束函数，例如:
```cpp
int main() {
    for (int i = 0; i < 7; ++i) {
        if (i % 2 == 0)
            return 0;
        cout << "i is :" << i << endl;
        Log("hello world");
    }

    std::cin.get();

}
```
一旦到达`return`语句，整个函数结束，不会走到`std::cin.get();`语句，`break`则不同。

[![top] Goto Top](#table-of-contents)

## 16. POINTERS in C++

内存在程序运行时是连续的（one big line），像是一条街道，访问内存相当于指定街道门牌号然后定点访问。
```cpp
    char* buffer = new char[8];
    char** ptr2ptr = &buffer;
    memset(buffer, 9, 8);
    cin.get();
    return 0;
```
在ptr2ptr处打断点，可以在debug模式下查看momory1（至于问什么是1而不是234还有待查阅），通过两次访问对应地址来查看地址对应数据。

变量类型不重要，cherno强调很不重要，指针只不过就是记录地址的**一个字节**，那我们所有指针都用`void`不就好了？不是，当我们不知道数据使用双方是int或者double时，void就无法判断出能否赋值或加减，这是给指针变量类型定义的原因。

btw，memory中的地址顺序为什么是相反的如：`b8 f1 02 00`实际数据为：`00 02 f1 b8`（字节存储次序的原因），并且将新的数据粘贴进地址索引栏时，不含空格。

[![top] Goto Top](#table-of-contents)

## 17. REFERENCES in C++

```cpp
void Increment(int value) {
    value++;
}
void Increment2(int* value) {
    (*value) += 1;//先取地址，再自增
}
void Increment3(int& value) {
    value++;
}
int main()
{//size of bytes?

    int a = 5;
    Increment(a);
    cout << a << endl;

    int b = 5;
    Increment2(&b);
    cout << b << endl;

    int c = 5;
    Increment3(c);
    cout << c << endl;

    cin.get();
    return 0;
}
```
指针和引用原理相同，只不过更强大一些，所有可以用引用的地方，都可以用指针，但是引用会使代码干净更容易阅读。

需要注意的是，引用只能始终引用某个特定变量，无法后期更改。如果需要更改，则通过指针，修改指向的内容。
```cpp
    int* ref = &a;
    *ref = 2;
    ref = &b;
    *ref = 1;
```
清华面向对象程序设计：
以上均为左值引用，右值引用定义是：
- 不能取地址的、没有名字的就是右值
- 匿名变量(临时变量)的别名：类型名 && 引用名 表达式
  - 例如：`int && sum = 3 + 4;`，`float && res = ReturnRvalue(f1, f2);`
  - 右值引用的典型应用是在函数参数中，例如:`void AcceptRvalueRef(T&& s){...}`目的是减少临时变量拷贝的开销


[![top] Goto Top](#table-of-contents)

## 18. CLASSES in C++
```cpp

class Player {
public:
    int x, y;
    int speed;

    void Move(int xa, int ya) {
        x += xa * speed;
        y += ya * speed;
    }
};

int main() {
    Player player;
    player.x=9;
    player.y=10;
    player.speed=1;
    player.Move(2,3);
    cout << player.x;
    std::cin.get();
}
```
请注意，class可以做到的事情，不用class绝对可以做到，你看那些c语言，汇编语言等，无需类。类的存在仅仅是语法里的甜点，让代码看起来整洁和易于维护。

类内成员默认为`private`，按需升为`public`，`private`成员类内可见。

`m_varName`，这里的m_是为了代表这是一个私有类成员，以和外部成员区分。
`class`内可能设多个`public`，成员函数和成员变量尽量分开，使得易读，可能还会有静态成员变量。

[![top] Goto Top](#table-of-contents)

## 19. CLASSES vs STRUCTS in C++

类和结构体唯一区别是，可见性。
如果生硬地直接将一个`class`改为`struct`，那么这个类内私有成员直接变为共有，除非特地注明为`private`。


其实我们可以利用如下语句`#define struct class`将struct替换为class，struct存在仅仅为了兼容c语言

其事两者并无区别，选取完全取决于代码习惯。cherno习惯将所有都是变量的东西作为结构体。

比如:
```cpp
struct Vec2{
    float x, y;

    void Add(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }
}
```
在这个结构体中，核心就是两个浮点数，没有任何功能。即便我加了功能，这个功能也是处理这两个变量的。

另外，结构体无法使用继承。

[![top] Goto Top](#table-of-contents)

## 20. How to Write a C++ Class

据Cherno说这个类写的很糟糕，那就不做记录了，只是比较值得学习的一点是：LogLevel，当指定某一Level时，要做筛选，不是所有Log都允许被打印出来，所谓的限制条件。

[![top] Goto Top](#table-of-contents)

## 21. Static in C++

类外的Static，该符号的链接声明符号的链接为Internal（内部），只在定义的部分可见，类似07. How the C++ Linker Works讲的头文件。

类内部的Static变量，则该变量将于该类的所有实例共享内存，在您所创建的该
类或者是结构体中的所有实例中，只有一个实例，也就是静态变量，相同的是，仅有一个静态函数。

在这讲，指关注静态变量在类外部的含义。

当我们定义了一个静态变量，在链接阶段，连接器不会在该符号定义的翻译单元（translation unit）之外寻找该函数或变量的定义或者声明。

在Static.cpp中定义`static int s_Veriable = 5;`，并且在main.cpp中定义全局变量` s_Veriable=10;`，这时编译不会报错，但是去掉Static.cpp内的`static`，则编译报错，链接错误。

为了避免报错，则去掉static.cpp中的`static`，在main.cpp中：`entern int s_Variable`，意思是，在外部单元，其他地方定义了`s_Variable`这个变量。

我们想：如果文件定义了一个变量，却没有声明`static`时，那这个变量全局可见，也就是，链接时，会查询所有文件，这会造成很糟糕的bug。所以本节重点是：尝试标记您的函数和变量为静态，除非您实际上却是需要全局链接。

[![top] Goto Top](#table-of-contents)

## 22. Static for Classes and Structs in C++

全局实例，且唯一。当修改某处的静态变量，则全局修改。

```cpp
struct Entity {
    static int x, y;
    static void Print() {
        std::cout << x << ", " << y<<std::endl;
    }
};
```
初始化`x`, `y`为静态变量，则xy不再属于类成员，不再支持这样来初始化成员了：`Entity e1 = { 5,8 };`

则在书写静态变量时可以这样写：
int Entity::x;
int Entity::y;

```cpp
int main()
{
    Entity e;
    e.x = 2;
    e.y = 3;

    Entity e1;
    e1.x = 4;//Entity::x = 4;
    e1.y = 5;//Entity::y = 5;
    
    e.Print();

    std::cin.get();
    return 0;
}
```
注意准确写法应该是注释的两行，因为`e`和`e1`指向的实际上是同一块内存。

这样使得跨类建立变量变得很容易，那么为什么不直接建立全局变量呢，区别就是将其放入实体是有意义的，如果有一条信息是需要共享的，横跨所有实体实例，或将其实际储存在实体类，因为他用于与组织目的的实体有关。此时最好建立静态变量而不是全局变量。

静态函数用法类似，所以上述main函数中的`e.Print();`，实际上应该这么写`Entity::Print();`，值得注意的是，静态函数无法访问非静态变量。在类中，每个非静态函数总是获取当前实例作为参数，这是类在幕后的实际工作方式

静态函数无法访问非静态变量，因为静态函数没有类的实例，本质上说，在类中写的每一个函数，每个非静态函数总是获取当前类的一个实例做参数，这就是类在幕后的实际工作方式。在类中看不到这种东西，他们通过隐藏参数发挥作用，但是静态函数不会获取那个隐藏的参数。

声明在类内，初始化在类外。

[![top] Goto Top](#table-of-contents)

## 23. Local Static in C++
声明一个变量，要考虑两点，这就是变量的声明周期（lifetime）和变量的作用域（scope）。

若静态变量不在类之内，那么这个静态变量生命周期和整个应用程序相同。
```cpp
void Function() {
    static int i = 1;
    i++;
    std::cout << i << std::endl;
}

int main()
{
    Function();
    Function();
    Function();

    std::cin.get();
    return 0;
}
```
若`i`为非静态变量，则调用一次增加一次，反正每次都是从`1`到`2`，若为静态变量，则只会初始化一次，`i`逐次增加。

但是这么做的坏处是，比如在main函数中令`i = 10;`，则`i`会被随时改变，

直接声明全局变量也可以，但是就像类的引入，不用类也可以完成代码，但是为了代码整洁。


[![top] Goto Top](#table-of-contents)

## 24. ENUMS in C++

当你想用整数来表示某种状态或某些数值时，它非常有用，他只是一种命名值的方法，以便代码易于阅读，不管怎么说，枚举就是整数值。

```cpp
enum Example {
    A, B, C
};
int main()
{
    Example value = B;
    std::cin.get();
    return 0;
}
```

在18讲如何写类的时候的Log类
```cpp
class Log {
public:
    enum Level {
        Error = 0, Warning, Info//枚举声明最后没有分号
    };
private:
    int m_Loglevel = Info;//没有枚举时候的写法
    Level m_Loglevel = Info;//将Loglevel设置为枚举类型，则Loglevel被限制为这三个了
};
```

则设置Log级别时候的书写方式变为如下：
```cpp
    Log log;
    log.SetLevel(Log::Error);
```
因为我们有一个枚举数叫Error在log这个类的命名空间中。注意这个枚举Level本身不是一个命名空间，叫做枚举类，

此外，为了避免名称冲突，比如Log类中Level枚举里的Error和Error函数，尽量将其命名为`LevelError`，即`className + Enumer`



[![top] Goto Top](#table-of-contents)

## 25. Constructors in C++


构造函数是特殊的函数，他在每次实例化对象时运行，他的作用是初始化该类，当创建一个新对象实例时，构造函数确保你初始化了所有内存，做了所有你需要的设置

`Log() = delete;`，不适用构造函数。

[![top] Goto Top](#table-of-contents)

## 26. Destructors in C++

如果在构造函数中调用了特定的初始化代码，你需要在析构函数中删除这些东西，否则会造成内存泄漏。一个很好的例子是在堆上分配的对象，如果您已经在堆上分配了任何类型的内存，那么需要手动清理。如果在类中使用或者构造分配了内存，你可能需要在析构函数中删除他们。

[![top] Goto Top](#table-of-contents)

## 27. Inheritance in C++
`class SubClass : public SperClass`

他继承允许我们有一个相互关联的类的层次结构，换句话说就是允许我们有一个包含公共功能的基类，为的是防止我们写重复代码。

子类一定是父类的超集，总拥有父类的所有，并且再加上一点点，这是面向对象编程中最重要的东西之一，记住，当你创建一个字类时，它将包含父类所包含的一切。

btw:`std::cout<<"size of a class"<< sizeof(SubClass)<<;`，意思是打印出某个类的对象的大小，取决于类中变量的个数和类型，比如只有一个`int`类型变量，则`sizeof`输出大小为`4`，不包含函数。如果我们重写函数和子类，那么我们就需要维护一个`V表（虚函数表）`，也就是要额外的内存。

[![top] Goto Top](#table-of-contents)

## 28. Virtual Functions in C++

虚函数允许我们在子类中重写函数，父类中的一个函数标记为`virtual`，我们可以选择在子类中重写函数，让他做其他事情。

```cpp
#include <iostream>

class Entity {
public:

    std::string GetName() {
        return "Entity";
    }
};


class Player : public Entity {
private:
    std::string m_Name;//储存一个名字
public:
    Player(const std::string &name) : m_Name(name) {}//构造函数名，指定名字

    std::string GetName() {
        return m_Name;
    }

};

int main() {

    Entity *e = new Entity();
    std::cout << e->GetName() << std::endl;

    Player *p = new Player("cherno");
    std::cout << p->GetName() << std::endl;

    //如果我们指向一个Player，就像他是一个Entity一样，我们就会遇到问题
    Entity *entity = p;
    //我们希望指针是Player，因为即使指定定是Entity指针，但是他确实是Player
    //这是因为，我们声明函数时，我们的函数通常在类的内部（起作用），当调用一个函数时
    //会调用属于该类型的函数
    //类似于调用了如下函数：
//    void PrintName(Entity *entity) {
//        std::cout << entity->GetName() << std::endl;
//    }

    std::cout << entity->GetName() << std::endl;

    return 0;
}
```
当我们需要告诉c++哪个函数是我们希望调用的时候，就是虚函数出现的时候，v表就是一个表，它包含基类中所有虚函数的映射，这样我们可以在运行时将他们映射到正确的override函数，简单期间，如果想覆写一个函数，必须将基类到基函数标记为虚函数。

正确做法是将`Entity`类的`string GetName`函数添加`virtual`关键词，可以告诉编译器：生成v表吧，为这个函数，这样如果他被重写了，你就可以指向正确的函数。在c++11后，覆写函数需要标记关键词`override`，`std::string GetName() override {return m_Name;}`，这不是必须的，但是你还是应该这样做，因为首先，这样代码更具可读性，因为我们知道这实际上是一个覆写的函数，而且它还可以帮助我们预防bug的发生。

以上就是虚函数的本质。

但遗憾的是，虚函数并不是免费的（无额外开销）的，有两种虚函数相关的运行时成本。首先我们需要内存来存储v表，这样我们分配到正确的函数，包括基类中要有一个成员指针，指向v表。其次，我们每次调用虚函数时，我们需要遍历这个表，来确定要映射到哪个函数。

如果比如在嵌入式这种cpu性能很差的情况，还是避免使用虚函数吧，但是一般情况下没有区别


btw，本部分涉及到了初始化对象，所以总结如下：
c++有三种方法创建对象

结合代码来看

```cpp
#include <iostream>
using namespace std;

class Test {
private:
public:
    add() {
        int x, y, sum;
        x = 5;
        y = 5;
        sum = x + y;
        cout << sum << endl;
    }
};

void main() {
    Test test1;  //栈中分配  ，由操作系统进行内存的分配和管理
    Test test2 = Test;  //栈中分配  ，由操作系统进行内存的分配和管理
    Test *test3 = new Test();  //堆中分配  ，由管理者进行内存的分配和管理，用完必须delete()，否则可能造成内存泄漏
    test1.add();
    test2.add();//"." 是结构体成员引用
    test3->add();//"->"是指针引用
    delete (test3);
    system("pause");
}
```
第一种和第二种没什么区别，一个隐式调用，一个显式调用，两者都是在进程虚拟地址空间中的栈中分配内存。**栈是系统数据结构**，对于线程/进程是唯一的，它的分配和释放由**操作系统**决定，不需要由开发者来管理。在执行函数时，函数内局部变量的存储单元可以在栈上创建，函数执行完毕，系统会自动释放这些存储单元。第三种使用了new，在堆中分配了内存，堆上的内存分配，亦称动态内存分配。程序在运行的期间用malloc申请的内存，这部分内存由程序员自己负责管理，其生存期由开发者决定：在何时分配，分配多少，并在何时用free来释放该内存。这是唯一可以由开发者参与管理的内存。使用的好坏直接决定系统的性能和稳定。**注意：栈中内存的分配和管理由操作系统决定，而堆中内存的分配和管理由管理者决定。**

**我们需要的内存很少，你又能确定你到底需要多少内存时，用栈。当你需要在运行时才知道你到底需要多少内存时，请用堆。**



关于new创建类对象特点：

1. new创建类对象需要指针接收，一处初始化，多处使用
2. new创建类对象使用完需delete销毁
3. new创建对象直接使用堆空间，而局部不用new定义类对象则使用栈空间
4. new对象指针用途广泛，比如作为函数返回值、函数参数等
5. 频繁调用场合并不适合new，就像new申请和释放内存一样

[![top] Goto Top](#table-of-contents)

## 29. Interfaces in C++ (Pure Virtual Functions)

接口只是c++的类罢了

特殊类型的虚函数，本质上与Java或c#中的抽象方法或接口相同。纯虚函数允许我们在基类中定于一个没有实现的函数，然后强制子类去实现该函数。

例如上一讲的`Entity`函数中的`GetName`函数，子类重写他为可选项，如果不写，依旧可以调用到父类的`GetName`函数。但是创建一个类，只由未实现的方法组成，然后强制子类去实现，这很常见，这通常称为接口。因此，类中接口只包含未实现的函数，作为模板。


在上一讲的Entity类中的GetName()函数中，将其改写为`virtual std::string GetName() = 0;`，其中仍保持`virtual`虚函数声明，并且将函数体换为`= 0`,成为纯虚函数，`= 0`意味着父类没有函数实现，子类必须将其重写。

如果某个类并不继承于某个纯虚函数类，则应加`,`来限定，如：
```cpp
class WhatEver:Entity ,Printable {

};
```

接续，接下来这个类作为基类，其他类继承于此，`GetClassName`函数纯虚函数，子类们需要在继承时`override`该函数，才能实例化对象。
```cpp
class Printable {
    virtual std::string GetClassName() = 0; 
};
```
覆写函数如下：

```cpp
#include <iostream>
//#include "Log.h"
//using namespace std;

class Printable {
public:
    virtual std::string GetClassName() = 0;
};



class Entity :public Printable
{
public:
    std::string GetClassName()override { return "Entity"; }

};

class Player :public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name) :m_Name(name) {}

    std::string GetClassName()override { return "Player"; }

};

class A :public Printable
{
    std::string GetClassName()override { return "A"; }
};


void Print(Printable* obj) {
    std::cout << obj->GetClassName() << std::endl;
}



int main()
{
    Entity* e = new Entity;
    Player* p = new Player("cherno");
    Print(e);
    Print(p);
    Print(new A());//仅用来测试用，实际不能这么写，造成内存泄露

    std::cin.get();
    return 0;
}
```




[![top] Goto Top](#table-of-contents)

## 30. Visibility in C++

我只想提一下，可见性是对程序实际运行方式完全没有影响的东西，对程序的性能或类似的东西没有影响，纯粹语言中的东西，只是为了写出更好看的代码。

`private`意味着只有`（only*）`这个类可以访问这些变量。这里的only需要加星号，因为在c++中有个叫`友元（friend）`的东西，`friend`关键词可以让类或者函数称为类的友元，友元实际上可以访问私有成员。

public继承也不可访问私有成员变量，成员函数同理。

`protected`可见性介于两者之间。意味着类和层次结构中的所有子类，可以访问这些符号。

那么为什么不让所有东西都`public`，首先是代码风格问题，可见性让代码更容易理解，易于维护。当你将一个事件标记为`private`时，这基本上告诉所有人包括你自己：你不应该操你个其他类访问这个，只能在类的内部访问这个。读代码时，看到类的结构，应该可以这么说，我只被允许接触`public`的东西。通过可见性，我们可以确保人们不会调用他们不应该调用的代码，并可能破坏某些东西。

一个很好的例子是UI界面，如果我想移动按钮的位置，如果我只访问按钮的坐标`x`和`y`，然后改变变量，按钮实际上可能不会动，我的意思是x轴和y轴的位置可能不同，为了真正让按钮移动，我们可能要刷新显示，如果我只设置`x = 5`之类，`x`确实变了，但显示器并不知道，它不知道从内存获取新的值，而继续用老的值。然而如果我在类中创建一个函数叫`SetPosition`，我可以做的不仅仅是给x赋值，我还可以调用另一个叫`refresh`之类的函数，他能做所有他需要做的事情，我可以让那个`x`变量本身私有，然后`SetPosition`函数为共有，显然，想使用这些代码的人可以看到，我不应该直接给`x`赋值，我应该调用SetPosition函数。

[![top] Goto Top](#table-of-contents)

## 31. Arrays in C++

c++数组就是表示一堆的变量组成的集合

尽量用`<`而不是`<=`，涉及到性能问题，因为你在做小于等于的比较


```cpp
int main()
{
    int example[5];//在栈创建，到大括号时销毁
    int* another = new int[5];//堆上创建，直到程序将他销毁，都是活跃的状态。

    delete[] another;//注意delete的方式，方括号
    std::cin.get();
    return 0;
}
```
上面代码，为什么要动态地用`new`来分配，而不是在栈上创建呢，最大的原因是因为生命周期，用`new`创建的数组，直到删除前都存在，如果你有一个函数返回一个数组，这个数组是在函数中创建的，那必须用`new`来分配他，除非你传入一个数组的地址参数。

此外，另一件事也需要考虑，那就是间接寻址，这时候应该在栈上创建数组来避免这种情况，因为在内存中跳跃肯定会影响性能。

在维护代码，尤其是数组大小时，一般采取如下手段，而非`sizeof`函数再除以`sizeof(int)`来处理
```cpp
    static const int exampleSize = 5;
    //在这里需要static限制，因为c++需要在编译前就知道example参数的具体值
    //只有const int exampleSize = 5;是无法满足c++编译需求的
    int exmaple[exampleSize];
```

如果你用c++11的`std::array`,如下：
```cpp
class Entity {
public:
    std::array<int, 5>another;
    Entity()//构造
    {
        for (int i = 0; i < another.size(); i++)
            another[i] = 2;
    }
};
```
c++11的array比自带的好一些，包括边界检查等优化，当然他会有性能开销，但是确实为维护代码提供便利，不再需要利用`sizeof`除法或手动维护了，会更好些总之。这通常是值得的，所以考虑用这个。

[![top] Goto Top](#table-of-contents)

## 32. How Strings Work in C++ (and how to use them)

一个字符是一个字节，这就是Ascii，也就是c++默认的文档编码。`char`就是一个字节，字符串实际就是一个字符数组。

`const char* name = "cherno";`
c language style,usually we don`t wanna change it,so we use const.

在这里`char*`并不意味着在堆上分配的，不需要`delete`，经验法则是：如果你不用`new`关键字，就不要用`delete`关键字。

```cpp
int main()
{
    char* name = "cherno";
    std::cin.get();
    return 0;
}
```

`cin.get()`处打断点，debug模式下内存输入`name`，可看到右侧显示cherno，说明右侧视图ascii表示。左侧视图里，第一个`0`出现时，字符串终止，字符串从指针的内存地址开始，然后继续下去知道碰到`0`。

```cpp
    char* name = "Cherno";
    char name2[6] = { 'C' ,'h','e','r','n','o' };
```
c++字符是通过单引号，而不是双引号来初始化，双引号默认是`char*`，但是`char name2[6] = { 'C' ,'h','e','r','n','o' };`是数组不是字符串，你可以看到一个包含六个字符的数组，这里没有空终止字符。如果我们拓展这个，加上`0`或者`'\0'`，同时，应该改为`name2[7]`

c++怎么处理字符串呢，标准库有一个叫叫`String`的类。实际上有一个类叫`BasicString`，他是一个模板类，`std::string`实际上是`baseString`的模板版本，模板参数是`char`，意思是`char`是每个字符背后的实际类型。

我们改用`std::string`:
```cpp
    //char* name = "Cherno";
    std::string name = "cherno";
```
`string`有一个构造函数，他接受`char*`或`const char*`参数，如果你把鼠标悬浮在`"cherno"`上，你会看到它实际上是一个`const char`数组，不是`char`数组，记得头文件要加入`include<string>`，因为`<<`操作符的允许我们发送字符串到流中的重载版本是在`string`头文件的内部。

`std::string`还有很多很好的方法，如果不用它的话还要找类似c语言的函数，如`strlen()`等，所以尽量还是用这个版本。

我们不能这么做`std::string name = "Cherno" + "hello";`，发生这种情况的原因是，你实际上是想将两个`const char`数组相加，这个双引号里面的东西是`const char`数组，他不是真正的字符串，不能把这两个指针相加，不能将两个数组直接相加。如果你想做类似的事情，一个很简单的方法是把他分开成多行，然后`name += "hello"`，是将一个指针加到了`name`，`name`是个字符串，你把他加到一个字符串上，`+=`这个操作在`string`类被重载了，所以可以这样写。或者是我常常做的`std::string name = std::string("Cherno") + "hello";`将两个相加的字符数组中的一个，显式调用一个`string`构造函数，相当于创建了一个字符串，然后附加这个（字符数组）给他。

如果在字符串中查找：
```cpp
    std::string name = "cherno";
    bool contains = name.find("no")!=std::string::npos;//npos代表一个不存在的位置
    //name.find返回的是no所在的首位置，所以在此，它会返回no开始的位置
```
我想传递一个字符串，一般不这么写:
```cpp
void PrintString(std::string string)
{
    std::cout << string << std::endl;
}
```
因为这实际上是一个副本，当你这样把类（对象）传递给一个函数时，你实际上在复制这个类（对象），如果我要做类似`string += "h"`这样的事，
```cpp
void PrintString(std::string string)
{
    //string += "h";
    std::cout << string << std::endl;
}
```
这样不会影响到传递的原始字符串，这显然是一个只读函数，我不修改任何东西，我们只将他打印出来，为什么要复制整个字符串呢，这意味着我们必须动态地在堆上分配一个全新的`char`数组来存储我们已经得到的完全相同的文本，这样很慢。字符串复制实际上很慢。因此当你传递一个这样的字符串，且只读的情况下，确保是通过常量引用传递他。修改如下：
```cpp
void PrintString(const std::string& string)
{
    std::cout << string << std::endl;
}
```
这告诉我们，这是一个引用，意味着不会被复制，`const`意味着我们承诺不会在这里修改它。

[![top] Goto Top](#table-of-contents)

## 33. String Literals in C++

字符串字面量，是在双引号之间的一串字符
```cpp
int main()
{
    "cherno";

    std::cin.get();
    return 0;
}
```
鼠标悬浮在`"cherno"`上时，提示`const char[7]`，包含了0终止位。

c++14有个`std::string_literls`给出了一些方便的字符串函数
例如上一节说的两个字符串相加，现可这么操作：
```cpp
int main()
{
    using namespace std::string_literals;
    std::string name = "Cherno"s + "hello";
}
```
`cherno`后面的`s`实际上是一个函数



[![top] Goto Top](#table-of-contents)

## 34. CONST in C++
```cpp
int main()
{
    const int MAX_AGE = 90;
    int* a = new int;

    *a = 2;//1. 逆向引用并赋值
    //a = &MAX_AGE;2. 重新分配实际的指针，指向其他的东西
    a = (int*)& MAX_AGE;//为了绕开const int类型，强制转换为int*类型,最好不这么做
}
```

指针的`*`运算符通常称为`dereference`运算符，某些翻译叫做逆向引用。

`const int* a = new int;`和`int const* a = new int;`,意义一样，代表你不能修改指针指向的内容，比如你想逆向引用这个指针然后改变`a`的值：`*a = 2;`，你看到这是不行的。当然只读操作是可以的：`std::cout<<*a<<std::endl;`，你也可以看到当我改变`a`本身时，也不会有问题：`a = (int*)& MAX_AGE;`，所以我让`a`指向其他东西是没有问题的，我只是不能改变那个指针指向的内容，也就是内存中的数据。

第二种是`int* const a = new int;`，我可以改变指针指向的内容，但我不能实际的指针本身重新赋值，指向别的东西。

最后，`const int* const a = new int;`，意味着不能改变指针指向的东西，也不能改变指针本身，让他指向别的。


类中的`const`：
```cpp
class Entity
{
private:
    int m_X, m_Y;
public:
    int GetX()const//这种方法只在类中有效。这意味着，我们只读数据，不会修改类的参数，所以在get函数后写const是有意义的(make sense)
    {
        return m_X;
    }
    void SetX(int x)//这里不能写cosnt，显然我们要写成员
    {
        m_X = x;
    }
};
```

指针：
```cpp
class Entity
{
private:
    int* m_X, *m_Y;//btw,如果int *m_X, m_Y,意味着只有m_X是指针，m_Y是整形
public:
    const int* const GetX()const
    {
        return m_X;//意味着我们返回了一个不能被修改的指针，且指针内容不能被修改
    }
    void SetX(int* x)
    {
        m_X = x;
    }
};
```

基于上述`Entity`类，对比下列函数：
```cpp
void PrintEntity1(Entity e)
{
    std::cout << e.GetX() << std::endl;
}
void PrintEntity2(const Entity& e)
{
    std::cout << e.GetX() << std::endl;
}
```
仍旧是老问题，不希望复制对象，第一个函数就是复制，第二个则通过常量引用来传递参数。这意味着第二个`e`是常量，再看第三个：
```cpp
void PrintEntity3(const Entity* e)
{
    e = nullptr;
}
```
如果`e`是指针，我们可以修改他指向的方向（也就是指针本身的值）但我不能修改`e`指向的内容。如果这里是引用的话，也是同样的情况。我不能修改`e`，我不能将他重新赋值，如：
```cpp
void PrintEntity3(const Entity& e)
{
    e = Entity();
}
```
这与指针工作方式不同，如果你重新分配这个引用，你实际上是在改变这个对象，而不是其他对象。这里没有指针本身和指针指向的内容的区别了，因为引用就是内容，就是你所能修改的。

总之，如果他们实际上没有修改类或者他们不应该修改类，标记你的函数为`const`。

有一种`const`情况，你确实想标记函数位`const`，但出于某些原因，他确实又需要修改一些变量，也许只是为了测试，或者它不会影响程序，我们仍想标记：
```cpp
class Entity
{
private:
    int m_X, m_Y;
    mutable int var;//mutable意味着可以被改变，即使在const函数中
public:
    int GetX()const
    {
        var = 2;
        return m_X;
    }
    void SetX(int x)
    {
        m_X = x;
    }
};
```
[![top] Goto Top](#table-of-contents)

## 35. The Mutable Keyword in C++.srt

mutable：易变的
immutable：不可改变的

让函数标记`const`的主要原因是：承诺不改变类。如果不标记`const`函数：
```cpp
class Entity
{
private:
    int m_X, m_Y;
    mutable int var;
public:
    int GetX()
    {
        return m_X;
    }
    void SetX(int x)
    {
        m_X = x;
    }
};


void PrintEntity(Entity e)
{
    std::cout << e.GetX() << std::endl;
}


int main()
{
    const Entity e;
    e.GetX();//在这里会报错，因为e是一个常量，但是函数注明const，应当int GetX()const才可以
}
```

在`const`函数中，我们承诺不会修改任何类成员，但是某些时候可能会有这样的需求，比如调试程序时，查看调用函数的次数，我定义一个`m_debugCount`变量：
```cpp
class Entity
{
private:
    int m_X, m_Y;
    std::string m_Name;
    mutable int m_debugCount=0;
public:
    const std::string& GetName()const//返回引用
    {
        m_debugCount++;
        return m_Name;
    }
};
```
以上是绝大多数时候的用法。

lambda表达式：
lambda基本上就是一个一次性小函数，你可以写出来并赋值给另一个变量，我们可以像调用其他函数一样调用它。
```cpp
int main()
{
    int x = 8;
    auto f = [=]()//将x传入
    {
        x++;//x通过值传递进来，报错，如需这样，则新建中间变量，或者，声明lambda：auto f = [=]()mutabl
        std::cout << x << std::endl;
    };
    f();
    //x = 8，你不是通过引用来传递它的，你仍然是通过值来传递它，所以x依旧是8，因为你只是复制了8这个值传进了lambda
}
```
当然，这种情况很少用到。

[![top] Goto Top](#table-of-contents)

## 36. Member Initializer Lists in C++ (Constructor Initializer List)

这是构造函数中初始化类成员变量的一种方式

```cpp
class Entity
{
private:
    std::string m_Name;
public:
    const std::string& GetName()const { return m_Name; }
    Entity()
        :m_Name("Unknown")//很重要的一点是，要按顺序写，不管你怎么写初始化列表，她都会按照定义类成员的顺序来进行初始化。
    {
    }

    Entity(const std::string& name)
        :m_Name(name)//用括号代替等号，然后把他移到这个列表中
    {
    }
};

int main()
{
    Entity e0;
    std::cout << e0.GetName() << std::endl;

    Entity e1("cherno");
    std::cout << e1.GetName();

    std::cin.get();
    return 0;
}
```

仅仅是代码风格问题吗，是也不是，列表初始化确实可以让构造函数更清晰，但是实际上有个功能上的区别，在特定的类的情况下：
```cpp

class Example
{
public:
    Example() {
        std::cout << "default function" << std::endl;
    }
    Example(int x) {
        std::cout << "define with " << x << std::endl;
    }
};

class Entity
{
private:
    std::string m_Name;
    Example m_Example;//调用了默认构造
public:
    const std::string& GetName()const { return m_Name; }
    Entity()
    {
        m_Name = std::string("Unknown");
        m_Example = Example(9);
    }

    Entity(const std::string& name)
        :m_Name(name)
    {
    }
};

int main()
{
    Entity e0;

    std::cin.get();
    return 0;
}

```
结果：
```bash
default function
define with 9
```
我们先创建了一个`Example`对象，然后扔掉它，用一个新的对象来覆盖他，我们创建了两个对象而不是一个，然而将其移到初始化列表里:
```cpp
    Entity()
        :m_Name("Unknown"), m_Example(8)//或者写成"m_Example(Example(8))"
    {
    }
```
结果为：
```bash
define with 8
```

所以这不仅仅是代码风格问题，更多对性能的节省。

[![top] Goto Top](#table-of-contents)

## 37. Ternary Operators in C++ (Conditional Assignment)

三元运算符就是一个问号一个冒号。

假设我想根据我们的`level`来调整`speed`:：
```cpp

static int s_Level = 1;
static int s_Speed = 2;

int main()
{
    if (s_Speed > 5)
        s_Speed = 10;
    else
        s_Speed = 5;

    s_Speed = s_Level > 5 ? 10 : 5;



    std::string otherRank;
    if (s_Level > 10)
        otherRank = "Master";
    else
        otherRank = "Beginner";

    std::string rank = s_Level > 10 ? "Master" : "Beginner";

    std::cin.get();
}
```

代码风格会更已读，并且，第二个例子中刚开始会构造一个空字符串，然后用一个新的对象覆盖那个字符串对象，所以`if-else`的代码从技术上讲更慢，因为你在构造一个临时字符串然后销毁他。

三元运算符的嵌套：`s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;`，s_Level>5且s_Level>10，则s_Speed=15。s_Level > 5且s_Level < 10，则s_Speed = 15。s_Level < 5，则s_Speed = 5。这里数值可能用一些比较合理的东西，比如预定义值的数组，或者某种查找，以后会讲到。

[![top] Goto Top](#table-of-contents)

## 38. How to CREATE INSTANTIATE OBJECTS in C++

今天讨论如何用c++创建对象。

创建有两种方式，区别主要是内存从哪里来，我们在哪里创建对象。当我们创建一个c++对象时，他需要一些内存，即使是一个空的类，没有成员，他也至少占用一个字节的内存。应用程序会将内存主要分为两部分，栈和堆。还有其他部分到内存，如源代码的区域，这些都是机器代码，这些以后再考虑，我们现在主要考虑堆和栈。在c++中，我们要选择对象放在哪里，是在栈上还是堆上创建。

栈对象有一个自动的生存期，他们的生存期实际上是由他声明的地方作用域决定的，只要变量超出作用域，也就是说内存释放了。因为当作用域结束的时候，栈会弹出，作用域里的东西，栈上的任何东西会被释放。但堆不同，堆是个很大很大很神秘的地方，一旦在堆中分配一个对象，实际上你已经在堆上创建了一个对象，他会一直呆在那里，直到你做出决定，我不再需要他了，我想释放这个对象，你想怎么处置那段内存都行。

在栈上创建：
```cpp
#include <iostream>
#include <string>

using String = std::string;//利用using来简化这段代码，这样就不用到处写std::string了


class Entity {
private:
    String m_Name;
public:
    Entity() : m_Name("Unknown") {}

    Entity(const String &name) :
            m_Name(name) {}
    const String &GetName() const { return m_Name; }
};

int main() {
    Entity entity;
    return 0;
}
```
我们想在什么时候这样创建对象？答案是，几乎所有时候，如果你能这么创建，那就这样创建，这是c++中最快的方法，而且也可以“管控”的方法去初始化对象。那什么时候不可以？

1. 一个最常见的情况就是：如果你想把它放置到函数生存周期之外

```cpp
int main() {
    Entity *e;
    {
        Entity entity("cherno");
        e = &entity;
        std::cout << entity.GetName() << std::endl;
    }
    return 0;
}
```
即便是最简单的花括号，当出了括号，生命周期结束。而且作用域不一定是函数，他们可以是`if`语句，甚至是空的。

上例中，如果我们希望在作用域之外仍存在，就不能分配到栈上。

2. 另一个我们不想分配到栈的原因是，如果这个实例太大，而我们可能有太多的entity，我们可能没有足够的空间在栈上分配，因为栈通常非常小，通常是`1m`或者`2m`

`Entity *entity=new Entity("cherno");//返回一个Entity* ，也就是entity在堆上被分配内存的地址`

简单来说，就是性能问题，在堆上分配要比栈花费更长的时间，而且在堆上分配的话，您必须手动释放被分配的内存。

```cpp
int main() {
    Entity *e;
    {
        Entity *entity = new Entity("cherno");//在堆上创建entity对象，在堆上
        e = entity;//赋值，我们没有复制任何数据，所做的就是储存entity内存地址，当复制entity对象时，只复制地址
        std::cout << (*entity).GetName();//又是逆向引用指针，*entity的结果是entity对象，也可以这么写entity->GetName()
    }
    std::cin.get();
    delete e;
}
```

总之，如果对象太大，或者你要显式控制对象声明周期（那就在堆上创建）。如果不是，那就在栈上创建吧，简单很多，不仅是自动化而且更快，而在堆上分配，需要手动`delete`，否则会造成内存泄露。

智能指针情况下，我们仍可以在堆上分配，并且仍然可以获取大小的优势，还有指针超处作用域时，对象会自动删除，或者比如`shared_ptr`，在没有引用时自动删除。bb

[![top] Goto Top](#table-of-contents)


shift + alt + 上下箭头，clion上下移动选中代码


## 39. The NEW Keyword in C++

`new`的主要目的是在堆上分配内存。也有`new int`的写法，占据四个字节内存，一旦分派好后，它会返回一个指向这个内存的指针，这样你就可以开始使用你的数据，并在那里存储数据，并进行读写访问，做这些有趣的事情。

所以大概要做的事情列出来了，大致分为五步，这就是最主要的部分。当你调用`new`时，将会消耗时间。当拓展四个字节的时候，不会去依次扫描，而是有一个叫空闲列表的东西，他会维护有空闲字节的地址。

`int* b = new int;`：动态分配内存，并通过new关键字再堆上创建，一个单一的四字节，在堆上分配，这个`b`存储的是他的内存地址，如果我想分配一个数组，那么就`int* b = new int[50];`这样就是说我们需要200字节的内存，如果想创建一个`Entity`对象，则`int* e = new Entity;`，特别的`int* e = new Entity[50]`则返回连续Entity类型数组50个。

来看`new`的源码：
```cpp
_Ret_notnull_ _Post_writable_byte_size_(_Size)
_VCRT_ALLOCATOR void* __CRTDECL operator new(
    size_t _Size
    );
```
`new`是`operator`，也就是操作符，重载操作符。并且，返回一个`void`类型指针，指针指向那个分配的内存块的地址。

通常调用`new`会调用隐藏在里面的c函数`malloc()`，他代表内存分配，他的实际作用是传入一个`size`，也就是我们需要多少字节，然后返回一个`void`指针，如`malloc(50);`,所以，`int* e = new Entity;`相当于`int* e = (*Entity)malloc(sizeof(Entity));`，两句仅有的区别是，前者调用了构造函数，在c++你最好不要这么做，除了某些时候，以后再谈这个。

当调用了`new`时，一定要记住必须调用`delete`，它调用了c函数的`free`，`free`可以释放`malloc`申请的内存。且当`int b = new int[20];`时，用`delete[] b;`

另一件事是`placement new`，这就是要决定前面的内存来自哪里，`int* e = new Entity;`，所以你没有真正分配内存，你只需要调用构造函数，在一个特定的内存地址中初始化你的`Entity`，可以通过写`new(b)`指定内存地址，比如`b`，应该是没有问题的，因为我假设`Entity`大小是小于200字节的，但是这段代码实在难以理解`placement new`会优化你的代码，但是是在未来讲解。

[![top] Goto Top](#table-of-contents)

## 40. Implicit Conversion and the Explicit Keyword in C++

`explicit`关键字。

隐含的意思是不会明确地告诉他要做什么，所以有点像自动化，通过上下文知道的意思。c++实际上允许编译器对代码执行一次隐式转换。如果我们开始有一个数据类型，然后有另一个类型，在两者之间，c++允许隐式转化，而不需要`cast`做强制转换，

```cpp
class Entity {
private:
    String m_Name;
    int m_Age;
public:
Entity(const String & name)
    :m_Name(name),m_Age(-1){}
Entity(int age)
    :m_Name("Unknown"),m_Age(age){}

};
int main()
{
    Entity a("cherno");
    Entity b(9);
    Entity c = 22;
    return 0;
}
```
在`main`函数中，三种初始化方式都可以，第三种隐式地将22转换成一个Entity，构造出


```cpp
int main()
{
    PrintEntity(22);//c++认为22可以转换成一个Entity，因为你可以调用这个构造函数，22是你创建Entity的唯一参数
    //PrintEntity("cherno");//不可行，因为这个cherno不是std::string，他是一个char类型数组，为了让其工作，c++需要两步工作，一个是从const char数组到string吗，一个是从string到Entity，但它只允许做一次隐式转换
    PrintEntity(String("cherno"));//这样才可以，把他包装在一个构造函数中
    //或者如下：
    PrintEntity(Entity("cherno"))//隐式的将字符串转换为std::string 标准字符串，然后被推进Entity构造函数
    
    Entity a("cherno");
    Entity b(9);
    Entity c = 10;
    return 0;
}
```

这就是隐式构造函数，非常酷的东西，可以大大简化你的代码，但是就我个人而言，尽量避免使用它，除了一些可以简化代码的情况，而不总是通过构造函数来包装。

`explicit`函数，禁用这个隐式（implicit）功能，`explicit`关键字放在构造函数之前，如果你有一个`explicit`构造函数，意味着没有隐式转换，如果要使用整数构造`Entity`对象，则必须显式调用此构造函数。本代码中，将`explicit`关键字放在构造函数前，则隐式转换失败。如果我还想这么做，则需要`Entity b = (Entity)22;`，当然直接`Entity b = Entity(22);`也可以。

这就是`inplicit`、`explicit`的对立关系。

一般在数学库之类的东西使用`explicit`，因为我不想总是将数字变成向量，我想确保我的代码尽可能安全。其实并不常用它。当你写低级封装(low level wrapper)时，或者类似的事情，它可以派上用场，它可以防止做意外转换，导致性能问题或bug，有很多内容，但是无需担心，只要意识到他能为你做些什么就可以了。我认为这节课中最大的收获就是意识到隐形构造函数的存在。

[![top] Goto Top](#table-of-contents)


## 41. OPERATORS and OPERATOR OVERLOADING in C++

运算符以及运算符重载。

运算符是我们使用的一种符号，通常代替一个函数来执行一些事情。我说的不仅仅是数学运算符，比如加减乘除，而且还包括`dereference`(逆向引用)运算符，箭头运算，还包括`new`、`delete`等。

在这个意义上，重载这个术语本质是给运算符重载赋予新的含义，或者添加参数，或者创建，允许在程序中定义或更改运算符的行为。总之，运算符就是函数。不用给出函数名，你可以把他交给加号这样的运算符，在很多情况下这样真的有助于清理代码，使其干净整洁。

速度增加的代码，如下，代码过于冗长且难读懂
```cpp
#include <iostream>
#include <string>

using String = std::string;

struct Vector2 {
    float x, y;
    Vector2(float x, float y)
            : x(x), y(y) {}

    Vector2 Add(const Vector2 &other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Multiply(const Vector2 &other) const {
        return Vector2(x * other.x, y * other.y);
    }
};

int main() {
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);

    Vector2 result1 = position.Add(speed.Multiply(powerup));
    Vector2 result2 = position.Add(speed.Multiply(powerup));
    //显然，这里这么写会更好Vector2 result2 = position + speed * powerup;
    //所以我们来定义两个运算符，乘法运算符和加法运算符
```

增添了`+`和`*`操作符的定义后，可以这么写
```cpp

struct Vector2 {
    float x, y;
    Vector2(float x, float y)
            : x(x), y(y) {}

    Vector2 Add(const Vector2 &other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Multiply(const Vector2 &other) const {
        return Vector2(x * other.x, y * other.y);
    }
    //下面是定义操作符
    Vector2 operator+(const Vector2&other)const{
        return Add(other);
    }

    Vector2 operator*(const Vector2&other)const{
        return Multiply(other);
    }

};

int main() {
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);
    
    Vector2 result2 = position + speed * powerup;
}
```
但是因为操作符定义和函数一样，所以可以反过来做，不是`operator`调用`add`函数，而是`add`函数调用加法运算符，很多人并不知道这一点，因为这个语法看起来有点奇怪，你不常看到，你可以做的是把它改成这样，这是一种简单的情况，易于维护代码：

```cpp
    Vector2 Add(const Vector2 &other) const {
        //return *this + other;这里逆向引用的是什么？
        //因为this是一个指针，在这个例子中是const指针，他在逆向引用后就是一个普通的vector2对象，然后与other相加，这是大多数人的书写方式
        //但是我们也可以用+操作符，就像用一个函数一样：
        return operator+(other);
    }

    Vector2 operator+(const Vector2 &other) const {
        return Vector2(x+other.x,y+other.y);
    }
```
Cherno更倾向前者写法。

`std::cout<< result2<<std::endl;`不能这么做，因为`<<`这个运算符接收两个参数，一个是输出流output stream，也就是cout，另一个就是vector2了，我们可以将这个运算符（重载）加进来，在Vector2类外面。他和Vector2没有任何关系，我们是在cout中重载，我们写上`std::ostream&`输出流，是一个引用，这是我们需要对重载符号的最初定义。

这是最终代码：
```cpp
#include <iostream>
#include <string>

using String = std::string;

struct Vector2 {
    float x, y;

    Vector2(float x, float y)
            : x(x), y(y) {}

    Vector2 Add(const Vector2 &other) const {
        return operator+(other);
    }

    Vector2 Multiply(const Vector2 &other) const {
        return Vector2(x * other.x, y * other.y);
    }

    //下面是定义操作符
    Vector2 operator+(const Vector2 &other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator*(const Vector2 &other) const {
        return Multiply(other);
    }

};

std::ostream &operator<<(std::ostream &stream, const Vector2 &other)
//这里面是类，因为这是一个在类之外定义的运算重载符，所以我们仍然需要一个对现有流（stream）的引用，就是cout
//然后传入const vector2通过引用传递
{
    stream << other.x << "，" << other.y;//这里的stream已经知道如何打印浮点数，所以无需对浮点数重载
    return stream;//返回一个ostream引用，也就是自变量stream
}


int main() {
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);

    Vector2 result1 = position.Add(speed.Multiply(powerup));
    Vector2 result2 = position + speed * powerup;

    std::cout << result2 << std::endl;//不能这么做，因为这个运算符接收两个参数，一个是输出流output stream，也就是cout，另一个就是vector2了
}
```
最后，请记住，操作符只是一个函数，如果你愿意，重载一个操作符可以让代码看起来很古怪，但是不要这么做。我们重载的左移运算符有点像`ToStiring`，在Java或C#中经常被重写。

最后一个例子：
```cpp
    bool operator==(const Vector2&other)const//最后一个const保证了我们不会修改这个类
    {
        return x==other.x&& y==other.y;
    }
    bool operator!=(const Vector2&other)const//最后一个const保证了我们不会修改这个类
    {
        return !(*this==other);
        //return !operator==(other);对应的奇怪写法
    }

    int main() {
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);

    Vector2 result1 = position.Add(speed.Multiply(powerup));
    Vector2 result2 = position + speed * powerup;

    std::cout << result2 << std::endl;//不能这么做，因为这个运算符接收两个参数，一个是输出流output stream，也就是cout，另一个就是vector2了

    //if(!result1.equals(result1))没有判断操作符时，也许我们需要这么写，但现在重载了操作符，我们这样写：
    if(result1==result2){

    }
    if(result1!=result2){

    }
}
```
一些人不喜欢用这个东西，在写库的时候，我喜欢两种都用（函数和运算符重载），所以我仍然会像我例子中这样，我仍然会有我的`Add`函数，但我也会有操作符，这样你就能给到使用你api的人想要的函数了

[![top] Goto Top](#table-of-contents)

## 42. The 'this' keyword in C++

通过`this`，我们可以访问成员函数，在函数内部我们可以引用`this`，`this`是一个指向当前对象实例的指针，该方法属于这个对象实例。

我们可以写一个非静态函数，为了调用这个函数我们首先需要实例化一个对象，然后调用这个函数，这个函数必须要有一个有效的对象来调用，关键字`this`是指向该对象的指针，

```cpp
class Entity {
public:
    int x, y;

    Entity(int x, int y) {
        x = x;//我想用参数x来给成员变量x赋值，当然我可以用参数列表来初始化，但是都是x，我不想这么做，我想在函数内部写，这么做实际上是将x赋值给了自己，也就是什么都没做
        //我真正想做的是引用属于这个类的x和y，实际的成员
        //Entity *const e = this;这一步可省去
        //也可以这么写，逆向引用(*this).x = x;
        this->x = x;
    }

    int GetX() const {
        //Entity *e = this;在const函数中，不能将this赋值给一个entity
        //而可以这么写const Entity* e = this;
        //因为在函数后面有const我们就不能修改这个类，所以this必须是const的
        //所以我们就不能做这样的事了：e->x = 5;当然如果上述没有const，我们是可以的
        //正确写法是：
        const Entity *e = this;
        this->x = x;
        this->y = y;
    }
};

int main(){
        std::cin.get()
};
```

另一个用法是调用类外部的函数

```cpp
#include <iostream>
#include<string>
#include <utility>
class Entity;
using String = std::string;

//void PrintEntity(Entity* e);与PrintEntity(this);对应PrintEntity(this);
void PrintEntity(const Entity& e);

class Entity
{
public:

    int x, y;

    Entity(int x, int y)
    {
        this->x = x;
        this->y = y;

        Entity& e = *this;//非const函数中可以正常引用

        //PrintEntity(this);
        PrintEntity(*this);
    }
    int GetX()const
    {
        const Entity& e = *this;//const函数中常量引用
    }
};

void PrintEntity(Entity* e)
{
    //print
}

int main()
{
    return 0;
}

```

[![top] Goto Top](#table-of-contents)

## 43. Object Lifetime in C++ (Stack Scope Lifetimes)

本届讲对象的生命周期，以及对象如何在栈上生存,就是关于生存周期对于栈的变量意味着什么。所以分为两部分，一部分是你必须理解栈上的东西是如何存在的，第二步是如何利用好他。

栈可以理解为一种数据结构，你可以在上面堆叠一些东西。每次我们在c++中进入一个作用域我们在push栈帧，他不一定非得是将数据推进（push进）栈帧，你可以想象成把一本书放进书堆上，你在此作用域下（这本书内）声明的变量就像你在书里写东西，一旦作用域结束，你将这本书从书堆中拿出来，扔掉了，你在书中申明的每一个基于栈的变量，你在书中栈里创建的对象全都消失了，这是祝福也是诅咒，如果你能明白，则百分百是件好事。

作用域：作用域可以是任何东西，比如函数作用域，比如`if`语句作用域，或者`for`作用域，或者空作用域，像这样`{}`，还有类作用域，

```cpp

class Entity
{
public:
    Entity()
    {
        std::cout << "create Entity" << std::endl;
    }
    ~Entity()
    {
        std::cout << "destroy Entity" << std::endl;
    }
};

int main()
{
    {
        Entity* e = new Entity;
        //Entity e;
    }

    std::cin.get();
}
```
将注释去掉，可以看出基于栈变量和基于堆变量在对象生存期上的区别（一个没有执行到析构，一个有）。基于栈的变量，我们一出作用域就被释放了，摧毁了。

接下来看看在函数中创建一个数组：
```cpp
int *creatArray()
{
    int array[50];
    return array;
}
```
如果你通过这个函数创建数组，那就大错特错了，我们没有在堆上分配数组，因为没有使用new，没有在堆上分配，只是在栈上声明它，当我们返回一个指向它的指针时，他返回一个指向栈内存的指针，一旦离开作用域，内存就会被清除。
如果你非要这么写函数，那有两种方法，一种是你可以让这个在堆上分配数组：`int* array= new int[50];//确保生存周期一直存在`，或者你可以将这里创建的数据复制给一个在栈作用域之外存在的变量：
```cpp
int* creatArray(int * array)
{
    return array;
}

int main()
{
    int array[50];
    creatArray(array);
    std::cin.get();
}
```
在局部创建数组是一个典型错误，我常看到人们会创建一个基于栈的变量，然后尝试返回指向他的指针，一旦函数结束，你就超出了作用域，这些变量就嗝屁了。

既然这种栈上变量会自动销毁，有没有办法让他变得有用呢？答案是肯定的。它在很多方面都很有用，可以帮我们自动化代码，我们可以用它来做一件事就是，比如类的作用域，比如智能指针`smart_ptr`，或是`unique_ptr`，这是一个作用域指针，或者像域锁`scoped_lock`，但最简单的例子可能就是作用域指针。他基本上是一个类，他是一个指针的包装器，在构造时用堆分配指针，然后析构时删除指针，所以我们可以自动化这个`new`和`delete`

我仍然想在堆上分配，我想调用new之类的，然而在超出作用域也就是大括号之后，自动删除，答案显然是可以的，我们可以使用标准库中的`unique_ptr`，这是一个作用域指针，但这个例子我们写自己的实现代码：
```cpp
class Entity
{
public:
    Entity()
    {
        std::cout << "create Entity" << std::endl;
    }
    ~Entity()
    {
        std::cout << "destroy Entity" << std::endl;
    }
};
int* creatArray(int * array)
{
    return array;
}
class ScopedPtr {//只接受entity对象
private:
    Entity* m_Ptr;
public:
    ScopedPtr(Entity* ptr)
        : m_Ptr(ptr){}
    ~ScopedPtr() { delete m_Ptr; }
};//一个基本的作用域指针

int main()
{
    {
        ScopedPtr e = new Entity;//ScoedPtr e(new Entity());，代码中的写法其实是由于隐式转换，为了让两行代码看起来好看
        Entity* e = new Entity();//不同的是，一旦超出作用域，上一行的东西就会被摧毁，因为这ScopedPtr类的对象是在栈上分配的，这意味着e如果被删除了，在析构函数中会delete这个被包装的entity指针
    }

    std::cin.get();
}
```
在`main`函数中注释掉第二行，保留第一种方法，且在第一行加断点，我们可以看到析构函数会被执行，尽管我们`new`来做堆分配，同样的方法，第二行不会执行析构函数。这是`smart_ptr`、`unique_ptr`做的最基本的事。这种用法还有很多，比如一个计时器，假设你想计算你在基准测试范围内的时间，或者你可以写一个timer类，在对象构造时启动`timer`，然后在打印结果时停止`timer`，也就是计时器对象被销毁时。这样你就有了一个自动计时器，你只需要在函数开头写一行代价，那么整个作用域会被计时，而你不用手动调用计时器停止，因为一旦超出作用域，会自动调用（停止），还有很多，比如互斥锁（mutex locking），如果你想锁定一个函数，以便多个线程可以同时访问它而不爆炸，你可以有一个自动 作用域锁定，在函数开头锁住它，在函数结束时解锁他。

btw:
```cpp
    {
        //这是一个空的作用域
    }
```

[![top] Goto Top](#table-of-contents)

## 44. SMART POINTERS in C++ (std  unique_ptr, std  shared_ptr, std  weak_ptr)

智能指针是实现上一节自动删除`new`的内存，智能指针的意思就是当你调用`new`的时候，无需调用`delete`。在很多情况下调用智能指针，我们甚至不需要调用`new`，智能指针只不过是原始指针的封装。

`unique_ptr`：
作用域指针，超出作用域被销毁，然后调用`delete`。之所以叫`unique_ptr`就是因为他是唯一的。你不能复制一个`unique_ptr`，因为如果你复制了一个`unique_ptr`，那么他们指向的内存会有两个指针，两个`unique_ptr`指向同一块内存，如果一个死了，也就是说，你指向同一块内存的第二个`unique_ptr`指向了已经被释放的内存。`unique_ptr`是你想要一个作用域指针的时候，他是你唯一的参考。

要访问所有这些智能指针，你首先要做的是`#include<memory>`
```cpp
    {
        std::unique_ptr<Entity>entity(new Entity());
        //<Entity>是参数模板的意思，最后的entity是指针的名字
        //这里不能std::unique_ptr<Entity>entity = new Entity();因为如果你看unique_ptr，他的构造实际是explicit的，需要显式调用构造
        //然后你就可以访问其他任何东西一样访问它
        entity->Print();
    }
```
另一个更好的构造方式就是把`entity`赋值给`std::make_unique`:

`std::unique_ptr<Entity>entity = std::make_unique<Entity>();`这对于`unique_ptr`很重要，主要原因是出于异常安全，通常是没问题的，但是当出现异常时，会稍微更加安全一些，您最终不会得到一个没有引用的悬空指针，从而造成内存泄漏。
```cpp

class Entity
{
public:
    Entity()
    {
        std::cout << "create Entity" << std::endl;
    }
    ~Entity()
    {
        std::cout << "destroy Entity" << std::endl;
    }

    void Print(){}
};

int main(){
    {
        std::unique_ptr<Entity>entity = std::make_unique<Entity>();
        entity->Print();
    }
    std::cin.get();
}
```
这是第二种做法，当在`main`函数内的`{}`空作用域的第二步打断点，然后`F10`跳出作用域后，可看到析构函数被调用。作用域结束，这是最简单的智能指针，开销也很小甚至没有。只是一个栈分配对象，当栈分配对象死亡时，他就调用delete在你的指针上，并释放内存。正如所说，这个指针不能被复制与分享，你可以尝试`std::unique_ptr<Entity> e0 = entity;`编译器报错。如果你进入`unique_ptr`的定义，你会看到有些奇怪，拷贝构造函数和拷贝构造操作符实际上被删除了。这是专门用来防止你给自己挖坑的。

`shared_ptr`：

`shared_ptr`的实现取决于你的编译器和你在编译器中使用的标准库。大多数使用引用计数。引用计数基本上是一种方法可以，可以跟踪你的指针有多少引用，一旦引用数达到零他就被删除了。举个例子，我创建了一个`shared_ptr`，然后创建了另一个`shared_ptr`来复制他，我的引用数是`2`，第一个和第二个，当地一个死的时候，引用数减少`1`，另一个死的时候，引用数归零，我就死了，内存释放。

与`unique_ptr`不同，`shared_ptr`需要分配一块内存，叫控制块，用来存储计数，如果你首先创建一个`new Entity`，然后将其传递给`shared_ptr`，他必须做两次内存分配，然而你用`make_shared`你就可以将两者结合起来，这样更有效率。请看如下代码：
```cpp
    std::shared_ptr<Entity> e0;
    {
        std::shared_ptr<Entity>sharedEntity = std::make_shared<Entity>();
        e0 = sharedEntity;
    }
```
在作用域内部，第一行打断点，可以看到当步进出作用域时，不会被析构，因为`e0`仍然存在。当执行到`e0`结束（也许是main的return 0;），才会打印出来析构。当所有引用消失，当所有的栈分配对象追踪`shared_ptr`的，当他们死亡后，从内存释放后那就是底层`Entity`被删除的时候。


`weak_ptr`：

弱指针。它只是像声明其他东西一样声明，可以给他赋值为`sharedEntity`，但是此时赋值不会增加引用数，这就很好，如果你不想`Entity`的所有权，就像你可能在排序一个`Entity`列表，你不关心他们是否有效，你只需要存储他们的一个引用即可。

```cpp
    std::weak_ptr<Entity> e0;
    {
        std::shared_ptr<Entity>sharedEntity = std::make_shared<Entity>();
        e0 = sharedEntity;
    }
```
由上述所有权的解释可知，我们出大括号的时候，`shared_ptr`即被析构。所以出大括号后，`weak_ptr`指向一个无效的指针。

总之，尽量多用智能指针，让你的代码变得更安全（以防遗忘delete导致内存泄漏），但并非完全取代。另外，`unique_ptr`开销小于`weak_ptr`，所以使用优先顺序也是如此。


## 45. Copying and Copy Constructors in C++

拷贝以及拷贝构造函数。

如果可以避免拷贝，则尽量避免不必要的拷贝。就像我只读一个变量，或者修改一个已经存在的变量，我们当然不想复制，复制需要时间。一方面，拷贝是很好的东西，让事情根据我们想要的来做，另一方面，拷贝会浪费性能。

这段代码显示了拷贝的用法：
```cpp
class String {
private:
    char* m_buffer;
    unsigned int m_Size;
public:
    String(const char* string) {
        m_Size = strlen(string);
        m_buffer = new char[m_Size + 1];//可以用strcpy函数，拷贝时包含了终止字符串
        memcpy(m_buffer, string, m_Size + 1);//也可以用for循环来依次赋值
        m_buffer[m_Size] = 0;//为了防止字符串最后一位不能通过空字符串结束，手动添加最后一位
    }

    ~String() {
        delete[]m_buffer;
    }
    friend std::ostream& operator<<(std::ostream & stream, const String & string);
    //声明为友元，可以使重载函数访问到私有成员变量
};


std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.m_buffer;
    return stream;
}

int main()
{
    String string = "cherno";
    String second = string;

    std::cout << string << std::endl;
    std::cout << second << std::endl;

    std::cin.get();
}
```
在执行完`cin.get();`后，程序崩溃，会有如下报错：
```bash
untitled(87438,0x10c8f0600) malloc: *** error for object 0x600002c0c030: pointer being freed was not allocated
untitled(87438,0x10c8f0600) malloc: *** set a breakpoint in malloc_error_break to debug
```
当复制发生时，会将所有变量赋值到新的内存，新的内存包含了`second`字符串，所以内存中的两个`String`对象，有相同的`char*`值，换句话说，相同的内存的地址，也就是`m_Buffer`的内存地址，对于这两个`String`来说是相同的，程序会崩溃是因为当我们到达作用域尽头时，这两个`String`都被销毁，析构函数被调用，然后执行`delete[] m_Buffer`两次，程序视图两次释放同一内存块，这就是导致崩溃的原因，因为程序已经被释放了。

或许有更好的方式证明两者内存地址是相同的，当执行拷贝时，执行的是浅拷贝，在`main`的打印阶段打断点，可以看出`string`和`second`这两个字符串中的`m_Buffer`指向地址相同。

我们希望做到的是，第二个`String`有自己独立的内存，也就是深拷贝。拷贝构造函数是一个构造函数，当你复制第二个字符串时，它会被调用。当你把一个字符串赋值给一个对象（也是一个字符串）时，当你试图创建一个新的变量并给他分配另一个变量时，这个变量和你正在创建的变量有相同的变量类型，你复制这个变量，也就是所谓的拷贝构造函数。

c++有默认拷贝构造，你可以用拷贝构造做几件事，拷贝构造定义与声明。

这是默认的拷贝构造：
```cpp
    String(const String & other)//默认复制构造所做的是：内存复制，将other对象内存，浅拷贝进这些成员变量
        :m_buffer(other.m_buffer), m_Size(other.m_Size)
    {

    }
```
这样不行，因为我们不仅仅想复制指针，我们想复制指针所指向的内容。如果我们禁止复制`String(const String & other) = delete`，我们可以看到`main`函数中复制会报错，其实这就是`unique_ptr`所作的。所以我们需要建立自己的拷贝构造函数进行深拷贝。最终的代码如下：
```cpp
#include <iostream>
#include<string>
#include <memory>

class String {
private:
    char* m_buffer;
    unsigned int m_Size;
public:
    String(const char* string) {
        m_Size = strlen(string);
        m_buffer = new char[m_Size + 1];
        memcpy(m_buffer, string, m_Size + 1);
        m_buffer[m_Size] = 0;
    }

    String(const String & other)
        :m_Size(other.m_Size)
    {
        m_buffer = new char[m_Size + 1];
        memcpy(m_buffer, other.m_buffer, m_Size+1);
    }

    ~String() {
        delete[]m_buffer;
    }
    friend std::ostream& operator<<(std::ostream & stream, const String & string);
    char& operator[](unsigned int index) {
        return m_buffer[index];
    }

};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.m_buffer;
    return stream;
}
void PrintString(String string) {//惯性思维下是String string，但是正确写法是const String& string，你可以在复制构造中打印标记来试试就知道了
    //如果不加const来限制，那么string[2] = 9;，可以修改参数，除此之外，也意味着我们可以将临时的右值，传到实际函数中去
    std::cout << string << std::endl;
}


int main()
{
    String string = "cherno";
    String second = string;
    second[2] = 'a';

    PrintString(string);
    PrintString(second);


    std::cin.get();
}
```
我想告诉你的是，总是通过`const`来传递对象，我们以后再来深入讨论它的优化，因为某种情况下，复制可能更快，但无论如何，基础使用中，`const&`更好。因为可以决定在函数内部是否需要复制，但是没理由到处复制，他们会拖慢你的程序，这是很愚蠢的，当你传递字符串时，不管他是你自己的`String`类还是`std::string`总是，总是！通过引用传递。

[![top] Goto Top](#table-of-contents)

## 46. The Arrow Operator in C++

箭头操作符

```cpp
    Entity e;
    e.Print();

    Entity* ptr = &e;//指向e的指针。
    ptr.Print();//这只是一个指针，也就是数值（不是对象，根本不能调用函数）
```
但是这样是可以的：
```cpp
    Entity e;
    e.Print();

    Entity* ptr = &e;//指向e的指针。
    Entity& entity = *ptr;//逆向引用ptr
    entity.Print()
```
但是为了避免多出的这一行，我们还可以逆向引用：
```cpp
    Entity* ptr = &e;
    (*ptr).Print();
```
但是看起来很臃肿，所以总之用箭头更好，但是这只是一个快捷方式。上述方法是箭头的默认用法了，这可能是90%情况下，你使用的方式。

重载：
```cpp
class Entity {
public:
    void Print()const { std::cout << "hello" << std::endl; }
};

class ScopedPtr {//智能指针类
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity*entity)
        : m_Obj(entity) {
    }

    ~ScopedPtr() {
        delete m_Obj;
    }

    Entity* operator->() {
        return m_Obj;
    }

};


int main() {
    {
        ScopedPtr entity = new Entity();
        entity->Print();
    }
    std::cin.get();
}
```
通过重载来实现智能指针的基础用法，一旦`entity`指针消失，则实体消失

实际使用箭头操作符，来获取内存中某个成员变量的偏移量。

`x, y, z`会在内存中有不同的布局，我想写一些东西来获取这些成员的偏移量。我想做的是访问这些变量，但是不通过有效的内存地址，地址从零开始。这有点难以解释。我会写一个`0`然后将它转换成一个`Vector3`指针，然后通过箭头来访问`x`，将会得到这些内存布局。我要做的是取这个`x`的内存地址，然后得到这个`x`的偏移量，因为我从`0`开始。其中`0`也可以写成`nullptr`：
```cpp
struct Vector3 {
	float x, y, z;
};

int main()
{
	const int offset = (int)&((Vector3*) nullptr)->x;
	std::cout << offset << std::endl;
	std::cin.get();
}
```
分别将`x`替换位`y`、`z`，可以看到箭头运算符可以帮助我们来获取内存中某个值的偏移量，这是非常有用的，当你把数据序列化为一串子节流时，当你想要计算某些东西的偏移量时，当我们开始做图形编程吗，游戏引擎系列的时候，我们会接触到这些令人兴奋的代码，因为我们总是要处理子节流

[![top] Goto Top](#table-of-contents)

## 47. Dynamic Arrays in C++ (std  vector)

c++中的动态数组，特别是标准库的`vector`类（`std::vector`)。标准库，这种情况下应该叫标准模版库。标准模版库本质上是一个库，里面装满了容器，容器类型，这些容器包含特定的数据，之所以被称为标准模版库，是因为他可以模版化任何东西。整个库模版化这意味着容器的底层数据类型，换句话说，容器包含的数据类型，实际上由你决定，所有东西由模版组成，你只需要知道模版可以处理你提供的底层数据类型。这意味着你不需要编写自己的数据结构或类似的东西。

所以c++提供给我们`Vector`类在`std`命名空间中。

`vector`的命名是有故事的，他其实不应该被称为向量，他应该被称为`ArryList`，因为这更有意义，他实际上是一个动态数组。他不是一个数学向量，他有点像一个集合，一个不强制其实际元素具有唯一性的集合，换句话说，基本上是一个数组。但与c++普通数组不同的是，原始数组或者是标准数组类可以调整数组大小，这意味着当你创建这个`vector`时，当你创建这个动态数组时，他没有固定的大小，你可以给他一个固定的大小，如果你想用一个特定的大小初始化他，但是一般情况下，不给他一个特定的大小。你只需要创建一个数组，然后把元素放进去，每次你往里面放一个元素，数组大小会增长。

一半工作室和团队都会创建自己的容器库，会重写很多c++中存在的数据结构，因为会比标准模版库中快很多，因为标准模版库的速度不是优先考虑的问题。


```cpp
struct Vertex {
    float x, y, z;
};

std::ostream &operator<<(std::ostream &stream, const Vertex &vertex) {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}
int main() {
    std::vector<Vertex>vertices;

    std::cin.get();
}
```
`<>`内是模版类型，是指数组中元素的类型，我们的例子中是`vertex`，也可以是`int`之类。起名叫`vertices`，至于为什么不采用`<Vertex*>`也就是存储一堆`vertex`指针，主要考虑的是，存储`vertex`对象比存储指针在技术上更优，因为如果是`vertex`对象，你的内存分配将是在一条线上，动态数组是内存连续的数组，这意味着她在内存中不是碎片而是在一条线上，如果你这样讲`vertex`对象存储在一条直线上，你有一个顶点`x, y, z; x, y, z; x, y, z;`一个接一个，这是最优的，因为你像遍历他们、设置他们、改变他们，读取他们，或者不管你想做什么，因为在某种意义上说，他们都在同一条高速缓存线上，如果可能的话，你要试着像这样（一条线上）分配，唯一的问题是，如果要调整`vector`的大小，他需要复制所有的数据。如果你碰巧有一个字符串的`vector`，你要调整`vector`的大小，他确实需要重新分配和复制所有的东西，这可能是一个非常缓慢的操作。而指针不同，实际内存保持不变，因为你只是正确保存了指向内存的指针，到了调整大小的时候，他只是副本也就是整数，只是时机数据的内存地址吗，而数据仍然被存储在内存的不同位置，这很难决定，但是尽量使用对象而不是指针

接下来是`vector`的使用
```cpp
int main() {
    std::vector<Vertex> vertices;
    vertices.push_back({1, 2, 3});//大括号里的是初始化列表
    vertices.push_back({4, 5, 6});

    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i] << std::endl;
    }

    for (Vertex v: vertices) {//另一种遍历的方式
        std::cout << v << std::endl;
    }//这实际上是将每个vertex复制到这个for范围的循环中，我们不想那样做，尽量避免复制

    vertices.erase(vertices.begin() + 1);//删除第二个元素
    //单独去除某一个vertex，如果读C++提示读信息，可以看到参数是const iterator
    //意味着参数不能设置为2或者类似的东西，我们需要一个迭代器（iterator）

    for (const Vertex &v: vertices) {//加上&符号就不会复制，甚至可以加上const
        std::cout << v << std::endl;
    }
    //vertices.clear();//将数组大小设回0
    
    std::cin.get();
}
```
另外，当你将这些`vector`传给函数或者其他东西时，你要确保是通过引用传递他们的。如果你不会修改他们，那么用`const`引用限定，因为这样做你可以确保你没有把整个数组复制到这个函数中：
```cpp
void Function(const std::vector<Vertex>& vertices){

}

int main() {
    std::vector<Vertex> vertices;
    vertices.push_back({1, 2, 3});//大括号里的是初始化列表
    vertices.push_back({4, 5, 6});

    Function(vertices);

    std::cin.get();
}
```
以上是`vector`的基础流程，下次再讲如何优化，`vector`通常情况下就是很慢的，有些时候我们就是会压榨出所有性能，在下一个话题里见。

[![top] Goto Top](#table-of-contents)

## 48. Optimizing the usage of std  vector in C++

整个系列中，我们会很多涉及到优化，这也是c++吸引人的地方。优化最重要的规则之一就是很好的了解你的环境，环境意思是你应该了解事情怎么运转的，我该怎么做，应该会发生什么，今天我们讲一些皮毛，看看我们能做些什么，特别是`vector`例子。

通常情况下你是这样使用`vector`的，你创建一个`vector`，然后开始`push_back`元素，也就是向数组中添加元素，如果`vector`容量不够大，不能容纳你想要的新元素，基本上需要做的是`vector`需要重新分配新的内存，至少足够容纳这些想加入的新元素，当前的`vector`的内容，从内存的旧位置复制到了内存中的新位置，然后删除旧位置的内存，所以当我们尝试push_back一个元素时，如果容量用完，则会调整大小重新分配，这就是将代码拖慢的原因之一，事实我们需要不断重新分配，我们现在对于复制的优化策略，如何避免复制对象，如果处理`vector`，特别是基于`vector`的对象，我们没有存储`vector`指针，我们存储的是`vector`对象，正如所说，要知道你的环境，我们需要知道什么时候发生复制，为什么会发生。

为了查看我们复制了多少次，一个很好的方法是在`vertex`类添加一个拷贝构造函数，可能在那里放一个断点，或者只是在控制台打印一些东西，看看拷贝构造函数什么时候被调用了。

```cpp
struct Vertex {
    float x, y, z;

    Vertex(float x, float y, float z)
            : x(x), y(y), z(z) {
    }

    Vertex(const Vertex &vertex)
            : x(vertex.x), y(vertex.y), z(vertex.z) {
    //其实如果写个简单的拷贝构造，我们其实不需要填这些成员初始化列表
        std::cout << "Copied!" << std::endl;
    }

};

int main() {
    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(1, 2, 3));//改为默认构造函数，为了便于阅读
    vertices.push_back(Vertex(4, 5, 6));
    vertices.push_back(Vertex(7, 8, 9));
}
```
当我们在第一次构造处打断点，当执行完第一次构造后发现即会发生复制，原因是当我们创建`vertex`时，我们实际上是在主函数当前栈帧中构造他，所以我们在`main`的栈上创建他，然后我们需要做的是把它放到这个`vector`中，所以我们需要从那个`main`函数中，从`main`函数（把这个创建的`vertex`）放到实际的`vector`中，放到`vector`分配的内存中，我们所做的就是把`vertex`从`main`函数复制到`vector`类中。这是第一个可以优化的地方。

如果我们可以在适当位置构造那个`vertex`，在`vector`分配的内存中。继续`debug`下去，可以发现又出现两个`copied!`，发生了什么？查看变量可以看到`vertices`容量为`2`，意味着vector在物理上有足够的内存来存储两个顶点（两个顶点对象），意味着再往下走时，他需要将容量调整到3或者更高的值，这样我们才能有足够内存来放入第三个顶点vertex，这是另一个潜在的优化策略，我们的vector在这里调整里两次大小，默认大小为1，如果我们知道环境，如果我们知道计划放入三个vertex对象，那为什么不直接告诉vertex对象：嘿，制造足够3个对象的内存，这样你就不必调整两次大小了。这是第二种优化策略。

让我们来做这个快速且简单的优化策略：
```cpp
vertices.reserve(3);
```
这与调整大小（`resize`）或在构造函数中传入`3`是不同的，我们在构造中传入`3`这个参数，这段代码甚至无法编译，报错显示`vertex`没有正确的默认构造函数可用，因为这实际上不仅仅是分配足够的内存，来储存三个`vertex`对象，他实际上是构造三个`vertex`对象，我们不想构造任何对象，我们只是想有足够的内存来容他们，这就是`reserve`所做的，`reserve`可以确保我们有足够的内存，所以分三步，创建`vertices vector`，然后`reserve 3`，然后把元素`push_back`，现在`copied!`是三个而不是六个了。

但我们实际上仍然得到了一个复制`copies`，因为这个`vertex`实际上是在`main`函数中构造的，然后复制到实际的`vector`中，我想在实际的`vector`中构造，我们可以这么做，使用`emplace_back`而不是`push_back`，这种情况下不是传递我们已经构建的`vertex`对象，我们只是传递了构造函数的参数列表，他告诉我们的`vector`，在实际的`vector`内存中，使用以下参数构造一个`vertex`对象。

看看我们的优化吧，很简单，只要知道他是如何工作的，意识到`vertex`对象实际上被复制了六次，写出优化代码也不难，但是这段代码会比最初的代码运行快很多。
```cpp
struct Vertex {
    float x, y, z;

    Vertex(float x, float y, float z)
            : x(x), y(y), z(z) {
    }

    Vertex(const Vertex &vertex)
            : x(vertex.x), y(vertex.y), z(vertex.z) {
        std::cout << "Copied!" << std::endl;
    }

};

int main() {
    std::vector<Vertex> vertices;
    vertices.reserve(3);
    vertices.emplace_back(1, 2, 3);//改为默认构造函数，为了便于阅读
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(7, 8, 9);
}
```
这是我们第一次讲优化代码，以后会有更多，我们会在c++更多的讨论这类问题。

[![top] Goto Top](#table-of-contents)

## 49. Using Libraries in C++ (Static Linking)

今天讲c++库，特别是如何在项目中使用外部库。

首先，我讨厌包管理，塔檐链接到其他的代码仓库之类的东西。我理想的项目设置是，如果您签出（`checkout`）我的远程存储库，来自`GitHub`或者其他，你应该在存储库中有你所需要的所有东西，以便能直接编译和运行项目的应用程序，而不需要考虑包管理去下载其他需要的库，当然这只针对c++，我倾向于在实际解决方案的实际项目文件夹中，保留使用的库的版本，所以实际上我有那些物理二进制文件或者代码的副本，这取决于我在解决方案的实际工作目录中的使用方法。

这就引出了另一个问题，我应该自己编译这些文件吗，或者他们应该链接到预构建的二进制文件吗？对较为严谨的项目来说，我绝对推荐实际构建源代码，如果你用**visual studio**，你可以添加另一个项目，该项目包含您的依赖库的源码，然后将其编译成静态或动态库，然而如果你拿不到源码，或者你的计划这只是一个快速项目，不想花太多时间去设置他，因为这只是一次性的东西，或者是一个不那么重要的项目，那么我可能更倾向于链接二进制文件，因为这样会更快更容易，具体地说，我们将以二进制文件的形式进行连接而不是获取实际依赖库的源代码进行自己编译。

今天只讨论处理二进制，也就是上述的后者情况。今天例子是`GLFW`库。

进入下载页面后，下载的64位二进制或者32位二进制文件（Linux或UNIX只能下载源码自行编译），不取决于您电脑的操作系统，而是取决于目标应用程序，作为`X86`也就是`win32`程序，那就要32位二进制文件，如果在编译一个64位应用程序，那就要64位二进制文件，一定要匹配起来否则无法链接。

库通常包含有两部分，`includes`和`library`，包含目录和库目录，包含目录是一堆我们要使用的头文件，这样我们就可以实际使用预构建的二进制文件中的函数。然后`lib`目录中有那些预构建的二进制文件，这里通常有两个部分，有动态库和静态库，但并不是所有的库都为您提供了这种两种库，但`GLFW`库为您提供了2种，你可以选择静态链接还是动态链接。

简单讲下区别，静态链接意味着这个库会被放到你的可执行文件中，他在你的exe文件中，或者其他操作系统下的可执行文件，而动态链接库是在运行时被链接的，所以你仍然有一些链接，你可以选择在程序运行时，装载动态链接库，有一个叫做`loadLibrary`，你可以在`WindowsAPI`中使用它做例子，他会载入你的动态库，可以从中拉出函数，然后开始调用函数，你也可以在调用应用程序启动时，加载你的`dll`文件,这就是动态链接库。主要的区别是，库文件是否被编译到exe文件中或链接到exe文件中，还是只是一个单独的文件，在运行时你需要把他放在你的exe文件旁边或者某个地方，然后你的exe文件可以加载他。

通常我喜欢静态的，尽可能的链接，静态链接在技术上更快，因为编译器或链接器实际上可以执行链接时优化之类，静态链接在技术上可以产生更快的应用程序。静态库可被优化方式很多，因为我们知道在链接时我们要链接的函数。动态库链接时我们不知道要发生什么，我们必须保持它的完整，当动态链接库被运行时的程序装载时，程序的部分被补充完整。通常静态链接是最好的选择。

-include
    -GLFW
        -glfw3.h
        -glfw3native.h
-lib-vc2015
    -glfw3.lib
    -glfw3.dll
    -glfw3dll.lib

在`sln`文件夹内建立文件夹`Dependencies`文件夹，在`Dependencies`内建立GLFW文件夹，在该文件夹内放入下载的glfw库，其中dll为运行时动态链接库，我们在运行运行时动态链接时，会用到他，`glfw3dll.lib`实际上是动态库，他与`glfw3.dll`是一起用的，这样我们就不需要实际询问dll：嘿，我们有一堆指向所有这些函数的函数指针吗？也就是说，这个glfw3dll.lib文件实际上包含了`glfw3.dll`中所有的函数、符号和位置，所以我们可以在编译时链接他们。相比之下，如果我们没有glfw3dll.lib，我们仍然可以使用glfw3.dll（dll文件）我们要通过函数名来访问dll文件内的函数，但是lib文件已经包含了所有这些函数的位置，连接器可以直接找到他们。

glfw3.dll，你可以看到，静态链接库比其他的大很多，如果我们不想编译时链接，我们就链接这个（lib），如果这样，我们在运行exe时，我们不需要这个dll。

在设置中的`configuration`设置为`all configuration`，设置include目录，sln为解决方案目录，从这个目录开始，我可以输入`$(SolutionDir)`，这是一个宏，在vs中可以使用，在宏中可以搜索以及查阅存在的宏的值，如`ProjectDir`等，在宏后无需加`/`因为宏自带了。尖括号和`"`区别，实际上没区别，因为如果引号的话会先检查相对路径，如果它们有找到任何相对于这个文件的东西，也就是相对于`main.cp`文件他就回去找编译器，他会检查编译器的`include`路径，我选择的方法是，如果这个源文件在vs中，所以如果`GLFW.h`在解决方案的某个地方，也许在另一个项目，没关系，只要在这个解决方案里，那就用引号，如果它完全是一个外部依赖，或者外部库，不在vs中和解决方案一起编译，那就用尖括号，来表示他实际上是外部的。这个例子中，用尖括号。

如果只是这样，添加里`include`路径，头文件添加`include`，可以编译通过，但是会报链接错，因为连接器无法找到具体函数。进入头文件可看到，只有函数声明但无函数定义，相当于只是有：`GLFW int glfwInit(void);`，这里只有一个分号，只有函数签名，我们需要做的是找到这个函数的定义，如果此时你自己写一个定义，完全可以编译通过，比如`int glfInit(){return 0;}`那么build没有问题，可以成功生成exe文件，很显然我不想要这个函数，而是要库里面的那个，所以我们需要链接到库，设置中选择`linker`，`general`，在`linker`下的`input`，我们要包含`glfw3.lib`文件，在`Additional Dependencies`中添加lib但是我不想添加完整路径，虽然我也可以输入`$(SolutionDir)`等等，但我指向保持干净，只想写`glfw3.lib`，如果想这么做，我要在`linker`的`general`中设置附加库目录，就像在c++的`general`下，附加包含目录中所作的一样，所以这应该是包含我`glfw3.lib`库文件的根目录。

这些头文件可以自己写里面的内容，库的链接也好，头文件也好，并没有什么了不得的魔法，他们只是将系统的所有组成部分链接在一起，因此头文件通过提供声明，告诉我们哪些函数是可用的，然后库文件为我们提供了定义，这样我们就可以链接到那些函数，并在c++中调用函数时执行正确的代码。

[![top] Goto Top](#table-of-contents)

## 50. Using Dynamic Libraries in C++

今天我们将讨论如何动态链接，它是什么，如何使用它，什么时候应该使用它。还是拿GLFW举例

之所以称为动态链接，是因为动态链接是链接发生在运行时。静态链接是在编译时发生的，当你编译一个静态库的时候将其链接到可执行文件，也就是应用程序，或链接到一个动态库，这有点像你取出静态库的内容，然后将这些内容放入到其他二进制数据中，它实际上在你的动态库或者在你的可执行文件中，正因为如此，有很多优化可能发生，因为编译器和链接器现在完全知道，静态链接时，实际进入应用程序的代码。总之记住，静态链接允许更多优化发生，因为编译器和链接器可以看到更多东西（从静态链接中），特别是链接器，可以看到更多。

而动态链接就像我提到的，发生在运行时，这意味着只有当你真正启动可执行文件时，你的动态库才会被加载，所以它实际上不是可执行文件的一部分，当你执行一个普通的可执行文件时，可执行文件会被加载到内存中，然而如果您有一个动态链接库，这意味着您实际上链接了另一个库，一个外部二进制文件，在运行时动态的链接，这样当运行您的应用程序时，你将一个额外的文件加载到内存中。现在可执行文件的工作方式变了，他现在需要某些库，某些动态库，某些外部文件，在实际运行应用程序之前，就需要具备这些（库、外部文件），这就是为什么在windows上，例如，你可能会看到，当你启动一个应用程序时，你可能会看到当你启动一个应用程序时，你可能会看到一个错误消息弹出，比如需要`dll`，或者没有找到`dll`，这是动态链接的一种形式，我喜欢叫他“彼此彼此”，因为可执行文件知道动态链接库的存在，可执行文件实际上把动态库作为一项需要，虽然动态库仍然是一个单独文件，一个单独模块，并且在运行时加载，你也可以完全动态的加载动态库，这样可执行文件就与动态库完全没有关系了，你可以启动你的可执行文件，你的应用程序，她甚至不会要求你包含一个特定的动态库，但是在你的可执行文件中，你可以写代码去查找并在运行时加载某些动态库，然后获得函数指针或任何你需要的那个动态库中的东西，然后使用那个动态库。对于动态库，请记住这一点，其中之一是“静态的”动态库版本，我的应用程序现场需要这个动态链接库，我已经知道里面有什么函数，我可以使用什么。然后另一个版本是我想任意加载这个动态库，我甚至不知道里面有什么，但我想取出一些东西，或者我想用它做很多事情。这两种动态库他们都有很好的用途。

我们先专注第一种形式。

`include`不用变，头文件同时支持静态和动态链接，对于函数之类的声明，实际上有一些不同之处，这个等会会有展示。在`linker`设置中去掉静态`lib`替换为动态`lib`。所需为:`glfw3.dll`、`glfw3dll.lib`，后者基本就是一堆指向`dll`文件的指针，这样我们就不用在运行时去检索所有东西的位置，同时编译这两个文件是非常重要的，因为如果你尝试不同的静态库，在运行时链接到`dll`，你可能会得到不匹配的函数和错误类型的内存地址，函数指针不会正常工作。所以这两个文件是由`glfw`发行的，所以他们是同时编译的，他们是直接相关的，你不能把他们分开。

回到vs中，只在`linker`中添加`glfw3dll.lib`是不行的，虽然可以产生可执行文件，但是启动应用程序时会报错`dll`找不到，最简单解决方案是将`dll`和可执行文件放在一起。你也可以设置库的搜索位置，但是可执行文件的根目录下，也就是包含你程序的目录，是一种自动搜索路径。

回到头文件。我们来看看静态链接和动态链接之间的区别。

具体来说，如果我们看这里的任何函数，你会看到他在返回类型和实际函数名前定义了`GLFWAPI`，如果我去看他的定义，这里有几个定义，选取其中一个，你可以看到，我们有这整个东西，在这个条件下，如果我们是Windows系统下，如果我们要构建`dll`，然后他会输出`dll`函数，这很重要，如果没有构建这个，程序就不能工作。然后如果定义了`win32`和`glfw_dll`，意思是我们将`glfw`作为`win32 dll`调用，也就是declspec(dllimport)，然后就是构建静态库了，调用`glfw`静态库，这里定义`#define GLFWAPI`为`nothing`，这也是现在定义的（情况），这里有一个有趣的问题，我们仍然定义`GLFWAPI`啥也不是（`nothing`），即使我们把它当作真正的dll来使用，所以`GFLW_DLL`应该被定义吗？如果我进入属性，进入c++的`preprocessor`，然后添加预处理定义`GLFW_DLL`，我们重新编译依次，ok，看起来很合法，这里发生了什么？为什么我不需要定义`declspec dllimport`？什么都没用？到底为什么，不需要`declspec dllimport`就能在`dll`文件中成功的链接到这些函数？

请评论留言。

[![top] Goto Top](#table-of-contents)

## 51. Making and Working with Libraries in C++ (Multiple Projects in Visual Studio

c++中创建与使用库。今天主要讲如何在visual studio中建立多个项目，以及如何创建一个库让所有项目都能使用。这是非常重要的一点，如果你的项目很大的话，它不仅可以帮助您用代码创建模块或库，并多次重用这些代码，还允许你混和语言。

我们将讨论如何创建一个项目作为库的项目，特别是静态库，然后链接到一个可执行文件中。

在创建项目最开始阶段，选择模版时，勾选Creat directory for solution，我们做一个叫game的项目，也就是实际的可执行程序，然后做一个叫Engine的库，他将链接到游戏中。在项目属性中，注意将General下的Project Default的Configuration Type设为Application(.exe)，Engine设置为Static Library(.lib)，在大多数情况下，都会设置为静态库，再次强调，确保所有配置甚至所有平台上都修改。

在include之后，可以将Engine.h改为尖括号，但是我不喜欢这么做，还是上一节讲的道理，如果我包含了vs解决方案之外的东西，我会使用尖括号，也就是一些完全与项目无关的外部依赖项，如果这个engine.h的代码实际上是在这个解决方案中找到的，具体地说，是我在这个解决方案中写的东西，而不是c++标准库，我将使用引号，来表明这是我们的源文件之一。

在设置好include路径后，再引入需要的头文件，便可以生成理想的lib文件，这是我们想要链接的，现在我们可以做的是到连接器设置把它作为输入，但我们不需要这么做，vs帮我们做了。我们右键Game，点击add，然后reference，然后可以选择engine项目，这个给了我们好处，出了不需要处理链接输入文件之外，很明显当我们把engine改成Core之类的名字，vs参与使得我们无需重新修改输入lib，这些都是自动化的，除此之外，不得不说的一个好处是，Engine现在是Game的依赖，Game依赖于Engine，这意味着如果Engine内部某些东西发生了变化，然后我们去编译Game，Game实际上是要编译的Engine和Game，所以我们知道我们总是在处理最新的代码，而不会是编译到一半发现Engine忘记编译了，导致各种不能用。

你可以尝试clean然后rebuild，可以看到是先构建了engine然后构建Game，Game需要Engine才能工作，因为Game引用了Engine。

现在回到代码，尽管我们有两个项目，如果我进入解决方案目录，debug目录下，将game.exe文件复制到其他位置，这就是运行这个程序所需的，双击即可执行，就是这样，因为当我们静态链接时，所有东西都被放入这个exe文件，没有外部文件依赖。这非常有用，因为如果我们真的要构建一个游戏引擎，我们可能会这样做，这个解决方案有好几个项目，比如引擎使用，比如几个游戏等等，这就是我们想要模块化的原因，这样所有核心代码都集中在一个项目中，然后我们就可以将我们所有的实际应用，所有可执行程序，链接到一个集中的项目

[![top] Goto Top](#table-of-contents)

## 52. How to Deal with Multiple Return Values in C++

c++中如何处理多返回值。这一集我们讨论什么是元组tuple，什么是pair，如何在c++中处理多个返回类型。

具体来说，我们有一个问题就是我们有一个函数，这个函数需要返回两个字符串，c++默认是不能的，返回两种类型，通常来说，一个函数要返回整形和字符串之类的，我们就会有麻烦。如果有一个函数要返回两个或者多个相同类型的变量，则可以返回vector或数组，或者之类的东西，只包含这两个元素，不过这也不是最好的做法，同样的问题，如何返回不同类型的变量。

快速补充一点，输出变量前最好加上out。

通过输入参数的方法肯定可以，但是较为麻烦，所以虽然cherno讲到了，但是暂时不做记录。

**返回数组：**
```cpp
static std::string* Parese(const std::string& filePath) {
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];

    return new std::string[2]{ vs,fs };
}

int main() {

    std::string* source = Parese("D:\pyl\devNotes");
    std::cin.get();
}
```
main中的数组有点烦，因为我们不知道他有多大，对吧，她只是一个指针

**最简单的，最后一种方法，是返回一个`std::array`：**

```cpp
static std::array<std::string,2>Parese(const std::string& filePath) {//类型为string，大小为2
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];
    return std::array<std::string, 2>();//不知道如何接收参数，甚至不知道是否接收参数
}

int main() {
    std::array<std::string,2> source = Parese("D:\pyl\devNotes");
    std::cin.get();
}
```
我不常使用std::array，但是有一种方法肯定可以，创建数组。
```cpp

static std::array<std::string,2>Parese(const std::string& filePath) {
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];

    std::array<std::string, 2> result;
    result[0] = vs;
    result[1] = fs;

    return result;
}

int main() {
    std::array<std::string,2> source = Parese("D:\pyl\devNotes");
    std::cin.get();
}
```
这里可以换为std::vector，两者主要区别是array会在栈上创建，而vector会把它的底层存储存储在堆上，所以从技术上讲，std::array会更快。

以上是返回两个相同类型的方法，下面是一种通用大方法，来返回两个不同类型的变量。

**tuple(元组)：**

tuple基本上是一个类，它可以包含x个变量，但他不关心类型。

```cpp
static std::tuple<std::string, std::string> Parese(
    const std::string& filePath) {
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];

    return std::make_pair(vs, fs);
}

int main() {
    std::tuple<std::string, std::string> source = Parese("D:/pyl/devNotes");
    std::cin.get();
}
```

如果将source作为输入，从tuple里面取数据：
```cpp
static std::tuple<std::string, std::string> Parese(
    const std::string &filePath) {
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];

    return std::make_pair(vs, fs);
}

int main() {
    auto source = Parese("D:/pyl/devNotes");
    // std::string vs = std::get<0>(source);
    // std::string fs = std::get<1>(source);

    unsigned int shader = CreatShader(std::get<0>(source), std::get<1>(source));
    std::cin.get();
}
```
代码风格很诡异，0和1是我们实际变量的名字，很难分辨，哪个是vertex哪个是fragment，从逻辑上来讲，01顺序是没错的，但如果有人不知道他们在做什么，那就搞不清了，我们不能用数字来处理名字。

如果换成pair：
```cpp
static std::pair<std::string, std::string> Parese(
    const std::string &filePath) {
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];

    return std::make_pair(vs, fs);
}
```
区别是，仍然可以用`std::get<>();`，但是此时可以用`unsigned int shader = CreatShader(source.first,source.second);`因为他们是一对，这样更好一些，就语法而言。

但是我仍然不知道第一个变量，第二个变量是什么。所以这就是为什么我用`struct`结构体来做。和这边返回一对（pair）差不多，但是可以对变量命名。

```cpp
struct Shade {
   std::string VetexSource;
   std::string FragmentSource;
};

static Shade Parese(const std::string& filePath) {
   //这里shade背后就是一个pair，由两个string组成，所有东西在栈上创建
   std::string ss[2];

   std::string vs = ss[0];
   std::string fs = ss[1];

   return {vs, fs};
}

int main() {
   auto source = Parese("D:/pyl/devNotes");

   unsigned int shader = CreatShader(source.VetexSource, source.FragmentSource);
   std::cin.get();
}
```
肯定还有很多其他处理多返回的方法，有待开发。

[![top] Goto Top](#table-of-contents)

## 53. Templates in C++

c++模版，其他语言里的“范型”，但是她比范型和那些托管语言牛逼的多，模版有点像宏，他可以让你做很多事，而范型却非常受制于类型系统。模版是一个巨大、复杂的话题，本次只是其中之一。

模版允许你定义一个可以根据你的用途进行编译的模版，你可以让编译器为你写代码，例如当我在写一个函数时，我在这个函数里面使用模版，我实际在做的事创建一个蓝本，因此当我决定要调用这个函数时，我可以指定特定参数，这个参数决定了放入到模版中的实际代码，这些就决定了我实际如何使用这个函数，我可以给你定义，在cpp reference或维基百科中都有，最好的方法还是在代码中。

一个很好的例子展示为什么要使用模版

语法：`template<typename T>`，`t`是模版的名字。
```cpp
template <typename T>
void Print(T value) {
    std::cout << value << std::endl;
}
//这段其实不是一个真的函数，只有当我们实际调用的时候才会被真正创建，当我们调用的时候，基于传递的参数，这个函数才会被创建出来，并作为源码编译
//在这个例子中，我们选择typename作为模版的参数类型，T作为名字，也可以写成Cherno，他实际是模版的参数名称，我们可以在整个模版代码中使用，替换在例子中出现的类型。
int main() {
    Print("hello!");
    Print(5);
    
    std::cin.get();
}

```
函数输入部分不写实际变量类型，而是换成了`T`，这段代码已经可以完成工作了。

现在这个例子有些难读，因为他看上去像显式指定参数类型，实际上这个类型是隐式地从实际参数中得到，实际上可以`Print<int>(5);`指定类型。也可以`Print<std::string>("Hello!");`。回到原来的代码，我们在这里使用的参数有可能计算（推导）出类型，返回类型也可以，我们稍后再谈，所以`Print(5);`是可行的，换句话说，c++编译器知道5是一个`int`，他能自动推导出类型T是什么，所以上述我们没有必要尖括号指定类型。

如果我们不调用Print函数，那么这个模版只是一个模版，只有调用这个函数时，这个函数才会被实际创建，使用我们给定的模版来创建，所以即便模版里有语法错误也没关系，因为直到我们调用，这个模版才真实存在，只有当它基于你模版的使用情况，发送到编译器，进行编译后，才会具体化为真正的代码，MSVC编译器不会对你不使用的模版错误进行报错，但是clang会。


```cpp
template <typename T>
void Print(T value) {
    std::cout << value << std::endl;
}
void Print(int value) {
    std::cout << value << std::endl;
}

int main() {
    Print(5);
    std::cin.get(); 
}
```
第二个函数就是编译时候的实际过程，将int替换了T，就像填空。

模版绝不仅限于类型或者任何东西，也不会仅限于函数，你也可以创建一个类，基于模版，事实上，大量的c++标准模版库完全使用了模版，再来个不用类型做参数的模版例子。

这次作用在类上，而不是函数上。
```cpp
template <int N>

class Array {
    //我想让array类创建在栈上
    //我想要一个数组，他的大小是在编译时确定的
   private:
    int m_Array[N];

   public:
    int GetSize() const { return N; }

};

int main() {
    Array<5>array;
    std::cout<<array.GetSize()<<std::endl;

    std::cin.get();
}
```
这段代码在编译时实际会发生什么：
```cpp
class Array {
   private:
    int m_Array[5];

   public:
    int GetSize() const { return 5; }
};
```
这才是最后生成的代码。

所以你看我们不一定非要使用types，我们也可以使用整数或者其他数据类型，来指定我们想要如何生成一个类和整个类，让我们更进一步：
假设我们不显式地制定`int`，同样我也希望能在编译时候指定这个数组实际包含的类型，所以我们在整形前添加类型参数。
```cpp

template <typename T,int N>

class Array {
    //我想让array类创建在栈上
    //我想要一个数组，他的大小是在编译时确定的
   private:
    T m_Array[N];

   public:
    int GetSize() const { return N; }
};


int main() {
    Array<int,5>array;//Array<std::string,5>array;之类的等等
    std::cout<<array.GetSize()<<std::endl;
    
    std::cin.get();
}
```
这很酷，我们在这里创建的array与标准数组类在c++标准模版库中的工作方式非常相似，标准库有两个模版参数，type和size。这有点像c++的meta programing（元编程），因为你可以看到相比于实际的编程，我们的代码运行时，编译器在编译时实际的在进行编程。

这只是冰山一角，我的意思是，这可能很快就变得很疯狂。

在哪里使用模版呢，完全是个人观点，根据我的经验，这是他的运行方式，很多公司禁止使用模版，我觉得反应过度了，我觉得模版很有用，在日志系统、材质系统或者其他使用场景下。如果你的模版变得非常复杂，你开始让他为你生成一个完整的元语言，这个就是噩梦。这有一个平衡点，当模版越来越复杂时名，，那就有问题了，没人知道在搞什么，甚至不得不拿一个笔记本，然后开始手动填写这些类型，这样我觉得你搞的有点过了，我不认为你应该对模版太过疯狂，即使你可以。手动做一些事情，自己写代码，实际上会让你和团队收益更多。


值传递：
形参是实参的拷贝，改变形参的值并不会影响外部实参的值。从被调用函数的角度来说，值传递是单向的（实参->形参），参数的值只能传入，不能传出。当函数内部需要修改参数，并且不希望这个改变影响调用者时，采用值传递。

指针传递：
形参为指向实参地址的指针，当对形参的指向操作时，就相当于对实参本身进行的操作

引用传递：
形参相当于是实参的“别名”，对形参的操作其实就是对实参的操作，在引用传递过程中，被调函数的形式参数虽然也作为局部变量在栈中开辟了内存空间，但是这时存放的是由主调函数放进来的实参变量的地址。被调函数对形参的任何操作都被处理成间接寻址，即通过栈中存放的地址访问主调函数中的实参变量。正因为如此，被调函数对形参做的任何操作都影响了主调函数中的实参变量。

[![top] Goto Top](#table-of-contents)

## 54. Stack vs Heap Memory in C++

堆和栈的内存比较。今天我们谈谈内存。

他们是什么，当程序开始的时候，他被分成了一堆不同的内存区域，除了堆和栈之外，还有很多，但我们最关心的两个，是这两个。程序开始的时候，操作系统要做的就是，将整个程序加载到内存，并分配一大堆物理ram，以便我们的实际应用程序可以运行。

栈和堆是ram中实际存在的两个区域，栈通常是一个预定义大小的内存区域，通常2兆字节左右。堆也是一个与定义默认值的区域，但是他可以生长，并随着程序的进行而改变，重要的是要知道这两个内存区域的实际位置，在我们的ram中是完全一样的，很多人倾向认为栈可能是存储在cpu缓存中或者类似的地方，他活跃在缓存中，因为我们不断访问他，不能这样理解，不是所有的（栈内存）会存储在这个场所。只要记住，这两个内存实际位置都在我们的内存中，这就是为什么我们的内存有两个不同的区域，我们的程序中，内存是用来实际存储数据的，不管是局部变量还是从文件中读取的东西，栈和堆是我们存储数据的地方，他们工作原理非常不同，但本质上他们做的事情一样，c++可以给我们分配内存，堆和栈不同之处在于，他如何为我们分配内存。

举个例子，假设存储一个整数，int为4字节，那么我们如何找到一个由四个字节的内存组成的连续块，连续的意思是在一行中，栈和堆给我们内存的方式是不同的，当我们这样要求内存的时候，叫内存分配（memory allocation）。


```cpp
struct Vector3{
    float x,y,z;
};
```
栈：`Vector3 vector;`，堆：`Vector3* hvector = new Vector3();`，圆括号是可选的，但我习惯写上。

```cpp
struct Vector3 {
    float x, y, z;
    Vector3() : x(10), y(11), z(12) {}
};

int main() {
    int value = 5;
    int array[5];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;

    Vector3 vector;

    int* hvalue = new int;
    *hvalue = 5;
    int* harray = new int[5];
    harray[0] = 1;
    harray[1] = 2;
    harray[2] = 3;
    harray[3] = 4;
    harray[4] = 5;
    Vector3* hvector = new Vector3();

    delete hvalue;
    delete[] harray;
    delete hvector;

    std::cin.get();
}
```
在`int value = 5;`处打断点，观察栈分配的变量，尤其是他们的地址，可以看到数组或者value的内存就在附近，他们紧挨着，现在两者之间有一些字节，这只是因为我们在debug模式下运行，他实际上只是添加了安全守卫（safety guards），在所有变量周围，以确保我们不会溢出所有的变量，在错误的内存中访问他们，以及诸如此类的东西。

所以在内存中，他们都很近，因为实际发生的是，但我们在栈分配变量时，发生的是，栈指针，也就是栈顶部的指针，基本上就是移动这么多字节，如果我想分配一个4个字节的整数，我们把栈指针移动4个字节，如果我想分配一个数组，就像我们这里5个整数，是4乘以5，栈移动20字节，最后vector一样，内存实际上是相互叠加存储的，像一个栈，现在大多数栈实现中，栈是倒着来的，就是你现在看到这样，更高的内存地址，是第一个变量value，int value存储在更高的内存地址上，然后我们把数组存储在他旁边，在一个较低内存的地址，因为他是反向生长的，栈的做法就是，只是把东西堆在一起，这就是为什么栈分配非常快，他就像一条cpu指令，我们所做的就是移动栈指针，然后我们返回栈指针地址，就是这样。我要分配一个整数，这是四个字节，在这种情况下，我移动栈指针，反向移动四个字节然后返回那个内存地址，因为这是4个字节的开始，这就是栈分配，非常快。

堆，你调用了new，但是如果你用智能指针，也一样，他们会帮你调用new，其次，当然是你需要delete你new的内存，栈则不用，一旦作用域结束，栈分配内存就会弹出，释放掉，栈移动到它原来的位置，也就是我们进入到这个作用域之前到位置。

new实际上调用了一个叫malloc的函数，memory allocate的缩写，这样通常会调用底层操作系统或者平台特定函数，这将在堆上为你分配内存，他这样做的方式是，当你启动你的应用时，你会得到一定数量的物理ram分配给你，你的程序会维护一个叫空闲列表（free list）的东西，他是跟踪哪些内存块是空闲的，还有他们在哪里等，所以当你需要动态内存的时候，使用动态堆内存，当您使用malloc请求堆内存时，他可以浏览空闲列表，然后找到空闲内存，至少和你一样大，我会给你他们的一个指针，然后我还要记录一些东西，比如分配的大小，和他现在被分配的情况，你不能使用那块内存了，有一堆记录要做，然后你得到了那个指针，malloc实际实现是很复杂的，有很多操作，不仅仅是记录，当你想要更多内存，超过了空闲列表，超过了操作系统给你的初始分配，这时候你的程序需要访问你的操作系统，嘿，我需要更多内存，这种情况是非常麻烦的，潜在成本巨大，我想说的是在堆分配内存是一大堆事情，然而在栈分配就像一条cpu指令，这就是所有我想告诉你的。

分配才是两者快慢的主要矛盾。

control + F7编译，在设置里c++ output files下，我将assembly output选成assembly with source code，然后可以看到汇编代码。

尽量在栈分配，在堆分配的唯一原因，是你不能在栈分配，比如需要这个生命周期比函数作用域更长或者你在处理的作用域更长，或者你需要特别多的数据，比如我想加载一个纹理，有50M这么大，这就不适合在栈分配。


侯捷：
Stack:是存在于某作用域(scope)的一块内存空间(memory space)，例如当你调用函数，函数本身形成一个stack用来放置他所接收的参数，以及返回地址。

在函数本体(function body)内部声明的任何变量，其所使用的内存快都取自上述stack。

Heap:或者是system heap，是指由操作系统提供的一块global内存空间，程序可能动态分配(dynamic allocated)从某中获得若干区块（blocks) 

```cpp
class Complex{...}
...
{
    Complex c1(1,2);
}
```
c1就是stack object，其生命期在作用域之内，又称为auto object。

```cpp
class Complex{...}
...
{
    static Complex c1(1,2);
}
```
这种叫static object，其生命周期在作用域(scope)结束之后仍然存在，知道整个程序结束。

```cpp
class Complex{...}
...
Complex c1(1,2);
{
    ...
}
```
全局变量。

若忘记delete出现的状况就是出了作用域，指针所指向的object仍然存在，但是指针已经消失了，这样叫做内存泄漏。



[![top] Goto Top](#table-of-contents)

## 55. Macros in C++

宏，但是今天只是概述。

不管定义是什么，今天特别要讲的是，在c++中使用预处理器来“宏”化某些操作，这样就不用手动一遍又一遍手动输入代码了，我们可以用预处理器来实现自动化。当编译时，预处理器会过一遍你所有语句以`#`开头，这是预编译指令，当预编译器评估完代码后，会把评估后的代码给到编译器，进行实际编译以及其他操作，预编译阶段基本上是一个文本编辑阶段，这个阶段，我们可以控制什么代码实际送给编译器这是宏的用武之地，我们能做的事就是写一些宏，他将代码中的文本替换为其他东西，这基本上就像遍历我们的代码然后执行查找和替换，不一定是简单替换，它可以做形参，实参和变量来查找和替换，我们可以自定义调用宏的方式，定义宏如何展开，这可能会非常复杂。

和最近讨论的模板还是有区别的，因为他们发生的时间不同，模板评估时间会更晚。对宏来说，没什么不可替换的，因为它发生在编译之前。和模板最后讲的一样，尽量不要搞得太复杂，有个度。

不要认为你要使用每一个c++特性来编写你的程序，不是这么回事，这不是你写好代码的方式，不要向每个人炫耀你知道所有c++的特性，我只希望你努力写出好代码。

代码：
```cpp
#include <iostream>
int main() {
    std::cin.get();
}
```
宏之后：
```cpp
#define WAIT std::cin.get()
//注意上一行不用加;
int main() {
    WAIT;
}
```
每当遇到WAIT则文本替换为宏部分。但是这很蠢，因为如果这个宏是在另一个文件定义的，那你在这个文件只看到`WAIT`，你尽量不要写让人困惑的代码，所以不要这么使用宏。至于为什么不加分号，是因为分号加载main函数中看起来更合理。

```cpp
#define OPEN_CURLY {

int main() OPEN_CURLY

    std::cin.get();
}
```
看起来很蠢但是编译没问题。不要这么搞。
看看实际用法：
```cpp
#define LOG(x) std::cout<<x<<std::endl

int main() {


    LOG("hello");

    std::cin.get();
}
```
日志场景，控制debug模式输出日志，在release模式去掉日志，在c/c++的Preprocessor Definitions中，定义一些东西，叫做DEBUG，编译器可能有也可能没有，不如我们换做PR_DEBUG吧，PR这两个字母来自我们项目名，看起来像是我自己的宏，他就像命名空间namespace一样，不会和其他宏冲突,在release中定义PR_RELEASE。

```cpp
#ifdef PR_DEBUG
#define LOG(x) std::cout<<x<<std::endl
#else
#define LOG(x)//后面没有跟任何东西，它将会被替换为空
#endif



int main() {
    LOG("hello");

    std::cin.get();
}
```
这段代码是有问题的，首先使用`ifdef`这不太好，我可能会让`PR_DEBUG = 1;`我会给它一个实际的值而不是仅仅定义它。如果仅仅是定义，如果你误解了他的意思，在宏中，你可以仅仅做一个符号定义，`#define PR_DEBUG`

```cpp
#define PR_DEBUG 0//在这里控制PR_DEBUG（这个0处），也可以在项目属性的预处理定义，可以控制宏时，不必每次将所有不需要的宏全部注释或删除掉

#if PR_DEBUG == 1
#define LOG(x) std::cout<<x<<std::endl
#else
#define LOG(x)//后面没有跟任何东西，它将会被替换为空
#endif
```
另一个问题，算不上真的问题，但是我们仍然可以做的是，
```cpp
#define PR_DEBUG 1

#if PR_DEBUG == 1
#define LOG(x) std::cout<<x<<std::endl
#elif defined(PR_RELEASE)
#define LOG(x)
#endif
```
使用if而不是ifdef，ifdef很多情况更糟糕。

btw：
```cpp

#if 0

#define PR_DEBUG 1//在这里

#if PR_DEBUG == 1
#define LOG(x) std::cout<<x<<std::endl
#elif defined(PR_RELEASE)
#define LOG(x)
#endif

#endif
```
if 0可以将这段代码折叠掉，处于禁用状态，这是利用宏来删除特定的代码。

我们还能做很多其实，很多是为了debug，老实说，宏对调试来说很有用，
```cpp
#define  MAIN int main()\
{\
    std::cin.get();\
}
MAIN
```
其中`\`是换行符，确保你的`\`后没有空格，否则就会变成空格转义而不是换行了。

再一个例子，关于内存分配，在debug构建中，我们想知道多少字节被分配了，从哪个文件和哪行代码，就像是告诉我，在main.cpp的第15行，我分配了28字节，我想知道这些，为了跟踪或者调试的目的，如果你把new关键字替换成一个自定义的单词，他会自动跟踪是从哪个文件的哪一行进行的分配。

[![top] Goto Top](#table-of-contents)

## 56. The 'auto' keyword in C++

auto关键字。auto带来两面性，我们主要想这样：你可以这样使用它，但你不应该滥用它。

两面性：
```cpp
std::string GetName()
{
    return  "cherno";
}
int main()
{
    auto name = GetName();
    std::cin.get();
}
```
name变量无需改变即可接收GetName的输出，当返回值类型发生变化时，比如：
```cpp
char* GetName()
{
    return  "cherno";
}
int main()
{
    auto name = GetName();
    std::cin.get();
}
```
string变为char*，name类型无需二次改变代码，这点挺有用的，因为如果我开始改变我的api，可以看到在客户端不需要改变代码，也就是在main函数中无需改变，尽管我改变了返回类型，但是当我调用`int a = name.size();`或类似的东西，这时候main中的auto就是不行的了（改回string还是可以的），因此这是一个硬币的两面。一方面，改变api时候，客户端无需重复修改，但是另一方面，因为我不知道api已经变了他可能会破坏依赖特定类型的代码。一方面，你不用改任何代码，一方面他可能造成破坏。所以这些时候我不喜欢用auto（很多插件可以提示类型了不过）。

使用auto比较好的地方：
```cpp
int main()
{
    std::vector<std::string> strings;
    strings.push_back("apple");
    strings.push_back("orange");

    for (std::vector<std::string>::iterator it = strings.begin();
        it != strings.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::cin.get();
}
```
类型名很长的时候，增强可读性，`std::vector<std::string>::iterator`是一个巨大的类型，我可以直接写auto，
```cpp
for (auto it = strings.begin();
    it != strings.end(); it++)
{
    std::cout << *it << std::endl;
}
```
另一个例子，真实项目中的场景：
```cpp

class DeviceManager
{
private:
    std::unordered_map<std::string, std::vector<Device*>>m_Device;//一个从string到vector<Device*>的map（映射），变量名叫m_Devices。
public:
    const std::unordered_map<std::string, std::vector<Device*>>&GetDevices() const
    {
        return m_Device;
    }

};


int main()
{
    DeviceManager dm;
    const std::unordered_map < std::string, std::vector<Device*>>& devices = dm.GetDevices();
    
    std::cin.get();
}
```
在这里每当使用这个类型变量的时候，用以using，`using DeviceMap = std::unordered_map<std::string, std::vector<Device*>>`，这段定义可以放在main中使用，也可以在类定义时就定义清楚。

所以上述情况是使用auto的一个好场景。但是有注意事项：
```cpp
    const auto& devices = dm.GetDevices();
    auto devices = dm.GetDevices();
```
第一行是引用，而第二行会发生复制，不会发生引用，所以我们复制了整个map到一个局部变量，你可能会返回一个引用，但这并不意味着你会将它存储为一个引用。

总之变量名很长的时候，我会考虑，但是类似int或者string，我绝对不会使用auto，因为这会降低代码可读性，在我看来没啥好处。当然，当进入更加复杂的代码集，包含了模板，你不得不使用auto，没有别的办法，因为你不知道类型是什么，但是说回来，我不会让自己代码复杂到必须使用auto的地步。

不管怎样，除了刚才说的auto使用场景，它也可以使用在后置返回类型或者你可以使用与函数，在c++14中，
```cpp
auto GetSize()
{
}
```
或者在这之前c++11标准下，你可以使用后置返回类型
```cpp
auto GetSize()->char*//通过这样来确定类型
{
}
```

decltype关键词：定一个一个变量与某一表达式的类型相同，但并不用该表达式初始化变量：
`decltype(i)j = 2`表示`j`以`2`作为初始值，类型与`i`一致。

[![top] Goto Top](#table-of-contents)

## 57. Static Arrays in C++ (std  array)

c++标准数组。今天我们要特别专注于一个实际的类，标准数组类，是c++标准模板库的一部分，c++库提供给你的用来处理静态数组，这里的静态数组我指的是不增长的数组，当你创建这个数组时，你来定义他有多大，也就是有多少元素，以及里面是什么类型的元素，但是不能改变大小，从这里开始，它的大小就是一个常数。

`#include <array>`

`std::array<int, 5>date;`参数99.9%需要用两个，

如果是传统数组：
```cpp
void PrinArray(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {

    }
}
```
接收一个指向数组的指针，然后遍历数组，遍历时无法知道数组长度的唯一解决办法就是传入数组长度的参数，但是如果用std::array的话，可以直接获取出数组大小，因为本身就是一个类：
```cpp
std::array<int, 5>date;
date.size();
```
不仅如此，我们也可以用它做其他事情，我们可以将它作为迭代器，有begin有end，我们可以通过foreach循环来遍历，我们也可以使用大量std（标准模板库）算法，因为支持迭代器，比如我们可以使用std::sort对数组进行排序，因为他是一个实际的数组类。

但是最大的好处是，如果我们有这样一个普通数组，`int dateOld[5];`我们必须要一直维护它，要一直知道它的大小，否则我们就不能正确使用这个数组。然而两种数组工作方式一样，都存储在栈，和std::vector在堆上创建不同，而且如果可以设定ITERATOR_DEBUG-LEVEL宏，他就会做边界检查，当你越界操作数组时，debug模式下会发生警告，而不至于像普通数组发生修改越界的数值的同时编译器不报错。

下一个问题是，它占用了多少内存？因为他存储了大小。

不，它实际上不存储大小，size时你给他的一个模板参数，这意味着size函数直接就返回5，他不返回size或size变量存储在栈或堆上的某个地方。

下一个问题，你怎么知道的？

很多情况下是经验之谈。但这里我们可以看std::array的源码。size函数和max_size函数都会返回_Size，也就是模板的参数。

总之，你应该开始到处使用这个std::array，而不是普通的c语言数组，因为他有增加了一层调试，如果你希望对代码进行保护，而且也没有性能代价，而且它还可以记录数组大小等。

[![top] Goto Top](#table-of-contents)



## 58. Function Pointers in C++

函数指针，我们现在讨论的是原始风格的函数指针，来源c语言，我喜欢称之为原始函数指针（raw function pointer）。

函数指针，是将一个函数赋值给一个变量的方法。到目前为止，我们在调用某个函数，我们不能用函数来做任何逻辑（运算），他就像一个符号，当我们想要某件事发生时，我们可以调用它。我们可以传入参数，得到返回值。从这点出发，我们还可以将函数作为参数传递给其他函数，或者其他有趣的事，如果不适用函数指针，那就非常麻烦，它确实能将代码变得更干净。

一般函数调用：
```cpp
void HelloWorld()
{
    std::cout << "hello world" << std::endl;
}
int main()
{
    HelloWorld();
}
```
现在将函数赋值给某个变量。auto关键字对函数指针之类的东西非常有用，但是`auto function = HelloWorld();`肯定不行，我们不能推导出auto类型，因为实际返回类型为void，我们要做的是调用这个函数，但是去掉括号的话，我们就不是在调用这个函数，我们所做的是获取函数指针 ，具体地说，这个就像是带了&取地址符号一样(`auto function = HelloWorld;`),函数当然只是cpu指令当我们编译代码时，函数就在二进制文件在某个地方，将来再讲二进制文件，现在想象一下，当你编译代码时，每个函数都被编译成cpu指令，他们就在我们的二进制文件中，在可执行文件中。
```cpp
void HelloWorld() { std::cout << "hello world" << std::endl; }
int main() {
    void(*fun_ptr)();
    
    auto function = HelloWorld;//auto在这里指代void(*function)()
}
```
这段代码中，fun_ptr就是个名字，后面的括号是函数的参数，第一行就是function的实际类型。就像这段代码：
```cpp
#include <iostream>
void HelloWorld() { std::cout << "hello world" << std::endl; }
int main() {
    void (*cherno)();
    cherno = HelloWorld;

    function();
}
```
看起来确实很奇怪，第一步是上面的代码，接下来调用cherno，就像调用函数一样：
```cpp
void HelloWorld() { std::cout << "hello world" << std::endl; }
int main() {
    void (*cherno)();
    cherno = HelloWorld;

    cherno();
}
```
这就是为什么人们用auto来使用函数指针。

或者你也可以使用typedef：
```cpp
#include <iostream>

void HelloWorld() { std::cout << "hello world" << std::endl; }
int main() {
    typedef void (*HelloWorldFunction)();
    HelloWorldFunction function = HelloWorld;
    function();
}
```
以及带参数的：
```cpp
void HelloWorld(int a) { std::cout << "hello world Value: " <<a<< std::endl; }
int main() {
    typedef void (*HelloWorldFunction)(int);
    HelloWorldFunction function = HelloWorld;
    function(7);
}
```
我们刚才所做的是将函数作为一个变量名，进行调用，将函数参数化，我可以输入任何值，调用这个函数，用不同的参数值，所以最简单写法是：
```cpp
void HelloWorld(int a) {
    std::cout << "hello world value of a is: " << a << std::endl;
}
int main() {
    auto cherno = HelloWorld;
    cherno(9);
}
```
再来看一个实际的例子：
```cpp
void PrintValue(int value) { std::cout << "Value: " << value << std::endl; }

void ForEach(const std::vector<int>& values, void (*func)(int)) {
    for (int value : values) func(value);
}

int main() {

    std::vector<int> values = {1, 2, 3, 4, 5};
    ForEach(values, PrintValue);
}
```
这是一个很酷的例子，就像告诉函数，嘿我想让你做这件事，在一个特定的时间。不过这事情似乎做的有点多。

lambda。lambda本质上就是一个普通函数，他是在我们代码在个过程中生成的，用完即弃的函数。不是真正的函数，是匿名函数.

```cpp
// void PrintValue(int value) { std::cout << "Value: " << value << std::endl; }

void ForEach(const std::vector<int>& values, void (*func)(int)) {
    for (int value : values) func(value);
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    ForEach(values,
            [](int value) { std::cout << "Value: " << value << std::endl; });
}
```
[]叫做捕获方式，也就是如何传入传出参数，()内是我们的参数，后面的和其他函数就一样了。

[![top] Goto Top](#table-of-contents)

## 59. Lambdas in C++

Lambda本质上是我们定义一种叫做匿名函数的方式，我们用这种方式创建函数，不需要实际创建一个函数，就像一个快速的一次性函数，展示下需要运行的代码，我们更想将他视作一个变量，而不是像一个正式函数那样，在我们实际编译的代码中作为一个符号存在。

Lambda如何使用，答案是，只要你有一个函数指针，你都可以在c++中使用Lambda，可以参考上节课的代码。这就是他的工作原理，总之就是我们不需要通过函数定义就能定义一个函数的方法。

```cpp
void ForEach(const std::vector<int>& values, void (*func)(int)) {//这里的函数指针告诉我们lambda表达式需要做成什么样子，换句话说，我们知道返回void我们也知道接受一个int参数
    for (int value : values) func(value);
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    ForEach(values,
            [](int value) { std::cout << "Value: " << value << std::endl; });
}
```
func(value)实际上是调用main函数中定义的lambda表达式。

我能给出的一个最大的例子是，我们希望能够将一个函数传递给一个api，以便于未来某个时间，她可以为我们调用这个函数，因为我们不知道现在能不能调用这个函数。因为函数还没有他需要的数据，或者就是我们暂时还不想调用它。lambda是一个很好的方法，来指定这个函数，制定未来想运行的代码，就像这里的forEach函数，我们运行这个代码对元素进行迭代时，就到了我们调用函数并传入特定参数的时候了。

其实我们可以去cppreference[网站](https://zh.cppreference.com/w/首页)，看看每个参数都是什么。这是非常好的一个网站。

捕获区能传入变量，[捕获](形参)lambda说明符 约束(可选){函数体}，等，在cppreference上可以看到所有解释，那到底什么是捕获，考虑一个问题，如果我们想把外部变量放到lambda函数内部指令中呢：
```cpp
void ForEach(const std::vector<int>& values, void (*func)(int)) {
    for (int value : values) func(value);
}
int main() { int a = 5; }
```
ForEach函数如何访问a呢，两种方法，通过值传递，通过引用传递，这也就是捕获这一块东西都作用。第一个方括号就是说我们打算如何传递变量
```cpp
void ForEach(const std::vector<int>& values, void (*func)(int)) {
    for (int value : values) func(value);
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    int a = 5;
    auto lambda = [=](int value) { std::cout << "value: " << a << std::endl; };
    ForEach(values, lambda);
}
```
传递所有变量，通过值传递，或者写上&传递所有变量，通过引用传递，或者直接写上a，值传递进去，还有&a，引用传递进去a，但是不管如何，这段代码都会出错，因为我们正在使用原始函数指针,改成c++11新的指针即可：
```cpp
void ForEach(const std::vector<int>& values, const std::function<void(int)>&func) {
    for (int value : values) func(value);
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    int a = 5;
    auto lambda = [=](int value) { std::cout << "value: " << a << std::endl; };
    ForEach(values, lambda);
}
```
你可以决定到底是拷贝还是引用。

我们有一个可选的修饰符，比如mutable，它允许函数体通过拷贝传递捕获的参数。

上述代码中，如果我们想在lambda中修改a，编译器不让我们这么做，有点奇怪，因为我们通过值传递的a，如果我们再普通函数中通过值传递某个变量，我们当然可以重新复制，如果要修复这个问题，我们就需要加上mutable，`auto lambda = [=](int value) mutable{ a = 5; std::cout << "value: " << a << std::endl; };`，看起来很奇怪，但是像这些东西你可能都不会意识到它的存在，如果你不看这些参考文档，去看下所有可能的东西的话。

来看看另一种用法，为什么您可能想使用lambda，在一个std::find_if的函数，他是algorithm头文件的部分，我们可以用来在某种迭代器中找到值，这个函数接受迭代器为入参。
```cpp
int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    auto it = std::find_if(values.begin(), values.end(),
                           [](int value) { return value > 3; });//返回布尔值，也就是是否满足条件
    std::cout << *it << std::endl;
}
```
遍历整个数组，找到比3大的整数，然后返回一个迭代器，满足条件的第一个元素。

我们很容易就做到了，通过指定一个简单的函数，让我们代码进行调用。他做的是循环便利我们的列表，和上述的ForEach相似，就好像我们加入了判断标准：
```cpp
    for (int value : values)
    { if(value>3)
        return value;
    }
```
相对麻烦，但是可以使用lambda通过指定这个if布尔语句来快速实现。

[![top] Goto Top](#table-of-contents)

## 60. Why I don't 'using namespace std'

为什么我不使用'using namespace std'。

首先辨识度高，我很清楚哪些是标准库的函数，如果我自己的函数和标准库一样，也蛇形命名法，那就和c++标准库一样，阅读代码就更加困难了。

另一个应该百分之百避免的就是在头文件中使用using namespace，对于大型项目来说很难追踪，就是灾难。

如果你确实需要使用using namespace，那就在一个足够小的作用域下使用。

[![top] Goto Top](#table-of-contents)

## 61. Namespaces in C++

今天讨论c++中命名空间是什么，以及如何进一步拓展名称空间的使用，以及为什么要使用名称空间。

```cpp
namespace apple {
    void print(const std::string &text) {
        std::cout << text << std::endl;
    }
}

namespace orange {
    void print(const char *text) {
        std::string temp=text;
        std::reverse(temp.begin(),temp.end());
        std::cout << temp << std::endl;
    }
}
```
例子从两个命名空间但是函数名相同，但入参不同（函数签名不同）。

但是如果我们转换为，两者都接受const char*，如果将命名空间注释掉，再打印`"Hello"`，那么会报错，那就会出现问题，因为这些函数是相同的，报错说我们print函数已经有了实体(body)，因为我们有两个相同名字的符号，他们是相同的符号。当我说符号的时候，我指的是类、函数、变量、常数之类的东西。这里的两个函数有相同的函数签名，所以这两个符号是相同的，不能同时有两个相同的符号，会产生链接错误，如果这两个函数放在同一个文件里面的话。

如果我们确实想要两个print函数，或者使用另一个已经定义了print函数的库，但是我们想要有自己的print函数。

c语言是没有名称空间的，所以c语言的库，比如GLFW，没有名称空间，在库内，每个函数都是GLFW开头的，OpenGL也是一样，显示OpenGL后面才是符号名，比如`glBegin()`和`glEnd()`等，我们将库的实际名称或者某种id嵌入到函数名中，而这是c语言风格。他们不能将一个函数名取为init，因为这个名称太普通，如果每个库都这么写的话，那你就永远不能使用这些库而不必修改源代码，所以他们不得不把库的名字放在前面，比如glfwInit。c++中就不会有这个问题，namespace就是来解决这个问题的，名称空间的主要目的是避免命名冲突。

类也是一种名称空间，类本身就是命名空间，这就是为什么如果我们访问另一个类中的内部类或枚举类，或者静态函数，或者非静态函数，我们要使`::`操作符，这就是`::`的意思。

上节讲尽量不用using namespace，但是我可以只单独引入print函数，我们可以使用`using apple::print`。

还有可以`namespace a = apple;`，这样就是`a::print`，这其实非常有用，比如在嵌套的名称空间，apple中还有一个名称空间functions里面包含了所有函数，不要问我为什么这样，这只是个例子。正常我们要`apple::functions::print`，你可以`using namespace apple::functions`，也可以`namespace a = aplle::functions;`。显然，定义的namespace只在限定的作用域下成立，还是那个建议，尽量将这些限制在一个小的作用域下。

可以参考大型的严肃的项目，关于名称空间这件事。

[![top] Goto Top](#table-of-contents)

## 62. Threads in C++

c++线程以及如何优化。

多线程不仅仅可以提升性能，也能让我们利用它做些什么。例如我们利用std::cin.get()，请求来自用户的输入到控制台，然而，在等待输入的时候，我们什么也做不了，只是在等着接收消息，就像一个while循环一样，一直循环下去，直到我们按下enter，就像我们线程被阻塞了。但是如果我们可以做一些其他的事情，比如向控制台打印一些东西，会怎么样，或者记录点什么，或者拓展文件什么的，当我们在等待用户输入的时候，我们仍然希望有其他事情发生。


```cpp
#include <thread>
void DoWork() {
    //这个函数实际上会执行我们想要在另一个执行线程中发生的事情。
}
int main() {
    std::thread worker(DoWork);//一旦写完这段代码，他就会立刻启动那个线程，去做DoWork里的任务。
    //接受一个函数指针，这就是为什么传入DoWork而不带圆括号
    //就像我们的工作线程，然后要做的是传入一个函数以及可选参数
}
```

```cpp
static bool s_Finished = false;

void DoWork() {
    using namespace std::literals::chrono_literals;
    std::cout<<"Started thread id: "<<std::this_thread::get_id()<<std::endl;
    while (!s_Finished) {
        std::cout << "Working..." << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

int main() {
    std::thread worker(DoWork);

    std::cin.get();
    s_Finished = true;
    
    worker.join();
    std::cout<<"Finisher."<<std::endl;
    std::cout<<"Started thread id: "<<std::this_thread::get_id()
    
    std::cin.get();
}
```
`worker.join();`等待一个线程完成他的工作的方式，针对的是worker线程对象。join函数本质上是要等待这个线程加入进来(thread joining)，她所做的是说：嘿，你能在当前线程上等待这个线程完成工作吗？因此阻塞当前线程直到另一个线程完成。因为这个东西是并行运行，我们的主线程开始一个工作线程，最后我们写的这个join调用的目的，是在主线程上等待工作线程完成所有的执行后，再继续执行主线程。

所以我们想写的程序是：直到我们按下回车，等待我们按回车的那行代码阻塞了执行，因为他在等我们按回车，所以他不能连续打印working。所以在一个线程上并不能真正工作，我们需要能够在同一时间做两件事：我们希望能等待用户按下enter，并反复检查用户是否按下enter，而且还希望将working记录到控制台。

这按代码可以说是很无用的，但是这节课可以的重点是首先想你展示如何在c++中借助api访问线程，并最终变成特定的平台代码。你需要包含thread，输入std::thread来创建一个线程对象，一个变量，然后你给这个构造函数传入一个函数，然后立即开启这个线程，做他想做的事，这个线程将继续，直到他完成，你可以使用join的方法，等待当前线程启动的第二个线程结束运行，以防你需要做一些清理或等待工作，以便在所有线程完成之后，结束整个程序。

这里还有std::this_thread，可以用它来给当前线程下命令，

[![top] Goto Top](#table-of-contents)

## 63. Timing in C++.

今天我们将讨论计时(时间)

我们如何完成某个操作或执行某个代码所需时间。

c++11之后，有了chrono，他是c++库的一部分，不需要使用操作系统库，但在有chrono之前，如果你想要高分辨率的时间，那你需要使用操作系统库。例如在Windows中我们有一个叫做QueryPerformanceCounter的东西。然而今天，我们只会看一看这种平台无关的c++标准库方法，他可以计算出在执行代码时，代码经历了多长时间。

这个视频对c++系列未来很重要，因为当我们开始集成更多复杂特性时，我开始更多地谈论如何正确的做事情，以及如何编写性能良好的代码时，我们需要计时来看差异。这一点很重要，我们可能会从这一点延伸到基准测试，我们可以设置一些api，这样我们就可以计算函数完成时间和任意范围的代码所需时间。

首先`#include <chrono>`我还会`#include <thread>`

```cpp
int main() {
    auto start = std::chrono::high_resolution_clock::now();//当前时间
    //因为类型实在过长，所以采用auto

    using namespace std::literals::chrono_literals;//有了这个才能用1s中的"s"
    std::this_thread::sleep_for(1s);//告诉当前线程休眠一秒
    //但是线程时间不能保证是你告诉他的睡眠时间，而且计时器本身也有开销，

    auto end = std::chrono::high_resolution_clock::now();//当前时间

    std::chrono::duration<float> duration = end - start;//duration作为高精度计时，翻译为持续时间，这里其实也可以用auto
    std::cout << duration.count() << "s " << std::endl;

    std::cin.get();
}
```

我建议你用这个方法来满足你所有的时间需求，除非你在做一些特定的，底层的事情，实际上99%的情况下使用std::chrono就够了。

一个更聪明的方法来解决这个问题。

在这里我要做的是利用整个对象生存周期之类的范例，让他自动为我计时。构造函数要启动这个计时器，在析构函数中为end赋值，其实你可以不用存储end，因为马上就要用到它，但万一人们想访问他，我还是把end写进了我们的timer结构体。

我们真正要做的就是在需要计时的函数开头创建对象，这样，整个作用域整个函数，就会被计时了，就是这么简单。

测试下。std::endl非常慢，因为某些原因，如果我换成`\n`，打印时间可以看到快了很多。

```cpp
#include <iostream>
#include <chrono>

struct Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << "ms \n";
    }
};

void Function() {
    Timer timer;
    for (int i = 0; i < 100; ++i) {
        std::cout << "Hello\n";
    }
    //测试打印100个hello需要的时间
}

int main() {
    Function();
}
```

这是个粗略的例子，我只是展示如何使用计时器api，而不是如何实际执行基准测试，当然你也可以使用visual studio分析工具或者其他ide工具，这种东西叫插码(instrumentation)，你可以使用插码来实际修改代码，以包含某种分析工具，比如这个计时器，这是一种非常简单的方法，因为并不是所有平台都足够好，不增加开销的分析工具，你可以通过这个做很多事，比如将数据收集成一个大文件然后输出，然后另一个工具读取，这样就能看到图标之类的东西。

你使用c++可能是因为你关心性能，你想要编写快速的代码，那么无论如何一定要习惯这类东西。

[![top] Goto Top](#table-of-contents)

## 64. Multidimensional Arrays in C++ (2D arrays)

进入讲c++多维数组，二维、三维、四维等等。在处理任意类型的数组时，指针非常重要。因为数组就是内存块，处理内存的简单方法就是使用指针。

```cpp
int main() {
    int **a2d = new int *[50];
    //遍历数组
    for (int i = 0; i < 50; i++)
        a2d[i] = new int[50];

    int ***a3d = new int **[50];
    for (int i = 0; i < 50; ++i) {
        //我们有50个指向指针的指针
        a3d[i] = new int *[50];
        for (int j = 0; j < 50; ++j) {
            a3d[i][j] = new int[50];//a3d[i]是对指针第一部分的解引用，a3d[i][j]是对第二部分进行解引用
            //和下面写法是一个意思：
            //int**ptr = a3d[i];
            //ptr[j]=new int[50];每个指针一个数组
        }
    }
    a3d[0][0][0]=0;
    //a3d[0]是指针的指针的数组，a3d[0][0]是指针的数组，a3d[0][0][0]是整数
}
```
回到二维数组：
```cpp
    a[0][0] = 0;//第一个元素
    a[0][1] = 0;//第二个元素
```
最右边一列，是你访问的整数，左边一列，他是指针的索引，而不是整数的索引。

如果是堆分配的，那我们需要delete他们，遍历然后delete所有数组，一次delete肯定无法删除所有，没有`delete[][]`这种操作符，只能`delete[]`，如果这时候`delete[a2d];`那么删除的是`int **a2d = new int *[50];`，这是200字节的内存，他只是数组，保存实际整形数组的指针，而后面50乘200字节的内存也就是你的50个数组的数据，会造成内存泄漏，因为我们删除了保存这些指针的数组，只有他们才能告诉我们，这些数组在哪。所以要先遍历删除，然后在删除外面的数组：
```cpp
int main() {
    int **a2d = new int *[5];
    //遍历数组
    for (int i = 0; i < 5; i++)
        a2d[i] = new int[5];


    for (int i = 0; i < 5; ++i) {
        delete[] a2d[i];
    }
    delete[] a2d;

}
```
还没结束。出了这些明显难以处理的问题之外，我还有其他看法，你这样处理数组会造成内存碎片。实际上我们创建了5个单独的缓冲区，每个缓冲区5个整数，而不是一块连续内存，除非你采用某种自定义分配或者是采用内存池分配。他们会被分派到内存的随机的位置，可能相隔很近或者很远，没办法保证一定很近，这是个问题，因为如果我们要访问这25个整数我们每次遍历 5 个之后，跳到数组的下一行，或者说是数组的其他维度，也就是跳到下一个整数数组时，我们必须跳转到内存中另一个位置来读写数据，这会导致cache miss（缓存不命中），这意味着我们浪费时间从ram中获取数据，如果他们恰好是紧密一起分配的，那么这可能不会造成cache miss，但是不能指望一定会分配到一起，通常是不会分配在一起的，所以实际上，用这种方式遍历25个整数要比我只分配一个一维数组慢很多，因为一维数组的话，内存分配都在同一行，最重要的一点是当你在编程和优化时，你在处理内存问题时，你可以优化的最重要一点就是优化你的内存访问，所以如果你能将要访问的内存数据存储在一起，那么你在定位数据时，会有更多的cache hits（缓存命中），以及更少的cache miss，你的程序会更快，有人说我确实要用到二维数组啊，没有其他方法可以做到。错！

你创建了25个整数，5个数组每个数组5个整数。

```cpp
int main() {
    int **a2d = new int *[5];
    //遍历数组
    for (int i = 0; i < 5; i++)
        a2d[i] = new int[5];

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            a2d[x][y] = 2;//这是一个二维的网格，很容易通过x，y来处理网格
        }
    }
//==========另一种方式来存储这25个数据========//
    int *array = new int[5 * 5];
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            array[x + y * 5] = 2;//每次y增加1，我就向前跳5个元素，就相当于你的数组网格向下跳一行
        }
    }

    for (int i = 0; i < 5; ++i) {
        delete[] a2d[i];
    }
    delete[] a2d;

    delete[] array;
}
```

第二种明显比第一种快很多，因为第一种每次都要跳出for循环，跳到一个完全不同的内存地址，而第二种访问的事我们在内存中同一行的内存。所以我尽量避免二维数组，有时候使用他们很有意义，但大多数时候是没有意义的，如果我要存储一个位图，bitmap，所有像素都在一张图片里，你可以把图像想像成照片或纹理，这种二维东西，我应该把它存储为一个2D数组，不不不，不要这样！把它存储成一维数组即可，存储为啥都是没问题的，但是在一维数组，在存储图像上，要好很多。

[![top] Goto Top](#table-of-contents)

## 65. Sorting in C++

c++中的排序。假设我有一个整数向量，或者一个整数数组，我想让他们按他们的值或者某种谓语排序。显然你可以自己写算法，冒泡排序，快速排序等，或者任何一种遍历列表并对元素排序的算法，但是有些情况下，当你想做一些比如你在处理c++的内置集合类型，如`std::vector`等，你就没必要自己写一套自己算法，你可以让c++库帮你排序，今日我们聚焦`std::sort`，他可以为你进行排序，或者为你提供给他任何类型的迭代器进行排序。

还是在cppreference网站上查看std::sort相关资料，可以看到很多相关设置及参数。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


int main() {

    std::vector<int> values = {3, 5, 1, 4};
    
    //升序排列：
    std::sort(values.begin(), values.end());
    //第三个参数是某种谓语，但是如果不提供任何类型的谓语，也就是不提供一个函数来进行排序，对于整数他会按升序排列
    //如果我想提供某种方式来排序，我可以通过提供一个函数来实现，他可以是一个你创建的结构体内的函数，也可以是一个lambda，也可以是内置函数

    // 从大到小
    std::sort(values.begin(), values.end(), std::greater<int>());

    //lambda排序

    std::sort(values.begin(), values.end(), [](int a, int b) {
    //查阅文档发现，返回true或者false来决定参数排列顺序，
        return a < b;
    });

    //再调整下：
    std::sort(values.begin(), values.end(), [](int a, int b) {
        if(a==1)
            return false;
        if(b==1)
            return true;

        return a < b;
    });


    //输出
    for (int value: values) {
        std::cout << value << std::endl;
    }

}
```

[![top] Goto Top](#table-of-contents)

## 66. Type Punning in C++

c++的类型双关。类型双关知识一个花哨的术语，用来在c++中绕过类型系统。

在c++中，虽然类型是编译器强制实行的，但您可以直接访问内存，这意味着，在我的代码中，我一直在使用这种类型，比如说整数，但实际上，我现在要把这段内存当作double类型或者class类型，你可以很容易绕过你的类型系统，你是否要使用，取决于你的实际情况，在某些情况下，你绝对不应该规避类型系统，因为类型系统存在是有原因的，除非你有充分理由，否则你可能不想过多使用他，但是在其它情况，这样做完全是可以的。假设我们有一个类，我们想把它写成一个字节流，不需要很麻烦，假设他是一个基本类型的结构，并且没有指向内存中其他地方的指针，那么我们就可以重新解释整个结构或者类等等，将它作为一个字节数组，然后将它写出来或者流出来（字节流），我们深知不需要关心里面是什么类型，让我知道数据访问的大小，然后把它放到某个地方，在很多情况下，他是非常有用的，是一种原始的，底层的访问，这就是为什么c++效率这么高，也是我喜欢c++的原因了。

```cpp
int main() {

    int a = 50;
    double value = a;//隐式转换
    double value = (double) a;//显式转换

    double value = *(double *) &a;//类型双关，把a部分内存当作double对待
    //在四个字节的int后，未初始化的部分4字节继续设为value，所以打印出来结果很奇怪，这很糟糕，某些情况下会造成崩溃
    //此处含义为，先取a地址，然后转换为double类型指针，然后要把它变回double，从指针回到实际类型，所以我们解引用*
}
```
如果你不想创建一个全新的变量，你只是想把这个int当作double来访问，你只需要double后面加一个&：`double& value = *(double *) &a;`，引用而不是拷贝成一个新的变量。

这样你就会编辑这个int内存，这样很危险，如果我令`value = 0.0;`，他实际上要写8字节内存而不是4字节，但是我们只有四个字节，这可能会导致程序崩溃。

如果结构体是空的，那么会至少占用一个字节，来寻址用，如果不是空的，那么他就像这样一样，只包含两个整数，就这样，没有多余的数据。

```cpp
struct Entity {
    int x, y;
};//在内存中，这个结构体其实就是两个整数组成的，就是这两个整数，如果查看内存，可以看到他是两个挨着的整形

int main() {
    Entity e = {5, 8};

    std::cin.get();
}
```
因此，我们可以将Entity结构体看成一个int数组，而且不用通过`e.x`、`e.y`就可以取出这些整数，我的意思是不仅仅上述方法，而且可以这样做，创建一个数组，一个原始指针：
```cpp
struct Entity {
    int x, y;
};
int main() {
    Entity e = {5, 8};

    int *position = (int *) &e;
    std::cout << position[0] << ", " << position[1] << std::endl;//就像position是一个数组一样

    std::cin.get();
}
```
结果为`5, 8`，因此我们将他们转换为了数组，所以像访问数组那样访问他们。

```cpp
    //正常人都会这么写int y=e.y;
    //但是你也可以这么写：
    int y = *(int *) ((char *) &e + 4);
    //取e地址，然后转换成char*，我不知道你为什么这么做，但我只能说你这样做了
    // 当然这是一个字节大小，所以我们向前移动四个字节，然后将这个内存转换成一个int指针，然后解引用，然后就得到了y
```
当然这些代码永远不可能出现在实际应用程序中。

我们想让Entity的两个变量作为一个数组的话，创建一个GetPositions的函数：
```cpp
struct Entity {
    int x, y;

    int *GetPositions() {
        return &x;
    };

};

int main() {
    Entity e = {5, 8};
    int *position = e.GetPositions();
    position[0] = 2;
//没有做任何复制，我没有冗余地复制内存，我只是链接到了相同地内存，
    std::cin.get();
}
```

这就是类型双关，也就是说，我要把握拥有的这段内存，当作不同类型内存来对待，可以看到我们可以非常自由的来做这些，我们需要做的只是将该类型作为指针，然后将其转换为另一个指针，如果有必要，还可以对其解引用。

[![top] Goto Top](#table-of-contents)

## 67. Unions in C++

c++的联合体，联合体像类类型或者结构体类型，只不过它一次智能占用一个成员内存。我的意思是，通常如果我们有一个结构体，比如四个浮点数，我们可以有四乘四个字节在结构体中，总共16字节，而且很明显，当你不断向类或结构体增添成员时，大小会不断增长。一个联合体只能有一个成员，比如我声明四个浮点数，比如a、b、c、d，联合体大小仍然是4字节，当我尝试处理他们，比如我改变a、b、c、d的值，他们的内存都是一样的，如果我改变a，将它设为5，d也会变为5，这就是联合体的工作方式，你可以像使用结构体或类一样使用他们，你也可以给他添加静态函数或者普通函数等，然而你不能使用虚函数，还有一些其他限制，蛋通常人民使用联合体来做的事情，是和类型双关紧密联系的，当你想给同一个变量取两个不同的名字时，他很有用。例如我有一个数学向量类，`vector3 {x, y, z}`，我可能还想把它当做一个rgb颜色，`XYZ rgb`，我怎么才能做到这一点？可以用时用来两种方式来使用它，x与r对齐，g与y对齐等，这些都可以通过union来实现。

通常union是匿名使用的，但是匿名union不能含有成员函数。

```cpp
int main() {
    struct Union {
        union {
            float a;
            int b;
            //如果这是一个结构体，那么会有两个不同的成员
        };
    };
    Union u;
    u.a = 2.0f;
    std::cout<<u.a<<", "<<u.b<<std::endl;//输出结果可以看到类型双关的效果
}
```
下面是一个更为实用的例子：
```cpp
struct Vector2
{
    float x, y;

};
struct Vector4
{
    float x, y, z, w;

};
void PrintVector(const Vector2& vector)
{
    std::cout << vector.x << ", " << vector.y << std::endl;
}
```

Vector4实际上是两个Vector2，或者至少这是一种看待它的方式，尝试从Vector4中提取出Vector2。
```cpp
struct Vector2 {
    float x, y;

};
struct Vector4 {
    union {
        struct {
            float x, y, z, w;
        };
    };
};
```
现在我可以正常访问`vector.x`并且可以把它设为`0.2f`，我可以像往常一样访问它，是因为我没有给他一个名字什么的，你可以尝试如果我给他取个名字，一切都破坏了。如果他是匿名的，他只是一种数据结构，他没有添加任何东西，这里的好处是，他将所有这些转换为单个成员，这就是union所期望做的事。

最后，我在这union里再创建一个结构体，很明显这是向union里添加了第二个成员，也就是说他和第一个元素占据相同的空间，他由两个Vector2组成，好了现在我有几种访问Vector4内存的方法。我可以用x、y、z、w或者a、b。a和x, y的内存是一样的，b将是与z, w相同的内存，以下是示例代码：
```cpp
struct Vector2 {
    float x, y;

};
struct Vector4 zh
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            Vector2 a, b;
        };
    };
};

void PrintVector(const Vector2 &vector) {
    std::cout << vector.x << ", " << vector.y << std::endl;
}

int main() {
    Vector4 vector = {1.0f, 2.0f, 3.0f, 4.0f};
    PrintVector(vector.a);
    PrintVector(vector.b);

    std::cout << "--------------------" << std::endl;
    vector.z = 500.0f;
    PrintVector(vector.a);
    PrintVector(vector.b);
}
```
输出：
```bash
1, 2
3, 4
--------------------
1, 2
500, 4
```
我希望这是union的一个好例子，当你想这样做事情的时候，他们真的很有用，当你有多种方法或者你想用多种方法来处理相同数据时，他在很多方面都很有用。再说一次，你可以使用类型双关或者其他，通常union的可读性更高，但是union可能会产生一些问题，因为基本上不会发生这些问题，你不用担心这个问题，所以以后再说。

[![top] Goto Top](#table-of-contents)

## 68. Virtual Destructors in C++

c++中虚析构函数。首先你要学了析构函数和虚函数，因为虚析构函数，你可以想象，就是虚函数和析构函数的组合。

内容比较简单，但是实际上虚析构函数是非常非常重要的，对于处理多态，换句话说，如果我有一些列的子类和所有的继承，如果你不知道什么是c++继承，那你要先去学习。

如果你有一个类A，然后一个类B派生于A，你想把类B引用为A，但它实际上是类B，然后你决定删除A或者他以某种方式被删除了，然后你还是希望运行B的析构函数，而不是运行A的析构函数，这就是所谓的虚析构函数以及他的作用，如果只是在脑子里过一遍可能没啥意义，因为很难想象，所以直接进入代码。

先在堆上分配一个Base，这样我们就可以明确地建立和删除它。

```cpp

class Base//作为基类
{
public:
    Base() { std::cout << "Base Constructor\n" << std::endl; }

    ~Base() { std::cout << "Base Destructor\n" << std::endl; }
};

class Derived:public Base//派生自Base
{
public:;
    Derived() { std::cout << "Derived Constructor\n" << std::endl; }

    ~Derived() { std::cout << "Derived Destructor\n" << std::endl; }
};

int main(){

    Base* base=new Base();
    delete base;

    std::cout<<"-------------------\n";

    Derived* derived=new Derived();
    delete derived;

}
```
现在没什么是不同的，我的意思是，我没有标记任何东西是virtual的。运行结果你可能会猜到发生了什么：
```bash
Base Constructor
Base Destructor
-------------------
Base Constructor
Derived Constructor
Derived Destructor
Base Destructor
```
当我们创建base类的时候，他只会调用base类的析构函数，而当我们删除它的时候，也只会调用base类的析构函数，对于Derived类，首先调用了基类的构造函数，然后是Derived类的构造函数，当我们删除时，调用了Derived类的析构函数，然后是Base类的析构函数，这里一切正常正如我们所预料。

当我们有这个场景时，需要虚析构函数的问题就出现了。我们创建一个Derived实例，但是我们赋值给Base类类型，我们把这种poly对象当作Base类指针进行处理，但它实际上是一个指向Derived类型的指针：
```cpp
class Base//作为基类
{
public:
    Base() { std::cout << "Base Constructor\n" << std::endl; }

    ~Base() { std::cout << "Base Destructor\n" << std::endl; }
};

class Derived:public Base//派生自Base
{
public:;
    Derived() { std::cout << "Derived Constructor\n" << std::endl; }

    ~Derived() { std::cout << "Derived Destructor\n" << std::endl; }
};

int main(){

    Base* base=new Base();
    delete base;

    std::cout<<"-------------------\n";

    Derived* derived=new Derived();
    delete derived;

    std::cout<<"-------------------\n";

    Base* poly=new Derived();
    delete poly;
}
```
结果是：
```bash
Base Constructor
Base Destructor
-------------------
Base Constructor
Derived Constructor
Derived Destructor
Base Destructor
-------------------
Base Constructor
Derived Constructor
Base Destructor
```
你可以看到，第三个场景中，基类构造函数和派生类构造函数都被正确调用，正如我们在第二个例子中期待那样，然而当我们决定删除的时候，只有基类的析构函数被调用了，而派生类的析构函数没有被调用，这很重要，因为这会导致内存泄漏，我马上告诉你怎么泄漏的。你能看到，当我们删除poly的时候，会发生什么，`delete poly`时，他不知道这个调用析构函数，可能有另一个析构函数，因为他没有被标记为虚函数，标记为virual，意味着c++知道可能会有一个方法（函数）在层次结构下的某种重写函数（方法），因为在普通的函数面前标记为virtual，那么他就可以被覆写。这意味着要做虚函数表这样的设置，析构函数有一点不一样，虚析构函数的意思不是覆写析构函数，而是加上一个析构函数，换句话说，如果我把基类析构函数改为虚函数，换句话说，如果我把基类析构函数改为虚函数，他实际会调用两个析构函数，他会先调用派生类析构函数，然后在层次结构中向上，调用基类析构函数，所以我们需要做的就是在析构函数前面标记virtual。

首先我们讨论一下为什么我们需要调用派生类的析构函数，考虑这个例子，也许我们有一个成员，比如一个int数组或者其他在堆上分配的东西，构造函数中我们构造它，然后在析构函数中我们决定要删除该数组，当前情况下根本无法调用那个派生析构函数，但是调用了派生类的构造函数，很明显我们分配了20字节的内存，然后我们没有析构，所以我们永远不会删除堆分配数组，也就是说我们有内存泄漏。我们需要做的就是在基类的析构函数标记为虚函数，这意味着这个类有可能被拓展为子类，可能还有一个析构函数也需要被调用。这高速人们：嘿，你需要调用派生析构函数，如果他们存在的话。
```cpp

class Base//作为基类
{
public:
    Base() { std::cout << "Base Constructor\n" << std::endl; }

    virtual ~Base() { std::cout << "Base Destructor\n" << std::endl; }
};

class Derived : public Base//派生自Base
{
public:;

    Derived() {
        m_Array = new int[5];
        std::cout << "Derived Constructor\n" << std::endl;
    }

    ~Derived() {
        delete[]m_Array;
        std::cout << "Derived Destructor\n" << std::endl;
    }

private:
    int *m_Array;
};

int main() {

    Base *base = new Base();
    delete base;

    std::cout << "-------------------\n";

    Derived *derived = new Derived();
    delete derived;

    std::cout << "-------------------\n";

    Base *poly = new Derived();
    delete poly;
}
```
运行结果回复正常，产生两个析构函数，这意味着这个数组确实得到了清理，大家都很高兴，即使我们把poly当作多态类型来处理，或者说我们把它当作基类类型来处理。

当你在写一个要拓展的类或者自类时，这一点非常重要，只要你允许一个类拥有自类，你需要百分之一百声明你的析构函数是虚函数，否则没人能安全地拓展这个类，包括你自己也不能，因为如果这样做，就怒能使用析构函数，如果你根据类的基类类型来处理该类，那么类的析构函数将永远不会被调用，比如你把它（派生类的对象指针）传递给一个函数，而那个函数可能只接收基类指针，然后函数做了删除（基类指针）或者其他操作，这是一个完美的例子，所以你一定要确保声明析构函数是虚函数，如果你允许他有子类的话。

[![top] Goto Top](#table-of-contents)

## 69. Casting in C++

c++的类型转换。

我认为这个话题，是一种需要练习并通过经验来学习的东西，而不是我告诉你他是如何运作的。首先什么是类型转换，我说的是必须在c++可用的类型系统中进行的类型转换，c++是一种强类型语言，意味着我必须坚持我的类型，除非有一个简单的隐式转换，这意味着c++知道如何在这来年各种功能类型之间转换并且没有数据损失，这就是隐式转换，或者有一个显式转换，嘿，你需要把这个类型转换成这个类型。

在讨论类型双关时，我们在一定程度上讨论了类型转换，但是在这个视频中，我们正式介绍一下强制类型转换的含义。

有两种风格，c风格和c++风格。

```cpp
int main() {

    int a = 5;
    double value = a;//隐式转换，很容易，且没有数据丢失

    double value2 = 5.25;
    double a2 = (int)(value + 5.3);//显式转换，

    std::cout << a2 << "\n";
}
```
c风格类型转换，在圆括号里制定了要强制转换的类型，然后是我们要强制转换的变量。

c++风格：`double s = static_cast<int>(value + 5.3);`，c++风格的转换有很多种，有reinterpret_cast、dynamic_cast、const_cast共四种主要的cast。现在必须意识到的是，他们不做任何c风格类型转换不能做的事，我的意思是他们可能会做其他的事情，但实际结果可能只是一个成功的类型转换而已，c风格的强制转换可以实现所有这些，这并不是添加新功能，他只是添加了一些语法糖到你的代码中，例如我们将实际执行一个检查，如果转换不成功，可能返回NULL，所以他做了额外的事，这也意味着实际上代码会慢下来，但在大多数情况下，c++风格类型转换也不会做额外的事，他们只是放进去英语单词，例如static_cast，意思是静态类型转换，在静态类型转换情况下，他们还会做一些其他编译时的检查，看看这种转换是否真的可行，reinterpret_cast也一样，就是像是把我们说过的类型双关用英语说出来一样，reinterpret_cast意思是我把这段内存重新解释成别的东西，const_cast，移除或者添加变量的const限定，搞这么多cast的好处是，除了可能收到的那些编译之外的检查之外，还可以在代码库中搜索他们，如果我 想看到我的类型转换都在哪，也许我性能有问题，我不想用dynamic_cast，我可以搜索它（dynamic_cast），如果我使用的c风格的cast，那就无法搜索了，所以他对我们程序员阅读和编写代码都有帮助，而且它也帮助我们减少强制转换时，可能会意外犯的错误，比如类型不兼容。

一个例子：
```cpp

class Base {
public:
    Base() {}

    virtual ~Base() {}
};

class Derived : public Base {
public:
    Derived() {}

    ~Derived() {}
};

class AnotherClass : public Base {
public:
    AnotherClass() {}

    ~AnotherClass() {}
};

int main() {
    double value = 5.25;
    double a = (int) value + 5.3;//显式转换，
    //如果我尝试转换value，把它换成AnotherClass类型，这会报错，因为构造函数引起的
    double s = static_cast<AnotherClass>(value + 5.3);
    //但是如果加上指针，你可以看到这是一个无效的类型转换，c++做的是编译器看到这个，然后认为是行不通的
    //即使我们获取了地址，返回了int指针，我们试图对他进行类型双关，这行不通
    double s = static_cast<AnotherClass>(value + 5.3);

    //现在对于类型双关，我们需要使用reinterpret_cast，将value指针处数据重新解释为AnotherClass实例的数据
    double s = reinterpret_cast<AnotherClass *>(&value + 5.3);
    //这里的关键是，他知道我们不能做某些类型的转换，而如果我们只是用普通c风格转换，就没办法知道了，他默认使用reinterpret_cast的事

    std::cout << s << "\n";
}
```
说了很多但是这一部分知识最好的方法就是实践，尝试自己构建示例。我个人倾向使用c风格转换，但是我鼓励你如果你从零开始做一个全新的项目，或者你有一个非常小的项目，你应该使用c++风格的转换，因为更可靠且对参与的人都更友好。

const_cast还没谈及，他是用来添加或者删除const修饰符的，挺简单的，你可以用它来隐式添加const，但大部分情况下，是用来移除const的。再说一次，在你的代码库中有这样的代码是很好的，因为你可以搜索你所有移除了const瞎搞的地方，修正他们或者干其他的事情。

然后是reinterpret_cast，在类型双关的课程中所有事情都可以用reinterpret_cast，这就是她的用法了，当我不想转换任何东西，只是想把指针解释成别的东西的时候，我想把现有内存解释成另一种类型时，这就是reinterpret_cast用武之地。

[![top] Goto Top](#table-of-contents)

## 70. Conditional and Action Breakpoints in C++

今天讲的是visual studio的技巧，开发和调试的一般技巧，是关于断点的，但是也不仅仅是断点，这不是一个普通的断点，而是关于条件与操作(conditions and actions)应用在断点上，通过条件或条件断点，我的意思是我们可以告诉编译器，我想在这里设置一个断点，但是只希望在特定条件下触发，内存中的某些东西符合了我的条件，那就触发这个断点，操作断点是允许我们采取某种动作，一般是在碰到断点时打印一些东西到控制台。有两种类型的操作断点，一是让你在打印你想要的东西时继续执行，举个例子，记录鼠标位置，我能做的是每次记录鼠标的位置，因为每次鼠标移动移动事件就会发生，我可以让那个断点打印一些东西到控制台，但保持程序运行，或者我让他打印些东西到控制台，但仍然中断程序，暂停程序执行，这样我们就可以检查内存中其他东西。断点可以手动添加，也可以类似宏，写在代码里，这种条件的，对于动作断点，显然向控制台打印一些东西同样可以在代码中完成。但是这个真正有用的地方是我们可以让程序进入某种状态，也许是一个bug，我们想检查某些属性，找出是什么导致了这个bug，或者为什么处于这个状态，这个状态是什么，比如我的东西设置成什么，为什么会发生这种事。很显然如果我们决定添加代码到代码库，我们必须终止程序然后重新编译，这是一个问题，因为我们也许无法再次进入那个状态，或者很难，我的意思是这通常会减缓工作流程，如果我们不得不停止代码运行、添加代码、重新编译等，然后回到调试状态。

在断点处右键然后选择conditions。我想这最大的好处是，当然你也可以通过在应用程序的源代码中添加代码的方式打印这些，但这里比较酷的事情是：我没有停止我的应用程序，也没有重新编译代码。另一种方式就是普通断点，然后看中断的程序，然后找变量，这样太耗时了。

个人感觉还是上一条，在bug出现时，无需停止程序，即可展开debug，不至于让程序关闭重新复现。

还有一件事，条件conditons是非常有用的，比如在loops循环中，如果你有一个更新循环，比如一个游戏，这个更新频率每秒循环60次，我想要一个特殊条件，对于断点来说这几乎是不可能的，比如我在游戏中遍历所有实体的节点层次结构，我有5000个实体，我只想在“玩家”或者“405号敌人”那里中断程序，因为这里是出现问题的实体，手工就很难完成，你放置一个断点，然后一直点击F5，直到实体名字是“405号敌人”为止，不如直接放置一个条件。

[![top] Goto Top](#table-of-contents)

## 71. Safety in modern C++ and how to teach it
c++中安全意味着什么，以及关于现代c++和安全的整个争论。

c++里说的安全是什么意思，安全编程，或者说是在编程中，我们希望降低崩溃、内存泄漏、非法访问等问题，随着c++11的到来，我想说的是，我们应该转向智能指针这样的概念，而不是原始指针。特别是今天我想重点讲指针和内存，而不是异常或者其他安全编程有关的比如错误检查之类的，我不关心。

当我们开始倾向于智能指针之类的东西时，这一切都可以归结为我想要分配内存。我想问题来自几个方面，如果我忘记释放内存会发生什么，这是一个问题，因为这会导致内存泄漏，可能是完全无害的，你甚至不回注意到，或者是灾难性的，导致程序崩溃，因为内存耗尽。然后还有所有权的问题，那么谁拥有分配的内存呢，如果我有一个原始指针，指向这块内存，我开始把它从一个函数传递到另一个函数，从一个类传递到另一个类，谁负责管理和清理这些内存，这是所有权的问题，如果你开始有一个原始指针，那你知道，会有一些编程场景，你有一个管理她的函数A和管理她的函数B，你不确定这些函数谁最后结束，但是你需要这两个函数都能访问那个指针，那你怎么说呢，好，在这两个函数完成他们工作的时，就是我释放内存的时候，这是不可能的，除非你能明确的说，我要运行函数a，我要运行函数b，然后在最后，我将会有第三个函数，或者其他东西，保证在这两个函数完成后，再运行并执行一个清理步骤，这显然极大的复杂了整个程序，这是我们绝对要避免的，这是另一种所有权问题。但是说实在的，忘记释放内存这件事，其实也是个简单的问题，因为解决这个问题的方法就是当你在编程的时候专心一点，但这不是我想说的，就像很难说出口，做一个更好的程序员就行了，这是啥意思，这太武断了，我在编程的时候更加注意我的代码，这不是一个解决方案。我只是想说，“成为一个更好的程序员”这可能只是一个假设性的解决方案，然后你还是需要考虑更复杂的结构来删除由你自己明确分配的内存，我知道，当另一个程序员出现在团队中，并决定写一些其他东西来操纵这个内存，他们可能会把事情搞砸。

这两大问题就是我们需要自动删除内存的原因。智能指针只要自动化一行简单的代码，就搞定了内存删除于释放的问题。如果不使用c++标准库里面的智能指针，这没问题，有些人可能会选择写自己的，比如一个基于作用域的指针，类似于std::unique_ptr，或者像是引用计数系统，相当于std::shared_ptr，这都没问题，然后你可以引入弱引用之类的概念，这都没问题，就像weak_ptr，你可以做你自己的构造，我不反对，有时候也会喜欢这样做，既是为了根据自己需要定制他们，也是为了尝试榨出特定平台的性能，你知道平台特定的性能限制和要点，通过写自己的系统来百分之百榨取他们性能，完全没问题。但如果你选择100%原始指针，这对你来说是一种写代码的策略，这并不意味着你是一个糟糕的程序员，而是为什么，为什么那样做，这没有任何意义。

就我而言，如果写代码很快的话，我也默认写原始指针，我这么做的最大原因是，就我而言，他们仍然更容易些，更容易读，因为你不需要思考，你只要加个小星星就行了，然后如果我愿意，我可以选择删除内存，但这可能并不重要，因为我说的是一个简单的沙箱应用程序，他可能不会超过100行代码，因为我只是想测试一个小的东西，在那种情况下，我要是用智能指针的话，这会让我的代码变成一个沉重负担，而如果我只用原始指针，代码会更干净更容易阅读，我不关心是否释放了内存，我不关心所有权，因为我写的只是一个小应用程序。

我的意见是，我认为人们应该停止原始指针和智能指针的争论，在一个真正的框架环境中，真正的应用程序中，如果是生产代码的话，要使用智能指针，不这么做是非常愚蠢的举动，有了代码可维护性和可靠性，以及能够自由地编写代码而不用担心什么时候内存会被释放以及所有权的问题，所有这些问题都可以通过智能指针来解决，可能线程方面有点问题，因为shared_ptr不是线程安全的，使用智能指针还有其他约束，所以智能指针不是通用的内存解决方案，但是当然，对于典型情况，他们确实对你有很大帮助，所以你应该使用他们。当我们进入更严肃的代码时，我们肯定会使用智能指针，所以别误会我，只是在学习c++阶段，我坚信你需要知道什么是原始指针，你需要知道内存是如何工作的，为什么？因为智能指针只是在原始指针上的包装，这就是他们的全部。他们围绕原始指针做了额外辅助代码，以便自动化所有事情，但本质上只是删除和释放内存。这就是他们存在的原因，如果你不知道原始指针是什么，那么你就不知道幕后发生了什么，因为我想教大家成为一名优秀的c++工程师不仅仅是我能写c++代码，更重要的是我能写实时的，对性能至关重要的c++代码，你必须知道一切是如何工作的，这就是为什么我做了关于编译器和链接器如何工作的，这就是为什么我喜欢深入讲解我的视频，因为我想教大家如何成为优秀的c++程序员，为了做到这一单，你需要理解事物是如何工作的。为了做到这一点，你需要理解他是如何工作的，如果一个char指针让你害怕，那就有问题了，很明显和我的目标不一样了，所以我认为作为一个社区，人们会说我教的c++都是些老式的东西，在我看来，当然这只是我的观点，没有什么确定的信息说你永远不应该使用智能指针，或者你应该总是使用智能指针，这是现实世界的两种观点，你要使用什么取决于你在做什么，这只是我的观点，但我强烈建议，你需要知道所有这些你需要知道的老东西，c++是如何工作的，以及这些东西就是我的观点，如果你想成为一名优秀的c++程序员的话，这是我的观点，如果你不喜欢，那么你可能知道有很多好的c++资源，我不是唯一好的一个，我只是网上众多c++资源中的一个，你可以买书，你可以做任何你想做的事，但在我的频道上，我就是这么教的。


[![top] Goto Top](#table-of-contents)

## 72. Precompiled Headers in C++

预编译头文件，实际上是让你抓取一堆头文件，并将它们转换成编译器可以使用的格式，而不必一遍又一遍的读取这些头文件。

举个例子，我大量使用std库，比如vector、string等，我会使用标准库中其他东西，比如std::cout等等，特别是来自头文件的标准模板库，他们由头文件组成，因为他们是模板，必须在头文件定义，举个例子，每次在c++文件中`#include <vector>`时他都需要读取整个vector头文件并编译它，不仅如此，vector还包含一堆其他包含文件，这些文件一样需要读取，预处理器必须把所有这些复制到vector文件，这就有上万行代码了，他们需要解析，以某种形式标记，在你编译main文件之前，因为你的main文件包含vector，vector必须复制粘贴到main文件中，然后是整个代码，所有代码每次都要被解析和编译，总之重点是，每次你对c++文件进行修改，整个文件都要更新和重新编译，所以那个vector类或vector文件必须重新复制到你的c++文件中，从头开始重新解析并编译。

这意味着你的编译时间会比潜在的要长很多。所以你需要一个叫做预编译头文件的东西来代替，它的作用是接收一堆你告诉它要接受的头文件，基本上是一堆代码，它只编译一次，它以二进制格式存储，这对编译器来说比单纯文本处理要快很多，因为他是已经处于一种过去的状态，并且是二进制的，不是文本的。每次你包含了预编译头文件，他就有了你需要的一切，这意味着你将大大减少编译时间，特别是你的项目越来越大。

但是我也想谈谈预编译头文件不应该做什么。到目前为止，我提到的预编译头文件其本质上还是头文件，因此很多人可能会想，我可以把项目中很多东西都放到这个pch中，放到预编译头文件中，以节省编译时间。是的，是这样，但是如果你把东西放到pch文件中，而这些东西会变化，显然，必须重新构建pch，而这要花时间，这可能导致编译速度变慢，因此不要将常常改变的文件放入pch中。比如你的log库，你只需要编译一次，那放进去很好，这让他很方便，因为你不需要手动将log包含到项目中的每个cpp文件中，但是我确信，如果我正在修改我的log库，我不会这么做，不会把他放进pch中。

pch真正有用的是外部链接，本质上，它主要用于不是你写的代码，比如stl，标准模板库或标准c++库中的代码，或者是Windows api，所以他没有理由不包含在预编译头文件中。

如果你决定通过实际头文件而不是pch来包含GLFW库或者其他，就会更加清晰，这个文件需要这个文件。但是如果你只包含pch，然后在pch中放很多包含文件，这可能会让它变得有点难。要注意不是包含所有依赖，而如果你包含的是实际依赖，那么他会更加清晰，且易于阅读，我在某种程度上同意这一点，取决于依赖的形式。比如当你大型项目中只有一个cpp中引用了GLFW库，在这种情况下为啥还要将其安放在预编译头中呢，他会降低可读性，虽然加速编译，但是只有一个cpp用到了它。你应该放进去stl这种的，因为string这种到处用到。

对于visual studio，我们需要做的是创建一个包含头文件的cpp文件，然后在cpp文件上点击右键，属性，c/c++下，precompiled header，选择precompiled header为creat，对这个特定的pch.cpp文件，我们creat一个预编译头文件，点击ok。然后到整个项目的属性下，在c/c++下的precompile header选use。

一般来说，每个软件项目都应该使用预编译的头文件，不存在我该不该用的问题，在你的预编译头文件中放入什么，那就是不同的故事了。


## 73. Dynamic Casting in C++

动态转换类型。dynamic casting是作为一种安全机制提供给我们的，当我们想要做特定的类型转换时。

现在过一遍c++类型转换，有两种，一个是c风格，在变量前的括号中写你的新类型，另一个是c++风格的，比如static_cast、const_cast，dynamic_cast是c++风格的类型转换，他做了额外的工作来确保我们实际的类型转换，是有效的类型转换，是否使用denamic_cast完全取决于你自己，我想给你们一些要点，我想这会让你知道你想做什么，你是否应该使用它。

dynamic_cast更像是一个函数，认识到这一点很重要，他不像编译时进行的类型转换，而是在运行时计算，正因为如此，他确实有相关的运行成本，当然，因为dynamic_cast做了额外的工作，他确实会带来一个小的性能成本，这是正常的。

dynamic_cast是专门用于沿继承层次结构进行的强制类型转化。这本质上意味着，如果我有一个类，他是另外一个类的子类，我想转换为基类型，或者从基类型转换为派生类型，这就是我可以使用dynamic_cast的地方。

假设我们有一个Entity类，游戏中所有实体entity的类，然后我们有玩家类和敌人类，他们都是实体，所以他们都是从Entity类派生的，如果我只是想将玩家对象转换回Entity对象，这很简单，我的意思是玩家本身就是Entity对象，因此可以做隐式转换，不需要做casting（强制转换）当然如果我们想，我们也可以使用dynamic_cast来做，反过来，事情就变得复杂了。反过来的意思是，如果我有一个Entity实例，我们想把它转换成一个玩家，我们不知道他是不是玩家，我们只知道他是一个Entity指针，他是一个Entity实例，是一个Entity的对象实例，我可以让他成为一个玩家，我们可以让他成为一个敌人，也可以让他成为一个Entity，他可能是三种类型，如果我们想将这个转换成玩家，我们不知道他是不是玩家。编译器如果相信我们，但是如果我们错了，他其实是敌人，那么我们尝试访问玩家独有数据或修改玩家独有数据的函数，我们程序可能会崩溃，那将是一场灾难。因为这个原因，dynamic_cast常被用来做验证。所以如果我们有一个Entity实例，他实际是一个敌人，但我们尝试使用dynamic_cast将其转换为一个玩家，这个会转换会失败，dynamic_cast会返回一个NULL指针，也就是0，然后我们可以验证它或者其他事情，我们可以用它来检查一个对象是否给定类型，换句话说我可以尝试在实例Entity对象上运行dynamic_cast，将其转换为玩家对象，然后检查他是否返回NULL，如果是NULL，那就不是玩家。

```cpp
class Entity {
};

class Player : public Entity {
};

class Enemy : public Entity {
};


int main() {

    Player* player=new Player();
    //现在这个player有两种类型，既是Entity，也是玩家，他甚至是一个无类型的东西，我们以后可能会讲到
    //可以很简单的改变为Entity* player=new Player();，Entity类型，或者Entity* e = player隐式转换
    //但是一旦我做了那些，我再想回到玩家，就很难做到了
}
```
```cpp
    Player *player = new Player();
    Entity *e = player;
    Player *p = e;//报错，因为我要把它转换成不同类型，而这个很可能是enemy
```

```cpp
    Player *player = new Player();
    Entity *e = player;
    Entity *e1 = new Enemy();//是一个entity实体，但下面是一个player，至于是不是enemy我们不知道
    //因为系统要求，我们必须想编译器保证他是一个玩家player

    Player *p = (Player*)e1;
    //但是在这个例子中是非常危险的，因为e1实际上是enemy，如果把它强制转换为player，
    //也不是不行，如果enemy有的函数，player和entity也都有的话，我们试着运行这个函数他可能会没问题，我们深知可能不会注意到任何问题
    //但是如果我们尝试做一些enemy所没有的，而player所独有的事情，比如访问特定成员变量，只有player有，而enemy没有，因为潜在类型实际是enemy
    //我们程序会崩溃或者作出我们不想做的奇怪的事
```


```cpp
int main() {

    Player *player = new Player();
    Entity *actuallyPlayer = player;
    Entity *actuallyEnemy = new Enemy();//是一个entity实体，但下面是一个player，至于是不是enemy我们不知道
    //因为系统要求，我们必须想编译器保证他是一个玩家player

    //Player *p = (Player*)e1;
    //正因为如此，我们不实用原始类型转换，甚至是static_cast，
    // 你是可以使用static_cast，像这样也没问题Player *p = static_cast<Player*>(e1);
    //相反的，我们切换成dynamic_cast，他会告诉我们需要一个多态类型，因为dynamic_cast只用于多态类类型
    //我们怎么做呢，我们需要一个虚函数表，这实际上告诉我们，他实际上是一个多态类类型，所以我们可以做这个虚函数
    Player *p0 = dynamic_cast<Player*>(actuallyEnemy);//这里会失败，打断点可以看到指针为NULL
    //但是当：
    Player *p1 = dynamic_cast<Player*>(actuallyPlayer);//这里会成功，尽管他们现在都是Entity
    //这就是动态转换所做的，如果强制转化是有效的，那么他将返回你想要的Player指针的值，但是如果它无效，说明他不是你声称的给定类型，那么他就返回NULL
    //简言之，这就是dynamic_cast所做的

}
```
现在你要问他是怎么知道的，玩家是玩家，玩家不是敌人，要做到这一点是因为他存储了运行时类型信息(runtime type information)，也就是所谓的RTTI，运行时类型信息，这是增加开销的，但他可以让你做动态类型转换之类的事情。所以这有两件事需要考虑，首先rtti增加开销，因为类型需要存储更多关于自己的信息，其次，dynamic_cast也需要时间，因为我们需要检查类型信息是否匹配，这个实体是敌人还是玩家，还是什么的，当我们使用dynamic_cast时，我们必须在运行时进行验证。

我们可以在代码中，关闭运行时类型信息，如果我们不需要的话，我们在属性里的c/c++下面的language，可以看到enable runtime type information。使用时关闭它，会导致报错。

所以一定要了解动态类型转换的实际含义，因为他们会做一些额外的事情，他们需要rtti是打开的状态，在绝大多数情况下，举个例子，如果我们要从玩家到实体的转换，这是隐式的，这没问题，不会崩溃，但是如果想刚才那样关掉rtti，你会看到崩溃了，甚至不允许我们动态转换。

让rtti保持开启时常见的，但是也要知道他增加了一些开销。

最后一件事是，因为我们有dynamic_cast，我们可以做验证:
```cpp
    if (dynamic_cast<Player*>(actuallyEnemy))//实际情况一般写if(p0)
    {
        
    }
```

[![top] Goto Top](#table-of-contents)

## 74. BENCHMARKING in C++ (how to measure performance)

基准测试，你刚编写了一些代码，你想看看它实际运行速度有多快，因为你正在处理一个对性能非常关键的会话，或者你正在测试你刚刚了解的新技术，和原来的技术相比哪个快，方法其实有很多，分享我的。

必须要指出的是基准测试的主题很多，如果您尝试测试一段代码的性能，那么使用的工具不仅仅是您用来实际对代码进行基准测试的工具。


```cpp
#include <iostream>
#include <chrono>

class Timer {
public:
    Timer() {
        m_startTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        Stop();
    }

    void Stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(
                m_startTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        auto duration = end - start;

        double ms = duration * 0.001;
        //一般我会选择在stop函数中输出数据到某种跟踪器中，跟踪测量到实际结果，但这是一个非常大的系统，他输出所有的数据到一个文件，做很多事情，这样你就可以查看了，在单独的工具中，查看程序中所有的内容消耗的时间
        // 如果你想制作一款游戏，你会看到每一帧所花费的时间以及每一帧有哪些函数，哪些耗时比较多，这会在其他课程内讲到，但是现在我们要输出程序运行时间

        std::cout << duration << "us (" << ms << "ms)\n";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
};

int main() {

    int value = 0;
    {
        Timer timer;
        for (int i = 0; i < 100000; ++i)
            value += 2;
    }
    std::cout << value << std::endl;
}
```
我想在这里提一下，确保你所测量的东西，就是实际上被编译的代码，这是非常重要的。因为c++编译器显然可以优化代码，剥离某些代码，甚至完全可以改代码。比如debug和release的切换等等。

cherno还对智能指针进行了测试，回家敲代码

[![top] Goto Top](#table-of-contents)

## 75. STRUCTURED BINDINGS in C++

结构化绑定，只针对c++17。这是一个新特性，让我们更好的处理多返回值。

以前我说我喜欢用结构体来处理多返回值，但是随着结构化绑定的引入，这种情况可能会发生改变。

```cpp
#include <iostream>
#include <string>
#include<tuple>

std::tuple<std::string, int> CreatPerson() {
    return {"cherno", 24};
}

int main() {
    //在早期c++版本中，你可以有几种方式处理这些返回值
    auto person = CreatPerson();//在这种情况下，一般用auto，std::tuple<std::string,int>person=CreatPerson();
    //接下来访问数据就变得很烦人了
    std::string& name=std::get<0>(person);

    int age = std::get<1>(person);

}
```
在上面的情况下，我永远也不会使用元组，tie更好一些，你仍然需要创建两个变量，name和age：
```cpp
#include <iostream>
#include <string>
#include<tuple>

std::tuple<std::string, int> CreatPerson() {
    return {"cherno", 24};
}

int main() {
    std::string name;
    int age;
    std::tie(name, age) = CreatPerson();
    //这里我们没有实际的person变量，因为这里没有person，不是结构体，本身不是一个类型，他只是一个容器，用来存放我们想要的东西，包含了一个string和一个int
}
```
然而，他仍然需要三行代码，看起来仍然不太好，我可能仍然使用结构体，创建一个person结构体，然后荣国person.name,person.age来获取数据了（在之前的课程里讲述过）。

现在是你期待已久的部分，这就是c++17带来的一个叫结构化绑定的新特性。我们仍然需要用到tuple:
```cpp
#include <iostream>
#include <string>
#include<tuple>

std::tuple<std::string, int> CreatPerson() {
    return {"cherno", 24};
}

int main() {
    auto[name, age]=CreatPerson();//我们需要做的是使用auto，后面跟着我们给变量的两个名字，这样我们就可以给他取任何我们想要的名字
    std::cout << name;
}
```

再举个例子，52课时的例子完善：
利用结构体时：
```cpp
struct Shade {
   std::string VetexSource;
   std::string FragmentSource;
};

static Shade Parese(const std::string& filePath) {
   //这里shade背后就是一个pair，由两个string组成，所有东西在栈上创建
   std::string ss[2];

   std::string vs = ss[0];
   std::string fs = ss[1];

   return {vs, fs};
}

int main() {
   auto source = Parese("D:/pyl/devNotes");

   unsigned int shader = CreatShader(source.VetexSource, source.FragmentSource);
   std::cin.get();
}
```
用结构化绑定时，我们不打算使用pair而是使用tuple的原因是，tuple理论上可以支持更多的类型，而不仅仅是当前用的vertex和fragment。示例较为混乱就不再列出，简单说来见下：
```cpp
std::tuple<std::string,std::string> Shade::Parese(const std::string& filePath) {
    //这里shade背后就是一个pair，由两个string组成，所有东西在栈上创建
    std::string ss[2];

    std::string vs = ss[0];
    std::string fs = ss[1];

    return {ss[0].str(),ss[1].str()};//return语句没有改变，因为我们仍然可以以完全相同方式构造tuple
}
```

[![top] Goto Top](#table-of-contents)

## 76. How to Deal with OPTIONAL Data in C++

如何处理optional数据。今天讲的是当我们的数据可能存在也可能不存在的时候会发生什么，很多时候，我们有一个返回数据的函数，比方说我们正在读取一个文件，但是如果这个文件不能被读取，会发生什么，他是否不存在，抑或是数据不是我们期望的格式，很多时候，我们仍然需要从函数中返回一些东西，在这个特定的情况下，你可能只返回一个空字符串，但这不是很好，因为这没有多大意义，我的意思是，如果文件是空的，我们应该有办法看到数据是否存在，这就是要用到std::optional的地方了，他是c++17的新东西。
```cpp
std::string ReadFileAsString(const std::string &filepath) {//读取文件并以字符串方式来返回整个文件
    std::ifstream stream(filepath);
    if (stream){
        std::string result;
        //read file...

        stream.close();
        return result;
    }
    return "";//失败的情况下的return空字符串，也可以返回这样一个构造的字符串，return std::string();
}

int main() {

}
```
但是上述方法的重点是，我们很难知道文件是否被成功打开，一般我们判断data是否为空，这样搞就很不nice了，我更喜欢的是能知道数据是否被成功读取的方法，因为也许那个文件存在的，但是他是空的，但他可能是有效的，我们需要一种方法来确定他是否有效，所以另一种解决方法就是使用这个输出布尔值，取名sucess：
```cpp
std::string ReadFileAsString(const std::string &filepath, bool &outSucess) {
    std::ifstream stream(filepath);
    if (stream) {
        std::string result;
        //read file...
        outSucess = true;
        stream.close();
        return result;
    }
    outSucess=false;
    return "";
}

int main() {
bool fileOpendSucessfully;
std::string data= ReadFileAsString("data.txt",fileOpendSucessfully);

    if (fileOpendSucessfully){
        //这显然比空字符串检查好很多，然而他仍然不够好
    }
}
```
使用optional：
```cpp
#include <iostream>
#include <fstream>
#include <optional>

std::optional<std::string> ReadFileAsString(const std::string &filepath) {
    std::ifstream stream(filepath);
    if (stream) {
        std::string result;
        //read file...
        outSucess = true;
        stream.close();
        return result;
    }
    return {};
}

int main() {
    std::optional<std::string> data = ReadFileAsString("data.txt");//auto data = ReadFileAsString("data.txt");

    if (data.has_value()) {
        std::cout << "file read sucessfully\n";
    } else {//如果他没有值，那么我们就知道该文件没有被成功读取，因此文件不能被打开
        std::string &string = *data;//解引用字符串
        std::cout << "File could not be opend\n";

        //所以他和智能指针很想快，如果你想要访问数据，实际上还有一个data.value()可以用
        data.value();
    }
}
```
接下来，如果文件无法打开，或者文件特定部分没有被设置或读取，也许我们有一个默认值，这很常见：
如果数据确实存在于`std::optional`中，他将返回我们那个字符串，如果不存在，他将返回我们传入的任何值，比如"not present".

```cpp
#include <iostream>
#include <fstream>
#include <optional>

std::optional<std::string> ReadFileAsString(const std::string &filepath) {
    std::ifstream stream(filepath);
    if (stream) {
        std::string result;
        //read file...
        outSucess = true;
        stream.close();
        return result;
    }
    return {};
}

int main() {
    std::optional<std::string> data = ReadFileAsString("data.txt");//auto data = ReadFileAsString("data.txt");

    std::string value= data.value_or("not present");//如果数据确实存在于std::optional中，他将返回给我们那个字符串，比如"not present"
    // 这在解析文件时非常有用，比如提取变量或者任何已经设置的元素，因为通常你可能会在文件中有一些东西是可选的，如果某个参数没有在文件中设置，你可以使用你指定的默认值
    //这是非常有用的，因为我们可以在这里简单的使用一个int，例如count，我们可能要运行一个基准测试，在文件中有我们在基准测试中的次数，

    std::optional<int> count;
    //如果这个文件存在，我们可以提取这个计数，使用count_or(100)，如果它不存在，我们可以使用默认的100；
    int c=count.value_or(100);
    if (data.has_value()) {
        std::cout << "file read sucessfully\n";
    } else {//如果他没有值，那么我们就知道该文件没有被成功读取，因此文件不能被打开
        std::string &string = *data;//解引用字符串
        std::cout << "File could not be opend\n";

        //所以他和智能指针很想快，如果你想要访问数据，实际上还有一个data.value()可以用
        data.value();
    }
}
```

[![top] Goto Top](#table-of-contents)

## 77. Multiple TYPES of Data in a SINGLE VARIABLE in C++

今天要讲的是在一个变量中存储多种类型的数据，也是c++17的新特性，他并不是一个真正的特性，他更多的是在一个c++17中的新标准库中给我们的类。

怎么做呢，我们有一个叫做`std::variant`的东西，我觉得这东西和optional很像，他的作用是让我们不用担心处理的确切数据类型，只有一个变量，之后我们再考虑它的具体类型，我们所做的就是指定一个叫做`std::variant`的东西，然后列出他可能的数据类，例如你可能在解析一个文件，你可能不确定这是一个字符串还是一个整数，也许你在程序运行时接受一个命令行参数，你不确定那个参数是整数还是字符串，还是浮点数或者布尔值等，`std::variant`允许你列出所有有可能的类型然后你可以决定他将是什么，如果你想，你可以将它重新赋值给任何类型，这也是你创建可能类型的变量的一种方式。

```cpp
#include <iostream>
#include <variant>

int main() {
    std::variant<std::string, int> data;//输入可能的类型，把它称为data，利用构造函数给他赋值，但是为了更明确一点，我们也可以使用赋值操作符
    data = "cherno";

    data.index();// 0
    std::cout << std::get<std::string>(data)<<"\n";//访问数据
    data = 2;//因为我们列出了他是一个字符串或者整数，我们当然可以把他重新赋值给一个字符串或整数
    //data = false;//但是如果我们给他赋值其他类型，你可以看到他仍然允许我们这么做，但是如果我们这样做，我们实际上以后就不能访问他了，这不是我们想要的
    std::cout << std::get<int>(data)<<"\n";//访问数据

    //如果访问数据类型错误会报异常，但是我们不想要异常，来检查数据是否和我们想的一样，我们有几种方法

    //首先是intdex函数，这个函数会告诉你索引类型，他将每种类型映射到一个索引上，string是0，int是1，在本例中他将会告诉我们数据当前存储在哪个索引中
    data.index();// 1

}
```

更好的办法，get_if函数：

```cpp
#include <iostream>
#include <variant>

int main() {
    std::variant<std::string, int> data;//输入可能的类型，把它称为data，利用构造函数给他赋值，但是为了更明确一点，我们也可以使用赋值操作符
    data = "cherno";

    std::cout << std::get<std::string>(data) << "\n";//访问数据
    data = 2;//因为我们列出了他是一个字符串或者整数，我们当然可以把他重新赋值给一个字符串或整数
    //data = false;//但是如果我们给他赋值其他类型，你可以看到他仍然允许我们这么做，但是如果我们这样做，我们实际上以后就不能访问他了，这不是我们想要的
    std::cout << std::get<int>(data) << "\n";//访问数据

    //更好的办法，get_if函数
    auto value = std::get_if<std::string>(&data);//传递variant的内存地址或指针，然后这将为我们返回一个指针，所以我们可以检查这个指针是否为空
    //我们可以看到，如果不是这个类型，他将会给我们一个空指针，但是如果是的话，他将会给我们一个指向那个字符串的指针

    //这很酷，因为你只需要将它简单的封装到一个if块中，就像这样
    if (auto value = std::get_if<std::string>(&data)) {
        std::string &v = *value;//解引用value
    }
    else{
        //或者我们可以利用else if来处理另一种类型，这种是我最喜欢的处理方式，我认为他很干净，让我们得到期望的类型的那个值
    }
}
```
现在有很多关于variant的讨论，说他本质上就像类型安全的联合体union，我想说他们很不同，如果我们检查一下这个数据的大小，打印数据的大小，
```cpp
    std::variant<std::string, int> data;
    data = "cherno";

    std::cout<<sizeof(data)<<"\n";
```
如果是结构体的话，结果是什么，string就是最大的类型大小，如果联合体里面有double a、float b等，这个联合体大小是最大的类型的大小，a是双精度浮点数，那么有8字节。variants不是这样工作的，他只是将所有可能的数据类型存储为单独的变量作为单的的成员，比如我们试着比较这些数据的大小
```cpp
    std::variant<std::string, int> data;//输入可能的类型，把它称为data，利用构造函数给他赋值，但是为了更明确一点，我们也可以使用赋值操作符
    data = "cherno";
    std::cout<<sizeof(int )<<"\n";
    std::cout<<sizeof(std::string)<<"\n";
    std::cout<<sizeof(data)<<"\n";
```
你可以看到，他是为你创建了一个结构体或者类，他只是将这两种数据类型存储为那个类或结构体中的成员，因此从技术上讲union仍然是更有效率和更好的，然而variant更加类型安全，不会造成未定义行为，你应该使用它，除非你做的是底层优化，把内存大小保持在一个较低水平，但是如果你在桌面平台上，你可以自由地使用更多的内存和处理能力，那么`std::variant`在技术上更加安全。

再来一个例子说明variant是有用的：

```cpp
std::optional<std::string>ReadFilesAsString()
{
    return {};//如果文本存在的话将会返回所有文本的字符串，如果不存在或者不能读取，则返回optional{}
}
```
这虽然很好，能让我们容易地看到读取是否成功，`std::optional`能在任何情况下允许我们有一些不存在的可选数据，在今天的例子中，我们要知道哪里出了问题，而不仅仅说数据不存在，所以我们不用optional而是variant，如果我们成功的获取了数据，我们可以用字符串作为值，如果不成功，我们可以设置一些错误代码，我们可以把它编码成一个整数。比返回一个布尔值更详细一些，给我们更多信息而返回一个布尔值来判断是否有结果这种情况，就是之前optional的方式了。

```cpp
enum class ErrorCode {
    None = 0,//没有错误
    NotFound = 1,//没有找到
    NoAccess = 2//不能读取
};

std::variant<std::string, ErrorCode> ReadFilesAsString() {
    return {};
}
```

[![top] Goto Top](#table-of-contents)

## 78. How to store ANY data in C++.mp4

今天讲如何在c++单个变量中存储任意类型的数据。很多人会想拿void指针，是的这是对的但是今天暂时不讲，然而今天讲的是一个更好的办法是一个安全的方式，他也是c++17全新处理方式，就是：`std::any`。

我们可以存储任何东西，我认为这里更大的问题不是我们如何使用`std::any`，我认为这很简单，重要的是我们什么时候使用它，为什么要使用`std::any`而不是`std::variant`，这才是今天要讲的。

```cpp
#include <iostream>
#include <any>
#include <variant>

int main() {
    std::any data;//和variant很像，出了没有模版参数，因为他可以储存任何类型，然后输入变量名称data
    //std::any data= std::make_any()构造
    data = 2;
    data = "cherno";//const char
    data = std::string("cherno");

    //如果需要取出数据，你必须知道他是哪个类型，然后将它转换为那个类型，你可以用std::any_cast来做
    std::string string = std::any_cast<std::string>(data);//如果data不是你想转换的类型，这将会抛出一个类型转换异常，记住这一点

    //乍一看和variant很类似，我们可以存储任何类型，而std::variant要求我们列出所有类型，虽然很多人认为variant更糟糕，因为必须列出所有类型，而在any这里你根本不用担心类型
    //相反，这才是在绝大多数情况下，为什么variant比any更好的地方，事实上variant要求列出所有这些类型，这是很好的，会使得类型安全

    //std::string string = std::any_cast<std::string>(data);//所以这里是行不通的，cherno不是字符串，只是一个const char指针

    //然而在这个场景使用variant：
    std::variant<int, std::string> data2;
    data2 = 2;
    data2 = "cherno";
    std::string string2 = std::get<std::string>(data);

    //除了variant需要列出类型之外，是的这和他们的存储方式有关，variant只是一个类型安全的union，意思是他把所有的数据都存储在一个union里
    //查看any源码，可以总结如下：如果你在小类型上使用variant或any，float，比如一个类的vector或类似的东西，比如math库等，都没问题，我的意思是他们会以完全相同的方式工作
    //如果你需要更多的存储空间，std::any会动态分配，但是std::variant不会
    //换句话说，除了更加类型安全和有一点限制性（这是一件好事）之外，std::variant在处理较大数据时也执行的更快，而这些数据又需要避免动态内存分配
}
```
我能给你的另一个提高性能的技巧是确保你不会复制数据，所以你可以看到这里的字符串，`std::string string2 = std::get<std::string>(data);`我当然是在复制他。如果我们回到std::any的方式，（如果你不想复制），你需要通过引用返回这个，`std::string& string2 = std::get<std::string>(data);`，你发现这不行，这在std::get中是可以的，但是在std::any_cast中，如果你计划通过引用返回，要确保你把引用插入到模版参数中，才能很好的优化：`std::string& string2 = std::get<std::string&>(data);`

你可以看到，在这个例子中，很显然要确保我们使用的是`std::string`而不是`const char*`：`data = std::string("Cherno");`，在这种情况下，我们不会得到任何内存分配除了那个可能来自string的内存分配。（cherno在这里重载了new操作符，和不错的例子，在此做个书签日后再记录）

回到这个问题，什么时候使用std::any，这是一个棘手的问题，很多人会直截了当的告诉你，他有点无用，说实话我倾向于同意。什么是std::any好的用例？如果希望在一个变量中存储多个数据类型，请使用std::variant，他基本上是std::any的类型安全版本，这意味着你不能随意设置他的类型，而且他也不会动态分配内存，这样它的性能会更好，如果你需要，要求能够在单个变量中存储任何数据类型，也许你需要重新考虑程序的设计，我的意思是，我真的想不出一个有效的用例，我认为就不该用到他，我的意思是如果你有像缓冲区的数据，你完全不知道这些数据是什么，你只是想指向他们，那么你可以使用void指针，但这又是完全不同的，好吧，如果你有好的用例，请留言我很乐意阅读其中的一些注释。就目前来看，我不认为他和optional以及variant一样有用，std::any就是来搞笑的。


[![top] Goto Top](#table-of-contents)

## 79. How to make C++ run FASTER (with std  async)

我们会深入到一个项目中讨论如何通过多线程来提高性能。


[![top] Goto Top](#table-of-contents)

## 80. How to make your STRINGS FASTER in C++!

[![top] Goto Top](#table-of-contents)

## 81. VISUAL BENCHMARKING in C++ (how to measure performance visually)

[![top] Goto Top](#table-of-contents)

## 82. SINGLETONS in C++

[![top] Goto Top](#table-of-contents)

## 83. Small String Optimization in C++

[![top] Goto Top](#table-of-contents)

## 84. Track MEMORY ALLOCATIONS the Easy Way in C++

[![top] Goto Top](#table-of-contents)

## 85. lvalues and rvalues in C++

[![top] Goto Top](#table-of-contents)

## 86. Continuous Integration in C++

[![top] Goto Top](#table-of-contents)

## 87. Static Analysis in C++

[![top] Goto Top](#table-of-contents)

## 88. Argument Evaluation Order in C++

[![top] Goto Top](#table-of-contents)

## 89. Move Semantics in C++

[![top] Goto Top](#table-of-contents)

## 90. std  move and the Move Assignment Operator in C++

[![top] Goto Top](#table-of-contents)

## 91. ARRAY - Making DATA STRUCTURES in C++

[![top] Goto Top](#table-of-contents)

## 92. VECTOR DYNAMIC ARRAY -  Making DATA STRUCTURES in C++

[![top] Goto Top](#table-of-contents)

## 93. ITERATORS in C++

[![top] Goto Top](#table-of-contents)

## 94. Writing an ITERATOR in C++

[![top] Goto Top](#table-of-contents)

## 95. How to REALLY learn C++


[![top] Goto Top](#table-of-contents)

---

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

`const R b(20, 30);`意为该对象为const不可被修改，该对象只能调用常成员函数，非常对象也可以调用常成员函数。

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
除了在定义它的源文件中可以使用外还能被其它文件使用。。文件作用域中定义的变量默认情况下都是外部变量。在其它文件中如果需要使用需要用 extern 关键字声明。

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

- 若有异常则通过 throwt 创建一个异常对象并抛掷
- 将可能抛出异常的程序段嵌在 try 块之中。通过正常的顺序执行到达 try 语句，然后执行 try 块内的保护段
- 如果在保护段执行期间没有引起异常，那么跟在 ty 块后的 catch 子句就不执行。程序从 try 块后的最后一个 catch 子句后面的语句继续执
- catch 子句按其在 try 块后出现的顺序被检查。匹配的 catch 子句将捕获并处理异常（或继续抛掷异常）。
- 如果匹配的处理器未找到，则库函数 terminate 将被自动调用，其缺默认能是调用 abort 终止程序













[![top] Goto Top](#table-of-contents)

[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png