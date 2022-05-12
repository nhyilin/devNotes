银河麒麟及arm64环境下，离线编译osg3.4.0和osgEarth2.9库文件

# 编译
## 一、第三方库
编译前：

1. `osg`和`osgEarth`的关系是，`osg`是一个专门为了三维图像而生的函数库，而`osgEarth`则是在`osg`的基础上，更加集中于构建三维下的地球的一个函数库。

2. `osg`和`osgEarth`的版本选择很重要！两者的版本号是有相关性的，所以一定要注意你所下载的`osg`和`osgEarth`的版本，是否适配。所谓的适配，意思是，在`osgEarth`中会调用到一系列的`osg`的函数，但是这些函数，在最新的osg版本中，可能已经被取消了，或者更名了，都有可能。最新的`osg`是`3.6.5`版本，但是并不适用于所有的`osgEarth`的版本，`osgEarth`我能找到的最新版本是`3.1`，试了一下，`osgEarth3.1`和`osg3.6.4`版本，是无法成功编译的，当然，不能说是不适配，因为在我试的过程中，可能存在别的问题。但我可以肯定的是，`osg3.4.0`和`osgEarth2.8`以及`osgEarth2.9`版本是适配。

3. 注意在切换`osg`版本时，一定要将原版本卸载干净。我在这儿就吃了亏，一开始选用`osg3.6.4`版本，后来更换为`osg3.4.0`版本，当时没清理干净，导致在编译`osgEarth`时，不断报错，提示`xxx:未定义的引用`，当时很奇怪，这函数明明是源代码自带的代码中的函数，为什么一直报未定义的引用，这个报错，意思是在在头文件声明了，但是cpp中，或者说编译后的库文件中，未定义。后来我查到，库文件的链接，即`LINK`不对，指向了`osg3.6.4`版本，就是没删除干净。要删除干净，就需要搞清楚源代码编译究竟生成了什么，放在了哪里。源代码编译的时候，根据个人习惯，一是可以将依赖的库文件编译后放在一个自定义的位置，比如通过再`configure`后追加参数，`./configure --prefix=/home/iscas/`，另一种是放在默认位置，即`/usr/local`下，这个看个人习惯，各有各的好处，放在自定义的位置，方便卸载，放在默认位置，不用考虑环境变量的问题。源代码编译后的结果无非三种文件，一种是头文件，即函数的声明，默认放在`/usr/local/include`下，一种的可执行文件，默认放在`/usr/local/bin`下，一种是库文件，即函数的定义，默认放在`/usr/local/lib`或者`/usr/local/lib64`下。因此，知道了有什么东西，放在哪，卸载的时候，即手动去删除，务必删除干净。

4. 在编译`osg`代码时，需要指定使用`QT5`版本，因为现在大部分`linux`系统下，自带`QT4`和`QT5`，所以需要指定位置。在`CMakeList.txt`文件的`IF(OSG_USE_QT AND NOT ANDROID)`的前一行，添加`SET(DESIRED_QT_VERSION 5)`。

5. 在编译`osgEarth`时，在2.8版本中，如果不指定使用`X11`版本，会报错，因此，需要修改`CMakeList.txt`文件，在首行添加，`add_definitions(-std=gnu++11)`或者`add_definitions(-std=c++11)`。

6. 在`osgEarth`编译时，为生成可供`Qt`使用的库文件，修改`CMakeList.txt`中如下两处，由`OFF`改为`ON`。
```bash
OPTION(OSGEARTH_QT_BUILD "Enable to use Qt (build Qt-dependent libraries, plugins and examples)" ON)
OPTION(OSGEARTH_QT_BUILD_LEGACY_WIDGETS "Build the legacy Qt widgets" ON)
```
7. 将`bin`和`lib`文件夹写入环境变量。编译`osg`和`osgEarth`成功之后，在编译的目录下会出现`lib`和`bin`两个文件夹（inlcude的文件，已经默认放在了`/usr/local/include`下），将这两个单独放置一个妥善位置，建议同`osg`的`DATA`文件放一起，方便管理，而后将`lib`和`bin`的目录所在地址，写入`/etc/profile`，每次修改完这个文件profile后，记得`source /etc/profile`，使其生效。
```bash
export PATH=${PATH}:/home/iscas/osg_install/OpenSceneGraph-build/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/iscas/osg_install/OpenSceneGraph-build/lib
export OSG_FILE_PATH=/home/iscas/osg_install/OpenSceneGraph-Data
```

