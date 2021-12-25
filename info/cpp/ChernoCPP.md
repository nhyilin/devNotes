# Table of Contents
- [Table of Contents](#table-of-contents)
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

省略部分：
01. Welcome to C++
02.  How to Setup C++ on Windows
03. How to Setup C++ on Mac
04. How to Setup C++ on Linux
05. How C++ Works
06. How the C++ Compiler Works


# 07. How the C++ Linker Works

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

# 08. Variables in C++

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


# 10. C++ Header Files

头文件：公共位置，用来存储只是声明而不是定义，因为，请记住：我们智能在一个通用的地方来存储函数的声明。只是声明，没有实际定义，没有函数体。

`void Log(const char* message)`称作函数的签名（signature）

在每次调用一个函数时，都需要将其声明提前体现在该文件，那总不能每次都复制粘贴这些签名吧，所以这就是头文件的意义

[![top] Goto Top](#table-of-contents)

# 11. How to DEBUG C++ in VISUAL STUDIO.mp4

调试是为了读取内存，最终你要记住，电脑永远是对的。

在内存视图中，输入地址后，变量内容显示全为`cccc`之类的，主要是`c`，意味着变量还未初始化。且在内存视图下，两个数字等于一个字节，也就是8位，这也是为什么我们用十六进制来看这个视图，因为如果我们那样做，每两个十六进制数与一个`byte`对齐，我们就能分辨，这8个十六进制数字是4字节的内存。

当我在一个函数或者`for`循环内，不再想继续观察时，在想让程序停止的地方打断点，然后`F5`，让debug继续，就可以进行到断点处了。

[![top] Goto Top](#table-of-contents)

# 12. CONDITIONS and BRANCHES in C++ (if statements)

优化过的代码一般没有if语句，因为这样会拖慢程序

[![top] Goto Top](#table-of-contents)

# 13. BEST Visual Studio Setup for C++ Projects!



主要讲解了Cherno本人vs的设置。

1. 将源代码和sln等文件分离开，Cherno通过vs的Solution Exporler窗口中上边的Show All Files视图来调整实际的文件目录，代码目录命名为`src`，默认的filter视图其实是筛选器，虚拟的组织方案，在磁盘上并不真实存在，即使删除也没有关系，和磁盘上的实际目录毫无关系。
2. 当想查看生成的exe文件时，vs默认在存放源代码的目录下生成debug文件夹，这里存放了中间文件。项目目录和实际的可执行二进制文件放入sln同级目录下。更改设置可以在项目属性中更改，`Configuration Properties`内的`General`设置，其路径都相对于项目路径而言，项目路径不是指`sln`而是`vcxproj`文件。重要的是：在修改设置时，记得按需将`Configuration`改为`All Configurations`，将`Platform`改为`All Platforms`。
    - 在其中，`outPut Directory`设置为`$(SolutionDir)bin\$(Platform)\$(configuration)\`，目的是将所有二进制包括dll们存储在同一个文件夹下
    - 中间文件夹，`Intemediate Directory`设置为`$(SolutionDir)bin\intermediates\$(Platform)\$(configuration)\`
    - 前两条中，`SolutionDir`和`bin`文件夹中间没有反斜杠看，是因为宏定义时已经将反斜杠写了

[![top] Goto Top](#table-of-contents)

# 14. Loops in C++ (for loops, while loops)

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

# 15. Control Flow in C++ (continue, break, return)


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

# 16. POINTERS in C++

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

# 17. REFERENCES in C++

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

[![top] Goto Top](#table-of-contents)

# 18. CLASSES in C++
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

# 19. CLASSES vs STRUCTS in C++

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

# 20. How to Write a C++ Class

据Cherno说这个类写的很糟糕，那就不做记录了，只是比较值得学习的一点是：LogLevel，当指定某一Level时，要做筛选，不是所有Log都允许被打印出来，所谓的限制条件。

[![top] Goto Top](#table-of-contents)

# 21. Static in C++

类外的Static，该符号的链接声明符号的链接为Internal（内部），只在定义的部分可见，类似07. How the C++ Linker Works讲的头文件。

类内部的Static变量，则该变量将于该类的所有实例共享内存，在您所创建的该
类或者是结构体中的所有实例中，只有一个实例，也就是静态变量，相同的是，仅有一个静态函数。

在这讲，指关注静态变量在类外部的含义。

当我们定义了一个静态变量，在链接阶段，连接器不会在该符号定义的翻译单元（translation unit）之外寻找该函数或变量的定义或者声明。

在Static.cpp中定义`static int s_Veriable=5;`，并且在main.cpp中定义全局变量` s_Veriable=10;`，这时编译不会报错，但是去掉Static.cpp内的`static`，则编译报错，链接错误。

为了避免报错，则去掉static.cpp中的`static`，在main.cpp中：`entern int s_Variable`，意思是，在外部单元，其他地方定义了`s_Variable`这个变量。

我们想：如果文件定义了一个变量，却没有声明`static`时，那这个变量全局可见，也就是，链接时，会查询所有文件，这会造成很糟糕的bug。所以本节重点是：尝试标记您的函数和变量为静态，除非您实际上却是需要全局链接。

[![top] Goto Top](#table-of-contents)

# 22. Static for Classes and Structs in C++

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

# 23. Local Static in C++
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

# 24. ENUMS in C++

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

# 25. Constructors in C++


构造函数是特殊的函数，他在每次实例化对象时运行，他的作用是初始化该类，当创建一个新对象实例时，构造函数确保你初始化了所有内存，做了所有你需要的设置

`Log() = delete;`，不适用构造函数。

[![top] Goto Top](#table-of-contents)

# 26. Destructors in C++

如果在构造函数中调用了特定的初始化代码，你需要在析构函数中删除这些东西，否则会造成内存泄漏。一个很好的例子是在堆上分配的对象，如果您已经在堆上分配了任何类型的内存，那么需要手动清理。如果在类中使用或者构造分配了内存，你可能需要在析构函数中删除他们。

[![top] Goto Top](#table-of-contents)

# 27. Inheritance in C++
`class SubClass : public SperClass`

他继承允许我们有一个相互关联的类的层次结构，换句话说就是允许我们有一个包含公共功能的基类，为的是防止我们写重复代码。

子类一定是父类的超集，总拥有父类的所有，并且再加上一点点，这是面向对象编程中最重要的东西之一，记住，当你创建一个字类时，它将包含父类所包含的一切。

btw:`std::cout<<"size of a class"<< sizeof(SubClass)<<;`，意思是打印出某个类的对象的大小，取决于类中变量的个数和类型，比如只有一个`int`类型变量，则`sizeof`输出大小为`4`，不包含函数。如果我们重写函数和子类，那么我们就需要维护一个`V表（虚函数表）`，也就是要额外的内存。

[![top] Goto Top](#table-of-contents)

# 28. Virtual Functions in C++

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

# 29. Interfaces in C++ (Pure Virtual Functions)

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

# 30. Visibility in C++

我只想提一下，可见性是对程序实际运行方式完全没有影响的东西，对程序的性能或类似的东西没有影响，纯粹语言中的东西，只是为了写出更好看的代码。

`private`意味着只有`（only*）`这个类可以访问这些变量。这里的only需要加星号，因为在c++中有个叫`友元（friend）`的东西，`friend`关键词可以让类或者函数称为类的友元，友元实际上可以访问私有成员。

public继承也不可访问私有成员变量，成员函数同理。

`protected`可见性介于两者之间。意味着类和层次结构中的所有子类，可以访问这些符号。

那么为什么不让所有东西都`public`，首先是代码风格问题，可见性让代码更容易理解，易于维护。当你将一个事件标记为`private`时，这基本上告诉所有人包括你自己：你不应该操你个其他类访问这个，只能在类的内部访问这个。读代码时，看到类的结构，应该可以这么说，我只被允许接触`public`的东西。通过可见性，我们可以确保人们不会调用他们不应该调用的代码，并可能破坏某些东西。

一个很好的例子是UI界面，如果我想移动按钮的位置，如果我只访问按钮的坐标`x`和`y`，然后改变变量，按钮实际上可能不会动，我的意思是x轴和y轴的位置可能不同，为了真正让按钮移动，我们可能要刷新显示，如果我只设置`x = 5`之类，`x`确实变了，但显示器并不知道，它不知道从内存获取新的值，而继续用老的值。然而如果我在类中创建一个函数叫`SetPosition`，我可以做的不仅仅是给x赋值，我还可以调用另一个叫`refresh`之类的函数，他能做所有他需要做的事情，我可以让那个`x`变量本身私有，然后`SetPosition`函数为共有，显然，想使用这些代码的人可以看到，我不应该直接给`x`赋值，我应该调用SetPosition函数。

[![top] Goto Top](#table-of-contents)

# 31. Arrays in C++

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

# 32. How Strings Work in C++ (and how to use them)

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

# 33. String Literals in C++

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

# 34. CONST in C++
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

# 35. The Mutable Keyword in C++.srt

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

# 36. Member Initializer Lists in C++ (Constructor Initializer List)

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

# 37. Ternary Operators in C++ (Conditional Assignment)

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

<!-- figures -->

[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png

001 - 01. Welcome to C++.mp4
001 - 01. Welcome to C++.srt
002 - 02. How to Setup C++ on Windows.mp4
002 - 02. How to Setup C++ on Windows.srt
003 - 03. How to Setup C++ on Mac.mp4
003 - 03. How to Setup C++ on Mac.srt
004 - 04. How to Setup C++ on Linux.mp4
004 - 04. How to Setup C++ on Linux.srt
005 - 05. How C++ Works.mp4
005 - 05. How C++ Works.srt
006 - 06. How the C++ Compiler Works.mp4
006 - 06. How the C++ Compiler Works.srt
007 - 07. How the C++ Linker Works.mp4
007 - 07. How the C++ Linker Works.srt
008 - 08. Variables in C++.mp4
008 - 08. Variables in C++.srt
009 - 09. Functions in C++.mp4
009 - 09. Functions in C++.srt
010 - 10. C++ Header Files.mp4
010 - 10. C++ Header Files.srt
011 - 11. How to DEBUG C++ in VISUAL STUDIO.mp4
011 - 11. How to DEBUG C++ in VISUAL STUDIO.srt
012 - 12. CONDITIONS and BRANCHES in C++ (if statements).mp4
012 - 12. CONDITIONS and BRANCHES in C++ (if statements).srt
013 - 13. BEST Visual Studio Setup for C++ Projects!.mp4
013 - 13. BEST Visual Studio Setup for C++ Projects!.srt
014 - 14. Loops in C++ (for loops, while loops).mp4
014 - 14. Loops in C++ (for loops, while loops).srt
015 - 15. Control Flow in C++ (continue, break, return).mp4
015 - 15. Control Flow in C++ (continue, break, return).srt
016 - 16. POINTERS in C++.mp4
016 - 16. POINTERS in C++.srt
017 - 17. REFERENCES in C++.mp4
017 - 17. REFERENCES in C++.srt
018 - 18. CLASSES in C++.mp4
018 - 18. CLASSES in C++.srt
019 - 19. CLASSES vs STRUCTS in C++.mp4
019 - 19. CLASSES vs STRUCTS in C++.srt
020 - 20. How to Write a C++ Class.mp4
020 - 20. How to Write a C++ Class.srt
021 - 21. Static in C++.mp4
021 - 21. Static in C++.srt
022 - 22. Static for Classes and Structs in C++.mp4
022 - 22. Static for Classes and Structs in C++.srt
023 - 23. Local Static in C++.mp4
023 - 23. Local Static in C++.srt
024 - 24. ENUMS in C++.mp4
024 - 24. ENUMS in C++.srt
025 - 25. Constructors in C++.mp4
025 - 25. Constructors in C++.srt
026 - 26. Destructors in C++.mp4
026 - 26. Destructors in C++.srt
027 - 27. Inheritance in C++.mp4
027 - 27. Inheritance in C++.srt
028 - 28. Virtual Functions in C++.mp4
028 - 28. Virtual Functions in C++.srt
029 - 29. Interfaces in C++ (Pure Virtual Functions).mp4

030 - 30. Visibility in C++.mp4

















038 - 38. How to CREATE INSTANTIATE OBJECTS in C++.mp4
038 - 38. How to CREATE INSTANTIATE OBJECTS in C++.srt
039 - 39. The NEW Keyword in C++.mp4
039 - 39. The NEW Keyword in C++.srt
040 - 40. Implicit Conversion and the Explicit Keyword in C++.mp4
040 - 40. Implicit Conversion and the Explicit Keyword in C++.srt
041 - 41. OPERATORS and OPERATOR OVERLOADING in C++.mp4
041 - 41. OPERATORS and OPERATOR OVERLOADING in C++.srt
042 - 42. The 'this' keyword in C++.mp4
042 - 42. The 'this' keyword in C++.srt
043 - 43. Object Lifetime in C++ (Stack Scope Lifetimes).mp4
043 - 43. Object Lifetime in C++ (Stack Scope Lifetimes).srt
044 - 44. SMART POINTERS in C++ (std  unique_ptr, std  shared_ptr, std  weak_ptr).mp4
044 - 44. SMART POINTERS in C++ (std  unique_ptr, std  shared_ptr, std  weak_ptr).srt
045 - 45. Copying and Copy Constructors in C++.mp4
045 - 45. Copying and Copy Constructors in C++.srt
046 - 46. The Arrow Operator in C++.mp4
046 - 46. The Arrow Operator in C++.srt
047 - 47. Dynamic Arrays in C++ (std  vector).mp4
047 - 47. Dynamic Arrays in C++ (std  vector).srt
048 - 48. Optimizing the usage of std  vector in C++.mp4
048 - 48. Optimizing the usage of std  vector in C++.srt
049 - 49. Using Libraries in C++ (Static Linking).mp4
049 - 49. Using Libraries in C++ (Static Linking).srt
050 - 50. Using Dynamic Libraries in C++.mp4
050 - 50. Using Dynamic Libraries in C++.srt
051 - 51. Making and Working with Libraries in C++ (Multiple Projects in Visual Studio.mp4
051 - 51. Making and Working with Libraries in C++ (Multiple Projects in Visual Studio.srt
052 - 52. How to Deal with Multiple Return Values in C++.mp4
052 - 52. How to Deal with Multiple Return Values in C++.srt
053 - 53. Templates in C++.mp4
053 - 53. Templates in C++.srt
054 - 54. Stack vs Heap Memory in C++.mp4
054 - 54. Stack vs Heap Memory in C++.srt
055 - 55. Macros in C++.mp4
055 - 55. Macros in C++.srt
056 - 56. The 'auto' keyword in C++.mp4
056 - 56. The 'auto' keyword in C++.srt
057 - 57. Static Arrays in C++ (std  array).mp4
058 - 58. Function Pointers in C++.mp4
058 - 58. Function Pointers in C++.srt
059 - 59. Lambdas in C++.mp4
059 - 59. Lambdas in C++.srt
060 - 60. Why I don't 'using namespace std'.mp4
060 - 60. Why I don't 'using namespace std'.srt
061 - 61. Namespaces in C++.mp4
061 - 61. Namespaces in C++.srt
062 - 62. Threads in C++.mp4
062 - 62. Threads in C++.srt
063 - 63. Timing in C++.mp4
063 - 63. Timing in C++.srt
064 - 64. Multidimensional Arrays in C++ (2D arrays).mp4
064 - 64. Multidimensional Arrays in C++ (2D arrays).srt
065 - 65. Sorting in C++.mp4
065 - 65. Sorting in C++.srt
066 - 66. Type Punning in C++.mp4
066 - 66. Type Punning in C++.srt
067 - 67. Unions in C++.mp4
067 - 67. Unions in C++.srt
068 - 68. Virtual Destructors in C++.mp4
068 - 68. Virtual Destructors in C++.srt
069 - 69. Casting in C++.mp4
069 - 69. Casting in C++.srt
070 - 70. Conditional and Action Breakpoints in C++.mp4
070 - 70. Conditional and Action Breakpoints in C++.srt
071 - 71. Safety in modern C++ and how to teach it.mp4
071 - 71. Safety in modern C++ and how to teach it.srt
072 - 72. Precompiled Headers in C++.mp4
072 - 72. Precompiled Headers in C++.srt
073 - 73. Dynamic Casting in C++.mp4
073 - 73. Dynamic Casting in C++.srt
074 - 74. BENCHMARKING in C++ (how to measure performance).mp4
074 - 74. BENCHMARKING in C++ (how to measure performance).srt
075 - 75. STRUCTURED BINDINGS in C++.mp4
075 - 75. STRUCTURED BINDINGS in C++.srt
076 - 76. How to Deal with OPTIONAL Data in C++.mp4
076 - 76. How to Deal with OPTIONAL Data in C++.srt
077 - 77. Multiple TYPES of Data in a SINGLE VARIABLE in C++.mp4
078 - 78. How to store ANY data in C++.mp4
078 - 78. How to store ANY data in C++.srt
079 - 79. How to make C++ run FASTER (with std  async).mp4
080 - 80. How to make your STRINGS FASTER in C++!.mp4
080 - 80. How to make your STRINGS FASTER in C++!.srt
081 - 81. VISUAL BENCHMARKING in C++ (how to measure performance visually).mp4
081 - 81. VISUAL BENCHMARKING in C++ (how to measure performance visually).srt
082 - 82. SINGLETONS in C++.mp4
082 - 82. SINGLETONS in C++.srt
083 - 83. Small String Optimization in C++.mp4
083 - 83. Small String Optimization in C++.srt
084 - 84. Track MEMORY ALLOCATIONS the Easy Way in C++.mp4
084 - 84. Track MEMORY ALLOCATIONS the Easy Way in C++.srt
085 - 85. lvalues and rvalues in C++.mp4
085 - 85. lvalues and rvalues in C++.srt
086 - 86. Continuous Integration in C++.mp4
086 - 86. Continuous Integration in C++.srt
087 - 87. Static Analysis in C++.mp4
087 - 87. Static Analysis in C++.srt
088 - 88. Argument Evaluation Order in C++.mp4
088 - 88. Argument Evaluation Order in C++.srt
089 - 89. Move Semantics in C++.mp4
089 - 89. Move Semantics in C++.srt
090 - 90. std  move and the Move Assignment Operator in C++.mp4
090 - 90. std  move and the Move Assignment Operator in C++.srt
091 - 91. ARRAY - Making DATA STRUCTURES in C++.mp4
091 - 91. ARRAY - Making DATA STRUCTURES in C++.srt
092 - 92. VECTOR DYNAMIC ARRAY -  Making DATA STRUCTURES in C++.mp4
092 - 92. VECTOR DYNAMIC ARRAY -  Making DATA STRUCTURES in C++.srt
093 - 93. ITERATORS in C++.mp4
093 - 93. ITERATORS in C++.srt
094 - 94. Writing an ITERATOR in C++.mp4
095 - 95. How to REALLY learn C++.mp4
095 - 95. How to REALLY learn C++.srt