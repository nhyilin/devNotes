# 概述
这部分内容其实官方文档已经有介绍，包括三部分内容：“[Qt for Linux/X11 - Deployment](https://doc.qt.io/qt-5/linux-deployment.html)”、“[Qt for Windows - Deployment](https://doc.qt.io/qt-5/windows-deployment.html)”和“[Qt for MacOS - Deployment](https://doc.qt.io/qt-5/osx-deployment.html)”。看起来还是很简单的，如果不想看官文的话，我以自己的实际项目为例，说明如何在 Linux 下打包我们的程序。

本文目录结构：

一、准备两个脚本

ldd.sh脚本
hubeihdbtoexcel.sh脚本
给两个脚本加权限
二、打包过程

1.添加程序依赖库
2.添加 Qt 相关依赖库
三、验证

某个湖北现场需要将数据库中的数据输出为Excel文件。现场机器环境为Qt4，由于导出Excel文件的第三方库需要在Qt5环境下编译，因此该教程的目的是在现场机器不安装Qt5的情况下能正常运行Qt5编译的程序。

程序名：hubeihdbtoexcel

一、准备两个脚本

ldd.sh脚本
#!/bin/bash
LibDir=$PWD"/lib"
Target=$1
lib_array=($(ldd $Target | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"))
$(mkdir $LibDir)
for Variable in ${lib_array[@]}
do
    cp "$Variable" $LibDir
done
hubeihdbtoexcel.sh脚本
注意该脚本的名称必须和程序名一致。

#!/bin/sh
appname=`basename $0 | sed s,\.sh$,,`
dirname=`dirname $0`
tmp="${dirname#?}"
if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
$dirname/$appname "$@"
给这两个脚本加权限

sudo chmod 777 ldd.sh
sudo chmod 777 hubeihdbtoexcel.sh
二、打包过程
打包过程分为：添加程序依赖库和Qt依赖库。

添加程序依赖库
（1）新建一个空的文件夹，用于存放程序及其动态库。例如“ExportToExcel文件夹”；


（2）将ldd.sh脚本复制到编译目录，如“build-hubeihdbtoexcel-Desktop_Qt_5_5_1_GCC_32bit-Release”；


（3）执行“./ldd.sh hubeihdbtoexcel”，会在当前目录生成lib文件夹。其中存放着运行hubeihdbtoexcel所依赖的库文件；


（4）将lib文件夹中的所有文件复制到第1步新建的文件夹“ExportToExcel文件夹”中。至此，就可以删除生成的lib文件夹和ldd.sh脚本了

2. 添加 Qt 相关依赖库

（1）将ldd.sh脚本复制到Qt5安装目录的platforms文件夹中；


（2）执行“./ldd.sh libqxcb.so”，将生成的lib文件夹中的所有文件拷贝到“ExportToExcel文件夹”中。有些库可能重复，点击“替换”即可。执行完该步骤后就可以删除生成的lib文件夹和ldd.sh脚本了；

（3）返回上一级，将platforms整个文件夹拷贝到“ExportToExcel文件夹”中，层级关系如下图；


（4）该步骤为可选步骤。如果所编写的程序有操作数据库的动作，还需要将与platforms同级目录中的sqldrivers文件夹也拷贝到“ExportToExcel文件夹”中；


（5）最后将hubeihdbtoexcel.sh脚本拷贝到“ExportToExcel文件夹”中即可。然后将整个“ExportToExcel文件夹”压缩就可以在其他机器上解压缩后运行。


三、验证
（1）将压缩包解压；


（2）执行“./hubeihdbtoexcel.sh”，程序正常运行。




https://blog.csdn.net/z3512498/article/details/64922180


https://zhuanlan.zhihu.com/p/49919048