8. 最好先清理旧版本cmake，安装新版cmake(`cmake-3.23.0-rc5-linux-x86_64.tar.gz`)。
```bash
sudo apt-get remove cmake
sudo rm -rf /usr/local/share/cmake*
sudo rm -rf /usr/local/bin/cmake*
```
9. 编译三方库尤其是freetype之前最好先更新qt，否则该库会对qt安装造成影响，详见第三部分

10. 若是cmake报错或者警告提示某一库未找到，则应当将三方库（或者向前依赖项安装时指定路径，有时候不给默认参数也会造成三方库没有编译在`/usr/local`之中，造成想当然的错误）

11. 恒歌版本源码的问题。在编译恒歌osgearth之前，请确认gdal大版本号为`2.1`，小版本我使用的是`2.14`。源码`ReaderWriterGDAL`文件**2000**行处，papszOptions参数类型应该为`const char**`，将恒歌源码`CPLFetchBool`函数入参`papszOptions`强制转为`(const char**)`即可

12. 我个人将其编译路径设置为：`/home/iscas/osg_install/usr/local`，这样目的是为了没有makefile的第三方库在利用cmakelists生成时，和其他第三方库层次不一的问题，具体见下方install步骤

## 二、库文件依赖的解决
依赖问题始终是最棘手的问题，为了解决依赖问题，可以根据`osg`和`osgEarth`中的`CMakeList`中的提示，可以获悉需要什么依赖，以及该库的版本号。我在解决依赖问题的时候，将所有能下到的依赖库的源代码下了下来，自行编译，其实本人觉得，直接编译源代码会简单一些，源代码的编译方法其实相对比较简单，大致上就是两个方法去编译，一个就是看见源代码目录下，有`configure`文件，就使用`./configure`来编译，生成Makefile文件，第二种方法是看见目录下，有`CMakeList.txt`文件，就使用`cmake CMakeList.txt`去生成Makefile，总之，都是为了生成`Makefile`文件，然后可以进一步`make`，`sudo make install`。

在处理`osg`和`osgEarth`中涉及的依赖时，只编译了部分依赖，其实还有一些依赖未解决，但不影响`osg`和osgEarth编译的成功，不过不解决，会导致后面部分功能无法使用。

网上有一个集成依赖库的，`OSG`配置第三方资源库`3rdparty`，这个仅适用于`windows`平台，不适用于`linux`。

`osg`和`osgEarth`所涉及的依赖的库文件，他们之间也存在一些依赖关系，所以编译的顺序应该较为严格执行。以下顺序仅供参考。

1. 编译 zlib-1.2.8                       			//`sudo ldconfig`
2. 编译 png-1.2.40
3. 编译 curl-7.47.0
4. 编译 freetype-2.4.8                   		//编译前检查qt是否更新的目标版本
5. 编译 gdal（proj-4.9.2->geos-3.5.0->gdal-2.1.14）
6. 编译 jpeg（nasm-2.13.03->libjpeg-turbo-1.2.1）
7. 编译 tiff-3.8.2
8. 编译 minizip                         			//下面为可选项
9. 编译 sqlite
10. 编译 SDL2
11. 编译 libtool
12. 编译 googletest
13. 编译 protobuf                      			 //请参考下面的特殊情况
14. 编译 rocksdb(gflags->rocksdb)      //请参考下面的特殊情况
15. qwt-6.2.0

