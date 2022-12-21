本文记录日常c++中比较零碎的知识点，做整理用。

# Table of Contents
- [Table of Contents](#table-of-contents)
  - [\*和\&操作符](#和操作符)
  - [指针的指针，以及指针的引用](#指针的指针以及指针的引用)
    - [为什么需要使用它们](#为什么需要使用它们)
    - [使用指针的指针](#使用指针的指针)
    - [指针的引用](#指针的引用)
  - [三元运算符](#三元运算符)
  - [命名空间](#命名空间)
  - [struct和typedef struct](#struct和typedef-struct)
  - [else if](#else-if)
  - [数组引用和指针引用](#数组引用和指针引用)
  - [数组遍历十种方式](#数组遍历十种方式)
  - [char 转换为std::string的 10 种方法](#char-转换为stdstring的-10-种方法)
  - [C++获取项目路径的两种方式](#c获取项目路径的两种方式)
    - [一、Cmake传参：适用于简单场景](#一cmake传参适用于简单场景)
    - [二、从环境变量读取：适合脚本场景](#二从环境变量读取适合脚本场景)
  - [空指针异常](#空指针异常)

完整版笔记见：[ChernoCPP](ChernoCPP.md)

## *和&操作符
这段话节选自郑莉老师c++课堂，觉得很经典故摘录

C++提供了两个与地址相关的运算符——`*`和`&`。`*`称为指针运算符，也称解析（dereference），表示获取指针所指向的变量的值，这是一个一元操作符。例如，`*ptr` 表示指针 ptr 所指向的 int 型数据的值。`&`称为取地址运算符，也是一个一元操作符，用来得到一个对象的地址，例如，使用`&i`就可以得到变量 `i` 的存储单元地址。

必须注意，`*`和`&`<u>出现在声明语句中和执行语句中其含义是不同的</u>，它们作为一元运算符和作为二元运算符时含义也是不同的。

一元运算符`*`出现在声明语句中，在被声明的变量名之前时，表示声明的是指针，例如：

`int *p; //声明 p 是一个 int 型指针`

`*`出现在执行语句中或声明语句的初始化表达式中作为一元运算符时，表示访问指针所指对象的内容，例如：

`cout << *p; //输出指针 P 所指向的内容`

`&`出现在变量声明语句中位于被声明的变量左边时，表示声明的是引用，例如：

`int &rf; //声明一个 int 型的引用 rf`

`&`在给变量赋初值时出现在等号右边或在执行语句中作为一元运算符出现时，表示取对象的地址，例如：
```cpp
int a, b;
int pa, pb= &b;
pa=&a;
```

[![top] Goto Top](#table-of-contents)

## 指针的指针，以及指针的引用

不算生僻的一个知识点，记录备忘（这里说的指针的指针不是一个二维数组）
### 为什么需要使用它们
当我们把一个指针做为参数传一个方法时，其实是把指针的复本传递给了方法，也可以说传递指针是指针的值传递。

如果我们在方法内部修改指针会出现问题，在方法里做修改只是修改的指针的copy而不是指针本身，原来的指针还保留着原来的值。我们用下边的代码说明一下问题：
```cpp
int m_value = 1;

void func(int *p)
{
    p = &m_value;
}

int main(int argc, char *argv[])
{
    int n = 2;
    int *pn = &n;
    cout << *pn << endl;
    func(pn);
    cout << *pn <<endl;
    return 0;
}
```
输出两个2

### 使用指针的指针
```cpp
void func(int **p)
{
    *p = &m_value;

    // 也可以根据你的需求分配内存
    *p = new int;
    **p = 5;
}

int main(int argc, char *argv[])
{
    int n = 2;
    int *pn = &n;
    cout << *pn << endl;
    func(&pn);
    cout << *pn <<endl;
    return 0;
}
```
我们看一下`func(int **p)`这个方法

- `p`：  是一个指针的指针，在这里我们不会去对它做修改，否则会丢失这个指针指向的指针地址
- `*p`:  是被指向的指针，是一个地址。如果我们修改它，修改的是被指向的指针的内容。换句话说，我们修改的是`main()`方法里 `*pn`指针
- `**p`: 两次解引用是指向`main()`方法里`*pn`的内容

### 指针的引用
```cpp
int m_value = 1;

void func(int *&p)
{
    p = &m_value;

    // 也可以根据你的需求分配内存
    p = new int;
    *p = 5;
}

int main(int argc, char *argv[])
{
    int n = 2;
    int *pn = &n;
    cout << *pn << endl;
    func(pn);
    cout << *pn <<endl;
    return 0;
}
```
看一下`func(int *&p)`方法

- `p`:  是指针的引用，`main()`方法里的 `*pn`
- `*p`:是`main()`方法里的`pn`指向的内容。

## 三元运算符

`var = condition ? X : Y;`

等价于：
```cpp
if(condition){
   var = X;
}else{
   var = Y;
}
```
[![top] Goto Top](#table-of-contents)

## 命名空间
当自定义命名空间在h文件中，然后在cpp文件中希望使用时，见下代码：
Consider a pair of two source files: an interface declaration file (`*.h` or `*.hpp`) and its implementation file (*.cpp).

```cpp
/***.h***/
namespace MyNamespace {
  class MyClass {
  public:
    int foo();
  };
}

/***.cpp***/
#include "MyClass.h"
namespace MyNamespace {

  int MyClass::foo() { ... }

}
```

[stackoverflow](https://stackoverflow.com/questions/10816600/c-namespaces-how-to-use-in-header-and-source-files-correctly)


[![top] Goto Top](#table-of-contents)

## struct和typedef struct
1. C中定义一个结构体类型要用typedef
```c
typedef struct Student {
    int a;
} Stu;
```
于是在声明变量的时候就可：`Stu stu1`;(如果没有`typedef`就必须用`struct Student stu1;`来声明)

也可以不写`Student`:

```c
typedef struct {
    int a;
} Stu;
```
2. C++定义了结构体类型

不用typedef
```cpp
struct Student {
    int a;
};
```
定义了结构体类型Student，声明变量时直接Student stu2

或：
```cpp
struct Student {
    int a;
} stu1;  // stu1是一个变量
```

用typedef:
```cpp
typedef struct Student2 {
    int a;
} stu2;  // stu2是一个结构体类型=struct Student
```
stu先定义对象
```cpp

#include <iostream>

void test(void);

// 1、用typedef struct student{类型
// 变量名}STU,*STU1，在{}后面跟的STU是该结构体的变量名,*STU1是该结构体的类型的地址。
typedef struct student {
    int age;
} STU, *STUP;
/*
 上面的和下面的等价
 typedef struct student{
 int age ;
 }STU;
 typedef STU *STUP;
 */

int main(int argc, const char* argv[]) {
    // 声明一个结构体对象
    STU opooc;
    // 声明一个指向该类结构体对象的指针
    STUP opoocP;
    // 给结构体对象内部age变量赋值，用 . 语法
    opooc.age = 10;
    // 给指针赋值（这里赋值的是该结构体类型对象的地址）
    opoocP = &opooc;
    // 给所指向结构体变量对象的内部age修改值。对于指针，用 -> 语法
    opoocP->age = 20;
    return 0;
}

// 2、下面两种可以直接用 struct student2 和struct student3声明变量
struct studen2 {
    int age;
};
typedef struct student3 {
    int age;
};
// 3、用struct student{类型 变量名}stu,*stu;在{}后面跟的stu是struct
// student的结构体对象，*stu是指向该种结构对象的指针;
struct teacher {
    int class1;
} teacher1, *teacherP;
void test() {
    // 给对象赋值
    teacher1.class1 = 1;
    // 这里还可以根据结构体类型继续声明结构体对象。
    struct teacher teacher2;
    return;
}
// 4、直接改名
typedef struct {
    int class1;
} stu;
```
[![top] Goto Top](#table-of-contents)

## else if
其实直接if就可以完成的逻辑，但是else可以避免重复检查，提高效率

```cpp
int time = 22;
if (time < 10) {
  cout << "Good morning.";
} else if (time < 20) {
  cout << "Good day.";
} else {
  cout << "Good evening.";
}
// Outputs "Good evening."
```

[![top] Goto Top](#table-of-contents)

## 数组引用和指针引用

[数组引用和指针引用](http://www.codebaoku.com/it-c/it-c-221816.html)
```cpp
int *p [10] = // 指针数组， 这个数组里 可以装 10 个指针变量，
int (*p) [10] = // 数组的指针， 这个指针可以只向一个 容量是10个int 的数组
int (&r) [10] = // 引用， 引用一个 数组。 像这样的数组 int a[10]
```

[![top] Goto Top](#table-of-contents)

## 数组遍历十种方式

```cpp
int ia[3][4] = {1, 2, 3, 4, 5, 6, 7, 8};
// 下标
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
        cout << ia[i][j] << endl;
    }
}
// 指针
for (int (*p)[4] = ia; p != ia + 3; p++) {
    for (int *q = *p; q != *p + 4; q++) {
        cout << *q << endl;
    }
}
// 指针，迭代
for (int (*p)[4] = begin(ia); p != end(ia); p++) {
    for (int *q = begin(*p); q != end(*p); q++) {
        cout << *q << endl;
    }
}
// 范围for
for (int (&p)[4] : ia) {
    for (int q : p) {
        cout << q << endl;
    }
}
typedef int int_array[4];
// 类别名+指针
for (int_array *p = ia; p != ia + 3; p++) {
    for (int *q = *p; q != *p + 4; q++) {
        cout << *q << endl;
    }
}
// 类别名+迭代
for (int_array *p = begin(ia); p != end(ia); p++) {
    for (int *q = begin(*p); q != end(*p); q++) {
        cout << *q << endl;
    }
}
// 类别名+范围for
for (int_array &p : ia) {
    for (int q : p) {
        cout << q << endl;
    }
}
// auto
for (auto p = ia; p != ia + 3; p++) {
    for (auto q = *p; q != *p + 4; q++) {
        cout << *q << endl;
    }
}
// auto+迭代
for (auto p = begin(ia); p != end(ia); p++) {
    for (auto q = begin(*p); q != end(*p); q++) {
        cout << *q << endl;
    }
}
// auto+范围for
for (auto &p : ia) {
    for (auto q : p) {
        cout << q << endl;
    }
}
```

另：作为形参时`int str[]`=`int *str`

[![top] Goto Top](#table-of-contents)

## char 转换为std::string的 10 种方法

1. 使用 std::string 构造函数

一个简单的解决方案是使用字符串类填充构造函数 string (size_t n, char c); 
```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用字符串类填充构造函数
 
    std::string s(1, c);
    std::cout << s << std::endl;
 
    return 0;
}
```
2. 使用 std::stringstream 功能

另一个不错的选择是使用字符串流在字符串和其他数字类型之间进行转换。这个想法是将给定字符插入到流中，然后将其缓冲区的内容写入 `std::string`.
```cpp
#include <iostream>
#include <string>
#include <sstream>
 
int main()
{
    char c = 'A';
 
    // 使用字符串流
 
    std::string s;
    std::stringstream ss;
    ss << c;
    ss >> s;                // 或者，使用 `s = ss.str()`
    std::cout << s << std::endl;
 
    return 0;
}
```
3. 使用 std::string::push_back 功能

另一种常用的解决方案是使用 `push_back()` 函数，它为 `chars` 重载，并将一个字符附加到字符串的末尾。
```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用 string::push_back
 
    std::string s;
    s.push_back(c);
    std::cout << s << std::endl;
 
    return 0;
}
```
4. 使用 std::string::operator+=

`string& operator+= (char c);`

字符串 `+=operator` 对字符重载。我们可以使用它在字符串末尾追加一个字符，如下所示：
```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用 `std::string::operator+=`
 
    std::string s;
    s += c;
    std::cout << s << std::endl;
 
    return 0;
}
```
5. 使用 std::string::operator=
`string& operator= (char c);`

类似于 `+=operator`， 这 `=operator` 对于字符也是重载的。我们可以使用它用单个字符替换字符串的内容。
```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用 `std::string::operator=`
 
    std::string s;
    s = c;
    std::cout << s << std::endl;
 
    return 0;
}
```

6.使用 std::string::append 功能

`string& append (size_t n, char c);`

`append()`函数将追加 `char c` 的 `n` 个拷贝到`string`的末尾

```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用 `std::string::append`
 
    std::string s;
    s.append(1, c);
    std::cout << s << std::endl;
 
    return 0;
}
```
7.使用 std::string::assign 功能

`string& assign (size_t n, char c);`

`assgin()`函数将使用 `char c` 的 `n` 个拷贝来替换`string`当前的值
```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用 `std::string::assign`
 
    std::string s;
    s.assign(1, c);
    std::cout << s << std::endl;
 
    return 0;
}
```
8. 使用 std::string::insert 功能
`insert()`函数将 `char c` 的 `n` 个拷贝插在位置 `pos` 处

`string& insert (size_t pos, size_t n, char c);`

```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用 `std::string::insert`
 
    std::string s;
    s.insert(0, 1, c);
    std::cout << s << std::endl;
 
    return 0;
}
```
关于此方法的更普遍用途，见下例：
```cpp
    char c = 'A';
    std::string s = "abc";
    s.insert(1, 3, c);   // aAAAbc 
```

9.使用 std::string::replace 功能

`string& replace (size_t pos, size_t len, size_t n, char c);`

`replace()`函数将 `string s` 在位置 `pos` 处开始的 `len` 个字符替换为 `char c` 的` n` 个拷贝

```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 使用`std::string::replace`
 
    std::string s;
    s.replace(0, 1, 1, c);
    std::cout << s << std::endl;
 
    return 0;
}
```
关于此方法的更普遍用途，见下例：
```cpp
    char c = 'A';
    std::string s = "abcdef";
    s.replace(1, 2, 3, c);  // aAAAdef 
```
10. 将 char 转换为 C 字符串
最后，我们还可以将 char 转换为 C 字符串，然后将 C 字符串转换为 `std::string` 使用填充构造函数或 `std::string::append` 或者 `std::string::assign`.
```cpp
#include <iostream>
#include <string>
 
int main()
{
    char c = 'A';
 
    // 将 char 转换为 C 字符串
    const char* str = &c;
 
    // 使用 `std::string` 填充构造函数
    std::string s(str, 1);
    std::cout << s << std::endl;
 
    // 使用 `std::string::append`
    std::string S;
    S.append(str, 1);
    std::cout << S << std::endl;
 
    // 使用 `std::string::assign`
    S.assign(str, 1);
    std::cout << S << std::endl;
 
    return 0;
}
```

[![top] Goto Top](#table-of-contents)





## C++获取项目路径的两种方式
在某些特定的条件运行时不能使用局部地址，例如ci流程等，这就要求读取文件时必需使用全局地址，但是在项目路径不定的情况下很难知道某个文件的全局地址，目前存在两种获取项目路径的方式，其中一种更适用于ci流程。

### 一、Cmake传参：适用于简单场景
在Cmake中，很容易知道项目的地址，例如

`${PROJECT_SOURCE_DIR}`

可以在cmakelists中，将该值赋值给变量，例如MAIN_PATH：

`set(MAIN_PATH ${PROJECT_SOURCE_DIR})`

然后新建xxx.h.in文件，仅需一行即可利用宏捕获MAIN_PATH:

`#define PROJECT_PATH "@MAIN_PATH@"`

在cmakelists中将xxx.h.in编译成xxx.h：

`configure_file(src/param_deliver.h.in ../src/param_deliver.h)`

编译完成后即可生成对应的xxx.h：

`#define PROJECT_PATH "/home/type/mcamera/mcamera"`

然后调用该宏即可获得项目地址。

### 二、从环境变量读取：适合脚本场景
C++中自带函数`getenv`，可以读取指定的环境变量，返回`char *`。详见`std::getenv - cppreference.com`。

因此，可以在bash中将当前项目地址设置为指定的环境变量，例如

`export resource_path=${PWD}`

注意，是`${PWD}`而不是`${pwd}`。

然后在c++代码直接读取即可：

`char *path = getenv("resource_path");`

不存在则为空。

组合实例代码：

首先读取环境变量，如果不存在则从Cmake里读取:
```cpp
std::string getResourcePath() {
  char *path = getenv("RESOURCE_DIR");
  if (path != nullptr) {
      LOG("find path in ENV:%s", path);
      return path;
  }
  // not find in ENV
  std::string project_path = PROJECT_PATH;
  std::string resource_path = project_path + "/test/resource/";
  LOG("find path in CMake:%s", resource_path.c_str());
  return resource_path;
}
```
## 空指针异常

[微软给出的异常](https://learn.microsoft.com/en-us/visualstudio/debugger/how-can-i-debug-an-access-violation-q?view=vs-2022)

```cpp
#include <iostream>
using namespace std;

class ClassC {
   public:
    void printHello() {
        cout << "hello world";
    }
};

class ClassB {
   public:
    ClassC* C;
    ClassB() {
        C = new ClassC();
    }
};

class ClassA {
   public:
    ClassB* B;
    ClassA() {
        // Uncomment to fix
        // B = new ClassB();
    }
};

int main() {
    ClassA* A = new ClassA();
    A->B->C->printHello();

}
```

[![top] Goto Top](#table-of-contents)

[top]: up.png

[top]: https://upload.nhyilin.cn/2021-11-19-up.png