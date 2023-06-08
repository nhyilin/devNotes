
# visual studio
- [CMake命令/函数汇总（翻译自官方手册）](https://www.cnblogs.com/52php/p/5684588.html)
- 项目结构(base on cmake)：
```bash
cmake.exe -G "Visual Studio 15 2017" -A x64 -DTHIRDPARTY_ROOT_DIR=D:\myDevelop\ThirdParty -DCMAKE_PREFIX_PATH=C:/Qt/Qt5.9.6/5.9.6/msvc2017_64/lib/cmake -S D:\myDevelop\project\kneev2021\src -B D:\myDevelop\build\kneeV2021
```
-  项目属性中，以下参数的灵活使用
`output directory`:灵活制定调试程序的输出目录，方便在调试过程中的直接运行
`target name`:制定输出可执行文件的名称
- linker中`UAC Execution Level`：运行程序权限
- [vs中tab换位空格](https://blog.csdn.net/u012308586/article/details/101027542)：制表符大小选为4，勾选插入空格，即可
- 设置visualstudio默认打开方式为管理员权限：
找到vs安装目录下的：C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe



- 没有为此解决方案配置选中要生成的项目：右键项目，查看属性，常规里的配置管理器，勾选上“生成”选项即可

- vs在Release模式下开启Debug调试
  - 项目属性 -> c/c++ -> 常规 -> 调试信息格式化 -> 程序数据库(/Zi)
  - 项目属性 -> c/c++ -> 常规 -> 优化 -> 已禁用(/Od)
  - 项目属性 -> 链接器 -> 调试 -> 生成调试信息 -> 生成调试信息(/DEBUG)


- 在vs中设置目标生成路径，也可以设置生成后事件：项目属性->生成事件->后期生成事件->命令行中：
  ```bash
  copy /Y $(SolutionDir)$(Platform)\$(Configuration)\$(ProjectName).dll D:\myDev\TZSatelliteSimTool\release
  copy /Y $(SolutionDir)$(Platform)\$(Configuration)\$(ProjectName).lib D:\myDev\TZSatelliteSimTool\release
  copy /Y $(SolutionDir)$(Platform)\$(Configuration)\$(ProjectName).pdb D:\myDev\TZSatelliteSimTool\release
  ```
  `/Y`是禁止提示yes/no
- vs中调试DLL的源码文件，在使用dll的工程中工具->选项->调试->常规->取消选择要求源文件与原始版本完全匹配，然后从文件夹将DLL工程的源码文件拖入vs的DLL调用软件调试页面，就可以断点调试了



## resharper插件
- [resharper](https://www.jetbrains.com/resharper/)
- `contorl + shift + G`：显示简洁的`navigate to`，有一些常用的操作，如查看调用等


- 设置方法：VA options ->suggestions->Edit VA Snippets
```
文件注释：（快捷键：/file）
/********************************************************
	* @file    : $FILE_BASE$.$FILE_EXT$
	* @brief   :
*********************************************************/
$end$
```

# cLion

>习惯于VisualStudio开发，故在快捷键模块直接设置成为了：`Visual Studio copy`

- `code`标签页中:Reformate Code,重新整理代码，快捷键：`Ctrl+Alt+Enter`
- [clion使用技巧](https://www.cnblogs.com/xueqiuqiu/articles/12912209.html)
- 整理代码快捷键：
    - win：Control+Alt+L
    - Mac：command+Alt+L（可设置为command+control+L方便按）
- ⇧ + ⌘ + A 然后输入你想用到的功能，然后选中就可以了，尤其是当快捷键太多记不住的时候真的是很实用啊
- 调试快捷键
  - Step Over:`cmd + '`
  - Step Into:`cmd + ;`
- 返回上一文件光标(back & forward)：`cmd + [ or ]`
- [Intellij IDEA 关闭拼写检查](https://blog.csdn.net/Mars_wen/article/details/79013766)

# python

- [mac、Windows上matplotlib绘图中文乱码](https://blog.csdn.net/weixin_46474921/article/details/123783987)
  是字体问题，Mac版修改见下：
  ```python
    plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
    plt.title("中文标题")
    plt.show()
  ```

- 代码整理：
  - 在Windows环境下使用快捷键：`Shift + Alt + F`
- `tab替换为空格`：[VSCode烦人的空格处理](https://zhuanlan.zhihu.com/p/343307484)
总之配置如下：
```json
"editor.detectIndentation": false,  //关闭检测第一个tab后面就tab
"editor.renderControlCharacters": true, //制表符显示->
```

- [鼠标滚轮翻页速度](https://blog.csdn.net/bk_baokang/article/details/124219216)，mouseWheelScrollSensitivity自己显示器上设置第一个参数为0.25个人体验比较舒服
- 选择多列快捷键


# Linux

### tar命令解压
1. `*.tar`：用`tar -xvf`解压
2. `*.gz`：用`gzip -d`或者`gunzip`解压
3. `*.tar.gz`和`*.tgz`：用`tar -xzf`解压
4. `*.bz2`用`bzip2 -d`或者用`bunzip2`解压
5. `*.tar.bz2`用`tar -xjf`解压
6. `*.Z`用`uncompress`解压
7. `*.tar.Z`用`tar -xZf`解压
8. `*.xz`用`tar -xf`解压


## as a Server
以下服务端仅针对Ubuntu（麒麟适用），其他Linux方式可能会不同
- 本机IP地址查询`ip addr show`，在第二个段落中`inet`字符后面
- `/etc/network/interfaces`修改ip地址的文件
- `lsof -i:80`查看端口是否开放，如果开放，则有返回信息，反之未开放，也可用`netstat -apth`查看当前所有开放端口（`netstat`指令需提前安装`net-tools`工具）
- 无法在指定文件夹进行新建、复制粘贴等操作：
    - 权限管理，`sudo chmod 777 /var/www`
    - 或者直接`sudo`创建文件、文件夹等：
        1. `cd /var`
        2. `sudo mkdir fileName`
- nginx：
    - 查看nginx路径：`whereis nginx`
    - 启动文件：`/usr/sbin/nginx`


### 代码示例
```c++
#include <iostream>

int main() {}
```

#### 四级标题

```c++
#include <iostream>
// 四级标题
int main() {}
```

##### 五级标题

\begin{lstlisting}[language=c++]
#include <iostream>
// 五级标题
int main() {}
\end{lstlisting}