在上述库文件的编译过程中，大部分只需要简单的编译。
如，有`configure`文件时候，使用
```bash
./configure --prefix=/home/iscas/osg_install/usr/local
make -j8
sudo make install
```
有CMakeList.txt时，使用
```bash
cmake CMakeList.txt
make -j8
sudo make install DESTDIR=/home/iscas/osg_install
```
正如上文所言，这样写为了避免文件夹路径层次不一，当然，如果你事先了解这两种安装的区别，那么可以无视这条建议。

只有下述几个情况比较特殊。

在用`configure`生成`Makefile`文件时，有时候会报错`configure:error: cannot guess build type; you must specify one`，这时候，只需要在`configure`后添加参数，指定编译所用的引擎即可。`./configure --build=arm-linux`。

在编译`gflags`库，默认只生成静态库，而在编译`rocksdb`时候，需要调用`gflags`的动态库，需要动态库才行。解决的方法。在`cmake`生成`Makefile`时，启用动态库。`cmake -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON -DINSTALL_HEADERS=ON -DINSTALL_SHARED_LIBS=ON -DINSTALL_STATIC_LIBS=ON`。

在编译`protobuf`库文件时，需要首先运行`./autogen.sh`而后才会出现`configure`文件。

每编译完一个库文件，建议在命令行输入一次`sudo ldconfig`，更新引用，不然可能会有部分库文件不能马上生效，导致后续相关依赖的库文件编译时报错。

如若在库文件编译时，自定义目录，建议将所有目录统一，方便写入环境变量，写入环境变量，则需要使用`export`，写在`/etc/profile`最后面。

qwt编译：`qmake qwt.pro`(指定好了qmake和qwt文件夹内的pro文件)

## 三、测试是否成功
测试osg，可以在命令行运行`osgviewer cow.osg`是否显示一头牛，或者`osgversion`，看是否显示版本号。

测试`osgEarth`，可以在命令行运行`osgearth_version`，看是否显示版本号。



## 四、乱七八糟的问题

### 4.1显卡安装
1. 打开`/boot/grub/grub.cfg`在`Linux /vmlinuz-4.5.0....quiet splash `所在行最后加上`$vt_handoff nouveau.modeset=0`，并且将驱动文件防止在容易找的位置，如home文件夹内
2. 重启系统，分辨率变模糊
3. 使用`Ctrl+Alt+F2`进入命令行模式，先`sudo su`进入root用户，然后执行`init 3`进入完全多用户
4. `./***.run`命令安装显卡

### 4.2安装cmake时间遇到了系统没有openssl环境

以`./bootstrap -- -DCMAKE_USE_OPENSSL=OFF`方式执行安装脚本，然后执行`sudo make && make install`

> configure CMake with -DCMAKE_USE_OPENSSL=OFF to build without OpenSSL.

1. `c++: internal compiler error: 已杀死 (program cc1plus)Please submit a full bug report,with preprocessed source if appropriate.` 解决方案，提升虚拟机内存空间。


### 4.3报错未发现QtOpenGL

使用高级别版本qt（5.12），避免使用系统自带qt（5.6）。

    1. 下载`qt-opensource-linux-x64-5.12.12.run`文件
    2. chmod +x qt-opensource-linux-x64-5.12.12.run
    3. sudo ./qt-opensource-linux-x64-5.12.12.run


### 4.4安装qt时
> 这个问题可以通过先安装qt或者安装qt时将自己编译的freeetype临时隐藏得到解决，否则请参考下面方法

遇到`symbol lookup error: /home/frank/Qt5.12.2/5.12.2/gcc_64/lib/libQt5XcbQpa.so.5: undefined symbol: FT_Property_Set`类似的问题

> 我遇到的这种情况是因为有两个版本的freeetype导致的。

