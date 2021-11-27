# Table of Contents
<pre>
<a href="#November">November</a>
    <a href="#2021-11-26">2021-11-26</a>
    <a href="#2021-11-25">2021-11-25</a>
    <a href="#2021-11-24">2021-11-24</a>
    <a href="#2021-11-22">2021-11-22</a>
weekend
    <a href="#2021-11-17">2021-11-17</a>
    <a href="#2021-11-16">2021-11-16</a>
weekend
    <a href="#2021-11-16">2021-11-16</a>
    <a href="#2021-11-15">2021-11-15</a>
weekend
    <a href="#2021-11-12">2021-11-12</a>
    <a href="#2021-11-11">2021-11-11</a>
    <a href="#2021-11-10">2021-11-10</a>
    <a href="#2021-11-09">2021-11-09</a>
    <a href="#2021-11-08">2021-11-08</a>
weekend
    <a href="#2021-11-05">2021-11-05</a>
    <a href="#2021-11-04">2021-11-04</a>
    <a href="#2021-11-03">2021-11-03</a>
    <a href="#2021-11-02">2021-11-02</a>
    <a href="#2021-11-01">2021-11-01</a>
<a href="#October">October</a>
weekend
    <a href="#2021-10-27">2021-10-27</a>
    <a href="#2021-10-26">2021-10-26</a>
    <a href="#2021-10-25">2021-10-25</a>
weekend
    <a href="#2021-10-22">2021-10-22</a>
    <a href="#2021-10-21">2021-10-21</a>
    <a href="#2021-10-20">2021-10-20</a>
    <a href="#2021-10-19">2021-10-19</a>
    <a href="#2021-10-18">2021-10-18</a>
weekend
    <a href="#2021-10-15">2021-10-15</a>
    <a href="#2021-10-14">2021-10-14</a>
    <a href="#2021-10-13">2021-10-13</a>
weekend
    <a href="#2021-10-08">2021-10-08</a>
</pre>


2021工作记录
<!--more-->

# November
# 2021-11-26
主要任务：在Linux平台测试fastDDS库的可用性
进展：完成了在Windows系统visual studio平台下helloworld的测试
剩余部分：仍需对Windows以及Linux系统的QtCreator平台进行针对fastDDS库的测试

遇到困难：
用QtCreator导入、创建工程时，工程无法正常跑起来。

拟解决方案：
1. 周末在自家电脑上进行测试，排除qt版本差异的可能性
2. 查阅相关报错，再一一进行解决
3. 更换其他helloworld程序进行测试

