# 官方示例



# 信号槽

**信号（Signal）**就是在特定情况下被发射的事件，例如PushButton 最常见的信号就是鼠标单击时发射的 clicked() 信号，一个 ComboBox 最常见的信号是选择的列表项变化时发射的 CurrentIndexChanged() 信号。

GUI 程序设计的主要内容就是对界面上各组件的信号的响应，只需要知道什么情况下发射哪些信号，合理地去响应和处理这些信号就可以了。

**槽（Slot）**就是对信号响应的函数。槽就是一个函数，与一般的[C++](http://c.biancheng.net/cplus/)函数是一样的，可以定义在类的任何部分（public、private 或 protected），可以具有任何参数，也可以被直接调用。槽函数与一般的函数不同的是：槽函数可以与一个信号关联，当信号被发射时，关联的槽函数被自动执行。

**多个信号可以连接同一个槽**

connect()函数最常用的一般形式：

```c++
connect(sender, signal, receiver, slot);
```

五种重载：
```c++
QMetaObject::Connection connect(const QObject *, const char *, const QObject *, const char *, Qt::ConnectionType);

QMetaObject::Connection connect(const QObject *, const QMetaMethod &, const QObject *, const QMetaMethod &, Qt::ConnectionType);

QMetaObject::Connection connect(const QObject *, const char *, const char *, Qt::ConnectionType) const;

QMetaObject::Connection connect(const QObject *, PointerToMemberFunction, const QObject *, PointerToMemberFunction, Qt::ConnectionType)
  
QMetaObject::Connection connect(const QObject *, PointerToMemberFunction, Functor);
```

这是最常用的形式，我们可以套用这个形式去分析上面给出的五个重载。第一个，sender 类型是const QObject *，signal 的类型是const char *，receiver 类型是const QObject *，slot 类型是const char *。这个函数将 signal 和 slot 作为字符串处理。第二个，sender 和 receiver 同样是const QObject *，但是 signal 和 slot 都是const QMetaMethod &。我们可以将每个函数看做是QMetaMethod的子类。因此，这种写法可以使用QMetaMethod进行类型比对。第三个，sender 同样是const QObject *，signal 和 slot 同样是const char *，但是却缺少了 receiver。这个函数其实是将 this 指针作为 receiver。第四个，sender 和 receiver 也都存在，都是const QObject *，但是 signal 和 slot 类型则是PointerToMemberFunction。看这个名字就应该知道，这是指向成员函数的指针。第五个，前面两个参数没有什么不同，最后一个参数是Functor类型。这个类型可以接受 static 函数、全局函数以及 Lambda 表达式。

由此我们可以看出，connect()函数，sender 和 receiver 没有什么区别，都是QObject指针；主要是 signal 和 slot 形式的区别。具体到我们的示例，我们的connect()函数显然是使用的第五个重载，最后一个参数是QApplication的 static 函数quit()。也就是说，当我们的 button 发出了clicked()信号时，会调用QApplication的quit()函数，使程序退出。

或者，借助 Qt 5 的信号槽语法，我们可以将一个对象的信号连接到 Lambda 表达式，例如：

```c++
// !!! Qt 5
#include <QApplication>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Quit");
    QObject::connect(&button, &QPushButton::clicked, [](bool) {qDebug() << "You clicked me!";});
  //[](bool) {qDebug() << "You clicked me!";}，为第三种重载换位lambda表达式，也就是Functor
    button.show();

    return app.exec();
}
```

# 自定义信号槽



