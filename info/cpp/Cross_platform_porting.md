- 宏拆分Windows以及Linux
```cpp
#if defined _WIN32 || defined _WIN64
...
#endif
```

```cpp
#ifdef Q_OS_WIN
...
#else
...
#endif
```

```cpp
#ifdef WIN32
...
#endif
```

```cpp
#if defined(_MSV_VER)&&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif
```


- 中文乱码处理
当文件为utf-8编码保存：
```cpp
//
// Created by 裴奕霖 on 2022/7/12.
//

#include "widget.h"
#include <QPushButton>

// #if defined(_MSV_VER)&&(_MSC_VER >= 1600)
// #pragma execution_character_set("utf-8")
// #endif

widget::widget(QWidget *parent) :
        QWidget(parent) {
    QPushButton *btn = new QPushButton();
    QString str = QString::fromLocal8Bit("中文");
    btn->setText(str);
    btn->setParent(this);
    btn->show();
}
```
在msvc编译器下上述代码注释部分，若开启则乱码，若注释则正常状态,mingw以及clang下均正确。

乱码总结：
1. 源码字符集(the source character set)：源码文件是使用何种编码保存的
2. 执行字符集(the execution character set)：可执行程序内保存的是何种编码(程序执行时内存中字符串编码)

总体来说，解决方法就一个：你必须知道源码的编码和执行的编码。

最简洁的方法就是：把源码改为`UTF-8`编码，这样不用做任何转换，直接就能正确显示，例如:
```cpp
QString str="这是汉字";
ui->textEdit->append(str);
```
如果源码为`GB2312`，`QString`默认为为`UTF-8`，这时，要这样写才不会乱码：

```cpp
QString str= QString::fromLocal8Bit("这是汉字");
ui->textEdit->append(str);
```
这个例子是把本地编码（我们的操作系统得编码大多为GB2312），转换为QString支持的编码。

如果前期没有注意可以采用[本脚本](../../code/Python/gbk2utf-8/main.py)批处理











[操作系统宏](https://sourceforge.net/p/predef/wiki/OperatingSystems/)


[![top] Goto Top](#table-of-contents)




[top]: up.png