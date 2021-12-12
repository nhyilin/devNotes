# Table of Contents
- [Table of Contents](#table-of-contents)
- [Assist X](#assist-x)
- [visual studio](#visual-studio)
- [cLion](#clion)
- [python](#python)
  - [pycharm](#pycharm)
- [vscode](#vscode)
- [Linux](#linux)
  - [for Development](#for-development)
    - [tar命令解压](#tar命令解压)
  - [as a Server](#as-a-server)
  - [麒麟](#麒麟)
- [Data](#data)
- [GitAndSVN](#gitandsvn)
  - [svn](#svn)
  - [code maintenance](#code-maintenance)
  - [code download](#code-download)
    - [环境搭建](#环境搭建)
    - [SSH Keys生成及添加](#ssh-keys生成及添加)
    - [克隆代码到本地](#克隆代码到本地)
  - [svn](#svn-1)
- [dump windows](#dump-windows)
- [myMac](#mymac)
- [work experience](#work-experience)




# Assist X

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

# visual studio

- 项目结构(base on cmake)：
```bash
cmake.exe -G "Visual Studio 15 2017" -A x64 -DTHIRDPARTY_ROOT_DIR=D:\myDevelop\ThirdParty -DQT_DIR=C:/Qt/Qt5.9.6/5.9.6/msvc2017_64/lib/cmake -S D:\myDevelop\project\kneev2021\src -B D:\myDevelop\build\kneeV2021
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


- [注释/取消注释快捷键  control / ‘ 设置里的（编辑.注释）](https://zhuanlan.zhihu.com/p/343307484)


- vs2015中原生不支持ctrl+单击进入定义，`GoToDef.vsix`插件可满足需求

- [resharper](https://www.jetbrains.com/resharper/)

- [vs中tab换位空格](https://blog.csdn.net/u012308586/article/details/101027542)


- 设置visualstudio默认打开方式为管理员权限：

找到vs安装目录下的：C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe

右键->兼容性疑难解答->疑难解答程序->勾选该程序需要附加权限->测试后下一步->保存设置。

以后甭管双击sln还是快捷方式，都默认使用管理员权限启动vs2017了。

- 没有为此解决方案配置选中要生成的项目：右键项目，查看属性，常规里的配置管理器，勾选上“生成”选项即可



[![top] Goto Top](#table-of-contents)

# cLion

>习惯于VisualStudio开发，故在快捷键模块直接设置成为了：`Visual Studio copy`

- `code`标签页中:Reformate Code,重新整理代码，快捷键：`Ctrl+Alt+Enter`

[![top] Goto Top](#table-of-contents)

# python

## pycharm

- pycharm向左、右缩进快捷键：shift+tab、tab（win）

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

在Windows环境下使用快捷键：`Shift + Alt + F`

在Mac环境下使用快捷键：`Shift + Option + F`

在Ubuntu环境下使用快捷键：`Ctrl + Shift + I`

- `tab替换为空格`：[VSCode烦人的空格处理](https://zhuanlan.zhihu.com/p/343307484)

总之配置如下：
```json
"editor.detectIndentation": false,  //关闭检测第一个tab后面就tab
"editor.renderControlCharacters": true, //制表符显示->
"editor.renderWhitespace": "all", //空格显示...
"editor.tabSize": 4,//tab为四个空格
"editor.insertSpaces": true //转为空格
``` 

- [vscode关闭受限模式（工作区信任），启用调试等功能](https://blog.csdn.net/weixin_45755666/article/details/117877321)：`security.workspace.trust`改为`false`即可



[![top] Goto Top](#table-of-contents)

# Linux

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
- `dynamic`：动态库，`.so`文件,`static`：静态库，`.a`文件
- 接上一条，在win下，`.lib`为静态库，`.dll`为动态库。在`Mac`下，`.a`为静态库`.dylb`动态库，`.Framework`为打包方式，将库的二进制文件打包在一起。

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

- `sudo su`：登录root用户
- `sudo ufw status`：查看端口启用情况
- `sudo ufw allow <端口号>`：开启端口号
- `sudo ufw enable`：开启防火墙
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

- 分辨率调整：`xrandr -s 1280x800_60`(`xrandr`查看分辨率列表，其中60为刷新率...)
- 用户、管理员改为**短密码**：`sudo apt remove libpam-cracklib`(其实在其它Linux上`sudo passwd 用户名`就直接可以完成修改，但是麒麟额外需要卸载掉负责检查密码复杂度的`cracklib`包)

# Data

（局域网，别费劲了你）

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





[![top] Goto Top](#table-of-contents)

# GitAndSVN

## svn
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



## code download

### 环境搭建

1. [git下载](https://git-scm.com/downloads)
2. git安装，一路默认


### SSH Keys生成及添加

1. 右击打开Git Bash，并输入命令    ssh-keygen -t ed25519 -C "pyl@hhrbrobot.com"
2. 回车后，输入设置密码：XXXXXXX
3. 生成文件id_ed25519.pub（默认存放在Git Bash打开所在目录）
4. 输入命令 `cat /c/Users/Administrator/.ssh/id_ed25519.pub`
   或：`cat ~/.ssh/id_ed25519.pub`
5. 网页进入GitLab，点击右上角名字下拉列表，选择【Setting】->【SSH Keys】，将id_ed25519.pub里面的内容全选并粘贴到网页输入框，然后点击按钮【Add key】，至此完成。


### 克隆代码到本地

1. 在本地新建代码目录：D:\gitWorkCode\StatgeVersion，如：（D:\myDevelop\KneeV2021）
2. 在文件夹D:\gitWorkCode\StatgeVersion下，右击选择【Git Bash Here】打开Git Bash命令行窗口
3. 输入git clone git@192.168.102.89:cppdev/kneev2021.git   ，回车后输入正确的用户名及密码。
4. git pull 从服务端拉取代码


## svn

- 在setting里的saved data中，可清理Authentiction Data，清理上一个电脑使用者的数据。
清理完成之后，需要在svn管理员电脑服务端，一般是VisualSVNServer，新建用户，并且在目标项目上右键，权限（或者是属性巴拉巴拉的），把自己的用户名添加进去，否则访问会被拒。

- svn理念和git不同，很是麻烦和落伍，谨记一点就是：修改和提交代码之前，一定要保持代码是最新状态（否则会冲突）

[![top] Goto Top](#table-of-contents)

# dump windows

- 右键我的电脑，管理，服务和应用程序，来查看本地服务（若有自己手动注册或删除服务的需求，则在此观察并操作）

- 开发Windows程序时，win的api报错，如740等，可在vs中查询报错信息，具体在"Tools->Error Lookup"

- `win+shift+s`：截屏快捷键

- 检测本地IP：在cmd中敲：`ipconfig/all`，其中IPv4地址即为本机IP地址（随即敲`arp -a`可显示局域网内IP列表）

- 静态网页局域网访问，百度该关键字即可

[![top] Goto Top](#table-of-contents)


 # myMac

- 安全与隐私中，通用栏，`进入睡眠或开始屏幕保护程序...要求输入密码`，控制时间有利于中途查看代码，减少解锁次数

[![top] Goto Top](#table-of-contents)

# work experience

- 有道词典（开发必备）
下载好离线安装包后，离线包在如下路径：`C:\Users\ISCAS-7\AppData\Local\Yodao\DeskDict\Dictionary`

- happyLogging：
在所需log的地方添加引用:
`#include "D:/myDevelop/happyLogging/loggerFiles/easylogging++.h"`
将`main`函数替换为自己的`main.cpp`
提交代码前可保证代码干净整洁,happy codding~
btw,已经将include指令添加快件进番茄助手，简直不要再香，快捷键为:`#`


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