输入`find /usr -name libfreetype*`出现如下结果：
```bash
/usr/lib/x86_64-linux-gnu/libfreetype.a
/usr/lib/x86_64-linux-gnu/libfreetype.so.6
/usr/lib/x86_64-linux-gnu/libfreetype.la
/usr/lib/x86_64-linux-gnu/libfreetype.so
/usr/lib/x86_64-linux-gnu/libfreetype.so.6.12.1
/usr/local/lib/libfreetype.a
/usr/local/lib/libfreetype.so.6
/usr/local/lib/libfreetype.so.6.9.0
/usr/local/lib/libfreetype.la
/usr/local/lib/libfreetype.so
```
解决方案为：
`sudo rm /usr/local/lib/libfreetype.so.6`
或者
```bash
cd /usr/local/lib
sudo rm libfreetype.so.6 libfreetype.so libfreetype.so.6.9.0
```

切记：
1. 如果其中一个libfreetype是之前自己编译的，暂时将其隐藏即可，达到环境变量找不到这个动态库的目的
2. 不要把两个地方的libfreetype.so.6都删除了，我都删了之后，出现无法使用快捷键(如：ctrl+alt+t无法弹出终端)，以及重启无法进入系统的情况，最后通过重新创建/usr/lib/x86_64-linux-gnu/里面的/usr/lib/x86_64-linux-gnu/libfreetype.so.6，才重新进入系统。（libfreetype.so.6是一个软链接文件）

### 4.5 qtchooser加入新的qmake版本

编辑环境变量：
`sudo vi ~/.bashrc`
按下i输入，在其最后添加以下信息
```bash
export QTDIR=/home/iscas123/Qt5.12.12/5.12.12
export PATH=$QTDIR/gcc_64/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/gcc_64/lib
```
按Esc后输入:wq保存退出。

银河麒麟上的Qt版本管理工具是qtchooser：
输入qtchooser -l显示qmake的几种版本的列表：
```bash
kylin@kylin:/usr/lib/aarch64-linux-gnu/qtchooser$ qtchooser -l
4
5
default
qt-5.12-aarch64-linux-gnu
qt4-aarch64-linux-gnu
qt4
qt5-aarch64-linux-gnu
qt5
```
添加一个名字为5.12的:
`qtchooser -install qt5.12 /home/iscas123/Qt5.12.12/5.12.12/gcc_64/bin/qmake`

然后再看一下
`qtchooser -l`
```bash
4
5
default
qt4-x86_64-linux-gnu
qt4
qt5-x86_64-linux-gnu
qt5.12
qt5
```
好了加完了，再设一下环境变量
`export QT_SELECT=qt5.12`
好了现在的qmake就是5.12的了


### 4.6 missing: ZLIB_LIBRARY

make报错：`cmake Could NOT find ZLIB (missing: ZLIB_LIBRARY)`
解决方案：`cmake .. -DZLIB_INCLUDE_DIR=/usr/include -DZLIB_LIBRARY=/usr/lib`



# 移植

此处移植是指编译完成后移植到另一台电脑配置开发环境。默认已完成Qt5.12、cmake的安装，若不满足条件，请参考第一部分。

1. 将编译好的库文件、头文件、可执行文件打包好后(osg_oe)文件夹放在指定路径，如`/home/iscas/env`，将其解压
2. 动态库、静态库路径写入环境变量：
   1. `sudo xdg-open /etc/ld.so.conf`
   2. 在文件末尾写入：`/usr/local/lib`、`/usr/local/lib64`(需换行)
   3. 执行：`sudo ldconfig`
3. 环境变量中添加osg：`sudo xdg-open ～/.bashrc`
    文件末尾写入：
    ```bash
    export PATH=${PATH}:/home/iscas/env/bin
    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/iscas/env/lib
    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/iscas/env/lib64
    export OSG_FILE_PATH=/home/iscas/env/data
    ```

完成部署

