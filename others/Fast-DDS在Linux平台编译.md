本文记录Fast DDS在国产芯片及国产系统下的编译，具体情况每个环境有个别差异，酌情参考，另外本文直接在目标机器编译，不涉及交叉编译。


<!--more-->


Fast DDS 是 eProsima 开发的一个高性能、实时的通信中间件，基于 Data Distribution Service (DDS) 标准。它是一种发布/订阅的架构，广泛用于需要高效率、低延迟通讯的系统中，如机器人、自动驾驶、工业自动化以及物联网。


环境如下：  
芯片：            Phytium,D2000/8 E8C  
架构：            aarch64  
CPU 运行模式：     32-bit, 64-bit  
OS版本：          Linux kylin-pc 5.4.18-110-generic

涉及到的第三方库版本如下：asio-1.30.2、Fast-CDR-2.2.5、tinyxml2-v10.0.0、foonathan_memory_vendor-v1.3.1  

以及Fast-DDS-2.10.5


## 第三方库准备

### Fast_CDR

Fast_CDR是做idl序列化和反序列化的核心库，他不依赖任何库。

github下载源码，建议下载[Fast-CDR-2.2.5](https://github.com/eProsima/Fast-CDR)的tag分支。

```cmake
#源码路径
mkdir build
cmake ..  -DCMAKE_INSTALL_PREFIX=/data/DDSDEV/thirdparty/Fast_CDR 
make -j8
make install
```

## TinyXML2

github下载源码，建议下载 [tinyxml2-v10.0.0](https://github.com/leethomason/tinyxml2) 的tag分支。

```cmake
#源码路径
mkdir build
cmake .. -DCMAKE_CXX_FLAGS="-fPIC" -DCMAKE_C_FLAGS="-fPIC" -DCMAKE_INSTALL_PREFIX=/data/DDSDEV/thirdparty/Fast_CDR
make -j8
make install
```

这里需要注意的是，需要加上`-DCMAKE_CXX_FLAGS="-fPIC" -DCMAKE_C_FLAGS="-fPIC"`，主要目的是为了编译生成使用 -fPIC 编译的静态库（libtinyxml2.a），如果未使用该标志位，则链接到生成共享对象（.so）的过程会产生错误。

在 Linux 系统上，用于创建共享库的所有对象文件通常需要使用 -fPIC（Position Independent Code）编译。

如果不用，则编译Fast-DDS时会报错：

```bash
/usr/bin/ld: /data/DDSDEV/thirdparty/tinyxml2/lib/libtinyxml2.a(tinyxml2.cpp.o): relocation R_AARCH64_ADR_PREL_PG_HI21 against symbol `__stack_chk_guard@@GLIBC_2.17' which may bind externally can not be used when making a shared object; recompile with -fPIC

/usr/bin/ld: /data/DDSDEV/thirdparty/tinyxml2/lib/libtinyxml2.a(tinyxml2.cpp.o)(.text+0x4a8): unresolvable R_AARCH64_ADR_PREL_PG_HI21 relocation against symbol `__stack_chk_guard@@GLIBC_2.17'

/usr/bin/ld: 最后的链结失败: bad value

collect2: error: ld returned 1 exit status

make[2]: *** [src/cpp/CMakeFiles/fastdds.dir/build.make:3656：src/cpp/libfastdds.so.3.1.0] 错误 1

make[1]: *** [CMakeFiles/Makefile2:1158：src/cpp/CMakeFiles/fastdds.dir/all] 错误 2
```

当然，也可以使用动态库：

```cmake
-DTINYXML2_LIBRARY=/data/DDSDEV/thirdparty/tinyxml2/lib/libtinyxml2.so
```

### Asio

Asio是一个跨平台的C++库，用于网络和底层I/O编程。Asio库不用编译，直接下载源码，建议下载 [asio-1.30.2](https://sourceforge.net/projects/asio/) 的tag分支。

代码下载后解压到/data/DDSDEV/thirdparty下备用。


### Foonathan_memory

github下载源码，建议下载 [foonathan_memory_vendor-v1.3.1](https://github.com/eProsima/foonathan_memory_vendor.git) tag分支。

```cmake
#源码路径
mkdir build
#关闭所有主功能外的功能
cmake .. -DFOONATHAN_MEMORY_BUILD_EXAMPLES=OFF -DFOONATHAN_MEMORY_BUILD_TESTS=OFF -DFOONATHAN_MEMORY_BUILD_TOOLS=OFF -DCMAKE_INSTALL_PREFIX=/data/DDSDEV/thirdparty/Foonathan_memory
make -j8
make install
```

> 需要注意的是，这个库在cmake过程中，会自动下载[ memory ](https://github.com/foonathan/memory.git)库并执行cmake，离线未测试，联网情况会自动编译

### fastrtps（Fast-DDSs）编译安装

```cmake
cmake -DTHIRDPARTY=ON -DCOMPILE_TOOLS=ON -DCMAKE_PREFIX_PATH=/data/DDSDEV/thirdparty/Fast_CDR -DCMAKE_MODULE_PATH=/data/DDSDEV/thirdparty/Fast_CDR/lib/cmake -DAsio_INCLUDE_DIR=/data/DDSDEV/thirdparty/asio-1.30.2/include -DTINYXML2_INCLUDE_DIR=/data/DDSDEV/thirdparty/tinyxml2/include -DTINYXML2_LIBRARY=/data/DDSDEV/thirdparty/tinyxml2/lib/libtinyxml2.a -DCMAKE_INSTALL_PREFIX=/data/DDSDEV/thirdparty/Fast-DDS ..
```

注意里面的大小写，尤其是Asio，不是ASIO。


编译完成后用自带的demo测试：

```bash
cd /data/DDSDEV/Fast-DDS-2.10.5/examples/cpp/hello_world
mkdir build && cd build
make -j8
./hello_world publisher
```
另起一终端：
```bash
./hello_world subscriber
```
即可看到收发关系。