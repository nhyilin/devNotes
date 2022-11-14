了解xcode常用快捷键在coding中的使用，很容易摆脱鼠标的拖累，大大提高coding的效率。
***
快速搜索跳转文件
快捷键：cmd + shift + o

这个快捷键的使用频率非常高，是摆脱鼠标的一大利器。

***

快速跳至某行

快捷键：cmd + l

> 常用这个快捷键，首先你要留意一下行号。
> 
> 注意：字母l并不是大写的I，也不是数字1，是大写字母L的小写，l == line。

***

代码块上下移动

快捷键：option + cmd + [(or ])

> 很多时候，你需要将某几行代码交换位子顺序，或者某几行代码前移/后移几行，那么这个快捷键就有了用武之地了。
> 
> 注意：移动前选中你要移动的所有行。
***
.h/.m文件之间快速切换

快捷键：ctrl + cmd + ↑(or ↓)

> ↑(or ↓)效果一样

***

前进/后退

快捷键：ctrl + cmd + ←(or →)

> ←(or →)跟浏览器上一页or下一页类似。

***

显示当前类的方法列表，可搜索

快捷键：ctrl + 6

> 上述快捷键之后，可方向键选择后回车，也可触摸板滑动选择。
> 
> 最重要的是显示列表之后，可直接输入相关字符搜索。

***

搜索、替换

文件类搜索：cmd + f

文件类替换：cmd + option + f

全局搜索：cmd + shift + f

全局替换：cmd + shift + option + f

> 注意：全局搜索替换可以指定目录，也可以选择匹配格式，这个选择在搜索框与替换框之间。
> 
> 文件类与全局都可以在搜索框最前面的🔍位置点击切换搜索/替换。

***

打开Related Items列表

快捷键：ctrl + 1

> 光标停留在相应的关键词中，此快捷键可查看父类，调用者，被调用者，includes，included by等诸多信息。

***

收起/展开代码块

快捷键：option + cmd + ←(or →)

***

在左侧目录中快速定位当前文件位置

快捷键：cmd + shift + j

***

快速切换左边导航栏

快捷键：cmd + 1~8

> 注意：cmd + 0是‘显示/隐藏左侧栏’，cmd + cmd + option + 0是‘显示/隐藏右侧栏’。

***

全局修改局部变量

快捷键：ctrl + cmd + e

> 当你想要将button换一个变量名的时候，这个快捷键绝对能爽死你，当然你也能用鼠标或者触摸板实现这个功能，选中变量名，移动光标会出现一个小箭头，点开会有快捷菜单，选择Edit All in Scope
> 
> 当然还有一些基础的快捷键在这里就不一一列举了，相信大家也都知道，比如，编译(cmd + b)，运行(cmd + r)，clean(cmd + shift + k)，快速移动光标(cmd + 方向键)，快速选择代码(cmd + shift + 方向键)等。
> 
> 值得注意的是，除了上述快捷键之外，右键快捷菜单也是很有用处的，举个栗子：
> 
> 光标置于类名中，右键(或者触摸板两手指头单击)显示快捷菜单，选择Refactor -- Rename，全局替换类名。

***

XVim

最后，我想说的是，想要快捷键运用的炉火纯青，而且不会因为软件间系统间的各种差异出现很大的变化，vim！！

这个绝对是神器，xcode可以安装vim插件XVim。

注意： xcode 8之后，需要先安装证书.

下载下来编译不过的话，是因为类IDEPlaygroundEditor没实现(IDEPlaygroundEditor+XVim.h中)，加上实现@implementation即可，或者直接删除报错的文件以及引用此文件头文件的地方。

XVim快捷键使用见这里。

放出一张vim命令图解：

![vim命令图解](https://robberjj.github.io/imgs/vimCommod.png)

常见快捷键
⌘ + B：编译。
***
⌘ + R：运行。
***
⌘ + U：测试。
***
⌘ + .：停止。
***
⌃ + ⌘ + E：重命名。
***
⌃ + I：代码格式化。
***
⌃ + ⌘ + Click：跳转到点击内容的定义位置。
***
⌥ + ⌘ + /：添加文档注释。
***
⌘ + F：文件内查找。
***
⇧ + ⌘ + F：项目内查找。
***
⇧ + ⌘ + K：清理项目。
***
⌃ + ⌘ + → 和 ⌃ + ⌘ + ←：在最近打开的文件之间来回切换。
***
⌃ + ⌘ + ↑：生成当前文件的 interface。
***
⌘ + ⌥ + [和 ⌘ + ⌥ + ]：对选中代码进行上下移动。
***
⌘ + \：在当前行上添加或删除断点。
***
⌃ + 6：快速查看当前文件的方法列表。
***
⌃ + ⌘ + R：不编译直接运行（与QQ的录屏冲突）。
***

图标说明 

⌃：control

⌘：command

⌥：option

⇧：shift

***


1.Control + 空格：打开Spotlight菜单

2.CMD + [: 左缩进
   CMD + ]: 右缩进
3.CMD + Option +Left: 折叠

   CMD + Option +Right: 取消折叠

   CMD + Option + Shift +Left: 折叠全部函数

   CMD + Option +Shift + Right: 取消全部函数折叠

4.CMD + /: 注释或取消注释

5.CMD + R: 编译并运行

6.CMD + Left：光标移到行首

   CDM + Right：光标移到行尾

   Option + Left：光标移到单词前

   Option + Right：光标移到单词后

   Option + delete：删除当前单词

7.CMD + Control + Left：后退

   CMD + Control + Right：前进

8.CMD + Return：主编辑器

   CMD + Option + Return：辅助编辑器

9.CMD + 0 ：打开/关闭导航栏

   CMD + Option + 0：打开/关闭工具栏

   CMD + Shift + Y：打开/关闭调试窗口

10.Tab：前进到第一个歧义点

11.Control + Left/Right 切换屏幕   

12.Control + Shift + 点击视图：选择重叠视图中的一个

13.Ctrl + F ：前移光标
   Ctrl + B ：后移光标
   Ctrl + P ：移动光标到上一行
   Ctrl + N：移动光标到下一行
   Ctrl + A : 移动光标到本行行首
   Ctrl + E : 移动光标到本行行尾

   Ctrl + T ：交换光标左右两边的字符
   Ctrl + D：删除光标右边的字符
   Ctrl + K ：删除本行光标右边的所有字符
   Ctrl + L : 将插入点置于窗口正中

14.CMD + Shift + F：搜索导航器:Command+Shift+F

15.CMD + Shift + O：快速打开(输入首字母就可以)

16.CMD + Shift + J：展示当前你在工程导航器


[比较全的一个资料](https://codeantenna.com/a/ecI5GJWXdS)