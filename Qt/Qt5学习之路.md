# Table of Contents
- [Table of Contents](#table-of-contents)
- [1. 序](#1-序)
- [2. QT 简介](#2-qt-简介)
- [3. HELLO, WORLD!](#3-hello-world)
- [4. 信号槽](#4-信号槽)


# 1. 序

继[c++笔记](./info/cpp/ChernoCPP.md)后第二份系统学习笔记。本文绝大部分摘自[DevBean's](https://www.devbean.net/)，完全自用笔记，无商业行为。

[![top] Goto Top](#table-of-contents)


# 2. QT 简介

Qt 是一个著名的 C++ 应用程序框架。你并不能说它只是一个 GUI 库，因为 Qt 十分庞大，并不仅仅是 GUI 组件。使用 Qt，在一定程度上你获得的是一个“一站式”的解决方案：不再需要研究 STL，不再需要 C++ 的<string>，不再需要到处去找解析 XML、连接数据库、访问网络的各种第三方库，因为 Qt 自己内置了这些技术。

Qt 是一个跨平台的框架。跨平台 GUI 通常有三种实现策略：

1. **API 映射**：API 映射是说，界面库使用同一套 API，将其映射到不同的底层平台上面。大体相当于将不同平台的 API 提取公共部分。比如说，将 Windows 平台上的按钮控件和 Mac OS 上的按钮组件都取名为 Button。当你使用 Button 时，如果在 Windows 平台上，则编译成按钮控件；如果在 Mac OS 上，则编译成按钮组件。这么做的好处是，所有组件都是原始平台自有的，外观和原生平台一致；缺点是，编写库代码的时候需要大量工作用于适配不同平台，并且，只能提取相同部分的 API。比如 Mac OS 的文本框自带拼写检测，但是 Windows 上面没有，则不能提供该功能。这种策略的典型代表是 wxWidgets。这也是一个标准的 C++ 库，和 Qt 一样庞大。它的语法看上去和 MFC 类似，有大量的宏。据说，一个 MFC 程序员可以很容易的转换到 wxWidgets 上面来。

2. **API 模拟**：前面提到，API 映射会“缺失”不同平台的特定功能，而 API 模拟则是解决这一问题。不同平台的有差异 API，将使用工具库自己的代码用于模拟出来。按照前面的例子，Mac OS 上的文本框有拼写检测，但是 Windows 的没有。那么，工具库自己提供一个拼写检测算法，让 Windows 的文本框也有相同的功能。API 模拟的典型代表是 wine —— 一个 Linux 上面的 Windows 模拟器。它将大部分 Win32 API 在 Linux 上面模拟了出来，让 Linux 可以通过 wine 运行 Windows 程序。由此可以看出，API 模拟最大优点是，应用程序无需重新编译，即可运行到特定平台上。另外一个例子是微软提供的 DirectX，这个开发库将屏蔽掉不同显卡硬件所提供的具体功能。使用这个库，你无需担心硬件之间的差异，如果有的显卡没有提供该种功能，SDK 会使用软件的方式加以实现。*（关于举例，可以参考文末一段精彩的讨论。）*

3. **GUI 模拟**：任何平台都提供了图形绘制函数，例如画点、画线、画面等。有些工具库利用这些基本函数，在不同绘制出自己的组件，这就是 GUI 模拟。GUI 模拟的工作量无疑是很大的，因为需要使用最基本的绘图函数将所有组件画出来；并且这种绘制很难保证和原生组件一模一样。但是，这一代价带来的优势是，可以很方便的修改组件的外观——只要修改组件绘制函数即可。很多跨平台的 GUI 库都是使用的这种策略，例如 gtk+（这是一个 C 语言的图形界面库。使用 C 语言很优雅地实现了面向对象程序设计。不过，这也同样带来了一个问题——使用大量的类型转换的宏来模拟多态，并且它的函数名一般都比较长，使用下划线分割单词，看上去和 Linux 如出一辙。gtk+ 并不是模拟的原生界面，而有它自己的风格，所以有时候就会和操作系统的界面格格不入。），Swing 以及我们的 Qt。

Qt 和 wxWidgets 一样，也是一个标准的 C++ 库。但是它的语法类似于 Java 的 Swing，十分清晰，而且使用信号槽（signal/slot）机制，让程序看起来很明白——这也是很多人优先选择 Qt 的一个很重要的原因。不过，所谓“成也萧何，败也萧何”。这种机制虽然很清楚，但是它所带来的后果是你需要使用 Qt 的 moc 对程序进行预处理，才能够再使用标准的 make 或者 nmake 进行正常的编译，并且信号槽的调用要比普通的函数调用慢大约一个数量级（Qt 4 文档中说明该数据，但 Qt 5 尚未有官方说明）。Qt 的界面也不是原生风格的，尽管 Qt 使用 style 机制十分巧妙地模拟了原生界面。另外值得一提的是，Qt 不仅仅能够运行在桌面环境中，还可以运行在嵌入式平台以及手机平台。

Qt 第一版于 1991 年由 Trolltech （奇趣科技）发布。后来在 2008 年，Nokia 斥资 1.5 亿美元收购 TrollTech，将 Qt 应用于 Symbian 程序开发。2012 年 8 月 9 日，Nokia 将 Qt 以 400 万欧元的价格出售给 Digia。

伴随着 Qt，一直有两种授权协议：商业授权以及开源授权。在 Qt 的早期版本，商业授权包含一些开源授权不提供的组件，但是在近期版本则不存在这个问题。以往人们对 Qt 的开源授权多有诟病。早期版本的 Qt 使用与 GPL 不兼容的协议授权，这直接导致了 KDE 与 GNOME 的战争（由于 Linux 使用 GPL 协议发布，GPL 协议具有传染性，作为 Linux 桌面环境的 KDE 却是基于与 GPL 不兼容的 Qt 开发，这就不遵守 GPL 协议）。不过，现在 Qt 的开源版本使用的是 GPLv3 以及 LGPL 协议。这意味着，你可以将 Qt 作为一个库连接到一个闭源软件里面。可以说，Qt 协议的争议已经不存在了。

[![top] Goto Top](#table-of-contents)


# 3. HELLO, WORLD!

想要学习 Qt 开发，首先要搭建 Qt 开发环境。好在现在搭建 Qt 开发环境还是比较简单的。我们可以到 Qt 官方网站找到最新版本的 Qt。在 Downloads 页面，可以看到有几个版本的 Qt：Qt SDK、Qt Library、Qt Creator 等等。它们分别是：

- Qt SDK：包含了 Qt 库以及 Qt 的开发工具（IDE、i18n 等工具），是一套完整的开发环境。当然，这个的体积也是最大的（Windows 平台大约 1.7G，其它平台大约 780M）。如果仅仅为开发 Qt，建议选择这一项下载安装。安装方法很简单，同普通程序没有什么区别。所需注意的是，安装过程中可能能够提供选择是否安装源代码，是否安装 mingw 编译器（Windows），这个就按照需要进行选择即可。另外值得说明的是，Qt SDK 通常比单独的 Qt 库版本要旧一些。比如现在 Qt 正式版是 4.8.2，但是 Qt SDK 的最新版 1.2.1 中包含的 Qt 是 4.8.1。
- Qt Library：仅包含 Qt 库。如果您已经安装了 Qt 开发环境，为了升级一下 SDK 中提供的 Qt 库版本，就可以安装这一个。安装过之后，应该需要在 IDE 中配置安装路径，以便找到最新版本的 Qt（如果不是覆盖安装的话）。
- Qt Creator：基于 Qt 构建的一个轻量级 IDE，现在最新版是 2.5.2，还是比较好用的，建议使用 Qt Creator 进行开发。当然，如果你已经习惯了 VS2010 这样的工具，可以在页面最下方找到相应的 Addin。很多朋友希望阅读 Qt 代码以提高自己的开发水平。当然，Qt 的经典代码是 KDE，不过这个项目不大适合初学者阅读。此时，我们就可以选择阅读 Qt Creator 的代码，它的代码还是比较清晰的。
当我们安装完成 Qt 开发环境之后，就可以使用 Qt Creator 进行开发。在本系列中，豆子会一直使用这个 IDE 进行讲解。至于编译器，豆子一般会使用 mingw 或者 gcc。为了编译 Qt 5 的程序，你应该使用 gcc 4.5 以上的版本，这意味着，如果你是使用 Qt SDK 自带的 mingw，是不能编译 Qt 5 的程序的（因为这个自带的版本是 4.4），你应该升级 mingw 为 4.5 以上版本。

至此，我们已经有了 Qt 4 的完整开发环境。如果你想要开发 Qt 5，由于现在（2012 年 8 月） Qt 5 还处于测试阶段，并没有提供二进制库，所以我们需要使用 git 自己获取 Qt 5 的源代码自己编译（一般需要几个小时时间）。豆子非常不建议在 Windows 上编译 Qt 5，因为可能会出很多问题。如果你想尝试，可以参考这里。豆子提一句，在 Windows 上编译 Qt 5，需要安装 perl（并且要安装 GetOpt::Long 模块）、python 和 git，并且需要找到彼此路径。相比而言，Linux 上面就会简单很多。豆子建议，如果你想在 Windows 上尝试 Qt 5，可以考虑安装一个虚拟机，使用 Linux 平台；或者自己试着直接在 Windows 本地编译。豆子的环境是使用 openSUSE。openSUSE 的 Qt 5.0 Development Snapshots 已经提供了 Qt 5 二进制版本，免去了编译的过程。*基于此，本文的 Qt 4 版本将在 Windows 平台上使用 mingw 进行测试；Qt 5 版本将在 openSUSE 上使用 gcc 4.6 进行测试。在未来官方推出 Qt 5 Windows 平台的二进制版本，也不排除在 Windows 上面测试 Qt 5 代码。*

在 Qt Creator 中，我们可以在菜单栏的工具-选项-构建和运行的“Qt 版本”和“工具链”这两个选项卡中配置 Qt Creator 所使用的 Qt 版本和编译器。这或许是最重要的步骤，包括添加新的 Qt 版本以及以后的切换编译器或者 Qt 升级等。

下面尝试开发第一个 Qt 项目：HelloWorld。在 Qt Creator 中新建一个工程：

Qt Creator 新建工程
点击这个“新建文件或工程”，在左侧选择项目-Applications，中间选择 Qt Gui 应用，然后点击“选择...”：

Qt Creator GUI 工程
在弹出的对话框中填写名称、创建路径等信息：

Qt Creator 工程名字及位置
点击“下一步”，选择该工程的编译器。这里我们只选择 mingw 调试即可（在以后的项目中，根据自己的需要选择。）Shadow Build 的含义是“影子构建”，即将构建生成的文件不放在源代码文件夹下。这样可以最大地保持源代码文件夹的整洁。

Qt Creator 编译器选择
点击“下一步”，可以选择生成的主窗口文件。不过在我们的简单示例中是不需要这么复杂的窗口的，因此我们尽可能简单地选择，将“创建界面”的选择去除：

Qt Creator MainWindow
终于到了最后一步。这里是在询问我们是否添加版本控制。对于我们的小项目当然是不需要的，所以选择“无”，然后点击“完成”即可：

Qt Creator 版本管理
可以看到，Qt Creator 帮助我们在 HelloWorld 项目文件夹下生成了四个文件：main.cpp，mainwindow.cpp，mainwindow.h 和 HelloWorld.pro。pro 文件就是 Qt 工程文件（project file），由 qmake 处理，生成 make 程序所需要的 makefile；main.cpp 里面就是一个main函数，作为应用程序的入口函数；其他两个文件就是先前我们曾经指定的文件名的文件。

我们将 main.cpp 修改如下：

```cpp
#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel label("Hello, world");
    label.show();
    return app.exec();
}
```

点击 Qt Creater 左侧下面的绿色三角按钮即可运行（这里一共有三个按钮，从上到下分别是“运行”、“调试”和“构建”）。如果没有错误的话，就会看到运行结果：

Qt HelloWorld 程序运行结果
这个程序有这么几行。我们解释一下。

前两行是 C++ 的 `include` 语句，这里我们引入的是`QApplication`以及`QLabel`这两个类。`main()`函数中第一句是创建一个`QApplication`类的实例。对于 Qt 程序来说，`main()`函数一般以创建 `application` 对象（`GUI` 程序是`QApplication`，非 GUI 程序是`QCoreApplication`。`QApplication`实际上是`QCoreApplication`的子类。）开始，后面才是实际业务的代码。这个对象用于管理 Qt 程序的生命周期，开启事件循环，这一切都是必不可少的。在我们创建了`QApplication`对象之后，直接创建一个`QLabel`对象，构造函数赋值`“Hello, world”`，当然就是能够在`QLabel`上面显示这行文本。最后调用`QLabel`的`show()`函数将其显示出来。`main()`函数最后，调用`app.exec()`，开启事件循环。我们现在可以简单地将事件循环理解成一段无限循环。正因为如此，我们在栈上构建了`QLabel`对象，却能够一直显示在那里（试想，如果不是无限循环，`main()`函数立刻会退出，`QLabel`对象当然也就直接析构了）。

示例程序我们已经讲解完毕。下面再说一点。我们可以将上面的程序改写成下面的代码吗？

```cpp
#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *label = new QLabel("Hello, world");
    label->show();
    return app.exec();
}
```
答案是，不~~可以~~建议这样做！

首先，按照标准 C++ 来看这段程序。这里存在着内存泄露。当`exec()`退出时（也就是事件循环结束的时候。窗口关闭，事件循环就会结束），`label` 是没办法 `delete` 的。这就造成了内存泄露。当然，由于程序结束，操作系统会负责回收内存，所以这个问题不会很严重。即便你这样修改了代码再运行，也不会有任何错误。

早期版本的 Qt 可能会有问题（详见本文最后带有删除线的部分，不过豆子也没有测试，只是看到有文章这样介绍），不过在新版本的 Qt 基本不存在问题。在新版本的 Qt 中，`app.exec()`的实现机制确定，当最后一个可视组件关闭之后，主事件循环（也就是`app.exec()`）才会退出，`main()`函数结束（此时会销毁app）。这意味着，所有可视元素已经都关闭了，也就不存在后文提到的，`QPaintDevice`没有`QApplication`实例这种情况。另外，如果你是显式关闭了`QApplication`实例，例如调用了`qApp->quit()`之类的函数，`QApplication`的最后一个动作将会是关闭所有窗口。所以，即便在这种情况下，也不会出现类这种问题。由于是在`main()`函数中，当main()函数结束时，操作系统会回收进程所占用的资源，相当于没有内存泄露。不过，这里有一个潜在的问题：操作系统只会粗暴地释放掉所占内存，并不会调用对象的析构函数（这与调用`delete`运算符是不同的），所以，很有可能有些资源占用不会被“正确”释放。事实上，在最新版的 `Sailfish OS` 上面就有这样的代码：

```cpp
#include <QApplication>
int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(new QApplication(argc, argv));
    QScopedPointer<QQuickView> view(new QQuickView);
    view->setSource("/path/to/main.qml");
    ...
    return app->exec();
}
```

这段代码不仅在堆上创建组件实例，更是把`QApplication`本身创建在了堆上。不过，注意，它使用了智能指针，因此我们不需要考虑操作系统直接释放内存导致的资源占用的问题。

当然，允许使用并不一定意味着我们建议这样使用。毕竟，这是种不好的用法（就像我们不推荐利用异常控制业务逻辑一样），因为存在内存泄露。而且对程序维护者也是不好的。所以，我们还是推荐在栈上创建组件。因为要靠人工管理`new`和`delete`的出错概率要远大于在栈上的自动控制。除此之外，在堆上和在栈上创建已经没有任何区别。

如果你必须在堆上创建对象，不妨增加一句：

`label->setAttribute(Qt::WA_DeleteOnClose);`

这点提示足够告诉程序维护者，你已经考虑到内存问题了。

~~严重的是，`label` 是建立在堆上的，`app` 是建立在栈上的。这意味着，`label` 会在 `app` 之后析构。也就是说，`label` 的生命周期长于 `app` 的生命周期。这可是 Qt 编程的大忌。因为在 Qt 中，所有的`QPaintDevice`必须要在有`QApplication`实例的情况下创建和使用。大家好奇的话，可以提一句，`QLabel`继承自`QWidget`，`QWidget`则是`QPaintDevice`的子类。之所以上面的代码不会有问题，是因为 app 退出时，`label` 已经关闭，这样的话，`label` 的所有`QPaintDevice`一般都不会被访问到了。但是，如果我们的程序，在 `app` 退出时，组件却没有关闭，这就会造成程序崩溃。（如果你想知道，怎样做才能让 `app` 退出时，组件却不退出，那么豆子可以告诉你，当你的程序在打开了一个网页的下拉框时关闭窗口，你的程序就会崩溃了！）~~

[![top] Goto Top](#table-of-contents)



# 4. 信号槽

信号槽是 Qt 框架引以为豪的机制之一。熟练使用和理解信号槽，能够设计出解耦的非常漂亮的程序，有利于增强我们的技术设计能力。

所谓信号槽，实际就是观察者模式。当某个事件发生之后，比如，按钮检测到自己被点击了一下，它就会发出一个信号（signal）。这种发出是没有目的的，类似广播。如果有对象对这个信号感兴趣，它就会使用连接（connect）函数，意思是，用自己的一个函数（成为槽（slot））来处理这个信号。也就是说，当信号发出时，被连接的槽函数会自动被回调。这就类似观察者模式：当发生了感兴趣的事件，某一个操作就会被自动触发。*（这里提一句，Qt 的信号槽使用了额外的处理来实现，并不是 GoF 经典的观察者模式的实现方式。）*

为了体验一下信号槽的使用，我们以一段简单的代码说明：

```cpp
// !!! Qt 5
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Quit");
    QObject::connect(&button, &QPushButton::clicked, &QApplication::quit);
    button.show();

    return app.exec();
}
```

这里再次强调，我们的代码是以 Qt 5 为主线，这意味着，有的代码放在 Qt 4 上是不能编译的。因此，豆子会在每一段代码的第一行添加注释，用以表明该段代码是使用 Qt 5 还是 Qt 4 进行编译。读者在测试代码的时候，需要自行选择相应的 Qt 版本。

我们按照前面文章中介绍的在 Qt Creator 中创建工程的方法创建好工程，然后将`main()`函数修改为上面的代码。点击运行，我们会看到一个按钮，上面有“Quit”字样。点击按钮，程序退出。

按钮在 Qt 中被称为`QPushButton`。对它的创建和显示，同前文类似，这里不做过多的讲解。我们这里要仔细分析`QObject::connect()`这个函数。

在 Qt 5 中，`QObject::connect()`有五个重载：
```cpp
QMetaObject::Connection connect(const QObject *, const char *,
                                const QObject *, const char *,
                                Qt::ConnectionType);

QMetaObject::Connection connect(const QObject *, const QMetaMethod &,
                                const QObject *, const QMetaMethod &,
                                Qt::ConnectionType);

QMetaObject::Connection connect(const QObject *, const char *,
                                const char *,
                                Qt::ConnectionType) const;

QMetaObject::Connection connect(const QObject *, PointerToMemberFunction,
                                const QObject *, PointerToMemberFunction,
                                Qt::ConnectionType)

QMetaObject::Connection connect(const QObject *, PointerToMemberFunction,
                                Functor);
```
这五个重载的返回值都是`QMetaObject::Connection`，现在我们不去关心这个返回值。下面我们先来看看`connect()`函数最常用的一般形式：

```cpp
// !!! Qt 5
connect(sender,   signal,
        receiver, slot);
```
这是我们最常用的形式。`connect()`一般会使用前面四个参数，第一个是发出信号的对象，第二个是发送对象发出的信号，第三个是接收信号的对象，第四个是接收对象在接收到信号之后所需要调用的函数。也就是说，当 sender 发出了 signal 信号之后，会自动调用 receiver 的 slot 函数。

这是最常用的形式，我们可以套用这个形式去分析上面给出的五个重载。第一个，sender 类型是`const QObject *`，signal 的类型是`const char *`，receiver 类型是`const QObject *`，slot 类型是`const char *`。这个函数将 signal 和 slot 作为字符串处理。第二个，sender 和 receiver 同样是`const QObject *`，但是 signal 和 slot 都是`const QMetaMethod &`。我们可以将每个函数看做是`QMetaMethod`的子类。因此，这种写法可以使用`QMetaMethod`进行类型比对。第三个，sender 同样是`const QObject *`，signal 和 slot 同样是`const char *`，但是却缺少了 receiver。这个函数其实是将 `this` 指针作为 receiver。第四个，sender 和 receiver 也都存在，都是`const QObject *`，但是 signal 和 slot 类型则是`PointerToMemberFunction`。看这个名字就应该知道，这是指向成员函数的指针。第五个，前面两个参数没有什么不同，最后一个参数是`Functor`类型。这个类型可以接受 `static` 函数、全局函数以及 `Lambda` 表达式。

由此我们可以看出，`connect()`函数，sender 和 receiver 没有什么区别，都是`QObject`指针；主要是 signal 和 slot 形式的区别。具体到我们的示例，我们的`connect()`函数显然是使用的第五个重载，最后一个参数是`QApplication`的 `static` 函数`quit()`。也就是说，当我们的 `button` 发出了`clicked()`信号时，会调用`QApplication`的`quit()`函数，使程序退出。

信号槽要求信号和槽的参数一致，所谓一致，是参数类型一致。如果不一致，允许的情况是，槽函数的参数可以比信号的少，即便如此，槽函数存在的那些参数的顺序也必须和信号的前面几个一致起来。这是因为，你可以在槽函数中选择忽略信号传来的数据（也就是槽函数的参数比信号的少），但是不能说信号根本没有这个数据，你就要在槽函数中使用（就是槽函数的参数比信号的多，这是不允许的）。

如果信号槽不符合，或者根本找不到这个信号或者槽函数的话，比如我们改成：
`QObject::connect(&button, &QPushButton::clicked, &QApplication::quit2);`

由于 QApplication 没有 quit2 这样的函数的，因此在编译时，会有编译错误：
`'quit2' is not a member of QApplication`

这样，使用成员函数指针，我们就不会担心在编写信号槽的时候会出现函数错误。

借助 Qt 5 的信号槽语法，我们可以将一个对象的信号连接到 `Lambda` 表达式，例如：

```cpp
// !!! Qt 5
#include <QApplication>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Quit");
    QObject::connect(&button, &QPushButton::clicked, [](bool) {
        qDebug() << "You clicked me!";
    });
    button.show();

    return app.exec();
}
```

注意这里的 `Lambda` 表达式接收一个 `bool` 参数，这是因为`QPushButton`的`clicked()`信号实际上是有一个参数的。`Lambda` 表达式中的`qDebug()`类似于`cout`，将后面的字符串打印到标准输出。如果要编译上面的代码，你需要在 pro 文件中添加这么一句：

`QMAKE_CXXFLAGS += -std=c++0x`

然后正常编译即可。

Qt 4 的信号槽同 Qt 5 类似。在 Qt 4 的 `QObject` 中，有三个不同的`connect()`重载：

```cpp
bool connect(const QObject *, const char *,
             const QObject *, const char *,
             Qt::ConnectionType);

bool connect(const QObject *, const QMetaMethod &,
             const QObject *, const QMetaMethod &,
             Qt::ConnectionType);

bool connect(const QObject *, const char *,
             const char *,
             Qt::ConnectionType) const
```

除了返回值，Qt 4 的`connect()`函数与 Qt 5 最大的区别在于，Qt 4 的 signal 和 slot 只有`const char *`这么一种形式。如果我们将上面的代码修改为 Qt 4 的，则应该是这样的：

```cpp
// !!! Qt 4
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Quit");
    QObject::connect(&button, SIGNAL(clicked()),
                     &app,    SLOT(quit()));
    button.show();

    return app.exec();
}
```

我们使用了`SIGNAL`和`SLOT`这两个宏，将两个函数名转换成了字符串。注意，即使`quit()`是`QApplication`的 `static` 函数，也必须传入一个对象指针。这也是 Qt 4 的信号槽语法的局限之处。另外，注意到`connect()`函数的 signal 和 slot 都是接受字符串，因此，不能将全局函数或者 `Lambda` 表达式传入`connect()`。一旦出现连接不成功的情况，Qt 4 是没有编译错误的（因为一切都是字符串，编译期是不检查字符串是否匹配），而是在运行时给出错误。这无疑会增加程序的不稳定性。

信号槽机制是 Qt 的最大特性之一。这次我们只是初略了解了信号槽，知道了如何使用`connect()`函数进行信号槽的连接。在后面的内容中，我们将进一步介绍信号槽，了解如何设计自己的信号槽等等。

[![top] Goto Top](#table-of-contents)





[top]: up.png
