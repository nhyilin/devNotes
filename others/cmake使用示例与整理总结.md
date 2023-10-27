cmake使用示例与整理总结

# Table of Contents
- [Table of Contents](#table-of-contents)
- [`cmake`中一些预定义变量](#cmake中一些预定义变量)
  - [系统信息](#系统信息)
  - [开关选项](#开关选项)
- [cmake常用命令](#cmake常用命令)
  - [基本语法规则](#基本语法规则)
  - [部分常用命令列表](#部分常用命令列表)
- [cmake中如何生成动态库和静态库](#cmake中如何生成动态库和静态库)
- [cmake中如何使用动态库和静态库（查找库的路径）](#cmake中如何使用动态库和静态库查找库的路径)
- [cmake中如何指定生成文件的输出路径](#cmake中如何指定生成文件的输出路径)
- [cmake中如何增加编译选项](#cmake中如何增加编译选项)
- [cmake设置关闭编译警告](#cmake设置关闭编译警告)
- [有待整理部分](#有待整理部分)
  - [cmake获取项目路径](#cmake获取项目路径)
  - [cmake网络资料](#cmake网络资料)


# `cmake`中一些预定义变量
- `PROJECT_SOURCE_DIR`：工程的根目录
- `PROJECT_BINARY_DIR`：运行cmake命令的目录,通常是`${PROJECT_SOURCE_DIR}/build`
- `CMAKE_INCLUDE_PATH`：环境变量,非`cmake`变量
`CMAKE_LIBRARY_PATH`：环境变量
- `CMAKE_CURRENT_SOURCE_DIR`：当前处理的`CMakeLists.txt`所在的路径
- `CMAKE_CURRENT_BINARY_DIR`：`target`编译目录。使用`ADD_SURDIRECTORY(src bin)`可以更改此变量的值。`SET(EXECUTABLE_OUTPUT_PATH <新路径>)`并不会对此变量有影响,只是改变了最终目标文件的存储路径
- `CMAKE_CURRENT_LIST_FILE`：输出调用这个变量的`CMakeLists.txt`的完整路径
- `CMAKE_CURRENT_LIST_LINE`：输出这个变量所在的行
- `CMAKE_MODULE_PATH`：定义自己的`cmake`模块所在的路径。`SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)`,然后可以用`INCLUDE`命令来调用自己的模块。
- `EXECUTABLE_OUTPUT_PATH` 重新定义目标二进制可执行文件的存放位置
- `LIBRARY_OUTPUT_PATH`：重新定义目标链接库文件的存放位置
- `PROJECT_NAME`：返回通过`PROJECT`指令定义的项目名称
- `CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS`：用来控制`IF ELSE`语句的书写方式

## 系统信息

- `CMAKE_MAJOR_VERSION`：`cmake`主版本号,如`2.8.6`中的`2`
- `CMAKE_MINOR_VERSION`：`cmake`次版本号,如`2.8.6`中的`8`
- `CMAKE_PATCH_VERSION`：`cmake`补丁等级,如`2.8.6`中的`6`
- `CMAKE_SYSTEM`：系统名称,例如`Linux-2.6.22`
- `CAMKE_SYSTEM_NAME`：不包含版本的系统名,如Linux
- `CMAKE_SYSTEM_VERSION`：系统版本,如`2.6.22`
- `CMAKE_SYSTEM_PROCESSOR`：处理器名称,如`i686`
- `UNIX`：在所有的类`UNIX`平台为`TRUE`,包括`OS X`和`cygwin`
- `WIN32`：在所有的`win32`平台为`TRUE`,包括`cygwin`

## 开关选项

- `BUILD_SHARED_LIBS` 控制默认的库编译方式。如果未进行设置,使用`ADD_LIBRARY`时又没有指定库类型,默认编译生成的库都是静态库 （可在t3中稍加修改进行验证）
- `CMAKE_C_FLAGS` 设置`C`编译选项
- `CMAKE_CXX_FLAGS` 设置`C++`编译选项

[![top] Goto Top](#table-of-contents)

# cmake常用命令

## 基本语法规则
- `cmake`变量使用`${}`方式取值,但是在`IF`控制语句中是直接使用变量名
- 环境变量使用`$ENV{}`方式取值,使用`SET(ENV{VAR} VALUE)`赋值
- `指令(参数1 参数2…)`
    参数使用括弧括起,参数之间使用空格或分号分开。
```cmake
以ADD_EXECUTABLE指令为例：
ADD_EXECUTABLE(hello main.c func.c)或者
ADD_EXECUTABLE(hello main.c;func.c)
```
- 指令是大小写无关的,参数和变量是大小写相关的。推荐你全部使用大写指令。

## 部分常用命令列表
- `PROJECT`
  - `PROJECT(projectname [CXX] [C] [Java])`指定工程名称,并可指定工程支持的语言。支持语言列表可忽略,默认支持所有语言
- `SET`
    - `SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])`：定义变量(可以定义多个`VALUE`,如`SET(SRC_LIST main.c util.c reactor.c))`
- `MESSAGE`
    - `MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] “message to display” …)`：向终端输出用户定义的信息或变量的值
    - `SEND_ERROR`, 产生错误,生成过程被跳过
    - `STATUS`, 输出前缀为 `—` 的信息
    - `FATAL_ERROR`, 立即终止所有`cmake`过程
- `ADD_EXECUTABLE`
    - `ADD_EXECUTABLE(bin_file_name ${SRC_LIST})`：生成可执行文件
- `ADD_LIBRARY`
    - `ADD_LIBRARY(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] SRC_LIST)`：生成动态库或静态库
    - `SHARED`：动态库
    - `STATIC`：静态库
    - `MODULE`：在使用`dyld`的系统有效,若不支持`dyld`,等同于`SHARED`
    - `EXCLUDE_FROM_ALL`：表示该库不会被默认构建
- `SET_TARGET_PROPERTIES`
    - 设置输出的名称,设置动态库的版本和API版本
- `CMAKE_MINIMUM_REQUIRED`
    - `CMAKE_MINIMUM_REQUIRED(VERSION version_number [FATAL_ERROR])`：声明CMake的版本要求
- `ADD_SUBDIRECTORY`
    - `ADD_SUBDIRECTORY(src_dir [binary_dir] [EXCLUDE_FROM_ALL])`：向当前工程添加存放源文件的子目录,并可以指定中间二进制和目标二进制的存放位置
    - `EXCLUDE_FROM_ALL`含义：将这个目录从编译过程中排除
- `SUBDIRS`
    - `deprecated`,不再推荐使用
    - `(hello sample)`相当于分别写`ADD_SUBDIRECTORY(hello),ADD_SUBDIRECTORY(sample)`
- `INCLUDE_DIRECTORIES`
    - `INCLUDE_DIRECTORIES([AFTER | BEFORE] [SYSTEM] dir1 dir2 … )`：向工程添加多个特定的头文件搜索路径,路径之间用空格分隔,如果路径包含空格,可以使用双引号将它括起来,默认的行为为追加到当前头文件搜索路径的后面。有如下两种方式可以控制搜索路径添加的位置：
      - CMAKE_INCLUDE_DIRECTORIES_BEFORE,通过SET这个cmake变量为on,可以将添加的头文件搜索路径放在已有路径的前面
      - 通过AFTER或BEFORE参数,也可以控制是追加还是置前
- `LINK_DIRECTORIES`
    - `LINK_DIRECTORIES(dir1 dir2 …)`：添加非标准的共享库搜索路径
- `TARGET_LINK_LIBRARIES`
    - `TARGET_LINK_LIBRARIES(target lib1 lib2 …)`：为target添加需要链接的共享库
- `ADD_DEFINITIONS`
    - 向`C/C++`编译器添加`-D`定义
    - `ADD_DEFINITIONS(-DENABLE_DEBUG -DABC)`,参数之间用空格分隔
- `ADD_DEPENDENCIES`
    - `ADD_DEPENDENCIES(target-name depend-target1 depend-target2 …)`：定义`target`依赖的其他`target`,确保`target`在构建之前,其依赖的`target`已经构建完毕
- `AUX_SOURCE_DIRECTORY`
    - `AUX_SOURCE_DIRECTORY(dir VAR)`：发现一个目录下所有的源代码文件并将列表存储在一个变量中,把当前目录下的所有源码文件名赋给变量`DIR_HELLO_SRCS`
- `EXEC_PROGRAM`
    - `EXEC_PROGRAM(Executable [dir where to run] [ARGS <args>][OUTPUT_VARIABLE <var>] [RETURN_VALUE <value>])`：用于在指定目录运行某个程序（默认为当前`CMakeLists.txt`所在目录）,通过`ARGS`添加参数,通过`OUTPUT_VARIABLE`和`RETURN_VALUE`获取输出和返回值,如下示例
    ```cmake
    # 在src中运行ls命令,在src/CMakeLists.txt添加
    EXEC_PROGRAM(ls ARGS "*.c" OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
    IF (not LS_RVALUE)
        MESSAGE(STATUS "ls result: " ${LS_OUTPUT}) # 缩进仅为美观,语法无要求
    ENDIF(not LS_RVALUE)
    ```
- `INCLUDE`
    - `INCLUDE(file [OPTIONAL])`：用来载入`CMakeLists.txt`文件
    - `INCLUDE(module [OPTIONAL])`：用来载入预定义的`cmake`模块
    - `OPTIONAL`参数的左右是文件不存在也不会产生错误
    - 可以载入一个文件,也可以载入预定义模块（模块会在`CMAKE_MODULE_PATH`指定的路径进行搜索）,载入的内容将在处理到`INCLUDE`语句时直接执行

- `FIND_`
    - `FIND_FILE(<VAR> name path1 path2 …)`：`VAR`变量代表找到的文件全路径,包含文件名
    - `FIND_LIBRARY(<VAR> name path1 path2 …)`：`VAR`变量代表找到的库全路径,包含库文件名
    ```cmake
    FIND_LIBRARY(libX X11 /usr/lib)
    IF (NOT libx)
        MESSAGE(FATAL_ERROR "libX not found")
    ENDIF(NOT libX)
    ```
  - `FIND_PATH(<VAR> name path1 path2 …)`：`VAR`变量代表包含这个文件的路径
  - `FIND_PROGRAM(<VAR> name path1 path2 …)`：`VAR`变量代表包含这个程序的全路径
  - `FIND_PACKAGE(<name> [major.minor] [QUIET] [NO_MODULE] [[REQUIRED | COMPONENTS] [componets …]])`：用来调用预定义在`CMAKE_MODULE_PATH`下的`Find<name>cmake`模块,你也可以自己定义`Find<name>`模块,通过`SET(CMAKE_MODULE_PATH dir)`将其放入工程的某个目录供工程使用
- IF
语法：
```cmake
IF (expression)
    COMMAND1(ARGS ...)
    COMMAND2(ARGS ...)
    ...
ELSE (expression)
    COMMAND1(ARGS ...)
    COMMAND2(ARGS ...)
    ...
ENDIF (expression) # 一定要有ENDIF与IF对应
```
`IF(expression)`,` expression`不为：`空,0,N,NO,OFF,FALSE,NOTFOUND或<var>_NOTFOUND`,为真

`IF(not exp)`, 与上面相反

`IF(var1 AND var2)`

`IF(var1 OR var2)`

`IF(COMMAND cmd)`如果`cmd`确实是命令并可调用,为真

`IF(EXISTS dir) IF (EXISTS file)`如果目录或文件存在,为真

`IF(file1 IS_NEWER_THAN file2)`,当`file1`比`file2`新,或`file1/file2`中有一个不存在时为真,文件名需使用全路径

`IF(IS_DIRECTORY dir)`当`dir`是目录时,为真

`IF(DEFINED var)` 如果变量被定义,为真

`IF(var MATCHES regex)`此处`var`可以用`var`名,也可以用`${var}`

`IF(string MATCHES regex)`

```cmake
当给定的变量或者字符串能够匹配正则表达式regex时为真。比如：
IF ("hello" MATCHES "ell")
    MESSAGE("true")
ENDIF ("hello" MATCHES "ell")
```
- `file`：[获取指定目录下的所有符合条件的文件名列表](https://blog.csdn.net/qq_31261509/article/details/88692736)

    下面语句将会把`./src`目录下所有符合`*.cpp`结尾的文件存入`USER_LIBS_PATH`变量中，
    
    `file(GLOB USER_LIBS_PATH ./src/*.cpp)`
    
    如果我们不但在当前目录需要引入，还需要在当前目录子目录引入了，这里就直接使用GLOB_RECURSE
    
    `file(GLOB_RECURSE USER_LIBS_PATH ./src/*.cpp)`


**数字比较表达式**

`IF(variable LESS number)`
`IF(string LESS number)`
`IF(variable GREATER number)`
`IF(string GREATER number)`
`IF(variable EQUAL number)`
`IF(string EQUAL number)`

**按照字母表顺序进行比较**

`IF(variable STRLESS string)`
`IF(string STRLESS string)`
`IF(variable STRGREATER string)`
`IF(string STRGREATER string)`
`IF(variable STREQUAL string)`
`IF(string STREQUAL string)`

```cmake
一个小例子,用来判断平台差异：
IF (WIN32)
    MESSAGE(STATUS “This is windows.”)
ELSE (WIN32)
    MESSAGE(STATUS “This is not windows”)
ENDIF (WIN32)
上述代码用来控制在不同的平台进行不同的控制,但是,阅读起来却并不是那么舒服,ELSE(WIN32)之类的语句很容易引起歧义。
可以SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
这时候就可以写成:
IF (WIN32)
ELSE ()
ENDIF ()
配合ELSEIF使用,可能的写法是这样:
IF (WIN32)
    #do something related to WIN32
ELSEIF (UNIX)
    #do something related to UNIX
ELSEIF(APPLE)
    #do something related to APPLE
ENDIF (WIN32)
```

- WHILE
语法：
```cmake
WHILE(condition)
    COMMAND1(ARGS ...)
    COMMAND2(ARGS ...)
    ...
ENDWHILE(condition)
```
其真假判断条件可以参考IF指令

- FOREACH
    FOREACH指令的使用方法有三种形式：
    1. 列表
        语法：
          ```cmake
          FOREACH(loop_var arg1 arg2 ...)
               COMMAND1(ARGS ...)
               COMMAND2(ARGS ...)
           ...
          ENDFOREACH(loop_var)
          ```
        示例：
          ```cmake
          AUX_SOURCE_DIRECTORY(. SRC_LIST)
          FOREACH(F ${SRC_LIST})
               MESSAGE(${F})
          ENDFOREACH(F)
          ```
    2. 范围
        语法：
          ```cmake
          FOREACH(loop_var RANGE total)
              COMMAND1(ARGS ...)
              COMMAND2(ARGS ...)
              ...
          ENDFOREACH(loop_var)
          ```
        示例：
          ```cmake
          从0到total以１为步进
          FOREACH(VAR RANGE 10)
             MESSAGE(${VAR})
          ENDFOREACH(VAR)
          输出：
          012345678910
          ```
    3. 范围和步进
        语法：
          ```cmake
          FOREACH(loop_var RANGE start stop [step])
              COMMAND1(ARGS ...)
              COMMAND2(ARGS ...)
              ...
          ENDFOREACH(loop_var)
          ```
       从start开始到stop结束,以step为步进,
       **注意：**直到遇到ENDFOREACH指令,整个语句块才会得到真正的执行。
          ```cmake
          FOREACH(A RANGE 5 15 3)
              MESSAGE(${A})
          ENDFOREACH(A)
          输出：
          581114
          ```

[![top] Goto Top](#table-of-contents)

# cmake中如何生成动态库和静态库
参考`ADD_LIBRARY`和`SET_TARGET_PROPERTIES`用法
t3示例

[![top] Goto Top](#table-of-contents)

# cmake中如何使用动态库和静态库（查找库的路径）
参考`INCLUDE_DIRECTORIES`,`LINK_DIRECTORIES`, `TARGET_LINK_LIBRARIES`用法
t4示例使用动态库或静态库
t5示例如何使用`cmake`预定义的`cmake`模块(以`FindCURL.cmake`为例演示)
t6示例如何使用自定义的`cmake`模块(编写了自定义的`FindHELLO.cmake`)
注意读t5和t6的`CMakeLists.txt`和`FindHELLO.cmake`中的注释部分

[![top] Goto Top](#table-of-contents)

# cmake中如何指定生成文件的输出路径
- 如上`ADD_SUBDIRECTORY`的时候指定目标二进制文件输出路径（推荐使用下面这种）
- 使用SET命令重新定义`EXECUTABLE_OUTPUT_PATH`和`LIBRARY_OUTPUT_PATH`变量来指定最终的二进制文件的位置
  ```cmake
  SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
  SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
  ```
    上面的两条命令通常紧跟`ADD_EXECUTABLE`和`ADD_LIBRARY`,与其写在同一个`CMakeLists.txt`即可

[![top] Goto Top](#table-of-contents)

# cmake中如何增加编译选项
使用变量`CMAKE_C_FLAGS`添加`C`编译选项
使用变量`CMAKE_CXX_FLAGS`添加C++编译选项
使用`ADD_DEFINITION`添加

`cmake`中如何增加头文件路径
参考`INCLUDE_DIRECTORIES`命令用法

`cmake`中如何在屏幕上打印信息
参考`MESSAGE`用法

`cmake`中如何给变量赋值
参考`SET`和`AUX_SOURCE_DIRECTORY`用法

建议：在`Project`根目录先建立`build`,然后在`build`文件夹内运行`cmake ..`，这样就不会污染源代码, 如果不想要这些自动生成的文件了，只要简单的删除`build`文件夹就可以

# cmake设置关闭编译警告

虽然关闭编译警告（warning）并不是一个好习惯，但在某些情况下，关闭编译器警告可能是必须的。为了关闭编译器警告，您可以使用 CMake 中的 `add_compile_options()` 命令来添加编译选项。具体而言，您需要在 CMakeLists.txt 文件中添加以下行：

```cmake
add_compile_options(-w)
```

在上述代码中，`-w` 选项将关闭编译器的所有警告。如果您只想关闭特定类型的警告，可以使用以下选项：

- `-Wno-unused-parameter`：关闭未使用的参数警告。
- `-Wno-unused-variable`：关闭未使用的变量警告。
- `-Wno-unused-result`：关闭未使用的函数或操作结果的警告。
- `-Wno-deprecated-declarations`：关闭对已过时的函数或操作的警告。
- `-Wno-format-security`：关闭格式化字符串安全警告。

您可以在 `add_compile_options()` 命令中添加这些选项来关闭特定类型的警告。例如：

```cmake
add_compile_options(-Wno-unused-variable)
```

上述代码将关闭未使用变量警告。

需要注意的是，关闭编译警告可能会隐藏潜在的问题，因此我们建议仅在了解并确认相关警告无关紧要时再关闭它们。



# 有待整理部分

1. 生成可执行文件时，指令为`add_executable(pro_name library.cpp)`，若要生成静态库，则`add_library(pro_name library.cpp)`，动态库：`add_library(pro_name SHARED library.cpp)`
2. 关闭C++11特性
   ```cmake
   add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
   或者
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
   ```
3. CMakeLists.txt生成sln：
    ```bash
    cmake.exe -G "Visual Studio 17 2022" -A x64 -DTHIRDPARTY_ROOT_DIR=D:\myDevelop\ThirdParty -DCMAKE_PREFIX_PATH=C:/Qt/Qt5.9.6/5.9.6/msvc2017_64/lib/cmake -S D:\myDevelop\project\kneev2021\src -B D:\myDevelop\build\kneeV2021
    ```
    如需指定Qt路径(注意最后指定到cmake文件夹)：
    ```bash
    cmake.exe -D CMAKE_PREFIX_PATH=C:Qt/Qt5.10.1/5.10.1/msvc2015_64/lib/cmake -G "Visual Studio 17 2022" -A x64 -DTHIRDPARTY_ROOT_DIR=D:\myDevelop\ThirdParty -DCMAKE_PREFIX_PATH=C:/Qt/Qt5.9.6/5.9.6/msvc2017_64/lib/cmake -S D:\myDevelop\project\kneev2021\src -B D:\myDevelop\build\kneeV2021
    ```
4. 生成Xcode项目：`cmake -G "Xcode" .`，`.`代表当前目录，即CMakeLists.txt所在的目录，建议最好新建Xcode文件夹，并在Xcode文件夹内执行`cmake -G "Xcode" ../`。如果报错找不到编译器，可以使用：`.sudo xcode-select --switch /Applications/Xcode.app/`


## cmake获取项目路径

在Cmake中，很容易知道项目的地址，例如

`${PROJECT_SOURCE_DIR}`

可以在cmakelists中，将该值赋值给变量，例如MAIN_PATH：

`set(MAIN_PATH ${PROJECT_SOURCE_DIR})`

然后新建xxx.h.in文件，仅需一行即可利用宏捕获MAIN_PATH:

`#define PROJECT_PATH "@MAIN_PATH@"`

在cmakelists中将xxx.h.in编译成xxx.h：(注意这里生成头文件的路径，指定在src代码文件夹)

`configure_file(src/param_deliver.h.in ../src/param_deliver.h)`

编译完成后即可生成对应的xxx.h：

`#define PROJECT_PATH "/home/type/mcamera/mcamera"`

然后调用`PROJECT_PATH`即可获得项目地址。

[![top] Goto Top](#table-of-contents)

## cmake网络资料

[How to Build a CMake-Based Project](https://preshing.com/20170511/how-to-build-a-cmake-based-project/)

[![top] Goto Top](#table-of-contents)

[top]: up.png
