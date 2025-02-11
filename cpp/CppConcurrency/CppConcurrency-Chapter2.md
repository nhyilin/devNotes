
《C++ Concurrency In Action 2ed》（第2章 线程管理）

<!--more-->

# Table of Contents
- [Table of Contents](#table-of-contents)
  - [2.1 线程的基本操作](#21-线程的基本操作)
    - [线程的基本概念](#线程的基本概念)
    - [线程的启动](#线程的启动)
    - [线程的等待与分离](#线程的等待与分离)
      - [等待线程完成 (`join`)](#等待线程完成-join)
      - [分离线程 (`detach`)](#分离线程-detach)
    - [线程生命周期管理](#线程生命周期管理)
      - [避免局部变量的引用问题](#避免局部变量的引用问题)
      - [使用RAII管理线程](#使用raii管理线程)
      - [异常安全](#异常安全)
    - [后台线程（守护线程）](#后台线程守护线程)
    - [总结](#总结)
  - [2.2 传递参数](#22-传递参数)
    - [基本用法](#基本用法)
    - [字符串字面量的隐式转换问题](#字符串字面量的隐式转换问题)
    - [传递引用参数](#传递引用参数)
    - [传递成员函数指针](#传递成员函数指针)
    - [传递只支持移动的对象](#传递只支持移动的对象)
    - [总结](#总结-1)
  - [2.3 转移所有权](#23-转移所有权)
    - [时需要转移所有权？](#时需要转移所有权)
    - [函数中转移线程所有权](#函数中转移线程所有权)
    - [封装线程所有权](#封装线程所有权)
    - [量产线程](#量产线程)
    - [总结](#总结-2)
  - [2.4 确定线程数量](#24-确定线程数量)
    - [背景知识](#背景知识)
    - [基本语法](#基本语法)
    - [参数说明](#参数说明)
    - [返回值](#返回值)
    - [使用示例](#使用示例)
      - [1. 简单求和](#1-简单求和)
      - [2. 求积](#2-求积)
      - [3. 字符串连接](#3-字符串连接)
      - [4. 自定义操作](#4-自定义操作)
    - [2. 代码结构解析](#2-代码结构解析)
      - [(1) `accumulate_block` 结构体](#1-accumulate_block-结构体)
      - [(2) `parallel_accumulate` 函数](#2-parallel_accumulate-函数)
        - [a. 输入检查](#a-输入检查)
        - [b. 计算线程数](#b-计算线程数)
        - [c. 划分任务块](#c-划分任务块)
        - [d. 处理最后一个任务块](#d-处理最后一个任务块)
        - [e. 等待线程完成](#e-等待线程完成)
        - [f. 汇总结果](#f-汇总结果)
    - [3. 总结代码流程](#3-总结代码流程)
    - [4. 注意事项](#4-注意事项)
    - [5. 扩展](#5-扩展)
  - [ Goto Top](#-goto-top)
  - [2.5 线程标识](#25-线程标识)
    - [1. 什么是线程标识？](#1-什么是线程标识)
    - [2. 获取线程标识的两种方式](#2-获取线程标识的两种方式)
    - [3. 线程标识的特性](#3-线程标识的特性)
    - [4. 使用场景](#4-使用场景)
      - [4.1 检测线程是否需要执行某些操作](#41-检测线程是否需要执行某些操作)
      - [4.2 线程信息存储](#42-线程信息存储)
      - [4.3 输出线程标识](#43-输出线程标识)
    - [5. 实际应用](#5-实际应用)
    - [总结](#总结-3)


---

## 2.1 线程的基本操作

### 线程的基本概念
- 每个C++程序至少有一个主线程，负责执行`main()`函数。
- 新线程可以通过`std::thread`对象启动，线程的生命周期由其关联的函数或任务决定。
- 当线程的任务函数执行完毕，线程会自动退出。

---

### 线程的启动
- 使用`std::thread`对象启动线程：
  ```cpp
  void do_some_work();
  std::thread my_thread(do_some_work);
  ```
  线程启动后会执行`do_some_work()`。

- 也可以使用可调用对象（如类的`operator()`）启动线程：
  ```cpp
  class background_task {
  public:
      void operator()() const {
          do_something();
          do_something_else();
      }
  };

  background_task f;
  std::thread my_thread(f);
  ```

- 注意避免“最令人头痛的语法解析问题”（Most Vexing Parse）：
  ```cpp
  std::thread my_thread(background_task()); // 被解析为函数声明
  ```
  **解决方法**：
  - 使用额外的括号：
    ```cpp
    std::thread my_thread((background_task()));
    ```
  - 使用统一初始化语法：
    ```cpp
    std::thread my_thread{background_task()};
    ```
  - 使用Lambda表达式：
    ```cpp
    std::thread my_thread([] {
        do_something();
        do_something_else();
    });
    ```

---

### 线程的等待与分离
#### 等待线程完成 (`join`)
- 使用`join()`可以等待线程完成：
  ```cpp
  std::thread t(do_some_work);
  t.join(); // 阻塞当前线程，直到`t`完成
  ```
- `join()`会清理线程相关的资源，调用后`std::thread`对象不再与线程关联。
- 一个线程只能`join`一次。

#### 分离线程 (`detach`)
- 使用`detach()`将线程与`std::thread`对象分离，线程会在后台运行：
  ```cpp
  std::thread t(do_background_work);
  t.detach();
  ```
- 分离的线程无法再通过`std::thread`对象控制，线程的资源会在其完成后自动回收。

**注意**

- 在`std::thread`对象销毁前，必须对其调用`join()`或`detach()`，否则会导致程序终止（调用`std::terminate()`）。

---

### 线程生命周期管理
#### 避免局部变量的引用问题
- 如果线程函数中使用了局部变量的引用，而线程未完成时局部变量已经销毁，会导致未定义行为：
  ```cpp
  struct func {
      int& i;
      func(int& i_) : i(i_) {}
      void operator()() {
          for (unsigned j = 0; j < 1000000; ++j) {
              do_something(i); // 可能访问已销毁的局部变量
          }
      }
  };

  void oops() {
      int some_local_state = 0;
      func my_func(some_local_state);
      std::thread my_thread(my_func);
      my_thread.detach(); // 分离线程
  } // some_local_state 被销毁，但线程仍在运行
  ```

- **解决方法**：
  - 将局部变量复制到线程中，而不是传引用。
  - 使用`join()`确保线程结束后再销毁局部变量。

#### 使用RAII管理线程
- RAII（资源获取即初始化）模式可以确保线程在异常或函数退出时正确管理：
  ```cpp
  class thread_guard {
      std::thread& t;
  public:
      explicit thread_guard(std::thread& t_) : t(t_) {}
      ~thread_guard() {
          if (t.joinable()) {
              t.join();
          }
      }
      thread_guard(const thread_guard&) = delete;
      thread_guard& operator=(const thread_guard&) = delete;
  };

  void f() {
      int some_local_state = 0;
      func my_func(some_local_state);
      std::thread t(my_func);
      thread_guard g(t); // RAII管理线程
      do_something_in_current_thread();
  } // thread_guard析构时会调用t.join()
  ```

#### 异常安全
- 在异常处理中也要确保线程正确`join`：
  ```cpp
  void f() {
      int some_local_state = 0;
      func my_func(some_local_state);
      std::thread t(my_func);
      try {
          do_something_in_current_thread();
      } catch (...) {
          t.join(); // 确保线程结束
          throw;
      }
      t.join();
  }
  ```

---

### 后台线程（守护线程）
- 使用`detach()`可以创建后台线程（守护线程），这种线程通常用于执行长期任务或后台监控：
  ```cpp
  void edit_document(std::string const& filename) {
      open_document_and_display_gui(filename);
      while (!done_editing()) {
          user_command cmd = get_user_input();
          if (cmd.type == open_new_document) {
              std::string const new_name = get_filename_from_user();
              std::thread t(edit_document, new_name); // 启动新线程
              t.detach(); // 分离线程
          } else {
              process_user_input(cmd);
          }
      }
  }
  ```

- **适用场景**：
  - 长期运行的任务（如文件监控、缓存清理等）。
  - 不需要主线程直接交互的任务。

---

### 总结
- 使用`std::thread`可以方便地启动线程，但需要注意线程的生命周期管理。
- **等待线程**：
  - 使用`join()`确保线程完成后释放资源。
  - 使用RAII模式或异常处理机制避免线程未正确结束。
- **分离线程**：
  - 使用`detach()`让线程在后台运行，但要确保线程的任务不会依赖已销毁的资源。
- **避免问题**：
  - 避免线程函数中持有局部变量的引用。
  - 谨慎处理异常，确保线程安全。


[![top] Goto Top](#table-of-contents)

---



## 2.2 传递参数

在C++中，使用 `std::thread` 创建线程时，可以为线程函数传递参数。传递参数的方式很灵活，但需要注意一些细节，避免潜在的陷阱。

---

### 基本用法

在创建线程时，可以将参数直接传递给 `std::thread` 的构造函数。参数会被拷贝到新线程的上下文中。

```cpp
void f(int i, std::string const& s); // 一个线程函数

std::thread t(f, 3, "hello"); // 创建线程，传递参数3和"hello"
```

- **参数拷贝**：
  - 在例子中，`std::thread` 将参数 `3` 和 `"hello"` 传递给函数 `f`。
  - 注意：`std::thread` 会将参数拷贝到新线程中，即使函数参数是引用类型。

---

### 字符串字面量的隐式转换问题

如果将字符串字面量（如 `"hello"）传递到一个期望 `std::string` 类型的参数中， `std::thread` 会隐式地将其转换为 `std::string`。但需要小心动态分配的临时对象。

**错误示例：**
```cpp
void f(int i, std::string const& s);

void oops(int some_param) {
    char buffer[1024];  // 临时字符数组
    sprintf(buffer, "%i", some_param); // 格式化字符串
    std::thread t(f, 3, buffer); // 错误！buffer可能在线程运行前被销毁
    t.detach();
}
```

- **问题**：
  - `buffer` 是局部变量，在线程启动前可能已经销毁。
  - 线程可能访问到无效的指针，导致未定义行为。

**解决办法**：
在传递参数前，显式地将 `buffer` 转换为 `std::string`，以确保线程拥有独立的拷贝。

```cpp
std::thread t(f, 3, std::string(buffer)); // 显式转换为std::string
```

---

### 传递引用参数

如果线程函数需要引用参数，直接传递会导致 `std::thread` 拷贝参数，而不是传递引用。这会导致编译错误。

**错误示例：**
```cpp
void update_data(int& data); // 线程函数需要引用参数

int value = 42;
std::thread t(update_data, value); // 错误！期望引用，但传递了拷贝
```

**解决办法**：
使用 `std::ref` 包装引用参数，显式地告诉 `std::thread` 传递引用。

```cpp
std::thread t(update_data, std::ref(value)); // 使用std::ref传递引用
```

- `std::ref` 是一个辅助函数，用于创建 `std::reference_wrapper` 对象，保证参数以引用的形式传递。

---

### 传递成员函数指针

可以将类的成员函数作为线程函数传递，但需要同时提供该成员函数所属的对象。

**示例：**
```cpp
class X {
public:
    void do_work(int value) {
        // 成员函数
    }
};

X x;
std::thread t(&X::do_work, &x, 42); // 调用x.do_work(42)
```

- 第一个参数是成员函数指针（`&X::do_work`）。
- 第二个参数是对象指针（`&x`）。
- 后续参数是传递给成员函数的参数（`42`）。

---

### 传递只支持移动的对象

有些对象类型（如 `std::unique_ptr`）只能通过移动语义传递，而不能拷贝。对于这些类型，需要显式地使用 `std::move`。

**示例：**
```cpp
void process(std::unique_ptr<int> p);

std::unique_ptr<int> ptr(new int(42));
std::thread t(process, std::move(ptr)); // 使用std::move转移所有权
```

- `std::move` 将 `ptr` 的所有权转移到线程中。
- 线程函数 `process` 将接管 `std::unique_ptr` 的所有权。

---

### 总结

- **参数传递方式**：
  - 默认情况下，`std::thread` 会拷贝参数到新线程中。
  - 使用 `std::ref` 可以传递引用。
  - 使用 `std::move` 可以传递只支持移动的对象。

- **注意事项**：
  - 避免传递局部变量的指针或引用，防止线程访问到销毁的变量。
  - 显式转换动态分配的临时对象，确保线程拥有独立的拷贝。



[![top] Goto Top](#table-of-contents)


---

## 2.3 转移所有权

**背景**

在C++中，`std::thread` 对象拥有线程的所有权。这意味着每个 `std::thread` 实例负责管理一个线程的生命周期。为了确保线程的所有权是唯一的，`std::thread` 对象是**不可复制的**（`non-copyable`），但它是**可移动的**（`movable`）。这允许我们在程序中将线程的所有权从一个 `std::thread` 对象转移到另一个对象。

### 时需要转移所有权？

转移线程所有权的场景包括：
1. **将新创建的线程返回给调用者**：一个函数创建线程并将其返回给调用者，而不是自己管理线程。
2. **将线程的管理权交给另一个函数**：一个函数创建线程后，将其所有权转交给另一个函数进行管理。
3. **容器管理线程**：当需要将多个线程存储在容器（如 `std::vector`）中时，线程对象需要支持移动操作。

---

**示例代码**

以下是一个展示如何转移线程所有权的代码示例：

```cpp
void some_function();
void some_other_function();

std::thread t1(some_function);        // 创建线程 t1
std::thread t2 = std::move(t1);       // 将 t1 的线程所有权转移给 t2

t1 = std::thread(some_other_function); // t1 现在管理一个新线程
std::thread t3;                        // 创建一个空的线程对象
t3 = std::move(t2);                    // 将 t2 的线程所有权转移给 t3

t1 = std::move(t3);                    // 将 t3 的线程所有权转移回 t1
```

---

**代码解析**

1. **创建线程并转移所有权**
   - `std::thread t1(some_function);`：创建一个线程 `t1`，它运行 `some_function`。
   - `std::thread t2 = std::move(t1);`：将 `t1` 的线程所有权转移给 `t2`。此时，`t1` 不再管理任何线程。

2. **重新赋值线程**
   - `t1 = std::thread(some_other_function);`：将 `t1` 重新赋值为一个新线程，运行 `some_other_function`。

3. **空线程对象**
   - `std::thread t3;`：创建一个空的线程对象 `t3`。
   - `t3 = std::move(t2);`：将 `t2` 的线程所有权转移给 `t3`。

4. **防止未管理线程**
   - `t1 = std::move(t3);`：将 `t3` 的线程所有权转移回 `t1`。注意：如果 `t1` 在转移之前已经管理了一个线程，而该线程未被显式 `join()` 或 `detach()`，则会导致程序异常终止（调用 `std::terminate()`）。

---

**注意事项**

1. **线程对象的生命周期**
   - 在 `std::thread` 的生命周期结束时，必须确保线程已被 `join()` 或 `detach()`，否则程序会调用 `std::terminate()`。
   - 如果需要转移所有权，务必在转移前处理旧的线程对象。

2. **`std::move` 的使用**
   - 转移所有权时，必须使用 `std::move()`，因为线程对象是不可复制的。

3. **线程对象的空状态**
   - 转移所有权后，原线程对象进入“空状态”（即不再管理任何线程）。可以通过调用 `joinable()` 检查线程对象是否仍然管理线程。

---

### 函数中转移线程所有权
线程所有权的转移也可以通过函数返回值实现。例如：

```cpp
std::thread create_thread() {
    void some_function();
    return std::thread(some_function); // 返回一个线程对象，调用者接管所有权
}

void use_thread() {
    std::thread t = create_thread(); // 接管线程所有权
    t.join(); // 确保线程完成
}
```

在这个例子中，`create_thread()` 创建一个线程并将其返回，调用者负责管理线程的生命周期。

当所有权可以在函数内部传递，就允许`std::thread`实例作为参数进行传递，代码如下：

```c++
void f(std::thread t);
void g()
{
  void some_function();
  f(std::thread(some_function));
  std::thread t(some_function);
  f(std::move(t));
}
```

---

### 封装线程所有权
可以通过封装来简化线程所有权的管理，例如使用 `scoped_thread`：

```cpp
class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
        if (!t.joinable()) {
            throw std::logic_error("No thread");
        }
    }
    ~scoped_thread() {
        t.join(); // 确保线程完成
    }
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
};
```

此类会在析构时自动调用 `join()`，确保线程被正确管理。

---

### 量产线程

```c++
void do_work(unsigned id);

void f()
{
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < 20; ++i)
  {
    threads.emplace_back(do_work,i); // 产生线程
  } 
  for (auto& entry : threads) // 对每个线程调用 join()
    entry.join();       
}
```

我们有时需要线程去分割一个算法的工作总量，所以在算法结束的之前，所有的线程必须结束。代码2.8中线程所做的工作都是独立的，并且结果仅会受到共享数据的影响。如果f()有返回值，这个返回值就依赖于线程得到的结果。写入返回值之前，程序会检查使用共享数据的线程是否终止。结果在不同线程中转移的方案，会在第4章中再次讨论。

将`std::thread`放入`std::vector`是向线程自动化管理迈出的第一步：并非为这些线程创建独立的变量，而是把它们当做一个组。创建一组线程\(数量在运行时确定\)，而非代码2.8那样创建固定数量的线程。


### 总结
- C++ 中的 `std::thread` 是 **不可复制** 的，但可以通过 `std::move` 转移所有权。
- 转移线程所有权时，确保线程对象未管理线程，或已正确处理（`join()` 或 `detach()`）。
- 使用封装类（如 `scoped_thread`）可以简化线程管理，避免资源泄漏。

[![top] Goto Top](#table-of-contents)

---

## 2.4 确定线程数量

这个例子主要是实现一个**并行版本的`std::accumulate`**，通过多线程加速累加操作。


### 背景知识
- **`std::accumulate`**：
  - 是标准库中的一个函数，用于对一个范围内的元素进行累加。
  - 它是串行的（单线程），所以在处理大量数据时性能会受到限制。
  
- **并行化的目标**：
  - 将数据分成多个块，每个线程处理一部分数据，最后汇总所有线程的结果。
  - 通过并行化，充分利用多核 CPU 的性能。


`std::accumulate` 是 C++ 标准库 `<numeric>` 头文件中提供的一个函数模板，用于对范围内的元素进行累积操作（即求和、求积或其他自定义操作）。它是一个非常灵活且强大的工具。

### 基本语法

```cpp
#include <numeric>

template<class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init);

template<class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation op);
```

### 参数说明

1. **`first` 和 `last`**:
   - 表示输入范围的起始迭代器和结束迭代器，范围是 `[first, last)`，即包含 `first` 指向的元素，但不包含 `last`。

2. **`init`**:
   - 累积操作的初始值，累积操作从这个值开始。

3. **`op`**（可选）:
   - 自定义的二元操作函数或函数对象。默认情况下是加法操作。

### 返回值

- 返回累积操作的结果，类型与 `init` 相同。


### 使用示例

#### 1. 简单求和
默认情况下，`std::accumulate` 使用加法操作：

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int sum = std::accumulate(vec.begin(), vec.end(), 0); // 初始值为 0
    std::cout << "Sum: " << sum << std::endl; // 输出 15
    return 0;
}
```

#### 2. 求积
通过自定义操作符可以实现其他累积操作，例如求积：

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
    std::cout << "Product: " << product << std::endl; // 输出 120
    return 0;
}
```

#### 3. 字符串连接
`std::accumulate` 不仅可以用于数值，还可以用于字符串等其他类型：

```cpp
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> words = {"Hello", " ", "World", "!"};
    std::string result = std::accumulate(words.begin(), words.end(), std::string(""));
    std::cout << "Result: " << result << std::endl; // 输出 "Hello World!"
    return 0;
}
```

#### 4. 自定义操作
可以使用自定义的二元函数：

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int custom = std::accumulate(vec.begin(), vec.end(), 0, [](int a, int b) {
        return a + b * 2; // 每个元素乘以 2 后再累加
    });
    std::cout << "Custom result: " << custom << std::endl; // 输出 30
    return 0;
}
```


---

### 2. 代码结构解析

完整代码如下：

```c++
template<typename Iterator,typename T>
struct accumulate_block
{
  void operator()(Iterator first,Iterator last,T& result)
  {
    result=std::accumulate(first,last,result);
  }
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{
  unsigned long const length=std::distance(first,last);

  if(!length) // 1
    return init;

  unsigned long const min_per_thread=25;
  unsigned long const max_threads=
      (length+min_per_thread-1)/min_per_thread; // 2

  unsigned long const hardware_threads=
      std::thread::hardware_concurrency();

  unsigned long const num_threads=  // 3
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size=length/num_threads; // 4

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads-1);  // 5

  Iterator block_start=first;
  for(unsigned long i=0; i < (num_threads-1); ++i)
  {
    Iterator block_end=block_start;
    std::advance(block_end,block_size);  // 6
    threads[i]=std::thread(     // 7
        accumulate_block<Iterator,T>(),
        block_start,block_end,std::ref(results[i]));
    block_start=block_end;  // 8
  }
  accumulate_block<Iterator,T>()(
      block_start,last,results[num_threads-1]); // 9
      
  for (auto& entry : threads)
    entry.join();  // 10

  return std::accumulate(results.begin(),results.end(),init); // 11
}
```

以下是代码的核心部分及其功能解释：

#### (1) `accumulate_block` 结构体
```cpp
template<typename Iterator, typename T>
struct accumulate_block
{
  void operator()(Iterator first, Iterator last, T& result)
  {
    result = std::accumulate(first, last, result);
  }
};
```
- **功能**：这是一个可调用对象（仿函数），用于对指定范围的元素进行累加。
- **参数**：
  - `first` 和 `last`：范围的起始和结束迭代器。
  - `result`：存储累加结果的变量。
- **实现**：调用标准库的 `std::accumulate`，对范围 `[first, last)` 内的元素求和，并将结果存储到 `result` 中。

---

#### (2) `parallel_accumulate` 函数
这是整个并行化逻辑的核心部分。

##### a. 输入检查
```cpp
unsigned long const length = std::distance(first, last);
if (!length) // 如果范围为空
  return init;
```
- **功能**：检查输入范围是否为空。如果为空，直接返回初始值 `init`。

---

##### b. 计算线程数
```cpp
unsigned long const min_per_thread = 25;
unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;

unsigned long const hardware_threads = std::thread::hardware_concurrency();

unsigned long const num_threads = 
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
```
- **目的**：确定需要启动的线程数。
- **逻辑**：
  1. **`min_per_thread`**：每个线程处理的最小任务数，避免创建太多线程。
  2. **`max_threads`**：根据数据量和 `min_per_thread` 计算出理论上的最大线程数。
  3. **`hardware_threads`**：获取硬件支持的并发线程数。
      - 如果无法获取（返回值为 0），默认使用 2。
  4. **`num_threads`**：取硬件线程数和 `max_threads` 的较小值，确保线程数合理。



在这段代码中，使用 `unsigned long` 而不是 `int` 类型的原因主要与以下几个方面有关：

1. **避免负值**
   - `unsigned long` 是无符号类型，而 `int` 是有符号类型。
   - 在这段代码中，`min_per_thread` 和 `max_threads` 都是表示线程数量或长度的值，这些值本质上是非负的。
   - 如果使用 `int`，可能会引入负数的风险（例如，由于计算错误或溢出），而这些值本身不应该为负数。
   - 使用 `unsigned long` 可以明确表达这些值只能是非负的，避免负值带来的逻辑问题。
2. **防止溢出**
   - `unsigned long` 通常比 `int` 能表示更大的范围（具体范围取决于平台和编译器）。例如：
   - 在 32 位系统上，`int` 通常是 32 位，范围为 `-2,147,483,648` 到 `2,147,483,647`。
  - 而 `unsigned long` 通常是 32 位或更大，范围为 `0` 到 `4,294,967,295`（或更大）。
   - 如果 `length` 是一个非常大的值（例如表示一个超长数组的长度），使用 `int` 可能会导致溢出，而 `unsigned long` 能更安全地处理大范围的值。
3. **与硬件线程数量的兼容性**
   - `std::thread::hardware_concurrency()` 返回值的类型是 `unsigned int`，表示硬件支持的并发线程数。
   - 为了兼容性，代码中使用了一个更宽泛的类型 `unsigned long`，以确保在不同平台上不会因为类型不匹配而导致问题。
4. **表达意图**
   - 使用 `unsigned long` 明确表达了这些值是非负的，并且可能需要处理较大的范围。
   - 这是一种编码风格上的选择，旨在提高代码的可读性和可维护性。
5. **性能影响**
   - 在大多数情况下，`unsigned long` 和 `int` 的性能差异可以忽略不计。
   - 选择 `unsigned long` 是为了更好地适应可能的大范围值，而不是因为性能原因。


---

##### c. 划分任务块
```cpp
unsigned long const block_size = length / num_threads;

std::vector<T> results(num_threads);
std::vector<std::thread> threads(num_threads - 1);

Iterator block_start = first;
for (unsigned long i = 0; i < (num_threads - 1); ++i)
{
  Iterator block_end = block_start;
  std::advance(block_end, block_size);

  threads[i] = std::thread(
      accumulate_block<Iterator, T>(),
      block_start, block_end, std::ref(results[i]));

  block_start = block_end;
}
```
- **核心逻辑**：
  1. **每个线程处理的任务块大小**：`block_size = length / num_threads`。
  2. **存储中间结果**：用 `std::vector<T> results` 存储每个线程的计算结果。
  3. **存储线程对象**：用 `std::vector<std::thread> threads` 保存所有线程。
  4. **任务分配**：
     - 使用 `std::advance` 将迭代器 `block_start` 移动到当前块的末尾。
     - 创建线程，调用 `accumulate_block` 对当前块进行累加。
     - 将累加结果存储到 `results[i]` 中。

---

##### d. 处理最后一个任务块
```cpp
accumulate_block<Iterator, T>()(
    block_start, last, results[num_threads - 1]);
```
- **功能**：主线程处理最后一个任务块。
- **原因**：线程数比任务块数少 1，因此最后一个任务块由主线程完成。

---

##### e. 等待线程完成
```cpp
for (auto& entry : threads)
  entry.join();
```
- **功能**：等待所有线程完成任务（调用 `join`）。

---

##### f. 汇总结果
```cpp
return std::accumulate(results.begin(), results.end(), init);
```
- **功能**：对 `results` 中的中间结果进行累加，得到最终结果。

---

### 3. 总结代码流程
1. 检查输入范围是否为空。
2. 根据数据量和硬件支持，计算需要启动的线程数。
3. 将数据划分为多个任务块。
4. 创建线程并分配任务块，计算中间结果。
5. 主线程处理最后一个任务块。
6. 等待所有线程完成。
7. 汇总中间结果，返回最终结果。

---

### 4. 注意事项
- **线程数的选择**：
  - 线程数过多会导致上下文切换开销，性能反而下降。
  - 线程数过少可能无法充分利用多核 CPU 的性能。
  
- **结果的准确性**：
  - 如果 `T` 是浮点类型（如 `float` 或 `double`），并行化可能导致结果与串行版本不同（因为加法不满足结合律）。
  
- **迭代器要求**：
  - 必须是前向迭代器（如 `std::vector` 的迭代器）。

---

### 5. 扩展
- 在 C++17 中，可以直接使用 `std::reduce` 实现并行累加，它是 `std::accumulate` 的并行版本，避免了手动管理线程的复杂性。

[![top] Goto Top](#table-of-contents)
---



## 2.5 线程标识

### 1. 什么是线程标识？
线程标识是用来唯一标识一个线程的对象，其类型为`std::thread::id`。它是C++标准线程库中用于区分不同线程的工具。

- **线程标识的类型**：`std::thread::id`。
- **默认值**：如果线程标识没有关联到任何线程，则它会有一个默认构造值，表示“无线程”。

---

### 2. 获取线程标识的两种方式
1. **通过`std::thread`对象获取**：
   - 调用`std::thread`对象的成员函数`get_id()`可以获取该线程的标识。
   - 如果该`std::thread`对象没有关联到任何线程，`get_id()`将返回默认的“无线程”值。

   ```c++
   std::thread t([]{ /*线程任务*/ });
   std::cout << t.get_id(); // 输出线程t的ID
   t.join();
   ```

2. **通过当前线程获取**：
   - 调用`std::this_thread::get_id()`可以获取当前线程的标识。
   - 这个函数定义在`<thread>`头文件中。

   ```c++
   std::cout << std::this_thread::get_id(); // 输出当前线程的ID
   ```

---

### 3. 线程标识的特性
- **可复制和比较**：
  - `std::thread::id`对象可以自由地拷贝和比较。
  - 如果两个`std::thread::id`对象相等，则它们要么代表同一个线程，要么都表示“无线程”。
  - 如果不相等，则说明它们是不同的线程，或者一个有线程，一个没有线程。

- **排序和哈希支持**：
  - `std::thread::id`支持比较操作（如`<`、`>`），这意味着可以作为排序容器的键值。
  - 标准库还提供了`std::hash<std::thread::id>`，因此可以将`std::thread::id`作为无序容器（如`std::unordered_map`）的键值。

---

### 4. 使用场景
#### 4.1 检测线程是否需要执行某些操作
在多线程程序中，可以通过线程标识来区分主线程和其他线程，从而决定是否执行特定操作。例如：

```c++
std::thread::id master_thread;

void some_core_part_of_algorithm()
{
    if (std::this_thread::get_id() == master_thread)
    {
        do_master_thread_work(); // 主线程的特殊工作
    }
    do_common_work(); // 所有线程的通用工作
}
```

#### 4.2 线程信息存储
线程标识可以用作容器的键值，用来存储线程相关的信息。例如：
- 用`std::thread::id`作为键值存储线程的状态。
- 在多线程间传递信息时，用线程标识来区分不同的线程。

#### 4.3 输出线程标识
可以通过`std::cout`输出线程标识的值，用于调试或日志记录：

```c++
std::cout << std::this_thread::get_id();
```

**注意**：线程标识的输出结果依赖于具体的实现，C++标准只要求相同的线程必须有相同的输出。

---

### 5. 实际应用
- **线程区分**：在多线程程序中区分主线程和工作线程。
- **线程数据管理**：用线程标识作为键值，存储线程相关的数据或状态。
- **调试和日志记录**：通过线程标识帮助定位问题。

---

### 总结
- `std::thread::id`是C++中用于标识线程的工具。
- 可以通过`std::thread::get_id()`或`std::this_thread::get_id()`获取。
- 具有可比较、可排序、支持哈希等特性。
- 常用于线程区分、数据存储和调试。



[![top] Goto Top](#table-of-contents)

<!-- figures -->
[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png