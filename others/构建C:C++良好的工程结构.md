C++20通过了一项非常重要的特性：提供import机制。使用import来引用某个导出的库，而不是基于源代码展开的#include来引用头文件，有助于写出更直观的代码，减少编译时间。都9102年了，要知道在很多年前，C#，Java就支持了这个特性，如C#，以Assembly(程序集)的形式来管理模块，而C语言，C++，从诞生开始到现在仍然在用最原始的#include，真是让人头大。

那么，我就来稍微总结一下（我自认为的）良好的C/C++的工程代码结构应该是什么样子。在新建一个新工程的时候，我们可以以这个为模板，快速构建一个工程。

<!--more-->

# 一、工程的目录结构

一个良好结构的代码，一般会有以下几个部分：

- 构建系统：如CMakeLists.txt或者makefile脚本
- 自述文件：里面有说明和协议(License)
- 源代码：如果这个工程是开源的，那么它会有它的源代码。很多开源工程源代码放在了src文件夹
- 静态链接库：作者可能已经为你编好了静态库。很多工程静态链接库放在了lib文件夹中。
- 二进制文件：作者可能为你生成好了二进制文件，比如Windows下它里面包含dll和lib。很多工程二进制文件放在了bin文件夹。
- 头文件：基本上所有的开源库都会提供头文件。C/C++毕竟不像C#那样方便，你要知道类和函数的声明才可以正确使用它。
[以freetype某个版本为例](https://gitlab.freedesktop.org/freetype/freetype)

freetype可以说是一个很典型的结构了。builds里面为各种平台提供了构建环境，比如它生成了vs2010，vs2008等IDE的sln。它也提供Makefile和CMakeLists.txt，能够方便构建出它的编译环境。src里面是freetype的源代码，include里面是src所引用的头文件。根目录上的README则是自述文件，告诉使用者如何使用库，以及要注意的方面。

freetype需要使用者自己编译，因此它没有提供lib或者dll，或者是.so这样的文件。不过这并不影响什么，因为它已经考虑到了足够多，使用者应该可以轻轻松松编出包来。

# 二、解决方案的结构

开源库的作者应该充分考虑到使用者环境的多样性，比如，使用者可能不是在Windows平台，可能用的是GCC等。所以我们需要为各种环境来生成工程的解决方案。所以现在很多工程都会使用CMake，就是因为CMake是跨平台的，写好一份CMake脚本，就可以在各个平台上生成解决方案。

开发者应该给使用者至少提供动态链接库的版本和静态链接的版本。例如，在渲染引擎GameMachine中，为每一个库工程都生成了静态和动态版本，它们在Windows下分别生成lib文件和dll+lib文件。[顺便贴上这个库的地址](https://github.com/Froser/gamemachine)


静态库和动态库的区别在于，静态库是不需要导出函数的，它直接被编译进生成的二进制文件中，而动态库需要导出函数，以便自己的工程能在dll中找到某函数的偏移地址。从编译选项的角度来说，动态库往往比静态库多一个宏，表明自己是个动态库。例如上面的GameMachine，如果是个动态库，我就给它增加了个GM_DLL预处理宏。具体的原因我稍后再说。

# 三、工程的代码结构

1. 区分公开部分和非公开部分

我个人认为，一个良好的工程应该区分公开部分和非公开部分。公开和非公开是针对文件，而不是C++层面的public和private限定符。简单来说就是，我应该把别人要用的头文件放到include文件夹，并且如果依赖了其它库，且这个库位于自己的代码仓库，那么自己的源代码路径的头文件尽量不要用#include <>形式引用其它库（个人建议）。

举个例子，假设我有个工程A，它依赖了工程B，并且把工程B的include文件夹设置为了自己的include directory。

```tree
A --
   |--src
       |--A.h
       |--A.cpp

B --
   |--include
       |--B.h
```
并且A.h里面直接引用了B.h：
```cpp
#pragma once
#include <B.h>
```
上面的代码在结构上有一些瑕疵。假如使用者C想要使用工程A，那么他首先需要include A.h。但是A工程里面并没有include文件夹，C迫不得已只能将src设置为自己的include文件夹。如果src文件夹里面有很多文件和C的头文件重名，那么代码会造成混乱，所以首先应该在A工程加个include文件夹，并且新建个A.h：
```cpp
A --
   |--src
       |--A.h
       |--A.cpp
   |--include
       |--A.h

B --
   |--include
       |--B.h
```
include中A.h的代码非常简单，转而引用真正的A.h：

`#include "../src/A.h"`

这样，使用者C只需要把A的include文件夹设置为include directory，便可以使用A库所提供的功能了，避免了头文件的混乱。

下面来说一下另外一个问题。由于之前的假设是A和B在一个仓库，而A是通过设置B的include directory来引用B的头文件：
```cpp
#pragma once
#include <B.h>
```
这意味着使用者C也必须将B的include也设置成自己工程的include directory，否则当编译器遇到#include <B.h>时，它只会尝试查找A/include/B.h，然后发现并不存在这个文件，抛出一个抱怨。

这种情况下，A中的src的A.h，应该以相对路径的方式来引用B.h，将它改为：
```cpp
#pragma once
#include "../../B/include/B.h"
```
当然，这么改可能对于库作者来说是难看了点，但是减少了使用者出错的概率。

当然，还有其它很多种方法可以来解决这样的开发者工程属性和使用者工程属性不一致而导致的问题，比如开发者可以写一个CMake宏，来自动帮使用者生成一个解决方案，并且设置正确的include directory。

2. 头文件的依赖一定要写清楚

什么意思呢？还是假设有一个工程A：

```cpp
A --
   |--src
       |--A.h
       |--A.cpp
       |--B.h
   |--include
       |--A.h
       |--B.h
```
其中include中的A.h和B.h分别引入了src里面的A.h和B.h。其中B.h依赖了A.h，但是它又没有#include <A.h>：
```cpp
// B.h
#progma once
inline void B_doSomething()
{
  A a;
  a.doSomething();
}
```
然后库作者写出了这样的代码：
```cpp
#pragma once
#include <A.h>
#include <B.h>
inline void foo()
{
  B_doSomething();
}
```
这段代码对于库的开发者来说不会报错，因为虽然B.h没有include A.h，但是在include B.h之前，A.h已经被引入。但是对于使用者来说，就可能会很有些问题。他可能并不知道B.h是要依赖A.h的，假如他写了下面这样的代码：
```cpp
#pragma once
#include <B.h>
inline void foo()
{
  B_doSomething();
}
```
直接报错！因为B_doSomething里面用到了A，但是B.h并没有include A.h。并且编译器的错误会非常含糊，会说找不到A这个类型，然后使用者一脸蒙蔽，他并不知道还需要哪个头文件！修正的方法就是修改B.h的头文件，让它include A.h：
```cpp
// B.h
#progma once
#include <A.h>
inline void B_doSomething()
{
  A a;
  a.doSomething();
}
```
PS: 有些头文件，比如freetype或者windows的一些头文件，会检查某个头文件是否被include，否则会通过#error抛出个错误提醒用户引入。

3. 区分导出和非导出函数

当我们写一个动态库时，我们要设置函数的可见性，把需要公开的函数表明为可见函数，也就是导出函数。我们编写静态库时，则不能设置它可见性，因为它是二进制输出文件的一部分。

由于我们用到的是同一份头文件，因此最好的方法就是用宏来区分这个头文件是给谁用的。一般来说有2个群体，每个群体2种输出类型：

- 这个头文件给库开发者用，静态库
- 这个头文件给库开发者用，动态库
- 这个头文件给库使用者用，静态库
- 这个头文件给库使用者用，动态库


我们分别用2个宏，第一个宏用来区分是开发者还是使用者，第二个宏来区分是静态库还是动态库。

[以GameMachine为例：](https://github.com/Froser/gamemachine)

gamemachine和gamemachine_static分别是dll和lib库（开发者），gamemachinedemo和gamemachinedemo_dll分别是用了gamemachine和gamemachine_static的exe程序（使用者）。

gamemachine工程定义了GM_DLL宏，表示它是一个dll工程。gamemachinedemo定义了GM_USE_DLL宏，表示它用到的是gamemachine的动态库工程。
```cpp
#ifndef GM_DECL_EXPORT
#	ifdef GM_WINDOWS
#		define GM_DECL_EXPORT __declspec(dllexport)
#	elif GM_GCC
#		define GM_DECL_EXPORT __attribute__((visibility("default")))
#	endif
#	ifndef GM_DECL_EXPORT
#		define GM_DECL_EXPORT
#	endif
#endif
#ifndef GM_DECL_IMPORT
#	if GM_WINDOWS
#		define GM_DECL_IMPORT __declspec(dllimport)
#	else
#		define GM_DECL_IMPORT
#	endif
#endif

#ifdef GM_DLL
#	ifndef GM_EXPORT
#		define GM_EXPORT GM_DECL_EXPORT
#	endif
#else
#	if GM_USE_DLL
#		ifndef GM_EXPORT
#			define GM_EXPORT GM_DECL_IMPORT
#		endif
#	else
#		ifndef GM_EXPORT
#			define GM_EXPORT
#		endif
#	endif
#endif
```

以上是GameMachine用来区分导入、导出函数的宏。以VS为例，GM_DECL_EXPORT表示__declspec(dllexport)，GM_DECL_IMPORT表示__declspec(dllimport)。

那么：

1. gamemachine的GM_EXPORT将展开为__declspec(dllexport)

2. gamemachine的GM_EXPORT将展开为空

3. gamemachinedemo的GM_EXPORT将展开为空

4. gamemachinedemo_dll的GM_EXPORT将展开为__declspec(dllimport)

就这样，通过GM_EXPORT宏，巧妙将类和函数导出了。
```cpp
class GM_EXPORT GameMachine
{
};
```
这是一种非常常见的手法，遍布各种库，它可以作为一个模板，应用到各个C/C++工程中去。


以上便是我对于良好的工程结构的一些理解，欢迎大家补充和讨论。

里面说的很多手法，主要还是要结合实际，实践才是检验真理的唯一标准。