[![top] Goto Top](#table-of-contents)

# 2021-11-25

遇到困难：
编译SimNode、SimCentre节点静态库仍存在问题，问题如下：
- /usr/bin/ld: 找不到 -l./../../install/lib/libfastrtps.so.2.3.0。已尝试重新编译dds，dds编译没有问题，但无法奏效。尝试检查qmakelist中lib语法，语法正确但无法奏效。计划再多搜索相关资料，找其他解决方法
- SimCentre用的qt模板为core gui widgets winextras concurrent，模块为Windows拓展模块难以移植到Linux。拟将模块换位core gui widget再尝试编译


计划：
1. 尽早完成软件在麒麟下的编译

遇到困难：
- 这几个库分别是做什么用的，具体编译时用哪个？
- 为什么总是提示找不到，需要添加环境变量吗，install目录是否需要，还是本地安装完就行了，那pro文件还需要引用吗

[![top] Goto Top](#table-of-contents)

## 2021-11-24
完成：
1. fast dds动态库编译
2. SimDDS动态库编译

待完成：
1. SimNode编译
2. SimCentre编译

遇到问题：
1. SimNode编译过程中出现很多报错，以及lib库无法链接问题

拟解决方案：
1. 核对qmakelist中lib语法
2. 检查lib库是否正确
3. 检查SimDDS库编译是否正确
4. 重装qt5.12以避免无谓error
5. 尝试用cmake替换qmake重新构建



未来：
- `dds.tastID = settings->value("tastID").toString().toStdString();//TODO:会不会转换出错`

[![top] Goto Top](#table-of-contents)

## 2021-11-22
完成：
1. 编译fast-dds三方库（基于麒麟系统）

[![top] Goto Top](#table-of-contents)

## 2021-11-17

计划：
1. 时间demo
2. fast dds

[![top] Goto Top](#table-of-contents)

## 2021-11-16
计划：
1. 时间demo
2. 更新网易词典
3. fast dds
   1. win
   2. Linux


未来：
- setupUI放在那里比较合适，以及何时delete
- void timerEvent(QTimerEvent*) override;
- explicit
- explicit render(QWindow *parent =0),这里含义
- QBackingStore* m_backingStore;
- void RasterWindow::exposeEvent(QExposeEvent *)含义
- .pri文件`INCLUDEPATH+ = $$PWD`、`SOURCES += $$PWD/rasterwindow.cpp`、`HEADERS += $$PWD/rasterwindow.h`

[![top] Goto Top](#table-of-contents)

## 2021-11-16
计划：
1. fast dds初步掌握建立demo
    - readme和word中查询资料，搭建环境，可以运行简单的示例程序
    - 在示例程序基础上进行小幅调整，多台机器上进行协同控制（收发信息即可）
2. 计算时间demo

[![top] Goto Top](#table-of-contents)


## 2021-11-15
计划：
1. 计算时间的demo

[![top] Goto Top](#table-of-contents)

## 2021-11-12

计划：
1. 银河麒麟系统测试发布
2. 搭建`fast dds`

完成：
- 麒麟系统发布完成
- 打印材料等琐事

[![top] Goto Top](#table-of-contents)

## 2021-11-11

计划：
1. 测试麒麟系统可用性
2. 发布Linux
3. c++、qt代码整理

完成：
- 测试麒麟
- dotnet路径：`/usr/local/dotnet`
- Ubuntu完成发布

[![top] Goto Top](#table-of-contents)

## 2021-11-10

计划：
1. 发布Linux

[![top] Goto Top](#table-of-contents)

## 2021-11-09

完成：
- 静态网页发布

[![top] Goto Top](#table-of-contents)

## 2021-11-08

计划：
1. 完成静态网页发布
2. .net core后端程序开发

已完成：
- 本机ip信息：192.168.0.12，马明192.168.0.55
- 完成静态网页发布


```bash
Internet 地址         物理地址              类型
192.168.0.1           6c-0b-84-43-7b-56     动态
192.168.0.3           6c-0b-84-69-a1-ab     动态
192.168.0.8           6c-0b-84-e2-95-bb     动态
192.168.0.9           6c-0b-84-43-78-a9     动态
192.168.0.10          30-9c-23-77-7a-7f     动态
192.168.0.55          6c-0b-84-43-7b-0f     动态
192.168.0.100         2c-f0-5d-4b-b3-08     动态
192.168.0.150         30-9c-23-76-04-7b     动态
192.168.0.161         f4-93-9f-ec-51-81     动态
192.168.0.255         ff-ff-ff-ff-ff-ff     静态
224.0.0.22            01-00-5e-00-00-16     静态
224.0.0.251           01-00-5e-00-00-fb     静态
224.0.0.252           01-00-5e-00-00-fc     静态
239.255.0.1           01-00-5e-7f-00-01     静态
239.255.255.250       01-00-5e-7f-ff-fa     静态
255.255.255.255       ff-ff-ff-ff-ff-ff     静态
```
[![top] Goto Top](#table-of-contents)

## 2021-11-05


计划：
1. 协助马明看后端代码
    - vs2017以上
    - 基于c# 的.net core开发
    - 跨平台
    - ql bs 控制界面，浏览器控制界面，控制后端dds操作

未来：
- `#include "qcustomplot.h"`编译报错，是否真的需要这个头文件？

[![top] Goto Top](#table-of-contents)

## 2021-11-04

整理文献
阅读代码，马明手上的任务

[![top] Goto Top](#table-of-contents)

## 2021-11-03
整理文献

[![top] Goto Top](#table-of-contents)

## 2021-11-01

整理文献

[![top] Goto Top](#table-of-contents)

## 2021-11-01
周计划：
1. 暂未分配具体任务
2. 拟和庄老师或朱老师交流培养方向

计划：


完成：
- 文档整理，基于空间任务的卫星平台仿真研究的硕士论文

[![top] Goto Top](#table-of-contents)


# October

## 2021-10-27

任务：
1. 赵博

完成：

未来：
- `void myWidget::timerEvent(QTimerEvent *e)`括号里的参数是什么含义
- cmake文件格式


## 2021-10-26

完成：
1. `#pragma execution_character_set("utf-8")`，Qt程序支持中文


未来：
1. 虚析构函数
2. 内联
3. `QMenuBar *mBar = menuBar();`这种写法是什么含义，声明指针变量
4. qt可视化工具

## 2021-10-25

1. 隐藏功能函数撰写
    - 将默认值写入
    - 找到合适的调用位置

    - 找到选中的卫星
    - `UIData::IsEmpty()`来判断是否创建场景
    - `if(UIData::GetSelectedNode() == NULL)`判断是否选中父节点
    - `if (UIData::GetSelectedNode()->GetObjectType() != ObjectType_ObjectClassification && UIData::GetSelectedNode()->GetObjectType() != ObjectType_Scene)`判断是否选中正确节点
2. Qt课程
3. 功能完善：默认选择父节点

完成：
1. ui找到对应ui文件，然后`ui.`或`ui->`设置相关系数，如`ui->lineEdit_Name->setMaxLength(2);`

未来：
1. QLineEdit如何设置默认字符串 
2. 错误	C2679	二进制“<<”: 没有找到接受“const QString”类型的右操作数的运算符(或没有可接受的转换)
3. 点击地球，经纬度代码阅读



[![top] Goto Top](#table-of-contents)



## 2021-10-22

1. svn的gitIgnore功能
2. 撰写隐藏卫星以及轨道函数，位于`QSTKEarth.cpp`中
3. 了解各个模块在代码中所处位置
4. 如果this写在成员函数中，那么this指的是什么呢

完成：
- Form Files中包含所有ui文件，找空间时提供思路
- 信号是没有返回值的，所以槽函数一定没有返回值
- 信号就是函数的声明，只需声明无需定义，使用：`emit mySignal()`

[![top] Goto Top](#table-of-contents)

## 2021-10-21

1. 撰写隐藏卫星以及轨道函数，位于`QSTKEarth.cpp`中
    - 只需实现功能
    - 尽早完成
2. vs英文插件


完成：
1. `winnewscene.cpp`内包含了小的弹窗的信息，未来为了方便调试，可将默认参数写入,其实在qtdesigner里能看到很多信息，好像还真的是designer里更简单些
2. designer里的fn键（多按几下），拉动可看出代码里看不到的槽函数

未来：
1. emit是什么作用 
2. extern什么作用
3. 如何引用dll库
4. ui控制的qt程序，不太会查看相关变量
5. md文件
6. tbb_vc140.lib

[![top] Goto Top](#table-of-contents)

## 2021-10-20

1. 撰写隐藏卫星以及轨道函数，位于`QSTKEarth.cpp`中
    - 1.1 需求分析，无需要求格式，只需实现功能即可
2. bugFixed：没有卫星时新建星座导致崩溃solution：弹出提示框提示新建卫星
3. 是否可离线使用git
4. SetVisibility、Visible


完成：
1. bugFixed：没有卫星时新建星座导致崩溃solution：弹出提示框提示新建卫星
2. 番茄助手配合logging++
3. 新建svn账户

未来：
1. 希望整合cmake，需求是修改代码过程中只碰源代码，不碰其他
    - cmakelist
    - cmake脚本命令

[![top] Goto Top](#table-of-contents)

## 2021-10-19

1. stk内容，查阅手册，以达到可进行测试，或可完成某一项任务（如：增添、删除卫星，地基）的功能函数
2. 添加相应的log库，目前计划easylogging（完成本地测试）
3. 隐藏卫星以及轨道，cstk隐藏（api）
4. 拟写脚本，为方便开发，阻止开发过程中修改过多文件，来建立沙盒机制
5. tab转空格插件

关于3：


完成：
1. 将easylogging++加入（main.cpp中）



```cpp
#include "stdafx.h"
#include <iostream>
//两个的区别是？
```


[![top] Goto Top](#table-of-contents)

## 2021-10-18

1. 周一早会：
    - 1.1 感触发现需要提前整理思路和语言，哪怕提前五分钟想想理理思路，看看上周工作记录
    - 1.2 本周工作重点：和马明，协同赵博、庞志萍学姐进行“系统开发”，基于项目CECA，主要任务是熟悉stk

2. 找接口

[![top] Goto Top](#table-of-contents)

## 2021-10-15

1. 整理电脑开发环境
    - 1.1 目前把冗杂的文件（包含上一位程序员留下的垃圾文档）整理到一起，仍将d作为开发磁盘，myDevelop作为开发目录，myDevelop内分别放置build、sourceCode、thirdPart,代码结构尚待时日整理，为防止上传svn时传递过多无用信息，以及sln和Sourcecode混在一起，希望将项目设为从cmake构建
    - 1.2 文件目录放置e盘，其中包括笔记以及开发所用软件等杂乱文件

2. 重装vs，环境过于复杂。btw：vs2015的control+ 单击不能转到定义，通过vs插件商店GoToDef.vsix，可实现

3. 重装Visual Assist X。版本为“2420_0”,放置于：E:\devSoft\VisualAssistX_10.9.2420_0_Cracked

[![top] Goto Top](#table-of-contents)

待解决：

1. ._.DS_Store文件、._devingNote文件、._Q&A.md（隐藏文件）的生成(完成)

[![top] Goto Top](#table-of-contents)

## 2021-10-14

领导来所里验收十三五的收官项目

[![top] Goto Top](#table-of-contents)


# 2021-10-13

- [x]上午完成准备汇报工作

下午完成添加log

[![top] Goto Top](#table-of-contents)

## 2021-10-08

办理入职手续

[![top] Goto Top](#table-of-contents)


# things

OA服务器移动端地址https://159.226.29.1:89
新入职的员工请注意一下，OA的登录名是本人名字的全拼，密码是123456
第一次登录要改密码，请在电脑上改，https://159.226.29.1:80

1. 苹果手机直接在appstore里搜索emobile即可
2. 安卓用这个链接的第一个二维码https://emobile.weaver.com.cn/customer/azzj/produce.jsp
3. pc端没有客户端，登陆OA在地址栏输入：https://159.226.29.1:80

[![top] Goto Top](#table-of-contents)

# 项目配置

CECA：加载pro文件，配置为win32项目，qt设置为qt2015（非qt2015_64)

---

ISCAS属性配置：
1. 常规中的字符集改为`使用多字节字符集`
2. c/c++中常规的调试信息格式改为`程序数据库`
3. c/c++优化：禁用
4. 预编译头文件：`stable.h`
5. 链接器：调试中的生成调试信息设为`优化以便于调试（注意debug以及release）`






[![top] Goto Top](#table-of-contents)

[top]: up.png

