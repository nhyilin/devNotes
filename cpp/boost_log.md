## CMakeLists

```cmake
cmake_minimum_required(VERSION 3.23)
project(BOOSTlog)

set(CMAKE_CXX_STANDARD 23)

set(BOOST_ROOT /Users/peiyilin/env/boost_1_80_0)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost COMPONENTS log thread date_time filesystem REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(${PROJECT_NAME} main.cpp InitLog.cpp InitLog.h ParseINI.cpp ParseINI.h)
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
endif()
```

1. `set(Boost_NO_SYSTEM_PATHS ON)`是为了设置自定义路径而非默认的盘

2. `-DBoost_DEBUG=ON`当cmake找不到boost时可设置编译选项，对应写在cmakelists中是`set(Boost_DEBUG ON)`

## 宽字符

现代操作系统中将代码文件和生成文件都指定为`utf-8`即可，尽量不要去折腾宽字符和窄字符。

## 链接错误：error LNK2019

编译完成后在项目中使用时，demo中正常但是在项目中直接调用boost可能会造成[链接错误](https://blog.csdn.net/caimouse/article/details/124680165)，在csdn中是个付费问题，都是搞技术的，何必相互为难呢。

我尝试了几乎所有我能想到的方法，包括用官方对应版本的二进制文件安装，然后制定include路径和lib路径。重新编译所有lib，都无效。

其实最好的办法是查阅[boost官方文档](https://www.boost.org/doc/libs/1_80_0/libs/log/doc/html/index.html)。

1. 下载源码
2. 编译选项添加该关键字：`define=_WIN32_WINNT=0x0A00`
3. Enjoy boost!

我是阅读了文档的[How to read the documentation](https://www.boost.org/doc/libs/1_80_0/libs/log/doc/html/log/how_to_read.html)章节的[Configuring and building the library](https://www.boost.org/doc/libs/1_80_0/libs/log/doc/html/log/installation/config.html)小节得到答案的，BOOST_USE_WINAPI_VERSION接口中的[`_WIN32_WINNT`](https://msdn.microsoft.com/en-us/library/6sehtctf.aspx)查找对应参数即可。



源码见[GitHub](https://github.com/nhyilin/devNotes/tree/main/code/cpp/BOOSTlog)

# 报错记录
若是提示找不到boost，则一定要确认boost文件夹下文件结构组织，因为lib文件夹内cmake文件夹内的cmakelists写定了各个头文件以及lib的相对路径关系