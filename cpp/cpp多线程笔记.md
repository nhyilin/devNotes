借鉴Anthony Williams的《C++ Concurrency In Action》一书

<!--more-->

[C++ Concurrency In Action 2ed](https://github.com/anthonywilliams/ccia_code_samples)

## 线程代码示例
```cpp
#include <thread>
#include <iostream>
//Linux -lpthread
using namespace std;
void ThreadMain()
{
    cout << "begin sub thread main " << this_thread::get_id() << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "in thread " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));//1000ms
    }
    cout << "end sub thread main " << this_thread::get_id() << endl;
}
int main(int argc, char* argv[])
{
    cout << "main thread ID " << this_thread::get_id() << endl;
    //线程创建启动
    thread th(ThreadMain);
    cout << "begin wait sub thread  "<< endl;
    //阻塞等待子线程退出
    th.join();
    cout << "end wait sub thread  " << endl;
    return 0;
}
```


## 对象生命周期和线程等待和分离

```cpp
#include <thread>
#include <iostream>
//Linux -lpthread

bool is_exit = false;
void ThreadMain() {
  std::cout << "begin sub thread main " << std::this_thread::get_id() << std::endl;
  for (int i = 0; i < 10; i++) {
    if (!is_exit) break;
    std::cout << "in thread " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));//1000ms
  }
  std::cout << "end sub thread main " << std::this_thread::get_id() << std::endl;
}
int main(int argc, char *argv[]) {
  {
    //thread th(ThreadMain); //出错，thread对象被销毁 子线程还在运行
  }

  {
    std::thread th(ThreadMain);
    th.detach(); //子线程与主线程分离 守护线程
    //坑 ：主线程退出后 子线程不一定退出
    // 可能造成的问题是主线程推出(主程序退出)，程序报错(主线程退出，全部资源释放)
    // 一般解决方案：通过 is_exit 来控制，起到通知作用
    // 如果不做 detach，则必须维护 th 对象
  }

  {
    std::thread th(ThreadMain);
    std::this_thread::sleep_for(std::chrono::seconds(1));//1000ms
    is_exit = true; //通知子线程退出
    std::cout << "主线程阻塞，等待子线程退出" << std::endl;
    th.join(); //主线程阻塞，等待子线程退出
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

## 全局函数作为线程入口分析参数传递内存操作

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

## 线程函数传递指针和引用

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

## 使用成员函数作为线程入口并封装线程基类接口

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

## lambda临时函数作为线程入口

```cpp
#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
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

## 多线程的状态及其切换流程分析

线程状态说明：
1. 初始化：线程正在创建
   - 初始化内存空间等，代码干预不多，从初始化到就绪有一定的消耗，所以才会引入线程池，为了减少类似消耗
2. 就绪：线程在就绪列表中，等待CPU调度
3. 运行：该线程正在运行
4. 阻塞：线程被阻塞挂起。Blocked状态包括：pend(锁、事件、信号量等阻塞)、suspend(主动pend)、delay(延时阻塞)、pendtime(因为锁、事件、信号量事件等超时等待)
5. 退出：线程运行结束，等待父线程回收其控制块资源(栈等，不会释放线程运行中创建的堆资源)

## 竞争状态和临界区介绍_互斥锁mutex代码演示

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

## 互斥锁的坑_线程抢占不到资源原因和解决方法

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
// Linux -lpthread

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
## 超时锁timed_mutex和可重入锁recursive

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

## 共享锁shared_mutex解决读写问题

```cpp
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
// Linux -lpthread

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

<!-- 



手动实现RAII管理mutex资源_锁自动释放
c++11RAII控制锁lock_guard
unique_lock可临时解锁控制超时的互斥体包装器
C++14shared_lock共享锁包装器
c++17scoped_lock解决互锁造成的死锁问题
项目案例线程通信使用互斥锁和list实现线程通信
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

