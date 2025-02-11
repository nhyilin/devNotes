
《C++ Concurrency In Action 2ed》（第3章 共享数据）

<!--more-->

[第2 章 线程管理](https://nhyilin.cn/default/25.html)

# Table of Contents
- [Table of Contents](#table-of-contents)
  - [3.1 使用互斥量](#31-使用互斥量)
    - [1. 不变量的破坏](#1-不变量的破坏)
    - [2. 条件竞争](#2-条件竞争)
    - [3. 恶性条件竞争的特性](#3-恶性条件竞争的特性)
    - [4. 避免恶性条件竞争的方法](#4-避免恶性条件竞争的方法)
    - [5. 调试难点](#5-调试难点)
  - [3.2 使用互斥量](#32-使用互斥量)
    - [3.2.1 互斥量](#321-互斥量)
      - [核心概念](#核心概念)
      - [使用方式](#使用方式)
      - [示例代码：使用`std::mutex`和`std::lock_guard`](#示例代码使用stdmutex和stdlock_guard)
      - [C++17 的改进](#c17-的改进)
      - [面向对象的设计](#面向对象的设计)
      - [注意事项](#注意事项)
      - [总结](#总结)
    - [3.2.2 保护共享数据](#322-保护共享数据)
    - [3.2.3 接口间的条件竞争](#323-接口间的条件竞争)
      - [**问题描述**](#问题描述)
      - [**例子：栈（`std::stack`）的问题**](#例子栈stdstack的问题)
      - [**接口设计的问题**](#接口设计的问题)
      - [**解决方案**](#解决方案)
      - [**总结**](#总结-1)
    - [3.2.4 死锁：问题描述及解决方案](#324-死锁问题描述及解决方案)
    - [3.2.4 死锁：问题描述及解决方案](#324-死锁问题描述及解决方案-1)
      - [1. **问题描述**](#1-问题描述)
      - [2. **死锁的解决方法**](#2-死锁的解决方法)
        - [**(1) 使用`std::lock`**](#1-使用stdlock)
        - [**(2) 使用`std::scoped_lock`**](#2-使用stdscoped_lock)
      - [3. **注意事项**](#3-注意事项)
      - [4. **总结**](#4-总结)



---
## 3.1 使用互斥量

当多个线程同时访问共享数据时，如果数据只读，则不会出现问题；但如果有线程需要修改共享数据，则可能引发复杂问题。

### 1. 不变量的破坏
- **不变量**是数据结构在某一状态下的规则或约束。例如，双链表中每个节点的前后指针必须保持一致。
- 在修改共享数据时，不变量可能会暂时被破坏，直到修改完成后才恢复稳定。
- 如果在不变量被破坏的过程中，其他线程访问了共享数据，就可能导致错误。

### 2. 条件竞争
- **条件竞争**是指多个线程对共享数据的访问顺序影响最终结果。
- **良性条件竞争**：线程执行顺序不同，但结果仍然可接受。
- **恶性条件竞争**：线程执行顺序导致不变量被破坏，可能导致数据损坏或程序崩溃。
- 数据竞争是条件竞争的一种特殊形式，指多个线程同时修改一个独立对象，可能引发未定义行为。

### 3. 恶性条件竞争的特性
- 通常发生在对多个数据块的修改中，如双链表中两个指针的更新。
- 错误难以复现，因为其发生概率较低，且与执行时间敏感。
- 在系统负载高或执行次数增加时，问题出现的概率会提高。

### 4. 避免恶性条件竞争的方法
- **保护机制**：使用某种机制（如互斥量）保护数据结构，确保其他线程无法看到不变量的中间状态。
- **无锁编程**：通过修改数据结构和不变量，使其变化过程不可分割，但这种方法复杂且容易出错。
- **事务机制**：通过事务日志记录和提交数据更新，避免条件竞争（如软件事务内存，STM）。但C++标准目前未直接支持这种方法。
- **互斥量**：C++标准库提供的最基本的方式，用于保护共享数据结构。

### 5. 调试难点
- 条件竞争问题可能在调试模式下消失，因为调试模式会影响程序的执行时间。

通过这些方法和工具，可以有效避免恶性条件竞争，确保多线程程序的正确性和稳定性。

[![top] Goto Top](#table-of-contents)

---

## 3.2 使用互斥量

### 3.2.1 互斥量

#### 核心概念
互斥量（`std::mutex`）是C++中保护共享数据的最基础机制。它的作用是确保同一时刻只有一个线程可以访问共享数据，从而避免条件竞争和数据不一致的问题。

#### 使用方式
- **手动锁与解锁**  
  通过`std::mutex`的成员函数`lock()`和`unlock()`，可以手动对互斥量进行加锁和解锁操作，但这种方式容易出错，尤其是在代码中有多个出口（如异常处理）时，可能会导致忘记解锁。

- **RAII机制：`std::lock_guard`**  
  为了避免手动管理锁的复杂性，C++标准库提供了`std::lock_guard`，它是一种RAII（资源获取即初始化）机制的封装类。在构造时自动加锁，在析构时自动解锁，从而确保互斥量在任何情况下都能正确解锁。

#### 示例代码：使用`std::mutex`和`std::lock_guard`

```cpp
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;    // 1. 全局共享数据
std::mutex some_mutex;       // 2. 保护共享数据的互斥量

// 添加元素到列表
void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);  // 3. 自动加锁
    some_list.push_back(new_value);
}

// 检查列表中是否包含某个值
bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);  // 4. 自动加锁
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}
```

- **代码说明**：
  1. `some_list` 是一个全局共享的`std::list`。
  2. `some_mutex` 是保护`some_list`的互斥量。
  3. 在`add_to_list()`和`list_contains()`函数中，使用`std::lock_guard`对`some_mutex`进行加锁，确保线程安全。
  4. 当线程访问共享数据时，互斥量会将其他线程阻塞，直到当前线程完成操作并解锁。

#### C++17 的改进
- **模板参数推导**  
  在C++17中，`std::lock_guard`支持模板参数推导，因此可以省略类型声明，代码更加简洁。例如：
  ```cpp
  std::lock_guard guard(some_mutex);
  ```

- **`std::scoped_lock`**  
  C++17引入了`std::scoped_lock`，它是`std::lock_guard`的增强版，可以同时锁住多个互斥量，适用于需要同时操作多个共享数据的场景。例如：
  ```cpp
  std::scoped_lock guard(some_mutex1, some_mutex2);
  ```

#### 面向对象的设计
- 在大多数情况下，互斥量通常与需要保护的数据一起放在同一个类中，而不是定义为全局变量。这种设计符合面向对象的封装原则。
- 示例：
  ```cpp
  class ProtectedList {
  private:
      std::list<int> some_list;
      std::mutex some_mutex;

  public:
      void add_to_list(int new_value) {
          std::lock_guard<std::mutex> guard(some_mutex);
          some_list.push_back(new_value);
      }

      bool list_contains(int value_to_find) {
          std::lock_guard<std::mutex> guard(some_mutex);
          return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
      }
  };
  ```

#### 注意事项
- **不要返回受保护数据的指针或引用**  
  如果成员函数返回受保护数据的指针或引用，调用者可以绕过互斥量直接操作数据，从而破坏数据的安全性。

#### 总结
- `std::mutex` 是保护共享数据的核心机制。
- 使用`std::lock_guard`可以简化锁的管理，避免忘记解锁。
- C++17 提供了`std::scoped_lock`，进一步增强了多互斥量场景的支持。
- 面向对象的设计可以将互斥量与数据绑定在一起，方便封装和管理。


### 3.2.2 保护共享数据

使用互斥量来保护数据，并不是在每一个成员函数中加入一个`std::lock_guard`对象那么简单。一个指针或引用，也会让这种保护形同虚设。不过，检查指针或引用很容易，只要没有成员函数通过返回值或者输出参数的形式，向其调用者返回指向受保护数据的指针或引用，数据就是安全的。确保成员函数不会传出指针或引用的同时，检查成员函数是否通过指针或引用的方式来调用也是很重要的(尤其是这个操作不在你的控制下时)。函数可能没在互斥量保护的区域内存储指针或引用，这样就很危险。更危险的是：将保护数据作为一个运行时参数，如同下面代码中所示。

代码3.2 无意中传递了保护数据的引用

```c++
class some_data
{
  int a;
  std::string b;
public:
  void do_something();
};

class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    func(data);    // 1 传递“保护”数据给用户函数
  }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
  unprotected=&protected_data;
}

data_wrapper x;
void foo()
{
  x.process_data(malicious_function);    // 2 传递一个恶意函数
  unprotected->do_something();    // 3 在无保护的情况下访问保护数据
}
```

例子中process_data看起来没有问题，`std::lock_guard`对数据做了很好的保护，但调用用户提供的函数func①，就意味着foo能够绕过保护机制将函数`malicious_function`传递进去②，可以在没有锁定互斥量的情况下调用`do_something()`。

这段代码的问题在于根本没有保护，只是将所有可访问的数据结构代码标记为互斥。函数`foo()`中调用`unprotected->do_something()`的代码未能被标记为互斥。这种情况下，C++无法提供任何帮助，只能由开发者使用正确的互斥锁来保护数据。从乐观的角度上看，还是有方法的：切勿将受保护数据的指针或引用传递到互斥锁作用域之外。

基于上述问题的出现，可以对代码进行如下修改：

```cpp
class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    // 提供只读的 const 引用，防止修改或泄露
    func(std::as_const(data));
  }
};
```

或者
```cpp
class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    // 提供受控的代理对象
    func([this]() { return data; });
  }
};
```
第一种思路很以只读方式返回data的值，第二种思路为使用一个 Lambda 表达式（闭包）作为代理对象，用户函数只能通过这个代理访问 `data`。
Lambda表达式中，`[this]() { return data; }`表示返回`data`的值，而不是直接暴露`data`的引用或指针。

尽管这段代码改进了数据保护机制，但仍然存在一些潜在问题和改进空间：

- 返回整个 data 的副本可能代价较高
- 如果 some_data 是一个复杂的对象，返回它的副本可能会引入性能开销（尤其是拷贝构造函数的调用）。

改进方法：
- 如果只需要只读访问，可以返回`const some_data&`。
- 如果需要修改，可以返回一个代理对象，而不是整个数据。

改进代码示例：

```cpp
class data_proxy
{
private:
  some_data& data;
public:
  explicit data_proxy(some_data& d) : data(d) {}
  
  // 提供只读访问接口
  const some_data& get() const { return data; }
  
  // 如果需要，提供受控的修改接口
  void modify(int new_a, const std::string& new_b)
  {
    data.a = new_a;
    data.b = new_b;
  }
};

class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    data_proxy proxy(data); // 创建代理对象
    func(proxy);            // 将代理对象传递给用户函数
  }
};
```

用户函数只能通过`data_proxy`来访问或修改`data`，而不能直接操作`data`的引用或指针。


[![top] Goto Top](#table-of-contents)

---

### 3.2.3 接口间的条件竞争

#### **问题描述**

即使在多线程环境中使用了互斥量来保护共享数据，条件竞争（Race Condition）问题仍然可能发生。这是因为条件竞争不仅与实现方式相关，还与接口设计息息相关。

#### **例子：栈（`std::stack`）的问题**

以一个类似于 `std::stack` 的栈为例，栈的接口包括以下操作：
- **push()**：将新元素压入栈。
- **pop()**：弹出栈顶元素。
- **top()**：返回栈顶元素。
- **size()**：返回栈中元素的数量。
- **empty()**：判断栈是否为空。

虽然这些操作单独调用时是线程安全的（假设内部使用了互斥量保护），但在组合使用时会出现问题。例如：

```cpp
stack<int> s;
if (!s.empty()) {    // 1. 检查栈是否为空
    int value = s.top();    // 2. 获取栈顶元素
    s.pop();    // 3. 弹出栈顶元素
    do_something(value);
}
```

在单线程环境中，上述代码是安全的，但在多线程环境中可能会出现以下问题：

1. **条件竞争问题**：
   - 假如线程 A 和线程 B 同时执行上述代码。
   - 线程 A 在执行 `if (!s.empty())` 判断时，发现栈不为空。
   - 在线程 A 调用 `s.top()` 之前，线程 B 已经调用了 `s.pop()`，将栈顶元素弹出。
   - 此时，线程 A 调用 `s.top()` 会导致未定义行为，因为栈已经为空。

2. **逻辑错误问题**：
   - 如果两个线程在 `s.top()` 和 `s.pop()` 之间交替运行，可能会导致同一个栈顶元素被两个线程重复处理。这种逻辑错误可能难以察觉，但会导致程序的行为不符合预期。

#### **接口设计的问题**

上述问题的根本原因在于接口设计：
- **`empty()` 和 `top()` 的分离**：`empty()` 检查栈是否为空，而 `top()` 获取栈顶元素，这两个操作之间缺乏原子性。
- **操作的粒度过小**：栈操作的接口没有提供一种机制，能够保证一组操作（如检查是否为空、获取栈顶元素和弹出栈顶元素）是原子的。

#### **解决方案**

1. **修改接口设计**：
   - 提供一个新的接口，将 `top()` 和 `pop()` 合并为一个操作。例如：
     ```cpp
     std::shared_ptr<int> pop();
     ```
     这样，返回值可以直接包含栈顶元素，并在内部完成弹出操作，避免条件竞争。

2. **抛出异常**：
   - 在调用 `top()` 时，如果栈为空，直接抛出异常。这种方式虽然解决了问题，但显得笨拙，因为即使 `empty()` 返回 `false`，调用 `top()` 时仍需进行异常处理。

3. **使用更安全的堆栈实现**：
   - 设计一个线程安全的栈类（如代码 3.4 和 3.5 所示），通过封装和简化接口来避免条件竞争。
   - 示例代码：
     ```cpp
     template<typename T>
     class threadsafe_stack {
     public:
         void push(T new_value);
         std::shared_ptr<T> pop();
         bool empty() const;
     };
     ```

#### **总结**

接口设计的缺陷可能导致条件竞争，即使实现本身是线程安全的。要避免这种问题，需要重新设计接口，确保一组相关操作可以作为一个原子操作执行，从而消除潜在的竞争条件。

[![top] Goto Top](#table-of-contents)

---

### 3.2.4 死锁：问题描述及解决方案

### 3.2.4 死锁：问题描述及解决方案

#### 1. **问题描述**
死锁通常发生在以下情况下：
- 两个线程需要获取多个互斥量（`std::mutex`）。
- 每个线程都持有一个互斥量，并等待另一个线程释放其持有的互斥量。
- 由于两个线程都在等待对方释放锁，导致程序无法继续执行。

**示例：**
- 假设有两个孩子玩一个玩具鼓。玩具鼓需要两个部分（鼓和鼓锤）才能玩。
- 两个孩子同时尝试获取这两个部分，其中一个孩子拿到了鼓，另一个拿到了鼓锤。
- 如果两个孩子都不愿意放弃自己手中的部分，就会导致“死锁”——谁也无法玩。

在多线程编程中，这种情况同样适用：线程之间因为互斥锁的竞争而无法继续运行。

---

#### 2. **死锁的解决方法**
避免死锁的关键在于：
1. **固定锁的顺序**：总是以固定的顺序锁定多个互斥量。
2. **使用工具**：C++标准库提供了`std::lock`和`std::scoped_lock`来帮助避免死锁。

##### **(1) 使用`std::lock`**
`std::lock`可以一次性锁住多个互斥量，确保不会发生死锁。

**代码示例：**
```cpp
class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);

class X {
private:
    some_big_object some_detail;
    std::mutex m;

public:
    X(some_big_object const& sd) : some_detail(sd) {}

    friend void swap(X& lhs, X& rhs) {
        if (&lhs == &rhs)
            return;

        std::lock(lhs.m, rhs.m); // 一次性锁住两个互斥量
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 将锁交给lock_guard管理
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
        swap(lhs.some_detail, rhs.some_detail); // 交换操作
    }
};
```

**代码解释：**
1. **检查参数**：如果两个对象是同一个实例，直接返回，避免不必要的锁操作。
2. **`std::lock`**：一次性锁住`lhs.m`和`rhs.m`，避免死锁。
3. **`std::lock_guard`**：使用`std::adopt_lock`参数将已有的锁交由`std::lock_guard`管理，确保异常安全。
4. **异常安全**：如果`std::lock`在锁定过程中抛出异常，已经锁定的互斥量会自动释放，避免资源泄漏。

##### **(2) 使用`std::scoped_lock`**
C++17引入了`std::scoped_lock`，它是一个RAII类型，用于同时锁定多个互斥量，功能类似于`std::lock_guard`。

**代码示例：**
```cpp
void swap(X& lhs, X& rhs) {
    if (&lhs == &rhs)
        return;

    std::scoped_lock guard(lhs.m, rhs.m); // 一次性锁住多个互斥量
    swap(lhs.some_detail, rhs.some_detail); // 交换操作
}
```

**代码解释：**
1. **简化代码**：`std::scoped_lock`自动管理多个锁的生命周期，减少了手动管理的复杂性。
2. **模板推导**：C++17支持自动推导模板参数，因此可以直接传递互斥量实例。
3. **等价写法**：
   ```cpp
   std::scoped_lock<std::mutex, std::mutex> guard(lhs.m, rhs.m);
   ```

**优点**：
- 更简洁的代码。
- 减少错误的可能性（如忘记解锁）。

---

#### 3. **注意事项**
- 虽然`std::lock`和`std::scoped_lock`可以避免死锁，但它们的使用仍然需要开发者遵循一定的规则和经验。
- 在设计多线程程序时，应尽量减少锁的数量或使用更高级的同步机制（如条件变量或无锁数据结构）。

---

#### 4. **总结**
- **死锁定义**：当多个线程相互等待对方释放资源时，程序进入无法继续的状态。
- **解决方法**：
  1. 固定锁的顺序。
  2. 使用`std::lock`或`std::scoped_lock`避免死锁。
- **推荐**：在支持C++17的环境下，优先使用`std::scoped_lock`，它能减少手动管理锁的复杂性并提高代码安全性。



[![top] Goto Top](#table-of-contents)

<!-- figures -->
[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png