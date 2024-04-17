# Table of Contents
- [Table of Contents](#table-of-contents)
- [MarkDown](#markdown)
  - [代码删减样式](#代码删减样式)
  - [按键样式](#按键样式)
  - [自动生成toc](#自动生成toc)
  - [高亮](#高亮)
  - [不同颜色字体](#不同颜色字体)
- [Xcode](#xcode)
- [visual studio](#visual-studio)
  - [resharper插件](#resharper插件)
  - [Assist X插件](#assist-x插件)
- [cLion](#clion)
- [python](#python)
  - [pycharm](#pycharm)
- [vscode](#vscode)
- [Linux](#linux)
  - [vim](#vim)
  - [for Development](#for-development)
    - [tar命令解压](#tar命令解压)
  - [as a Server](#as-a-server)
  - [麒麟](#麒麟)
- [Data](#data)
- [GitAndSVN](#gitandsvn)
  - [code maintenance](#code-maintenance)
  - [git常用操作](#git常用操作)
- [dump windows](#dump-windows)
  - [office](#office)
    - [word](#word)
    - [visio](#visio)
- [myMac](#mymac)
- [work experience](#work-experience)

# MarkDown
## 代码删减样式
```diff
- var x = 1;
+ let x = 2;
```
## 按键样式
<kbd>ctrl</kbd> +  <kbd>s</kbd>


## 自动生成toc
VS Code 中安装 `Markdown All in One` 插件，将鼠标光标放到要生成目录的位置，右键打开「命令面板」(`ctrl/cmd + shift + P`)，搜索“toc”，选中「创建目录」，即可自动生成目录。

## 高亮
<mark>高亮</mark> 

## 不同颜色字体
<font color=red>红色</font>
<font color=blue>蓝色</font>
<font color=orange>橙色</font>
<font color=green>绿色</font>
<font color=purple>紫色</font>

另：  
[Shields.io](https://sspai.com/post/59593)、[Substats](https://github.com/spencerwooo/Substats) 定制动态数据小牌子


# Xcode

- [格式化代码](https://www.cnblogs.com/Wayou/p/xcode_clang_setup.html)
- 删除整行快捷键,my：`alt + L`，快捷键里自己添加的，但是是要在英文输入法的状态下。

您好，这是Bing。很高兴为您解答。😊

Xcode15快捷键：
  - <kbd>⌘ + Z</kbd> 撤销上一次的操作
  - <kbd>⌘ + ⇧ + Z</kbd> 重做上一次的操作
  - <kbd>⌘ + F</kbd> 查找文本或代码
  - <kbd>⌘ + G</kbd> 查找下一个匹配的文本或代码
  - <kbd>⌘ + ⇧ + G</kbd> 查找上一个匹配的文本或代码
  - <kbd>⌘ + ⌥ + F</kbd> 替换文本或代码
  - <kbd>⌘ + ⌥ + G</kbd> 替换下一个匹配的文本或代码
  - <kbd>⌘ + ⌥ + ⇧ + G</kbd> 替换上一个匹配的文本或代码
  - <kbd>⌘ + ⌥ + C</kbd> 复制当前行或选中的文本或代码
  - <kbd>⌘ + ⌥ + V</kbd> 剪切当前行或选中的文本或代码
  - <kbd>⌘ + ⌥ + L</kbd> 格式化当前文件的代码
  - <kbd>⌘ + /</kbd> 注释或取消注释当前行或选中的代码
  - <kbd>⌘ + [ </kbd> 向左缩进当前行或选中的代码
  - <kbd>⌘ + ] </kbd> 向右缩进当前行或选中的代码
  - <kbd>⌘ + ⌥ + [ </kbd> 上移当前行或选中的代码
  - <kbd>⌘ + ⌥ + ] </kbd> 下移当前行或选中的代码
  - <kbd>⌘ + ⌥ + \</kbd> 跳转到当前行或选中的代码的对应的大括号
  - <kbd>⌘ + ⌥ + ←</kbd> 折叠当前代码块
  - <kbd>⌘ + ⌥ + →</kbd> 展开当前代码块
  - <kbd>⌘ + ⌥ + ⇧ + ←</kbd> 折叠所有代码块
  - <kbd>⌘ + ⌥ + ⇧ + →</kbd> 展开所有代码块
  - <kbd>⌘ + ⌥ + B</kbd> 构建当前项目
  - <kbd>⌘ + R</kbd> 运行当前项目
  - <kbd>⌘ + B</kbd> 编译当前项目
  - <kbd>⌘ + Y</kbd> 启用或禁用调试器
  - <kbd>⌘ + ⇧ + O</kbd> 快速打开文件或符号
  - <kbd>⌘ + ⇧ + J</kbd> 在项目导航器中显示当前文件
  - <kbd>⌘ + 0</kbd> 显示或隐藏导航区域
  - <kbd>⌘ + ⌥ + 0</kbd> 显示或隐藏实用工具区域
  - <kbd>⌃ + ⌘ + [↑|↓]</kbd> 头文件、源文件切换

Xcode中查看项目的C++版本,可以在项目的任何一个.cpp文件中添加以下代码来查看C++版本：
`std::cout << __cplusplus << std::endl;`

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
- `ctrl+tab`：在VS中切换打开的窗口，即切换各个文件
- `ctrl+K+D`：代码整理（好用）
- `Ctrl+K+F`：整理选中代码
- `Ctrl+Shift+F9`：清理所有断点
- `F12`：转到所调用函数或变量的定义
- `Shift+Tab`：减少缩进
- `Ctrl+M`：展开或折叠当前的代码（展开或收缩方法，类等）
- `ctrl+-`：跳回上次编辑位置很好用
- `Ctrl+m+m`：折叠\展开函数
- `Edit.commentSelection(编辑.注释选定内容)`：在设置中搜索，自定义添加注释快捷键：`Ctro+/`
- `Edit.UncommentSelection(编辑.取消注释选定内容)`：在设置中搜索，自定义添加取消注释快捷键：`Ctro+'`
- `Window.NextDocumentWindowNav`设置切换打开页面快捷键：`Ctro+T`
- `Auto Hide`：命令行输出，自动隐藏对看代码很友好
- `shift+F12`：Find All References
- `Alt+shift+o`：打开输出窗口
- `ctrl+\,e`：打开错误列表
- `ctrl + q`：search visual studio，类似clion查找快捷键的搜索方式
- `ctrl + -`：返回，返回上一文件，如果ctrl进入定义后，回到原文件处
- [注释/取消注释快捷键  control / ‘ 设置里的（编辑.注释）](https://zhuanlan.zhihu.com/p/343307484)
- vs2015中原生不支持ctrl+单击进入定义，`GoToDef.vsix`插件可满足需求
- [vs中tab换位空格](https://blog.csdn.net/u012308586/article/details/101027542)：制表符大小选为4，勾选插入空格，即可
- 设置visualstudio默认打开方式为管理员权限：
找到vs安装目录下的：C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe

右键->兼容性疑难解答->疑难解答程序->勾选该程序需要附加权限->测试后下一步->保存设置。

以后甭管双击sln还是快捷方式，都默认使用管理员权限启动vs2017了。

- 没有为此解决方案配置选中要生成的项目：右键项目，查看属性，常规里的配置管理器，勾选上“生成”选项即可

- vs在Release模式下开启Debug调试
  - 项目属性 -> c/c++ -> 常规 -> 调试信息格式化 -> 程序数据库(/Zi)
  - 项目属性 -> c/c++ -> 优化 -> 已禁用(/Od)
  - 项目属性 -> 链接器 -> 调试 -> 生成调试信息 -> 生成调试信息(/DEBUG)

- 【以下文件中的行尾不一致。是否将行尾标准化?】原因分析可能是写代码的时候行尾的标识可能不一样造成的。默认情况下是坐对行尾进行检查。建议直接忽略检查即可：选项->环境->文档->"加载时检查一致的行尾(Check for consistent line endings on load)"钩去掉就不会检查了
- 查看dll导出函数接口：工具->命令行->开发者PowerShell，执行`dumpbin /exports ./release/cstkkernel.dll /out:D:/a.txt`，将cstkkernel.dll输出到D盘的`a.txt`
- 在vs中设置目标生成路径，也可以设置生成后事件：项目属性->生成事件->后期生成事件->命令行中：
  ```bash
  copy /Y $(SolutionDir)$(Platform)\$(Configuration)\$(ProjectName).dll D:\myDev\TZSatelliteSimTool\release
  copy /Y $(SolutionDir)$(Platform)\$(Configuration)\$(ProjectName).lib D:\myDev\TZSatelliteSimTool\release
  copy /Y $(SolutionDir)$(Platform)\$(Configuration)\$(ProjectName).pdb D:\myDev\TZSatelliteSimTool\release
  ```
  `/Y`是禁止提示yes/no
- vs中调试DLL的源码文件，在使用dll的工程中<kbd>工具</kbd>-><kbd>选项</kbd>-><kbd>调试</kbd>-><kbd>常规</kbd>->取消选择<kbd>要求源文件与原始版本完全匹配(Require source files to exactly match the original version)</kbd>，然后从文件夹将DLL工程的源码文件拖入vs的DLL调用软件调试页面，就可以断点调试了
- vs全屏显示：<kbd>shift</kbd>+<kbd>alt</kbd>+<kbd>enter</kbd>，返回正常状态相同按键
- 剪切整行：<kbd>ctrl</kbd>+<kbd>l</kbd>
- 删除整行：<kbd>ctrl</kbd>+<kbd>shift</kbd>+<kbd>l</kbd>

[![top] Goto Top](#table-of-contents)

## resharper插件
- [resharper](https://www.jetbrains.com/resharper/)
- `contorl + shift + G`：显示简洁的`navigate to`，有一些常用的操作，如查看调用等
- 菜单栏-扩展-resharper-option-IntelliSense-Autopopup，将所有的菜单都选择Display and preselect，也就是预先选择，之后就可以用enter而不是用tab进行补全了。之后tab为replace，enter为insert
- `ctrl + shift + F7`：在文件中突出被引用的地方，在右侧进度条也可看到相应的标记
- `ctrl + shift + n`：打开文件（Go to file）
- 代码分析下划线警告级别及样式：Code Inspection下的Inspection Severity
- `ctrl + k , ctrl + G`：Show Structure，看代码结构，其实就是附近的for或者if以及函数参数等
- win上，`Ctrl + Alt + F`：格式化选中代码，如果不起作用，那么检查Code Eiditing -> c++ Formatting Style -> General，选择如果是Clang-format有可能会失效，感觉是插件的bug
- 上下移动选中代码：`Ctrl + shift + Alt + 上&下`

[![top] Goto Top](#table-of-contents)


## Assist X插件

- 增添修改快捷键前，最好命名时在最前面加上`yilin_xxx`，有利于后期维护，如：`yilin_qDebug`

- Shortcut:`log`
Description:`for easy Qt logging`
Details:`"$YEAR$/$MONTH_02$/$DAY_02$ $HOUR_02$:$MINUTE$ [yilin] `
当在需要打印log的地方键入log字符，则插入代码块：`"2021/10/18 13:49 [yilin] `
配合easylogging++，更为方便`LOG(INFO) << "$YEAR$/$MONTH_02$/$DAY_02$ $HOUR_02$:$MINUTE$ [yilin] `同样将其快捷键设置为`log`,极为方便

- `Alt+Shift+O`: 查找整个Solution下的某个文件 O指open，打开指定的文件

- `Alt+m`:当前类的函数列表

- `VAssistX.FindReferences`：可设置为：`Control+0`

- 设置中的Brace Matching，vs中对应大括号高亮，或者是番茄助手的highlight选项选择

- 设置方法：VA options ->suggestions->Edit VA Snippets
```
文件注释：（快捷键：/file）
/********************************************************
	* @file    : $FILE_BASE$.$FILE_EXT$
	* @brief   :
	* @details :
	* @author  : china_zyl@yeah.net
	* @date    : $YEAR$-$MONTH$-$DAY$
*********************************************************/
$end$
```


```
函数注释：（快捷键：/*-）
/********************************************************
    *  @function :
    *  @brief    :  $brief$
    *  @input    :
    *  @output   :
    *  @return   :
    *  @author   :  Name  $YEAR$/$MONTH_02$/$DAY_02$ $HOUR_02$:$MINUTE$
	*  @History  :
*********************************************************/
```


```
作者注释：
/*************************Name $YEAR$/$MONTH$/$DAY$ $HOUR$:$MINUTE$ Begin**************************/
$end$
/*************************Name $YEAR$/$MONTH$/$DAY$ $HOUR$:$MINUTE$ End****************************/
```

- `//-`：代码开发单行注释快捷键

- `/**`：代码开发函数/类注释快捷键

[![top] Goto Top](#table-of-contents)


# cLion

>习惯于VisualStudio开发，故在快捷键模块直接设置成为了：`Visual Studio copy`

- `code`标签页中:Reformate Code,重新整理代码，快捷键：`Ctrl+Alt+Enter`
- [clion使用技巧](https://www.cnblogs.com/xueqiuqiu/articles/12912209.html)
- 整理代码快捷键：
    - win：Control+Alt+L
    - Mac：command+Alt+L（可设置为command+control+L方便按）
- ⇧ + ⌘ + A 然后输入你想用到的功能，然后选中就可以了，尤其是当快捷键太多记不住的时候真的是很实用啊
- shift + alt + 上下箭头，clion上下移动选中代码
- idea设置选中状态下括号的提示颜色：Editor->Color Scheme->General->Match brace
- Intellij设置默认开启不打开上一次项目：配置中的System Settings，右边的Reopen last project on startup
- `Alt + cmd + 左右键`：切换前、后编辑器tab
- 调试快捷键
  - Step Over:`cmd + '`
  - Step Into:`cmd + ;`
  - Force Step Over:`alt + cmd + '`
  - Force Step Into:`alt + cmd + ;`
  - Smart Step into:`alt + cmd + ;`
  - Step out:`cmd + \`
  - Run to Cursor:`ctrl + shift + \`
  - Force Run to Cursor:`alt + ctrl + shift + \`
  - Resume Program:`ctrl + \`
- 返回上一文件光标(back & forward)：`cmd + [ or ]`
- [Intellij IDEA 关闭拼写检查](https://blog.csdn.net/Mars_wen/article/details/79013766)

Linux(麒麟)下：
search everywhere: `Double Shift`
Go to File: `Ctrl+Shift+n`
Recent File: `Ctrl+E`
Navigation Bar: `Alt+Home`
Find in Files: `Ctrl+Shift+F`

- clion在确保cmakelist没有问题的情况下(可以从命令行之行cmake测试)，仍报错cmake找不到某三方库，如Qt5webengine等，尝试在clion的cmake设置里添加环境变量，并且Reset Cache and Reload Project


[![top] Goto Top](#table-of-contents)

# python

- [离线安装anaconda及第三方库](https://blog.csdn.net/SEU_LL/article/details/119385057)
- [离线迁移conda环境](https://blog.csdn.net/maximejia/article/details/115385868)
- [conda和pip临时和永久换源的方法](https://blog.csdn.net/weixin_44089252/article/details/121053639)
- [mac、Windows上matplotlib绘图中文乱码](https://blog.csdn.net/weixin_46474921/article/details/123783987)
  是字体问题，Mac版修改见下：
  ```python
    plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
    plt.title("中文标题")
    plt.show()
  ```

## pycharm

- pycharm向左、右缩进快捷键：shift+tab、tab（win）
- pycharm编辑快捷键时，搜索debug，`debug context configuration`为调试当前页面内容，run同理：`run context configuration`

- [pycharm每次运行的时候都会开一个新窗口，怎么关闭？关闭“控制台运行”模式](https://blog.csdn.net/kwinawyeth/article/details/106452463)

- [pycharm编辑器如何用鼠标滚轮随时放大缩小代码](https://blog.csdn.net/mao_hui_fei/article/details/106737051)

- pycharm为了输出结果好看，将字体设置为13号，字符间距为0.8

[![top] Goto Top](#table-of-contents)

# vscode

- [markdown自动生成toc轮子](https://ecotrust-canada.github.io/markdown-toc/)
- [基础配置](https://zhuanlan.zhihu.com/p/62913725)
- `Restore Windows`：设置重新打开编辑器时，是否恢复所有已打开文件（建议不打开，否则每次打开都是上一次的文件很不舒服）
- 字符自动换行：设置中`Editor: Word Wrap`改为on即可
- vscode中文乱码，编码自动检测：`files.autoGuessEncoding`
- [中文乱码解决方案](https://www.jianshu.com/p/6a2c21cc07bb)
- [万字长文把 VSCode 打造成 C++ 开发利器](https://zhuanlan.zhihu.com/p/96819625)（很多可以借鉴的地方）
- 代码整理：
  - 在Windows环境下使用快捷键：`Shift + Alt + F`
  - 在Mac环境下使用快捷键：`Shift + Option + F`
  - 在Ubuntu环境下使用快捷键：`Ctrl + Shift + I`
- `tab替换为空格`：[VSCode烦人的空格处理](https://zhuanlan.zhihu.com/p/343307484)
总之配置如下：
```json
"editor.detectIndentation": false,  //关闭检测第一个tab后面就tab
"editor.renderControlCharacters": true, //制表符显示->
"editor.renderWhitespace": "all", //空格显示...
"editor.tabSize": 4,//tab为四个空格
"editor.insertSpaces": true //转为空格
```
- [vscode关闭受限模式（工作区信任），启用调试等功能](https://blog.csdn.net/weixin_45755666/article/details/117877321)：`security.workspace.Trust:Enabled`改为`false`即可
- 光标处的代码折叠：
  - 折叠 Ctrl+Shift+[
  - 展开 Ctrl+Shift+]
  - 如果你有更多需求的话，可以使用Ctrl+Shift+P搜索fold和unfold，以查看更多选项。以下命令使用时查找即可，不必记忆(但上文的两种还是有必要熟悉的)。

- markdown预览快捷键：`shift + cmd + v`
- code + 文件名，vscode打开指定文件
- [mermaid画markdown流程图插件](https://www.cnblogs.com/dao0/p/4489837.html)
- tree终端指令列出当前文件夹下文件，然后写入到md文件中，格式按代码块处理
- [鼠标滚轮翻页速度](https://blog.csdn.net/bk_baokang/article/details/124219216)，<kbd>mouseWheelScrollSensitivity</kbd>自己显示器上设置第一个参数为0.25个人体验比较舒服
- 选择多列快捷键： <kbd>Shift</kbd>+<kbd>Alt</kbd>+<kbd>鼠标左键</kbd>

[![top] Goto Top](#table-of-contents)

# Linux

## vim
- `cat`显示指令
- `dd`删除当前行（在一般模式下）
- `ndd`删除光标及其下n行
- `u`撤销
- `yy`复制当前行
- `p`粘贴到下一行
- `nyy`复制n行
- 修改文件名：`mv a b`将a文件命名为b
- :wq  保存后退出vi，若为 :wq! 则为强制储存后退出（常用）
- :w    保存但不退出（常用）
- :w!   若文件属性为『只读』时，强制写入该档案
- :q    离开 vi （常用）
- :q!   若曾修改过档案，又不想储存，使用 ! 为强制离开不储存档案。
- :e!   将档案还原到最原始的状态！

## for Development

- `alt+F2`：相当于win的`win+R`，可执行前往文件夹等指令
- `Ctrl+H`：显示隐藏文件
- `Ctrl+Alt+T`：打开终端快捷键
- `Ctrl+L`：相当于clear，清屏
- `Ctrl+D`：关闭终端
- `wget`指令：Linux中下载文件的工具，详见`wget --help`（安装方法：`yum install -y wget`）
- `source /etc/profile`使环境变量生效，且该`profile`文件即为环境变量储存文件
- `/mnt/hgfs/VMshared`共享文件夹在Ubuntu内的路径
- `rm -rf 要删除的文件或目录`：删除当前目录下所有文件及目录，并且直接删除无需逐一确认
- `xdg-open`打开文件或文件夹,无空格。(macOs下对应`open`命令)
- 增添环境变量：（以cmake为例）
    - `vim ~/.bashrc`
    - 在文末，执行`i`指令（insert），添加`export PATH=/xxx:&PATH`，xxx是cmake地址，到bin目录
    - `source ~/.bashrc`
- lib库默认安装位置在`/usr/lib/`或者`/usr/local/lib`
- `alt+F4`:关闭
- `static`：静态库，`dynamic`：动态库。
- linux下，`.a`静态库，`.so`动态库。
- win下，`.lib`静态库，`.dll`动态库。
- Mac下，`.a`静态库，`.dylb`动态库，`.Framework`为打包方式，将库的二进制文件打包在一起。
- 文件以tree形式列出：`tree`(sudo apt  install tree)
- Linux设置vi编辑器
    - 配置文件：`sudo vi /etc/vim/vimrc`
    - tab键位4个空格：`set ts=4`
    - 显示代码行数：`set nu`
- 解决报错，运行脚本时，build.sh /bin/bash^M :坏的解释器：没有那个文件或目录：`sed -i 's/\$//' xxx.sh`，xxx.sh为对应脚本
- 只下载不安装`sudo apt-get install -d <软件包>`
  - `ls /var/cache/apt/archives/` #下载的包目录
- [ubuntu 执行`apt-get update`报错`Failed to fetch`：](https://blog.csdn.net/feiniao8651/article/details/60332535)
  如果要换源的话，可以在`/etc/apt`里面打开`source.list`文件，会出现一个设置框，在导航栏第一个里面的`download from`里面选择源。如果要选择国内的源，找到`China`，里面有很多可以选择，个人体验较好清华镜像，记得`sudo apt-get update`
- 重命名:
  例子：将目录A重命名为B：`mv A B`
  例子：将/a目录移动到/b下，并重命名为c：`mv /a /b/c`
- 终端记录输出：`script -f output.txt`
- `make install`指定目标目录
  1. 当有`configure`文件时指定`./configure --prefix=/...自定路径`，然后`sudo make && make install`即可
  2. 当只有`CMakeLists`时，对于大多数工程，特别是`cmake`生成的工程，`make`后`sudo make install DESTDIR=/...路径`
  3. 当只有CMakeLists时，少数工程如源码安装git发现用方法1实际上安装到了`/install/directory//home/username` 目录，即用户根目录，这是因为`Makefile`内部已经设置了一遍安装目标目录，手工设置的目录仅仅作为了一个前缀，打开`Makefile`文件，发现有如下代码（就在最顶端）
  ```bash
  prefix = (HOME) bindir =(prefix)/bin
  mandir = (prefix)/share/man infodir =(prefix)/share/info
  ```
  修改第一行`prefix`对应目录即可
- linux 下长命令的简化（命令别名）:在`~/.bashrc`文件中添加`alias gps='git push origin HEAD:refs/for/master'`，`source ~/.bashrc`
- deb文件安装：`sudo dpkg -i 软件包名.deb`
- 修改文件创建时间属性：`touch -mt YYYYMMDDhhmm`，比如：`touch -amt 201412010000 *`修改当前文件夹内所有文件时间为`201412010000`，Mac相同。参数：-a: 修改访问时间，或 –time=atime 或 –time=access 或 –time=use。-c: 或 –no-creat，如果文件不存在则不创建文件。-d: 使用指定的日期时间，可以使用不同的格式。-m: 或 –time=mtime 或 –time=modify，改变修改时间。-r: 把指定的文件日期更设成和参考文档或目录日期相同的时间。-t: 使用指定的日期时间，格式与 date 指令相同
- alias o='sudo xdg-open'
- alias osg='osgviewer'
- alias osge='osgearth_viewer'
- alias getbash='sudo xdg-open ~/.bashrc'
- alias setbash='source ~/.bashrc'
- alias log='scirpt -f /home/yilin/output.txt'
- alias c='cmake CMakeLists.txt'
- alias clion='/home/yilin/softWare/clion-2022.1/bin/clion.sh'
- alias share='sudo xdg-open /mnt/hgfs/dev'
- 某些环境变量，Linux下在`~/.bashrc`，在Mac中为`~/.bash_profile`
  ```bash
  export QTDIR=/home/yilin/Qt5.12.12/5.12.12
  export PATH=$QTDIR/gcc_64/bin:$PATH
  export LD_LIBRARY_PATH=$QTDIR/gcc_64/lib
  
  export PATH=${PATH}:/home/yilin/env/osg_oe/bin
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/yilin/env/osg_oe/lib
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/yilin/env/osg_oe/lib64
  export OSG_FILE_PATH=/home/yilin/env/osg_oe/data
  ```
- 关闭触摸板：`sudo modprobe -r psmouse`，打开`sudo modprobe psmouse`，[详见](https://blog.csdn.net/SAKURASANN/article/details/104262048)
- Ubuntu修改短密码：`/etc/pam.d/common-password`文件`password	[success=2 default=ignore]	...`行，将`minlen=4`附加即可，当第一次输入时，会提示`bad password:the password is shorter than 8 characters`,让你`retype new password`，直接再输入一次即可完成更新
- linux下给目录下所有子目录和文件赋权`sudo chmod -R 777 *`
- 终端关闭进程，用于特殊情境只能调动终端时：`ps -ef | grep ***`其中星号为进程名(若不知道进程名试试窗口名)，然后`kill -9 ****`其中星号为进程后的第一串数字，也就是PID
- 在Windows上代码，移植Linux前转utf-8-bom，而不是utf-8，这样是为了兼顾vs编译

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
- 或者`ifconfig -a`
- `sudo su`：登录root用户
- `sudo ufw status`：查看端口启用情况
- `sudo ufw allow <端口号>`：开启端口号
- `sudo ufw enable`：开启防火墙
- `sudo ufw disable`：关闭防火墙
- `sudo ufw reload`：重启防火墙
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
    - 配置文件路径：`/etc/nginx`
    - 启动nginx：`/usr/sbin/nginx`

## 麒麟

- 用户、管理员改为**短密码**：`sudo apt remove libpam-cracklib`(其实在其它Linux上`sudo passwd 用户名`就直接可以完成修改，但是麒麟额外需要卸载掉负责检查密码复杂度的`cracklib`包)
- 麒麟系统下Qt安装路径`/usr/lib/x86_64-linux-gnu/qt5`
- 分辨率问题：
  1. `export QT_DEVICE_PIXEL_RATIO=1.5`：该方法针对了qt的应用，例如qtcreator，qtcreator字体显示正常了，系统字体依旧小
  2. `gsettings set org.mate.font-rendering dpi 150.0`：桌面字体终于看得清了，不足的是该方案仅仅是放大了字体，系统原来的布局并没有一起放大
- `ctrl+alt+f5`进入命令行界面,`Ctrl+Alt+F7`回到图形界面即可。[（有的电脑是f1）ubuntu同理](https://blog.csdn.net/stone_fall/article/details/95971718)，`sudo service lightdm start`、`sudo service lightdm stop`
- 在当前文件下打开终端的快捷键：`shift + F10`，然后按下`t`
- 无法更新软件源头，在`/etc/apt/sources.list`中将源修改为如下：`deb http://archive.kylinos.cn/kylin/KYLIN-ALL 4.0.2-desktop main restricted universe multiverse`，[其他版本在这里](http://archive.kylinos.cn/kylin/KYLIN-ALL/)
- 开发纯离线机常时间戳对不上：`make: warning:  Clock skew detected.  Your build may be incomplete.`，意思就是检测到时钟偏差了，主要是两个设备系统之间的时间上存在差距。解决：`find . -exec touch {} \;`
- `VMware: vmw_ioctl_command error Invalid argument.`：`echo "export SVGA_VGPU10=0" >> ~/.profile`
- 在离线状态下，git可视化软件免费且较为好用的是GitAhead
- 麒麟其实很多开发包在系统镜像中已经有打包：vmware操作栏->虚拟机->可移动设备->CD/DVD(SATA)，然后连接上系统镜像，在文件夹里的光盘镜像中，进入Package文件夹，即可看到所有自带的开发包


[![top] Goto Top](#table-of-contents)

# Data

（局域网）

svn：yilin
123456

OA服务器移动端地址https://159.226.29.1:89
新入职的员工请注意一下，OA的登录名是本人名字的全拼，密码是123456
第一次登录要改密码，请在电脑上改，https://159.226.29.1:80

1. 苹果手机直接在appstore里搜索emobile即可
2. 安卓用这个链接的第一个二维码https://emobile.weaver.com.cn/customer/azzj/produce.jsp
3. pc端没有客户端，登陆OA在地址栏输入：https://159.226.29.1:80


- 项目配置

CECA：加载pro文件，配置为win32项目，qt设置为qt2015（非qt2015_64)

---

ISCAS属性配置：
1. 常规中的字符集改为`使用多字节字符集`
2. c/c++中常规的调试信息格式改为`程序数据库`
3. c/c++优化：禁用
4. 预编译头文件：`stable.h`
5. 链接器：调试中的生成调试信息设为`优化以便于调试（注意debug以及release）`


https://192.168.0.33/svn/cstkKernel/
https://192.168.0.33/svn/TZSatelliteSimTool/
https://192.168.0.33/svn/TZTKBQPlatform/





[![top] Goto Top](#table-of-contents)

# GitAndSVN

## code maintenance

1. 本地检出develop分支

```bash
git init
git remote add origin https://git.oschina.net/null.v2.git
git remote -v
git clone git@...
```

2. 基于develop分支在本地创建临时分支(feature_yymm_addInfo)
   `git checkout -b feature_2107_addInfo develop`


3. 修改内容后，将本地分支映射到远程分支

```bash
git status
git add .                           // 添加修改后的内容
git commit -m "log infor"           // 提交到缓存
git push origin feature_1906_addInfo:feature_1906_addInfo    #:号前边是本地分支，冒号后面是服务端映射分支

添加：rebase操作，然后再merge操作
```


4. 登录gitlab页面，选择feature_1906_addInfo_web分支和merge的目标分支。
5. 常用命令：

`git checkout .` #本地所有修改的。没有的提交的，都返回到原来的状态

btw: `git checkout`、`git reset`本地的修改并不会消失，而只是从暂存区回到了工作区

## git常用操作

1. 恢复所有本地修改至当前分枝`git checkout .`
2. 当修改`.ignore`文件后，清除远端数据：
```git
git rm -r --cached . 
git add . 
git commit -m 'update .gitignore'
git push <远程主机名> <本地分支名>:<远程分支名>
```
- 不删除工作空间改动代码，撤销`commit`，并且撤销`git add .` ：`git reset --mixed HEAD^`
- 撤销`commit`，不撤销`git add .` ：`git reset --soft HEAD^`
- 删除工作空间改动代码，撤销`commit`，撤销`git add .` ,注意完成这个操作后，会删除工作空间代码！！！恢复到上一次的`commit`状态。慎重！！！：`git reset --hard HEAD^`
- LF will be replaced by CRLF: Windows中换行符为CRLF，而Linux换行符是LF，git默认是CRLF，若发现项目有LF，就会弹出警告了，最终push就会统一转成CRLF作为换行符。false就是不转换符号，默认是true，[参考这里](https://blog.csdn.net/Jae_Wang/article/details/80379133)
3. git的pull操作会导致本地未提交修改消失，[Git 少用 Pull 多用 Fetch 和 Merge](https://www.oschina.net/translate/git-fetch-and-merge?print)
4. [Git更新合并代码后，本地修改丢失](https://blog.csdn.net/wjw_de_java/article/details/110224170)
5. git清除本地所有修改`git checkout . && git clean -xdf`前半段是丢弃所有git追踪的修改，`git clean`是删除文件夹内git没有跟踪的文件
6. [GitHub执行git clone项目下载不全不完整](https://blog.csdn.net/zhuiqiuzhuoyue583/article/details/108115638):
    主要原因是因为所下载的项目仓库的一些子模块是通过链接的方式链接到主项目目录上的。而这些子模块的仓库是单独建立在另外的目录下
    在clone目录中执行即可：`git submodule update --init --recursive`


[![top] Goto Top](#table-of-contents)

# dump windows

- 右键我的电脑，管理，服务和应用程序，来查看本地服务（若有自己手动注册或删除服务的需求，则在此观察并操作）

- 开发Windows程序时，win的api报错，如740等，可在vs中查询报错信息，具体在"Tools->Error Lookup"

- `win+shift+s`：截屏快捷键

- 检测本地IP：在cmd中敲：`ipconfig/all`，其中IPv4地址即为本机IP地址（随即敲`arp -a`可显示局域网内IP列表）

- 静态网页局域网访问，百度该关键字即可
- VMware快捷键：`Ctrl + B`启动，`Ctrl + E`关闭，`Ctrl + R`重启
- `netsh advfirewall set allprofiles state off`：关闭防火墙
- 测试软件时，尽量在虚拟机上搞...
- 修改键位：
- ALT+Esc 当前窗口最小化
- Win+D 最小化所有窗口，再按一下就可以还原窗口
- Windows+M：最小化所有窗口
- Windows+Shift+M：还原最小化的窗口。
- [3DMax离线安装激活](https://mp.weixin.qq.com/s?__biz=MzA4MjU4MTg2Ng==&mid=2247501581&idx=2&sn=05f48702515e57c3a145d601ed89501f&chksm=9f810708a8f68e1ea24951e5ee426ae5e69552a1104c7d7c2ffcd8b9fe95a0b6d992d0307085&scene=21#wechat_redirect)：安装时可能会失败，1. 打开Windows自动更新服务； 2. [离线安装.net framework 3.5](https://blog.csdn.net/chuozan6114/article/details/100768375)
- 在word中出现十字箭头才能全部选中表格,但有时候它不出现，方法1、把鼠标移至表格的最后一行的，表格外的“回车”按钮旁边，然后再滚动鼠标，返回表格最前方，就可以看到十字箭头了。 方法2、把鼠标移动到表格后面（必须是表格外）的文字，然后再滚动鼠标，返回表格最前方，就可以看到十字箭头了。 方法3、随便修改一下表格内容，然后Ctrl+S也能显示十字箭头。


- 禁止单击alt的功能，但是保留alt+tab的功能，防止写代码按到alt影响书写体验
AutoHotkey软件：
```bash
; 禁用左alt键
~LAlt::Send {Blind}{vkFF}
; 禁用右alt键
~RAlt::Send {Blind}{vkFF}
```
完整配置如下：
```bash
; 在 Windows 11 中，您需要在启动 AutoHotkey 脚本时提升脚本的权限以保证其正常运行。可以通过右键单击 .ahk 文件，在菜单中选择“以管理员身份运行”来提升脚本的权限
CapsLock::^+Space
F12::CapsLock
~LAlt::Send {Bind}{vkFF}
~RAlt::Send {Bind}{vkFF}

#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; Docs:
; https://autohotkey.com/docs/Hotkeys.htm
; https://autohotkey.com/docs/KeyList.htm
; Ref https://autohotkey.com/board/topic/60675-osx-style-command-keys-in-windows/

; You need to disable "Between input languages" shotcut from Control Panel\Clock, Language, and Region\Language\Advanced settings > Change lanugage bar hot keys

; Universal shotcuts

$!x::Send ^x
$!c::Send ^c
$!v::Send ^v
$!s::Send ^s
$!a::Send ^a
$!z::Send ^z
$!+z::Send ^y
$!w::Send ^w
$!f::Send ^f
$!n::Send ^n
$!q::Send !{f4}
$!r::Send ^{f5}
$!m::Send {LWin Down}{Down}{LWin Up}
$!`::Send {Alt Down}{Shift Down}{Tab}{Shift Up}

; Quick Switch Tab shotcuts

$!1::Send ^1
$!2::Send ^2
$!3::Send ^3
$!4::Send ^4
$!5::Send ^5
$!6::Send ^6
$!7::Send ^7
$!8::Send ^8
$!9::Send ^9
$!0::Send ^0

; Chrome shotcuts

$!t::Send ^t
$!+t::Send ^+t
$!+]::Send {Ctrl Down}{Tab Down}{Tab Up}{Ctrl Up}
$!+[::Send {Ctrl Down}{Shift Down}{Tab Down}{Tab Up}{Shift Up}{Ctrl Up}
$!l::Send ^l

; input methods

; $+,::Send ^,
; $+.::Send ^.

; navigation, selection, delete a word/till end

$!Left::Send {Home}
$!Right::Send {End}
$!Up::Send {Lctrl down}{Home}{Lctrl up}
$!Down::Send {Lctrl down}{End}{Lctrl up}

$#Left::Send {ctrl down}{Left}{ctrl up}
$#Right::Send {ctrl down}{Right}{ctrl up}
$#+Left::Send {ctrl down}{shift down}{Left}{shift up}{ctrl up}
$#+Right::Send {ctrl down}{shift down}{Right}{shift up}{ctrl up}

$!+Left::Send {shift down}{Home}{shift up}
$!+Right::Send {shift down}{End}{shift up}
$!+Up::Send {Ctrl Down}{shift down}{Home}{shift up}{Ctrl Up}
$!+Down::Send {Ctrl Down}{shift down}{End}{shift up}{Ctrl Up}

!BS::Send {LShift down}{Home}{LShift Up}{Del}
#BS::Send {LCtrl down}{BS}{LCtrl up}

$#Space::Send {Ctrl Down}{LWin Down}{Space}{LWin Up}{Ctrl Up}
```

## office
### word
1. 建立图片索引
    - 右键图片，选择“插入题注”
    - 新建想要的标签，完成建立索引
    - 当需要索引图片时，【插入】功能栏中选择【交叉引用】，选取所需即可
    - 在撰写文档时：可将字体设置为Menlo等开发时使用的字体，显示word中有代码的效果
2. [保存所有word里的图片](http://www.icanzc.com/word/186.html)："文件"，选择“另存为”或“另存为网页”，弹出对话框后，点击最下面的“保存类型”下拉菜单，选择“网页”，此时还可单击对话框中的“工具→Web选项
3. 显示所有格式标记：Ctrl + *（星号）（Ctrl+ shift + 8）
4. ①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳㉑㉒㉓㉔㉕㉖㉗㉘㉙㉚㉛㉜㉝㉞㉟㊱㊲㊳㊴㊵㊶㊷㊸㊹㊺㊻㊼㊽㊾㊿

5. 要在Word文档中同时选中所有的表格，您需要通过使用Visual Basic for Applications (VBA)编程语言来实现。以下是步骤：

   1. 打开您的Word文档，点击“文件”或者"File"选项。  
   2. 从下拉菜单中选择“选项”或者"Options"。  
   3. 在新打开的窗口中，从左侧的菜单中选择“自定义功能区”或者"Customize Ribbon"。  
   4. 在右侧的界面中，勾选“开发工具”或者"Developer"，然后点击“确定”或者"OK"。  
   5. 现在您会在Word的功能区菜单顶端看到新出现的“开发工具”选项卡，点击它。  
   6.  在新展开的菜单中，点击“Visual Basic”，这将打开VB Editor。  
   7.  在VB Editor中，从左侧的"Project"菜单中找到您的文档，然后右键点击"Normal -> Microsoft Word Objects"。  
   8.  选择“插入” -> "模块"来新建一个模块。  
   9.  在新打开的代码窗口中，输入以下代码：  
  ```Visual Basic
  Sub SelectAllTable()
      Dim tbl As Table
      For Each tbl In ActiveDocument.Tables
          tbl.Range.Editors.Add wdEditorEveryone
      Next tbl
      ActiveDocument.SelectAllEditableRanges wdEditorEveryone
      ActiveDocument.DeleteAllEditableRanges wdEditorEveryone
  End Sub
  ```
   10.  按下快捷键Ctrl+S来保存，然后关闭VB Editor。  
   11.  再回到Word文档，再次点击“开发工具”，这次选择“宏”或者"Macros"。  
   12.  在新打开的对话框中，从列表中选择“SelectAllTable”，然后点击“运行”或者"Run"。这将选中文档中的所有表格。  


### visio
- visio对其所有连接线：在`设计`中点击连接线下面的小三角，`分隔：相关线条(有时候相关也可以，但是很少)`，`重叠：相关线条`。


[![top] Goto Top](#table-of-contents)


 # myMac
1. [配置环境变量](https://blog.csdn.net/liaowenxiong/article/details/112180532)
2. 安全与隐私中，通用栏，`进入睡眠或开始屏幕保护程序...要求输入密码`，控制时间有利于中途查看代码，减少解锁次数
3. magnet快捷键：`control + option + 上下左右`（调整应用程序贴合屏幕位置）
4. magnet快捷键：`control + option + enter`（最大化显示）
5. Downie下载：设置中，下载目录文件格式设置为`播放清单索引 - 标题`，下载文件保存至文件夹：勾选任意一个可保证下载列表视频时，自动创建文件夹来放置下载的视频，否则所有文件下载至当前目录造成混乱。
6. HomeBrew安装脚本`/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"`
7. 显示桌面快捷键：`command + F3`，或者`Fn + F11`
8. 用户环境变量文件：`~/.bash_profile`，可参考Linux部分alias指令
9. 修改系统环境变零：`/etc/profile`文件中添加，如`export PATH=/opt/local/bin:$PATH`
10. 无法ping 通 github.com:在[这里](https://www.ipaddress.com/)查询[github.com](https://ipaddress.com/website/github.com#ipinfo)以及[github.global.ssl.fastly.netip](https://ipaddress.com/website/github.global.ssl.fastly.net#ipinfo)地址，`/etc/hosts`文件中最后添加：
  - `140.82.112.3    github.com`
  - `146.75.77.194  github.global.ssl.fastly.net`
 重启DNS：`sudo killall -HUP mDNSResponder`再ping github.com就通了！（Ubuntu下`udo /etc/init.d/network-manager restart`重启网络)
11. brew安装：`/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"`
12. brew卸载：`/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/HomebrewUninstall.sh)"`
13. 显示隐藏文件：`cmd + shift + .`
14. 前往文件夹：`cmd + shift +g`
15. 当文件夹显示为列表时，可以`cmd + ➕`，放大显示效果
16. brew 安装文件报错：[Error: No such file or directory @ rb_sysopen](https://blog.csdn.net/yuchangyuan5237/article/details/126925843?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-1-126925843-blog-121221676.pc_relevant_recovery_v2&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-1-126925843-blog-121221676.pc_relevant_recovery_v2&utm_relevant_index=1)使用国内镜像而该镜像未完全同步问题。临时去除镜像即可。

```bash
export HOMEBREW_BOTTLE_DOMAIN=''
#重新安装
brew install graphviz
```
17. [mac上文件夹树图](https://www.cnblogs.com/anywherego/p/11132670.html)：`brew install tree`，安装完毕后，有三种方式来生成：tree #打印所有目录层级，`tree -L 2 #遍历2层`，`tree > README.md #输出结果到Markdown文档`，其中，md文档形式，预览时只需用代码块包住即可

18. Mac 跳到行尾、行首、Home和end快捷键（其中部分快捷键在终端terminal中也可使用）  
Ctrl+A：到行首  
Ctrl+E：到行尾  
Ctrl+N：到下一行  
Ctrl+P：到上一行  
Ctrl+K：从光标处开始删除，直到行尾  
fn键+左方向键是HOME  
fn键+右方向键是END  
fn+上方向键是page up  
fn+下方向键是page down  

19. [Open in vscode](https://stackoverflow.com/questions/64040393/open-a-folder-in-vscode-through-finder-in-macos)
20. 如何禁止生成u盘链接mac笔记本后的隐藏文件（` .DS_Store `文件和`._`开头的文件）
```bash
defaults write com.apple.desktopservices DSDontWriteNetworkStores -bool true
defaults write com.apple.desktopservices DSDontWriteUSBStores -bool true
```
上述命令分别禁止了在网络卷和 U 盘中生成 .DS_Store 文件和其他隐藏文件，这两个命令运行后，系统不会再在 U 盘中产生这些隐藏文件，但是已经存在的隐藏文件还要手动删除。
恢复：
```bash
defaults write com.apple.desktopservices DSDontWriteNetworkStores -bool false
defaults write com.apple.desktopservices DSDontWriteUSBStores -bool false
```

21. 启动微信：`nohup /Applications/WeChat.app/Contents/MacOS/WeChat > /dev/null 2>&1 &`

22. 将Desktop所有文件名输出到一个叫做 files.txt 的文件中：`ls ~/Desktop > files.txt`
23. 将Desktop所有所有 .cpp 文件输出到一个叫做 files.txt 的文件中：`find ./ -name "*.cpp" > files.txt`


[![top] Goto Top](#table-of-contents)

# work experience

- 现在感觉如果是自己开发的项目，有一定进展，勤提交，不要开发修改了一大堆，再想看差异一片糊

开发过程中搜索所需算法：
1. 明确你这个topic对应的英文叫啥
2. 用谷歌或者谷歌学术去搜索这个英文
3. 找引用比较高的，经典算法，多看几篇
4. 顺着引用这个经典算法的文章，找谁引用了它，一般都可以找到比较新的，并且引用也还不错的，如果有直接开源的就齐活了


- 有道词典（开发必备）
下载好离线安装包后，离线包在如下路径：`C:\Users\ISCAS-7\AppData\Local\Yodao\DeskDict\Dictionary`

- happyLogging：
在所需log的地方添加引用:
`#include "D:/myDevelop/happyLogging/loggerFiles/easylogging++.h"`
将`main`函数替换为自己的`main.cpp`
提交代码前可保证代码干净整洁,happy codding~
btw,已经将include指令添加快件进番茄助手，简直不要再香，快捷键为:`#`

- Qt程序运行提示“it could not find or load the QT platform plugin “windows”，打开qt的终端，然后进入release目录，执行`windeployqt ***.exe`即可完成qt库的收集。

- 工作初期，尽量不要信心满满说：“我完成了”、“没问题了”之类的话，应该将："您再帮我审查下“，"您再帮我把把关"

- matlab、python计算脚本随时准备好，log库随时准备好

- 代码初步改完了，测试用例还没写，您抽空帮我检查下一遍吧


提问：
1. In my limited experience with ..    谦虚表达自己在某方面的经验
2. I am searching for a long time on net. But no use. Please help or try to give some ideas how to achieve this.   找了很久未果，求助攻
3. after searching around for a decent XX solution and found that everything out there was difficult to use.  找了N种方法都发现太TM难了
4. I've looked around and apparently I've got the choice between these libraries/ solutions:   说明自己是努力搜索过的，然后目前有了哪几种方案
5. which seems it's a promising solution.  看起来是一个好解决方案
6. I`ve tried multiple variations of this, but none of them seem to work. Any ideas? 试了很多种方法都无效，求助
7. Wanted to know if it's good practice to do that and what would be the best way to do that? 我的做法是否正确，是否有更好的法子？
8. Thanks in advance.   先行谢过

回答问题：
1. If I understand you correctly, you want to xxx      如果我没理解错，你想。。
2. Can you provided more details about your use case ? Can you provide more xml and code setting the url ? 提供更详细

当别人回答你的问题后，你对回答的评论：
1. thank you for your answer sincerely 感谢回答blabla

思路整理：
1. 每种错误最多允许自己走一遍，如果错过那就记下来，不要重复试错，很浪费时间，更糟糕的是容易使脑子混乱。
2. 记住走错的方法容易走向误区，就是很详尽，不用遍历，但是方法的方向要把握，具体的度要在工作中把握。
3. 总之多推理少无谓的试错。

[![top] Goto Top](#table-of-contents)




<!-- figures -->
[top]: up.png

[top]: https://upload.nhyilin.cn/2021-11-19-up.png

