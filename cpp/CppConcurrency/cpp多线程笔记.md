# 1. Table of Contents
- [1. Table of Contents](#1-table-of-contents)
  - [1.1. 线程代码示例](#11-线程代码示例)
  - [1.2. 对象生命周期和线程等待和分离](#12-对象生命周期和线程等待和分离)
  - [1.3. 全局函数作为线程入口分析参数传递内存操作](#13-全局函数作为线程入口分析参数传递内存操作)
  - [1.4. 线程函数传递指针和引用](#14-线程函数传递指针和引用)
  - [1.5. 使用成员函数作为线程入口并封装线程基类接口](#15-使用成员函数作为线程入口并封装线程基类接口)
  - [1.6. lambda临时函数作为线程入口](#16-lambda临时函数作为线程入口)
  - [1.7. 多线程的状态及其切换流程分析](#17-多线程的状态及其切换流程分析)
  - [1.8. 竞争状态和临界区介绍\_互斥锁mutex代码演示](#18-竞争状态和临界区介绍_互斥锁mutex代码演示)
  - [1.9. 互斥锁的坑\_线程抢占不到资源原因和解决方法](#19-互斥锁的坑_线程抢占不到资源原因和解决方法)
  - [1.10. 超时锁timed\_mutex和可重入锁recursive](#110-超时锁timed_mutex和可重入锁recursive)
  - [1.11. 共享锁shared\_mutex解决读写问题](#111-共享锁shared_mutex解决读写问题)
  - [1.12. 手动实现RAII管理mutex资源\_锁自动释放](#112-手动实现raii管理mutex资源_锁自动释放)
  - [1.13. c++11RAII控制锁lock\_guard](#113-c11raii控制锁lock_guard)
  - [1.14. unique\_lock可临时解锁控制超时的互斥体包装器](#114-unique_lock可临时解锁控制超时的互斥体包装器)
  - [1.15. C++14shared\_lock共享锁包装器](#115-c14shared_lock共享锁包装器)
  - [1.16. c++17scoped\_lock解决互锁造成的死锁问题](#116-c17scoped_lock解决互锁造成的死锁问题)
  - [1.17. 项目案例线程通信使用互斥锁和list实现线程通信](#117-项目案例线程通信使用互斥锁和list实现线程通信)
  - [1.18. 条件变量应用场景\_生产者消费者信号处理步骤](#118-条件变量应用场景_生产者消费者信号处理步骤)
  - [1.19. condition\_variable代码示例读写线程同步](#119-condition_variable代码示例读写线程同步)
  - [1.20. 条件变量应用线程通信解决线程退出时的阻塞问题](#120-条件变量应用线程通信解决线程退出时的阻塞问题)
  - [1.21. promise和future多线程异步传值](#121-promise和future多线程异步传值)
  - [1.22. packaged\_task 异步调用函数打包](#122-packaged_task-异步调用函数打包)
  - [1.23. async创建异步线程替代thread](#123-async创建异步线程替代thread)


借鉴Anthony Williams的《C++ Concurrency In Action》一书

<!--more-->

[C++ Concurrency In Action 2ed](https://github.com/anthonywilliams/ccia_code_samples)

## 1.1. 线程代码示例
```cpp
#include <thread>
#include <iostream>
// Linux -lpthread

void ThreadMain() {
  std::cout << "begin sub thread main " << std::this_thread::get_id() << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << "in thread " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 1000ms
  }
  std::cout << "end sub thread main " << std::this_thread::get_id() << std::endl;
}
int main(int argc, char* argv[]) {
  std::cout << "main thread ID " << std::this_thread::get_id() << std::endl;
  // 线程创建启动
  std::thread th(ThreadMain);
  std::cout << "begin wait sub thread  " << std::endl;
  // 阻塞等待子线程退出
  th.join();
  std::cout << "end wait sub thread  " << std::endl;
  return 0;
}

```
[![top] Goto Top](#table-of-contents)

## 1.2. 对象生命周期和线程等待和分离

```cpp
#include <thread>
#include <iostream>
// Linux -lpthread

bool is_exit = false;

void ThreadMain() {
  std::cout << "begin sub thread main " << std::this_thread::get_id()
            << std::endl;
  for (int i = 0; i < 10; i++) {
    if (!is_exit) break;
    std::cout << "in thread " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 1000ms
  }
  std::cout << "end sub thread main " << std::this_thread::get_id()
            << std::endl;
}

int main(int argc, char *argv[]) {
  {
       thread th(ThreadMain); //出错，thread对象被销毁 子线程还在运行
  }

  {
    std::thread th(ThreadMain);
    th.detach();  // 子线程与主线程分离 守护线程
    // 坑 ：主线程退出后 子线程不一定退出
    //  可能造成的问题是主线程推出(主程序退出)，程序报错(主线程退出，全部资源释放)
    //  一般解决方案：通过 is_exit 来控制，起到通知作用
    //  如果不做 detach，则必须维护 th 对象
  }

  {
    std::thread th(ThreadMain);
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 1000ms
    is_exit = true;  // 通知子线程退出
    std::cout << "主线程阻塞，等待子线程退出" << std::endl;
    th.join();  // 主线程阻塞，等待子线程退出
    std::cout << "子线程已经退出！" << std::endl;
  }

  std::cin.get();

  return 0;
}
```
课程中用的vs2019，可以看到thread类的源码，可以看到构造、析构的写法(若没有join则删除对象，释放空间)。

1. 如果调用`detach`，则分离，主线程中不用再关注该线程
2. 若`join`方式来精确控制子线程，则一般需要维系该线程对象，一般将th对象放在成员函数中

当线程的执行结果不需要返回给主线程，或者可以通过其他方式通知主线程时，可以使用`detach()`。例如，一个后台日志记录线程，它只负责将日志信息写入文件，不需要和主线程交互，就可以使用`detach()`。

当线程的执行时间不确定，或者可能比主线程更长时，可以使用`detach()`。例如，一个网络请求线程，它可能会因为网络延迟或者服务器故障而阻塞很久，如果使用`join()`，就会导致主线程也无法继续运行，影响用户体验。如果使用`detach()`，就可以让主线程继续响应用户操作，而网络请求线程在后台等待结果。

当线程的执行逻辑和主线程无关，或者可以独立完成时，可以使用`detach()`。例如，一个音乐播放器程序，它可以创建一个音乐播放线程来控制音乐的播放、暂停、切换等操作，而主线程只负责显示界面和接收用户输入。这样的话，音乐播放线程就可以使用`detach()`，让它和主线程分离。

`detach()`也有一些潜在的风险和问题，例如：

- `detach()`后的线程可能会访问已经被销毁的对象或变量，导致程序崩溃或者数据不一致。例如，如果一个线程要访问主线中的对象以及指针问题。
- `detach()`后的线程可能会在主线程结束后还没有执行完毕，导致程序异常退出或者资源泄露。例如，如果一个线程要写入文件或者数据库等外部资源。
- `detach()`后的线程可能会难以控制和监控，导致程序逻辑混乱或者性能下降。例如，如果一个程序创建了过多的`detach()`的线程。

因此，在使用`detach()`时，需要注意以下几点：

- 尽量避免在`detach()`的线程中访问主线中的对象或变量，或者使用同步机制来保护共享资源。
- 尽量确保`detach()`的线程在主线结束前能够正常退出，或者提供一种机制来通知detach()的线程退出。
- 尽量控制`detach()`的线程的数量和质量，避免过度消耗系统资源和影响程序稳定性。

[![top] Goto Top](#table-of-contents)

## 1.3. 全局函数作为线程入口分析参数传递内存操作

```cpp
#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
using namespace std;
class Para {
 public:
  Para() { cout << "Create Para" << endl; }
  Para(const Para &p) { cout << "Copy Para" << endl; }
  ~Para() { cout << "Drop Para" << endl; }
  string name;
};

void ThreadMain(int p1, float p2, string str, Para p4) {
  this_thread::sleep_for(100ms);
  cout << "ThreadMain " << p1 << " " << p2 << " " << str << " " << p4.name << endl;
}

int main(int argc, char *argv[]) {
  thread th;
  {
    float f1 = 12.1f;
    Para p;
    p.name = "test Para class";
    //所有的参数做复制
    th = thread(ThreadMain, 101, f1, "test string para", p);// 在这里会产生复制，thread对象在建立时候，会将参数复制
  }
  th.join();
  return 0;
}
```
如何避免复制，[4. 线程函数传递指针和引用](#4-线程函数传递指针和引用) 中解释。

[![top] Goto Top](#table-of-contents)

## 1.4. 线程函数传递指针和引用

```cpp
#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread

class Para {
 public:
  Para() { std::cout << "Create Para" << std::endl; }
  Para(const Para &p) { std::cout << "Copy Para" << std::endl; }
  ~Para() { std::cout << "Drop Para" << std::endl; }
  std::string name;
};

void ThreadMain(int p1, float p2, std::string str, Para p4) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "ThreadMain " << p1 << " " << p2 << " " << str << " " << p4.name << std::endl;
}

void ThreadMainPtr(Para *p) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "ThreadMainPtr name = " << p->name << std::endl;
}

void ThreadMainRef(Para &p) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "ThreadMainPtr name = " << p.name << std::endl;
}
int main(int argc, char *argv[]) {
  {
    //传递引用
    Para p;
    p.name = "test ref";
    std::thread th(ThreadMainRef, std::ref(p));// ref 是为了标识为引用
    th.join();
  }
  std::cin.get();

  {
    //传递线程指针
    Para p;
    p.name = "test ThreadMainPtr name";
    std::thread th(ThreadMainPtr, &p); //错误 ，线程访问的p空间会提前释放
    // 解决方案是 1. 将 p 放在类成员当中 2. p 传入到堆 3. 静态 p
    // 所以 p 这个空间，一定要保证在整个线程运行期间，在他的生命周期内
    th.detach();
  }
  // Para 释放
  std::cin.get();
  {
    //传递线程指针
    Para p;
    p.name = "test ThreadMainPtr name";
    std::thread th(ThreadMainPtr, &p);
    th.join();
    std::cin.get();
  }

  std::thread th;
  {
    float f1 = 12.1f;
    Para p;
    p.name = "test Para class";
    //所有的参数做复制
    th = std::thread(ThreadMain, 101, f1, "test std::string para", p);
  }
  th.join();
  return 0;
}
```
[![top] Goto Top](#table-of-contents)

## 1.5. 使用成员函数作为线程入口并封装线程基类接口

```cpp
#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
class MyThread {
 public:
  //入口线程函数
  void Main() {
    std::cout << "MyThread Main " << name << ":" << age;
  }
  std::string name;
  int age = 100;
};

class XThread {
 public:
  virtual void Start() {
    is_exit_ = false;
    th_ = std::thread(&XThread::Main, this);
  }
  virtual void Stop() {
    is_exit_ = true;
    Wait();
  }
  virtual void Wait() {
    if (th_.joinable())
      th_.join();
  }
  bool is_exit() { return is_exit_; }
 private:
  virtual void Main() = 0;
  std::thread th_;
  bool is_exit_ = false;
};

class TestXThread : public XThread {
 public:
  void Main() override {
    std::cout << "TestXThread Main begin" << std::endl;
    while (!is_exit()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout << "." << std::flush;// flush保证及时刷新，cout的内容不会延迟
    }
    std::cout << "TestXThread Main end" << std::endl;
  }
  std::string name;
};

int main(int argc, char *argv[]) {
  TestXThread testth;// 进入派生类重载
  testth.name = "TestXThread name ";
  testth.Start();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  testth.Stop();

  testth.Wait();
  std::cin.get();

  // 成员函数作为参数
  MyThread myth;
  myth.name = "Test name 001";
  myth.age = 20;
  std::thread th(&MyThread::Main, &myth);
  // &MyThread::Main 成员函数指针
  // &myth 指当前对象地址(*this)
  th.join();

  return 0;
}
```
[![top] Goto Top](#table-of-contents)

## 1.6. lambda临时函数作为线程入口

```cpp
#include <thread>
#include <iostream>
#include <string>
// test lambda thread
class TestLambda {
 public:
  void Start() {
    std::thread th([this]() { std::cout << "name = " << name << std::endl; });
    th.join();
  }

  std::string name = "test lambda";
};
int main(int argc, char *argv[]) {
  std::thread th(
      [](int i) { std::cout << "test lmbda " << i << std::endl; },
      123
  );
  th.join();
  TestLambda test;
  test.Start();

  return 0;
}
```

[![top] Goto Top](#table-of-contents)

## 1.7. 多线程的状态及其切换流程分析

线程状态说明：
1. 初始化：线程正在创建
   - 初始化内存空间等，代码干预不多，从初始化到就绪有一定的消耗，所以才会引入线程池，为了减少类似消耗
2. 就绪：线程在就绪列表中，等待CPU调度
3. 运行：该线程正在运行
4. 阻塞：线程被阻塞挂起。Blocked状态包括：pend(锁、事件、信号量等阻塞)、suspend(主动pend)、delay(延时阻塞)、pendtime(因为锁、事件、信号量事件等超时等待)
5. 退出：线程运行结束，等待父线程回收其控制块资源(栈等，不会释放线程运行中创建的堆资源)

[![top] Goto Top](#table-of-contents)

## 1.8. 竞争状态和临界区介绍_互斥锁mutex代码演示

> 临界区：读写共享数据的代码片段

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
// Linux -lpthread
using namespace std;
static mutex mux;  // 尽晚申请，尽早释放
void TestThread() {
  for (;;) {
    // 获取锁资源，如果没有则阻塞等待
    // mux.lock(); // 操作系统层面的锁
    if (!mux.try_lock()) {
      // try_lock 可以帮助看到多线程竞争锁的情况
      cout << "." << flush;
      this_thread::sleep_for(100ms);  // 要进行停顿，否则会不停循环，将资源耗尽
      // try_lock可以控制多线程的同时带来了性能开销
      continue;
    }
    cout << "==============================" << endl;
    cout << "test 001" << endl;
    cout << "test 002" << endl;
    cout << "test 003" << endl;
    cout << "==============================" << endl;
    mux.unlock();  // 尽晚申请，尽早释放
    this_thread::sleep_for(1000ms);
  }
}
int main(int argc, char* argv[]) {
  for (int i = 0; i < 10; i++) {
    thread th(TestThread);
    th.detach();
  }
  std::cin.get();
  return 0;
}

```
[![top] Goto Top](#table-of-contents)

## 1.9. 互斥锁的坑_线程抢占不到资源原因和解决方法

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>

static std::mutex mux;

void ThreadMainMux(int i) {
  for (;;) {
    mux.lock();
    std::cout << i << "[in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    mux.unlock();
    std::this_thread::sleep_for(
        std::chrono::milliseconds(1));  // 这里，交给操作系统释放资源
    // 总之就是不能在unlock之后，立刻lock。一个小坑，只看代码很可能难以发现
  }
}
int main(int argc, char* argv[]) {
  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadMainMux, i + 1);
    th.detach();
  }

  std::cin.get();
  return 0;
}

```
[![top] Goto Top](#table-of-contents)

## 1.10. 超时锁timed_mutex和可重入锁recursive

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>

static std::mutex mux;
void TestThread() {
  for (;;) {
    // 获取锁资源，如果没有则阻塞等待
    // mux.lock(); //
    if (!mux.try_lock()) {
      std::cout << "." << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }
    std::cout << "==============================" << std::endl;
    std::cout << "test 001" << std::endl;
    std::cout << "test 002" << std::endl;
    std::cout << "test 003" << std::endl;
    std::cout << "==============================" << std::endl;
    mux.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
void ThreadMainMux(int i) {
  for (;;) {
    mux.lock();
    std::cout << i << "[in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    mux.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

std::timed_mutex tmux;

void ThreadMainTime(int i) {
  for (;;) {
    if (!tmux.try_lock_for(std::chrono::milliseconds(500))) {
      std::cout << i << "[try_lock_for timeout]" << std::endl;
      // 尝试获取一个名为tmux的定时互斥锁。如果锁已经被其他线程占用，并且在500毫秒内没有释放，
      // 则当前线程会返回false，否则会返回true并获取锁。
      continue;
    }
    std::cout << i << "[in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    tmux.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  // try_lock_for :
  // 尝试锁定关联互斥。阻塞直至经过指定的 timeout_duration
  // 或获得锁，之先到来者。成功获得锁时返回 true ，否则返回 false 等效地调用
  // mutex()->try_lock_for(timeout_duration)
}

std::recursive_mutex rmux;
void Task1() {
  rmux.lock();
  std::cout << "task1 [in]" << std::endl;
  rmux.unlock();
}
void Task2() {
  rmux.lock();
  std::cout << "task2 [in]" << std::endl;
  rmux.unlock();
}
void ThreadMainRec(int i) {
  for (;;) {
    rmux.lock();
    Task1();
    std::cout << i << "[in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Task2();
    rmux.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
int main(int argc, char* argv[]) {
  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadMainRec, i + 1);
    th.detach();
  }
  std::cin.get();

  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadMainTime, i + 1);
    th.detach();
  }
  std::cin.get();

  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadMainMux, i + 1);
    th.detach();
  }
  std::cin.get();

  for (int i = 0; i < 10; i++) {
    std::thread th(TestThread);
    th.detach();
  }
  std::cin.get();
  return 0;
}

```

还是推荐一下cppreference.com的示例代码：

timed_mutex 类是能用于保护数据免受多个线程同时访问的同步原语。

以类似 mutex 的行为， timed_mutex 提供排他性非递归所有权语义。另外， timed_mutex 提供通过 try_lock_for() 和 try_lock_until() 方法试图带时限地要求 timed_mutex 所有权的能力。

timed_mutex 类满足定时互斥与标准布局类型的所有要求。

recursive_mutex 的使用场景之一是保护类中的共享状态，而类的成员函数可能相互调用:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
 
class X {
    std::recursive_mutex m;
    std::string shared;
  public:
    void fun1() {
      std::lock_guard<std::recursive_mutex> lk(m);
      shared = "fun1";
      std::cout << "in fun1, shared variable is now " << shared << '\n';
    }
    void fun2() {
      std::lock_guard<std::recursive_mutex> lk(m);
      shared = "fun2";
      std::cout << "in fun2, shared variable is now " << shared << '\n';
      fun1(); // 递归锁在此处变得有用
      std::cout << "back in fun2, shared variable is " << shared << '\n';
    };
};
 
int main() 
{
    X x;
    std::thread t1(&X::fun1, &x);
    std::thread t2(&X::fun2, &x);
    t1.join();
    t2.join();
}
```
[![top] Goto Top](#table-of-contents)

## 1.11. 共享锁shared_mutex解决读写问题

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

// c++17  共享锁
// shared_mutex smux;

// c++14
std::shared_timed_mutex stmux;

void ThreadRead(int i) {
  for (;;) {
    stmux.lock_shared();
    std::cout << i << " Read" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    stmux.unlock_shared();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
void ThreadWrite(int i) {
  for (;;) {
    stmux.lock_shared();
    // 读取数据
    stmux.unlock_shared();
    stmux.lock();  // 互斥锁 写入
    std::cout << i << " Write" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    stmux.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
int main(int argc, char* argv[]) {
  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadWrite, i + 1);
    th.detach();
  }
  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadRead, i + 1);
    th.detach();
  }
  std::cin.get();
  return 0;
}

```
共享锁中主要包含两个锁，一个是共享锁，一个是互斥锁。

cppreference.com示例代码：
其实这个示例更多的是学习两个锁的初始化方式..

```cpp
#include <iostream>
#include <mutex>  // 对于 std::unique_lock
#include <shared_mutex>
#include <thread>

class ThreadSafeCounter {
 public:
  ThreadSafeCounter() = default;

  // 多个线程/读者能同时读计数器的值。
  unsigned int get() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    // 互斥元保护value_的读写，防止多个线程同时写value_,允许多个线程同时读value_
    return value_;
  }

  // 只有一个线程/写者能增加/写线程的值。
  void increment() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    // unique_lock和shared_lock都是互斥元，但是unique_lock可以在构造时指定锁的类型，而shared_lock只能是共享锁
    value_++;
  }

  // 只有一个线程/写者能重置/写线程的值。
  void reset() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = 0;
  }

 private:
  mutable std::shared_mutex mutex_;
  unsigned int value_ = 0;
};

int main() {
  ThreadSafeCounter counter;

  auto increment_and_print = [&counter]() {
    for (int i = 0; i < 3; i++) {
      counter.increment();
      std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';

      // 注意：写入 std::cout 实际上也要由另一互斥同步。省略它以保持示例简洁。
    }
  };

  std::thread thread1(increment_and_print);
  std::thread thread2(increment_and_print);

  thread1.join();
  thread2.join();
}

// 解释：下列输出在单核机器上生成。 thread1 开始时，它首次进入循环并调用
// increment() ， 随后调用 get() 。然而，在它能打印返回值到 std::cout
// 前，调度器将 thread1 置于休眠 并唤醒 thread2
// ，它显然有足够时间一次运行全部三个循环迭代。再回到 thread1 ，它仍在首个
// 循环迭代中，它最终打印其局部的计数器副本的值，即 1 到 std::cout
// ，再运行剩下二个循环。
// 多核机器上，没有线程被置于休眠，且输出更可能为递增顺序。

/*
可能的输出：
123084176803584 2
123084176803584 3
123084176803584 4
123084185655040 1
123084185655040 5
123084185655040 6
*/

```
其实上述代码很巧妙，也很可能是开发过程中难以调试的bug。

[![top] Goto Top](#table-of-contents)

## 1.12. 手动实现RAII管理mutex资源_锁自动释放

这种方式是手动方式，c++11提供了RAII控制锁lock_guard，见：[c++11RAII控制锁lock\_guard](#c11raii控制锁lock_guard)
```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

// RAII
class XMutex {
  // 这种简化的类的构造方式值得借鉴 哈
 public:
  XMutex(mutex& mux) : mux_(mux) {
    std::cout << "Lock" << std::std::endl;
    mux.lock();
  }
  ~XMutex() {
    std::cout << "Unlock" << std::std::endl;
    mux_.unlock();  // 借助析构函数释放资源，RAII主要就是这个思想
  }

 private:
  mutex& mux_;
};

static mutex mux;

void TestMutex(int status) {
  XMutex lock(mux);
  if (status == 1) {
    std::cout << "=1" << std::std::endl;
    return;
  } else {
    std::cout << "!=1" << std::std::endl;
    return;
  }
}
int main(int argc, char* argv[]) {
  TestMutex(1);
  TestMutex(2);

  std::cin.get();
  return 0;
}
```
[![top] Goto Top](#table-of-contents)

## 1.13. c++11RAII控制锁lock_guard

cppreference.com：  
资源获取即初始化（Resource Acquisition Is Initialization），或称 RAII，是一种 C++ 编程技术，它将必须在使用前请求的资源（分配的堆内存、执行线程、打开的套接字、打开的文件、锁定的互斥体、磁盘空间、数据库连接等——任何存在受限供给中的事物）的生命周期与一个对象的生存期相绑定。

RAII 保证资源能够用于任何会访问该对象的函数（资源可用性是一种类不变式，这会消除冗余的运行时测试）。它也保证对象在自己生存期结束时会以获取顺序的逆序释放它控制的所有资源。类似地，如果资源获取失败（构造函数以异常退出），那么已经构造完成的对象和基类子对象所获取的所有资源就会以初始化顺序的逆序释放。这有效地利用了语言特性（对象生存期、退出作用域、初始化顺序以及栈回溯）以消除内存泄漏并保证异常安全。根据 RAII 对象的生存期在退出作用域时结束这一基本状况，此技术也被称为作用域界定的资源管理（Scope-Bound Resource Management，SBRM）。
RAII 可以总结如下:

- 将每个资源封装入一个类，其中：
  - 构造函数请求资源，并建立所有类不变式，或在它无法完成时抛出异常，
  - 析构函数释放资源并且决不会抛出异常；
- 在使用资源时始终通过 RAII 类的满足以下要求的实例：
  - 自身拥有自动存储期或临时生存期，或
  - 具有与自动或临时对象的生存期绑定的生存期

移动语义使得在对象间，跨作用域，以及在线程内外安全地移动所有权，而同时维护资源安全成为可能。(C++11 起)

拥有 `open()/close()`、`lock()/unlock()`，或 `init()/copyFrom()/destroy()` 成员函数的类是典型的非 RAII 类的例子：

```cpp
std::mutex m;
 
void bad() 
{
    m.lock();                    // 请求互斥体
    f();                         // 如果 f() 抛出异常，那么互斥体永远不会被释放
    if(!everything_ok()) return; // 提早返回，互斥体永远不会被释放
    m.unlock();                  // 只有 bad() 抵达此语句，互斥体才会被释放
}
 
void good()
{
    std::lock_guard<std::mutex> lk(m); // RAII类：互斥体的请求即是初始化
    f();                               // 如果 f() 抛出异常，那么就会释放互斥体
    if(!everything_ok()) return;       // 提早返回也会释放互斥体
}                                      // 如果 good() 正常返回，那么就会释放互斥体
```

std::lock_guard示例代码：
```cpp
#include <thread>
#include <mutex>
#include <iostream>

int g_i = 0;
std::mutex g_i_mutex;  // 保护 g_i

void safe_increment() {
  std::lock_guard<std::mutex> lock(g_i_mutex);
  ++g_i;

  std::cout << std::this_thread::get_id() << ": " << g_i << '\n';

  // g_i_mutex 在锁离开作用域时自动释放
}

int main() {
  std::cout << "main: " << g_i << '\n';

  std::thread t1(safe_increment);
  std::thread t2(safe_increment);

  t1.join();
  t2.join();

  std::cout << "main: " << g_i << '\n';
}
```
lock_guard建立在栈上，离开大括号后自动释放锁，查看lock_guard源码，对应析构函数可以看到。
```cpp
~lock_guard() _LIBCPP_THREAD_SAFETY_ANNOTATION(release_capability()) {__m_.unlock();}
```

另一例：
```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

// RAII
class XMutex {
 public:
  XMutex(std::mutex& mux) : mux_(mux) {
    std::cout << "Lock" << std::endl;
    mux.lock();
  }
  ~XMutex() {
    std::cout << "Unlock" << std::endl;
    mux_.unlock();
  }

 private:
  std::mutex& mux_;
};

static std::mutex mux;

void TestMutex(int status) {
  XMutex lock(mux);
  if (status == 1) {
    std::cout << "=1" << std::endl;
    return;
  } else {
    std::cout << "!=1" << std::endl;
    return;
  }
}

static std::mutex gmutex;
void TestLockGuard(int i) {
  gmutex.lock();
  {
    // 已经拥有锁，不lock
    std::lock_guard<std::mutex> lock(gmutex, std::adopt_lock);
    // 结束释放锁
  }
  {
    std::lock_guard<std::mutex> lock(gmutex);
    std::cout << "begin thread " << i << std::endl;
  }
  for (;;) {
    {
      std::lock_guard<std::mutex> lock(gmutex);
      std::cout << "In " << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
int main(int argc, char* argv[]) {
  for (int i = 0; i < 3; i++) {
    std::thread th(TestLockGuard, i + 1);
    th.detach();
  }
  TestMutex(1);
  TestMutex(2);

  std::cin.get();
  return 0;
}
```
`lock_guard`什么时候释解锁，如果将其放在大括号内，则互斥量充满整个大括号，那么着是不是我们理想的效果，需要注意。

另外，临界区内不应该包含`sleep()`，`sleep()`的时候，锁还在占用，资源还在占用状态，这样会存在巨大风险。

`lock_guard`构造函数支持两种：
```cpp
    explicit lock_guard(mutex_type& __m) _LIBCPP_THREAD_SAFETY_ANNOTATION(acquire_capability(__m))
        : __m_(__m) {__m_.lock();}

    lock_guard(mutex_type& __m, adopt_lock_t) _LIBCPP_THREAD_SAFETY_ANNOTATION(requires_capability(__m))
        : __m_(__m) {}
```
第一种直接mutex类型即可完成构造，也就是有`lock()`和`unlock()`就可以。

第二种知识将锁存下来，但是并未进行锁操作，相同的，析构函数都会`unlock()`
```cpp
private:
    lock_guard(lock_guard const&) = delete;
    lock_guard& operator=(lock_guard const&) = delete;
```
`lock_guard`无法转移，不能由一个`lock_guard`到另一个`lock_guard`。

需要注意的是，lock_guard默认互斥资源没有被锁。

```cpp
static std::mutex gmutex;
void TestLockGuard(int i) {
  gmutex.lock();
  {
    std::lock_guard<std::mutex> lock(gmutex);
  }
}
```
gmutex已经在lock_guard之外锁住了资源，上述代码会抛出异常，如果不想锁相关资源，那么利用重载，调用不同构造，传入一个常量参数即可。



[![top] Goto Top](#table-of-contents)

## 1.14. unique_lock可临时解锁控制超时的互斥体包装器

- unique_lock C++11 实现可移动的互斥体所有权包装器
- 支持临时释放锁 unlock
- 支持 adopt_lock（已经拥有锁，不加锁，出栈区会释放）
- 支持 defer_lock （延后拥有，不加锁，出栈区不释放）
- 支持 try_to_lock 尝试获得互斥的所有权而不阻塞 ，获取失败退出栈区不会释放，通过 owns_lock()函数判断
- 支持超时参数，超时不拥有锁

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

// RAII
class XMutex {
 public:
  XMutex(std::mutex& mux) : mux_(mux) {
    std::cout << "Lock" << std::endl;
    mux.lock();
  }
  ~XMutex() {
    std::cout << "Unlock" << std::endl;
    mux_.unlock();
  }

 private:
  std::mutex& mux_;
};
static std::mutex mux;
void TestMutex(int status) {
  XMutex lock(mux);
  if (status == 1) {
    std::cout << "=1" << std::endl;
    return;
  } else {
    std::cout << "!=1" << std::endl;
    return;
  }
}

static std::mutex gmutex;
void TestLockGuard(int i) {
  gmutex.lock();
  {
    // 已经拥有锁，不lock
    std::lock_guard<std::mutex> lock(gmutex, std::adopt_lock);
    // 结束释放锁
  }
  {
    std::lock_guard<std::mutex> lock(gmutex);
    std::cout << "begin thread " << i << std::endl;
  }
  for (;;) {
    {
      std::lock_guard<std::mutex> lock(gmutex);
      std::cout << "In " << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main(int argc, char* argv[]) {
  {
    static std::mutex mux;
    {
      // 基础用法示例，可以先unlock()，然后lock()
      std::unique_lock<std::mutex> lock(mux);
      lock.unlock();
      // 临时释放锁
      lock.lock();
      // 退出大括号后依旧会释放锁，和 unique_lock 一样
    }

    {
      // 已经拥有锁 不锁定，退出栈区解锁
      mux.lock();
      std::unique_lock<std::mutex> lock(mux, std::adopt_lock);
    }
    {
      // 延后加锁 不拥有 退出栈区不解锁
      std::unique_lock<std::mutex> lock(mux, std::defer_lock);
      // 加锁 退出栈区解锁
      lock.lock();
    }
    {
      // mux.lock();
      // 尝试加锁 不阻塞 失败不拥有锁
      std::unique_lock<std::mutex> lock(mux, std::try_to_lock);

      if (lock.owns_lock()) {
        std::cout << "owns_lock" << std::endl;
      } else {
        std::cout << "not owns_lock" << std::endl;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    std::thread th(TestLockGuard, i + 1);
    th.detach();
  }
  TestMutex(1);
  TestMutex(2);

  std::cin.get();
  return 0;
}
```
注意：  
defer_lock功能时，__owns_(false)，同步析构时不会解锁
```cpp
unique_lock(mutex_type& __m, defer_lock_t) _NOEXCEPT
    : __m_(_VSTD::addressof(__m)),
      __owns_(false) {}

...

~unique_lock() {
  if (__owns_) __m_->unlock();
}
```
只能手动去lock或unlock

[![top] Goto Top](#table-of-contents)

## 1.15. C++14shared_lock共享锁包装器

以下这段代码值得商榷，主要看main函数中前两个大括号内的使用方法。

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
// Linux -lpthread

// RAII
class XMutex {
 public:
  XMutex(std::mutex& mux) : mux_(mux) {
    std::cout << "Lock" << std::endl;
    mux.lock();
  }
  ~XMutex() {
    std::cout << "Unlock" << std::endl;
    mux_.unlock();
  }

 private:
  std::mutex& mux_;
};
static std::mutex mux;
void TestMutex(int status) {
  XMutex lock(mux);
  if (status == 1) {
    std::cout << "=1" << std::endl;
    return;
  } else {
    std::cout << "!=1" << std::endl;
    return;
  }
}

static std::mutex gmutex;
void TestLockGuard(int i) {
  gmutex.lock();
  {
    // 已经拥有锁，不lock
    std::lock_guard<std::mutex> lock(gmutex, std::adopt_lock);
    // 结束释放锁
  }
  {
    std::lock_guard<std::mutex> lock(gmutex);
    std::cout << "begin thread " << i << std::endl;
  }
  for (;;) {
    {
      std::lock_guard<std::mutex> lock(gmutex);
      std::cout << "In " << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main(int argc, char* argv[]) {
  {
    // 共享锁
    static std::shared_timed_mutex tmux;
    // 读取锁 共享锁
    {
      // 调用共享锁
      std::shared_lock<std::shared_timed_mutex> lock(tmux);
      std::cout << "read data" << std::endl;
      // 退出栈区 释放共享锁
    }
    // 写入锁 互斥锁
    {
      // 这里不能先锁共享锁，然后锁互斥锁，死锁
      std::unique_lock<std::shared_timed_mutex> lock(tmux);
      std::cout << "write data" << std::endl;
    }
  }

  {
    static std::mutex mux;
    {
      std::unique_lock<std::mutex> lock(mux);
      lock.unlock();
      // 临时释放锁
      lock.lock();
    }

    {
      // 已经拥有锁 不锁定，退出栈区解锁
      mux.lock();
      std::unique_lock<std::mutex> lock(mux, std::adopt_lock);
    }
    {
      // 延后加锁 不拥有 退出栈区不解锁
      std::unique_lock<std::mutex> lock(mux, std::defer_lock);
      // 加锁 退出栈区解锁
      lock.lock();
    }
    {
      // mux.lock();
      // 尝试加锁 不阻塞 失败不拥有锁
      // unique_lock<mutex> lock(mux, try_to_lock);
      // 锁超时 阻塞指定时间 失败不拥有锁
      std::unique_lock<std::mutex> lock(mux, std::chrono::milliseconds(500));

      if (lock.owns_lock()) {
        std::cout << "owns_lock" << std::endl;
      } else {
        std::cout << "not owns_lock" << std::endl;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    std::thread th(TestLockGuard, i + 1);
    th.detach();
  }
  TestMutex(1);
  TestMutex(2);

  std::cin.get();
  return 0;
}
```
[![top] Goto Top](#table-of-contents)

## 1.16. c++17scoped_lock解决互锁造成的死锁问题

使用场景：在一个临界区代码中需要使用到两个锁，先用第一个锁lock，再用第二个锁lock。  
会出现问题：第一个线程把第一个锁锁住，另外一个线程把第二个锁锁住。  
紧接着要访问第二个锁，会造成阻塞。  
因为业务代码的问题，很难将锁的顺序定死，在这里用到scoped_lock  
测试很难复线，很难测

示例代码：
```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
// Linux -lpthread

// RAII
class XMutex {
 public:
  XMutex(std::mutex& mux) : mux_(mux) {
    std::cout << "Lock" << std::endl;
    mux.lock();
  }
  ~XMutex() {
    std::cout << "Unlock" << std::endl;
    mux_.unlock();
  }

 private:
  std::mutex& mux_;
};

static std::mutex mux;

void TestMutex(int status) {
  XMutex lock(mux);
  if (status == 1) {
    std::cout << "=1" << std::endl;
    return;
  } else {
    std::cout << "!=1" << std::endl;
    return;
  }
}

static std::mutex gmutex;

void TestLockGuard(int i) {
  gmutex.lock();
  {
    // 已经拥有锁，不lock
    std::lock_guard<std::mutex> lock(gmutex, std::adopt_lock);
    // 结束释放锁
  }
  {
    std::lock_guard<std::mutex> lock(gmutex);
    std::cout << "begin thread " << i << std::endl;
  }
  for (;;) {
    {
      std::lock_guard<std::mutex> lock(gmutex);
      std::cout << "In " << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

static std::mutex mux1;
static std::mutex mux2;

void TestScope1() {
  // 模拟死锁 停100ms等另一个线程锁mux2
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << std::this_thread::get_id() << " begin mux1 lock" << std::endl;
  // mux1.lock();
  std::cout << std::this_thread::get_id() << " begin mux2 lock" << std::endl;
  // mux2.lock(); //死锁
  // c++11
  //  lock(mux1, mux2);
  // c++17
  std::scoped_lock lock(mux1, mux2);  // 解决死锁

  std::cout << "TestScope1" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // 实际中临界资源中不要sleep

  // mux1.unlock();
  // mux2.unlock();
}

void TestScope2() {
  std::cout << std::this_thread::get_id() << " begin mux2 lock" << std::endl;
  mux2.lock();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << std::this_thread::get_id() << " begin mux1 lock" << std::endl;
  mux1.lock();  // 死锁
  std::cout << "TestScope2" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  mux1.unlock();
  mux2.unlock();
}

int main(int argc, char* argv[]) {
  {
    // 演示死锁情况
    {
      std::thread th(TestScope1);
      th.detach();
    }
    {
      std::thread th(TestScope2);
      th.detach();
    }
  }
  std::cin.get();

  {
    // 共享锁
    static std::shared_timed_mutex tmux;
    // 读取锁 共享锁
    {
      // 调用共享锁
      std::shared_lock<std::shared_timed_mutex> lock(tmux);
      std::cout << "read data" << std::endl;
      // 退出栈区 释放共享锁
    }
    // 写入锁 互斥锁
    {
      std::unique_lock<std::shared_timed_mutex> lock(tmux);
      std::cout << "write data" << std::endl;
    }
  }

  {
    static std::mutex mux;
    {
      std::unique_lock<std::mutex> lock(mux);
      lock.unlock();
      // 临时释放锁
      lock.lock();
    }

    {
      // 已经拥有锁 不锁定，退出栈区解锁
      mux.lock();
      std::unique_lock<std::mutex> lock(mux, std::adopt_lock);
    }
    {
      // 延后加锁 不拥有 退出栈区不解锁
      std::unique_lock<std::mutex> lock(mux, std::defer_lock);
      // 加锁 退出栈区解锁
      lock.lock();
    }
    {
      // mux.lock();
      // 尝试加锁 不阻塞 失败不拥有锁
      std::unique_lock<std::mutex> lock(mux, std::try_to_lock);

      if (lock.owns_lock()) {
        std::cout << "owns_lock" << std::endl;
      } else {
        std::cout << "not owns_lock" << std::endl;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    std::thread th(TestLockGuard, i + 1);
    th.detach();
  }
  TestMutex(1);
  TestMutex(2);

  std::cin.get();
  return 0;
}

```

析构函数(__unlock_unpack)：
```cpp
    ~scoped_lock() {
        typedef typename __make_tuple_indices<sizeof...(_MArgs)>::type _Indices;
        __unlock_unpack(_Indices{}, __t_);
    }
```
[![top] Goto Top](#table-of-contents)

## 1.17. 项目案例线程通信使用互斥锁和list实现线程通信

[thread_msg_server.md](./thread_msg_server/thread_msg_server.cpp)   
[xmsg_server.md](./thread_msg_server/xmsg_server.cpp)   
[xthread.md](./thread_msg_server/xthread.cpp)   
[xmsg_server.md](./thread_msg_server/xmsg_server.h)   
[xthread.md](./thread_msg_server/xthread.h)   

[![top] Goto Top](#table-of-contents)

## 1.18. 条件变量应用场景_生产者消费者信号处理步骤

（一）改变共享变量的线程步骤

准备好信号量

`std::condition_variable cv;`

1. 获得 std::mutex （常通过 std::unique_lock ）

`unique_lock lock(mux);`

2. 在获取锁时进行修改

`msgs_.push_back(data);`

3. 释放锁并通知读取线程

```cpp
lock.unlock();
cv.notify_one(); // 通知一个等待信号线程
cv.notify_all(); // 通知所有等待信号线程 一般是程序或者业务结束时候通知所有
```

（二）等待信号读取共享变量的线程步骤

1. 获得与改变共享变量线程共同的mutex

`unique_lock lock(mux);`

2. wait() 等待信号通知 
   2.1 无lambada 表达式
```cpp
//解锁lock,并阻塞等待 notify_one notify_all 通知
cv.wait(lock);

//接收到通知会再次获取锁标注，也就是说如果此时mux资源被占用，wait函数会阻塞
msgs_.front();

//处理数据
msgs_.pop_front();
```

  2.2 lambada 表 达 式 `cv.wait(lock, [] {return !msgs_.empty();});`

只在 `std::unique_lock<std::mutex>` 上工作的 `std::condition_variable`
```cpp
void wait(unique_lock<mutex>& _Lck) {
  // wait for signal // Nothing to do to comply with
  // LWG‐2135 because std::mutex lock/unlock are nothrow
  _Check_C_return(_Cnd_wait(_Mycnd(), _Lck.mutex()‐> _Mymtx()));
}
template <class _Predicate>
void wait(unique_lock<mutex>& _Lck, _Predicate _Pred) {
  // wait for signal and test predicate
  while (!_Pred()) {
    wait(_Lck);
  }
}
```
[![top] Goto Top](#table-of-contents)

## 1.19. condition_variable代码示例读写线程同步

一个生产者线程，写入，然后通知多个线程处理。重点是看wait函数，是否锁定的条件。

```cpp
#include <thread>
#include <iostream>
#include <mutex>
#include <list>
#include <string>
#include <sstream>

std::list<std::string> msgs_;
std::mutex mux;
std::condition_variable cv;

void ThreadWrite() {
  for (int i = 0;; i++) {
    std::stringstream ss;
    ss << "Write msg " << i;
    std::unique_lock<std::mutex> lock(mux);
    msgs_.push_back(ss.str());
    lock.unlock();  // 要先解锁，再发送信号，否则会造成死锁(在cv.wait时会对互斥量上锁)
    cv.notify_one();  // 发送信号
    // cv.notify_all();
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
}

void ThreadRead(int i) {
  for (;;) {
    std::cout << "read msg" << std::endl;
    std::unique_lock<std::mutex> lock(mux);
    // cv.wait(lock);//解锁、阻塞等待信号
    cv.wait(lock, [i] {
      std::cout << i << " wait" << std::endl;
      return !msgs_.empty();
    });
    // 获取信号后锁定
    while (!msgs_.empty()) {
      std::cout << i << " read " << msgs_.front() << std::endl;
      msgs_.pop_front();
    }
  }
}

int main(int argc, char* argv[]) {
  std::thread th(ThreadWrite);
  th.detach();
  for (int i = 0; i < 3; i++) {
    std::thread th(ThreadRead, i + 1);
    th.detach();
  }
  std::cin.get();
  return 0;
}
```

[![top] Goto Top](#table-of-contents)

## 1.20. 条件变量应用线程通信解决线程退出时的阻塞问题

[thread_msg_server_condition.cpp](./thread_msg_server_condition/thread_msg_server_condition.cpp)  
[xmsg_server.cpp](./thread_msg_server_condition/xmsg_server.cpp)  
[xthread.cpp](./thread_msg_server_condition/xthread.cpp)  
[xmsg_server.h](./thread_msg_server_condition/xmsg_server.h)  
[xthread.h](./thread_msg_server_condition/xthread.h)  

[![top] Goto Top](#table-of-contents)



## 1.21. promise和future多线程异步传值

何时获取线程结果是不确定的，也就是启动线程和获取结果是在两个接口当中。

`std::promise`和`std::future`在C++中是用于同步两个或更多并发任务的机制。试想一下，你有两个线程，这两个线程需要共享数据。在这种情况下，你可能会使用`std::promise`和`std::future`来进行同步。

让我们先来看一下每一个的基本定义：

- `std::promise`：在某个线程中储存一个值或异常，这个储存的值或异常可被另一个关联的`std::future`对象获取。

- `std::future`：在某个线程中获取一个值或异常，这个值或异常是由之前关联的`std::promise`对象设置的。

下面是一些具体的使用场景：

1. **多线程数据交换**：你可以在一个线程内设置promise，然后在另一个线程中通过与此promise对应的future来获取这个promise设定的结果。

2. **异步操作**：当你要在另一个线程中异步执行一些操作并获取结果时，可以使用promise和future机制。你先创建一个promise，然后将这个promise的future交给异步执行的函数。这个异步函数在完成计算后会设置promise的值。之后，主线程可以通过检查future的状态，或者直接调用future的get函数来获取异步操作的结果。

3. **将任务分离为生产者和消费者**：这是一种经典的并发设计模式，生产者生产数据并设置promise的值，消费者通过future获取这些数据进行处理。这样可以有效地分离两种类型的任务，提高程序的结构化和并发性能。

4. **线程间的同步**：Future对象的get()会阻塞主线程，直到promised的值被设置，这样就能保证在继续执行程序前，必要的数据或计算结果已经准备好。

一个demo：
```cpp

// #define _DEBUG
#ifdef _DEBUG

#include <iostream>
#include <cstddef>
#include <utility>
#include <iostream>
#include <future>
#include <thread>

int main() {
  // 来自 packaged_task 的 future
  std::packaged_task<int()> task([]() { return 7; });  // 包装函数
  std::future<int> f1 = task.get_future();             // 获取 future
  std::thread(std::move(task)).detach();               // 在线程上运行

  // 来自 async() 的 future
  std::future<int> f2 = std::async(std::launch::async, []() { return 8; });

  // 来自 promise 的 future
  std::promise<int> p;
  std::future<int> f3 = p.get_future();
  std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

  std::cout << "Waiting..." << std::flush;
  f1.wait();
  f2.wait();
  f3.wait();
  std::cout << "Done!\nResults are: " << f1.get() << ' ' << f2.get() << ' '
            << f3.get() << '\n';
}

#endif

#ifndef _DEBUG

#include <thread>
#include <iostream>
#include <future>
#include <string>

void TestFuture(std::promise<std::string> p) {
  std::cout << "begin TestFuture" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "begin set value" << std::endl;
  p.set_value("TestFuture value");
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "end TestFuture" << std::endl;
}

int main(int argc, char* argv[]) {
  // 异步传输变量存储
  std::promise<std::string> p;

  // 用来获取线程异步值获取
  auto future = p.get_future();

  auto th = std::thread(TestFuture, std::move(p));

  std::cout << "begin future.get()" << std::endl;
  std::cout << "future get() = " << future.get() << std::endl;
  std::cout << "end future.get()" << std::endl;
  th.join();

  std::cin.get();
  return 0;
}

#endif
```
clang编译器：
```cmd
begin future.get()
future get() = begin TestFuture
begin set value
TestFuture value
end future.get()
end TestFuture
```

MSVC编译器：
```cmd
begin future.get()
begin TestFuture
begin set value
future get() = TestFuture value
end future.get()
end TestFuture
```

总之`end future.get()`和`end TestFuture`的顺序可以看出，get返回不受线程是否退出影响的，另外get是阻塞的，一旦set_value就会取消。

[![top] Goto Top](#table-of-contents)

## 1.22. packaged_task 异步调用函数打包

```cpp
#include <thread>
#include <iostream>
#include <future>
#include <string>

std::string TestPack(int index) {
  std::cout << "begin Test Pack " << index << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟阻塞
  return "Test Pack return";
}

int main(int argc, char *argv[]) {
  std::packaged_task<std::string(int)> task(TestPack);
  auto result = task.get_future();
  std::thread th(std::move(task), 101);
  //  std::move将task的所有权从当前线程移交给新创建的线程th，因为std::packaged_task对象不可以被复制，只能被移动

  std::cout << "begin result get" << std::endl;

  // 测试是否超时
  for (int i = 0; i < 30; i++) {
    if (result.wait_for(std::chrono::milliseconds(100)) !=
        std::future_status::ready) {
      continue;
    }
  }
  if (result.wait_for(std::chrono::milliseconds(100)) ==
      std::future_status::timeout) {
    std::cout << "wait result timeout" << std::endl;
  } else
    std::cout << "result get " << result.get() << std::endl;
  th.join();

  std::cin.get();
  return 0;
}
```

这个代码演示了使用线程（特别是使用`std::packaged_task`）的几个理由和其优点：

1. **并发执行任务**：这段代码中的`TestPack`函数需要耗费2秒（由于`std::this_thread::sleep_for(std::chrono::seconds(2))`）。如果不使用线程，`main()`函数会被阻塞，直到`TestPack`函数执行完成。但是，通过在新线程中运行`TestPack`，`main()`函数可以同时执行其它任务。这样，你就可以充分利用多核CPU，并且在等待一个耗时操作（比如I/O操作）完成的同时，运行其他任务。

2. **获取异步任务的结果**： `std::packaged_task`将任务的结果存储在`std::future`对象中。`result.get()`允许你在任务完成后获得其结果。这意味着你可以在任何你想获取结果的地方获取到它，而不管它是在哪个线程中被计算出来的。

3. **方便处理耗时操作**：`std::packaged_task`和`std::future`在处理耗时操作时非常有用。例如，你可以通过检查`std::future`的状态来查看操作是否已完成，而不是不断轮询或者阻塞直到操作完成。在上述代码中，我们通过不断检查`result`的状态来查看`TestPack`函数是否已完成。

总的来说，使用线程和`std::packaged_task`，可以让代码并发执行任务，不阻塞主线程，同时便于获取异步任务的结果，处理耗时操作。  

[cppreference](https://zh.cppreference.com/w/cpp/thread/packaged_task)

类模板 std::packaged_task 包装任何可调用 (Callable) 目标（函数、 lambda 表达式、 bind 表达式或其他函数对象），使得能异步调用它。其返回值或所抛异常被存储于能通过 std::future 对象访问的共享状态中。

正如 std::function ， std::packaged_task 是多态、具分配器的容器：可在堆上或以提供的分配器分配存储的可调用对象。

```cpp
#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>

// 避免对 std::pow 重载集消歧义的独有函数
int f(int x, int y) { return std::pow(x, y); }

void task_lambda() {
  std::packaged_task<int(int, int)> task(
      [](int a, int b) { return std::pow(a, b); });
  std::future<int> result = task.get_future();

  task(2, 9);

  std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind() {
  std::packaged_task<int()> task(std::bind(f, 2, 11));
  std::future<int> result = task.get_future();

  task();

  std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread() {
  std::packaged_task<int(int, int)> task(f);
  std::future<int> result = task.get_future();

  std::thread task_td(std::move(task), 2, 10);
  task_td.join();

  std::cout << "task_thread:\t" << result.get() << '\n';
}

int main() {
  task_lambda();
  task_bind();
  task_thread();
}
```


[![top] Goto Top](#table-of-contents)

## 1.23. async创建异步线程替代thread

这段代码让我们来看看 C++ 中的异步编程。"async" 和 "future" 使用来创建和同步异步操作。

这里的 "async" 函数有两个主要作用：

1. 创建一个异步任务。该任务将在单独的线程（可能是现有的线程）上执行。通过这种方式，代码可以同时在多个线程上运行，从而改善程序的性能。
2. 返回一个 "future" 对象。这个对象代表了异步任务的结果。当异步任务完成时，可以使用 `get()` 函数从 "future" 对象中获取结果。如果调用 `get()` 时任务仍然在运行，那么调用 `get()` 的线程将阻塞，直到任务完成为止。

现在，让我们来具体看看这段代码中的异步操作。在这段代码中，我们创建了两个异步任务。我们使用了两种不同的方式来使用 `std::async` 函数：

1. 对于第一个异步任务，我们使用 `async(std::launch::deferred, TestAsync, 100)`。这里的 `std::launch::deferred` 参数意味着异步任务将会在 `future.get()` 被调用时才执行，而不是立即执行。这种方式下，并没有创建新的线程，而是复用了主线程。
   
2. 对于第二个异步任务，我们使用 `async(TestAsync, 101)`。在这个调用方式中， `std::async` 函数将立即创建一个新的线程（除非系统决定复用现有的线程）并开始执行 `TestAsync`。 `TestAsync` 任务的执行跟主线程是并行的，因此这是真正的异步调用。

你可以通过 `std::this_thread::get_id()` 的不同输出来区分是否创建了新的线程。在不创建新线程的情况下，`std::this_thread::get_id()` 的输出将会和主线程的线程 ID 相同。若是创建了新线程，则线程 ID 将会不同。  

```cpp
#include <thread>
#include <iostream>
#include <future>
#include <string>

std::string TestAsync(int index) {
  std::cout << index << " begin in TestAsync " << std::this_thread::get_id()
            << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return "TestAsync string return";
}

int main(int argc, char* argv[]) {
  std::cout << "main thread id " << std::this_thread::get_id() << std::endl;
  // 不创建线程启动异步任务
  std::cout << "==不创建线程启动异步任务==" << std::endl;
  auto future = async(std::launch::deferred, TestAsync, 100);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "begin future get " << std::endl;
  std::cout << "future.get() = " << future.get() << std::endl;
  std::cout << "end future get" << std::endl;

  // 创建异步线程
  std::cout << "=====创建异步线程====" << std::endl;
  auto future2 = async(TestAsync, 101);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "begin future2 get " << std::endl;
  std::cout << "future2.get() = " << future2.get() << std::endl;
  std::cout << "end future2 get" << std::endl;

  // 注意get只能调用一次，为了防止出错，用try catch包住

  getchar();
  return 0;
}
```
`std::async` 和 `std::thread` 都是 C++11 中用于创建并发任务的方式。不过它们的使用方式和关注点有些不同。

1. `std::thread`: 它是比较底层的线程创建和操作方式。创建一个 `std::thread` 会产生一个新的操作系统线程和对应的栈空间，并立即开始并发执行。`std::thread` 提供了更多的控制，你可以细粒度地管理和调度线程，包括线程优先级、线程间同步、线程局部存储等。但是，使用 `std::thread` 需要负责处理所有线程同步的问题，比如数据竞争、死锁等，并且还需要手动管理线程的生命周期，比如合适的调用 `join()` 或 `detach()`。`std::thread` 的使用场景通常是在性能优先，且你愿意并熟悉如何处理多线程编程中各种复杂问题的时候。

2. `std::async`和`std::future`：这是一种更高层次的并发抽象，主要关注的是任务并发，而不是线程并发。`std::async` 在创建任务的同时，返回一个`std::future`，代表异步任务的结果。`std::future::get`将阻塞等待任务完成并返回结果。任务在何时何地运行，是由实现决定的，可以是新建的线程，也可以是任务队列中的现有线程，甚至可以是调用 `get()` 的线程（当启动策略是 `std::launch::deferred` 时）。`std::async` 自动处理线程的生命周期管理，并为你处理部分线程同步问题。同时，由于使用 `std::future` 获取结果，也帮你处理了结果的返回和异常处理等问题。`std::async` 通常适用于需要并发并希望简化多线程编程的场景。

所以，你要根据实际的需求和上下文来选择使用 `std::async` 还是 `std::thread`，如果你需要对线程有更细的控制，或者需要优化到OS级别的并发，那么 `std::thread` 可能是一个更好的选择。如果你更关注任务结果，并愿意将具体的运行方式交给系统来决定，希望能简化并发编程，确保异常安全，那么 `std::async` 可能是更合适的选择。  

[![top] Goto Top](#table-of-contents)

<!-- 
c++多核计算分析并实现base16编码
c++11实现多核base16编码并与单核性能测试对比
c++17for_each多核运算示例编码base16
线程池实现步骤说明
完成线程池的初始化和启动
完成线程池任务调度
完成线程池退出并等待任务处理结束利用lambada表达式
线程池中在在运行的任务数量获取使用atomic原子变量
使用智能指针管理线程对象和任务对象的生命走起
异步获取线程池中任务执行结果
基于线程池实现音视频批量转码测试任务
完成线程池案例基于ffmpeg工具多线程转码视频
c++20屏障barrier实现线程协调 -->



<!-- figures -->
[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png