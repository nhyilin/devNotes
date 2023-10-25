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
  }

  {
    std::thread th(ThreadMain);
    std::this_thread::sleep_for(std::chrono::seconds(1));//1000ms
    is_exit = true; //通知子线程退出
    std::cout << "主线程阻塞，等待子线程退出" << std::endl;
    th.join(); //主线程阻塞，等待子线程退出
    std::cout << "子线程已经退出！" << std::endl;
  }
  getchar();

  return 0;
}
```



## 全局函数作为线程入口分析参数传递内存操作

<!-- 线程函数传递指针和引用
使用成员函数作为线程入口并封装线程基类接口
lambda临时函数作为线程入口
多线程的状态及其切换流程分析
竞争状态和临界区介绍_互斥锁mutex代码演示
互斥锁的坑_线程抢占不到资源原因和解决方法
超时锁timed_mutex和可重入锁recursive
共享锁shared_mutex解决读写问题
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



