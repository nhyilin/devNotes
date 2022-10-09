本文记录日常c++中比较零碎的知识点，做整理用。

# Table of Contents
- [Table of Contents](#table-of-contents)
  - [*和&操作符](#和操作符)
  - [指针的指针，以及指针的引用](#指针的指针以及指针的引用)
    - [为什么需要使用它们](#为什么需要使用它们)
    - [使用指针的指针](#使用指针的指针)
    - [指针的引用](#指针的引用)
  - [三元运算符](#三元运算符)
  - [命名空间](#命名空间)
  - [struct和typedef struct](#struct和typedef-struct)

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

[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png