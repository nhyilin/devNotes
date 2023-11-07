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
  - [C++14shared\_lock共享锁包装器](#c14shared_lock共享锁包装器)
  - [c++17scoped\_lock解决互锁造成的死锁问题](#c17scoped_lock解决互锁造成的死锁问题)
  - [项目案例线程通信使用互斥锁和list实现线程通信](#项目案例线程通信使用互斥锁和list实现线程通信)


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
  getchar();
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

## C++14shared_lock共享锁包装器

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

## c++17scoped_lock解决互锁造成的死锁问题

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

  getchar();
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

## 项目案例线程通信使用互斥锁和list实现线程通信




[![top] Goto Top](#table-of-contents)
<!-- 
条件变量应用场景_生产者消费者信号处理步骤
condition_variable代码示例读写线程同步
条件变量应用线程通信解决线程退出时的阻塞问题
promise和future多线程异步传值
packaged_task 异步调用函数打包
async创建异步线程替代thread
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