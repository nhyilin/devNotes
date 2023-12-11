# Table of Contents
- [Table of Contents](#table-of-contents)
- [c++ 右值引用](#c-右值引用)
  - [几个应用场景](#几个应用场景)
  - [右值引用提升代码性能应用场景](#右值引用提升代码性能应用场景)
  - [完美转发机制](#完美转发机制)
- [Code Snippet](#code-snippet)
  - [std::function](#stdfunction)
  - [std::forward replaces std::bind](#stdforward-replaces-stdbind)
# c++ 右值引用

**左值 (lvalue):**
- 左值表示的是内存中有明确可识别地址的对象，即可以取地址的表达式。
- 左值可以出现在赋值语句的左边或右边。例如，如果我们有 `int a = 1;` 那么 `a` 是一个左值表达式，因为你可以对它进行操作如 `a = 2;`。
- 左值通常可以持久存在直到其作用域结束。

**右值 (rvalue):**
- 右值表示的是临时的、不具有明确存储地址的对象，通常不能取地址，即通常不可以出现在赋值符号的左边。
- 右值表示的对象是在表达式评估过程中产生的临时值，它们通常用于初始化左值或者与左值进行比较，或者就是作为一个临时值。
- 例如，在表达式 `int x = 1 + 2;` 中，`1 + 2` 就是一个右值，它产生一个临时值，在赋值给左值 `x` 之后，该临时值就不再需要了。
- 右值还可以进一步分为纯右值(prvalue)和将亡值(xvalue)。纯右值是指那些非引用返回的临时量，没有实体与之对应的表达式的值，而将亡值通常是与对象生命周期结束相关的表达式，如std::move操作产生的值。

**右值引用**
C++11中引入了右值引用的概念，用来支持移动语义（Move Semantics）和完美转发（Perfect Forwarding）。右值引用可以绑定到一个右值上，允许程序员安全地从右值中窃取资源。右值引用使用 `&&` 符号标记。例如，

```cpp
int&& rref = 1 + 2; // 此时1+2是一个临时值，rref是一个绑定到该临时值的右值引用
```

## 几个应用场景

1. **支持移动语义 (Move Semantics):**
   在C++11之前，对象数据只能通过复制进行传递，这可能会导致性能问题，尤其是对于大型数据结构。右值引用和移动语义使得资源（如动态内存、文件句柄、网络连接等）可以从一个对象转移至另一个对象，而不需要复制数据。
   
   例如，标准库中的 `std::vector` 可以使用移动构造函数来接管另一个 `std::vector` 的内部数组，避免不必要的复制：
   ```cpp
   std::vector<int> original = {1, 2, 3};
   std::vector<int> moved_to(std::move(original)); // 使用原始vector的数据进行初始化
   ```
   在这个例子中，`original` 现在是空的，`moved_to` 接管了原来 `original` 的数据。

   更实际一些的例子：
   ```cpp
   #include <iostream>
   #include <vector>
   #include <string>

   int main() {
    std::vector<std::string> words;

    std::string word = "Hello";
    words.push_back(word);  // 复制
    std::cout << "After copy, word is: '"
                << "'" << std::endl;

    words.push_back(std::move(word));  // 移动而不复置，word 现在为空
    std::cout << "After move, word is '" << word << "'" << std::endl;

    std::cout << "Words in vector: ";
    for (const auto& w : words) std::cout << "'" << w << "'    ";
    std::cout << std::endl;

    return 0;
   }
   ```

2. **完美转发 (Perfect Forwarding):**
   在模板编程中，有时需要完整无缺地传递参数给另一个函数。右值引用，特别是与模板和 `std::forward` 一起使用时，可以保持参数的左值或右值属性。
   
   以下是一个采用完美转发的函数模板例子：
   ```cpp
   template <class T>
   void relay(T&& arg) {
      someOtherFunction(std::forward<T>(arg));
   }
   ```
   这里，如果 `relay` 的参数是左值，`arg` 将作为左值传递给 `someOtherFunction`；如果是右值，将作为右值传递。

3. **优化临时对象的处理:**
   如果函数对临时对象做特殊处理，右值引用可以优化这些情况。例如，一个接收右值引用的函数重载可以决定采取更高效的途径，包括窃取资源或者避免不必要的深拷贝。
   
   ```cpp
   class BigObject {
       // ...
   };
   
   void process(BigObject& obj) {
      // 处理 obj 的复制
   }
   
   void process(BigObject&& obj) {
      // 直接处理 obj，省去复制步骤
   }
   
   // 使用临时对象时，会选用右值引用版本的 process 函数
   process(BigObject());
   ```
   
当你有一个右值（比如临时对象或经过 `std::move` 转换的对象）时，使用右值引用可以大大提高性能，因为它允许资源的重新利用而不是资源的复制。这是现代C++编程中一个重要的优化手段。  

## 右值引用提升代码性能应用场景

1. **线程安全的移动操作:**
   如果需要将对象从一个线程传递给另一个线程，使用右值引用和移动语义可以避免复制对象，尤其是对于大的对象或包含资源如动态分配内存、文件句柄的情况。例如，`std::thread` 的构造函数就可以接受右值引用参数，从而允许直接在新线程中使用传入对象的资源：

   ```cpp
   void process_big_object(std::unique_ptr<BigObject> ptr);

   std::unique_ptr<BigObject> big_ptr(new BigObject());
   std::thread t(process_big_object, std::move(big_ptr)); // 在新线程中使用 big_ptr
   ```

2. **线程池任务队列:**
   对于线程池的实现，任务通常需要被放入队列中等待执行。如果任务是以函数对象的形式存储的，那么通过std::function可以对它们进行封装。如果这些函数对象支持移动操作（如使用`std::bind` 生成的函数对象），那么使用右值引用将任务添加到队列中时可以避免复制，提升效率。

   std::function 代码片段: [`std::function`](#stdfunction)

   ```cpp
   std::vector<std::thread> pool;
   std::queue<std::function<void()>> tasks;

   void add_task(std::function<void()>&& task) {
       tasks.emplace(std::move(task)); // 将任务移动到队列中，而不是复制
   }
   ```

3. **使用 `std::async`:**
   `std::async` 可以异步的执行任务。如果传递给`std::async` 的函数接受的是重对象或者资源的所有权，那么使用右值引用可以避免不必要的复制。

   ```cpp
   std::future<ResultType> result = std::async(std::launch::async, 
                                               process_huge_data, 
                                               std::move(huge_data));
   ```

   在这个场景中，使用 `std::move` 可以直接将 `huge_data` 移动到异步任务中，减少数据的复制。

4. **使用 `std::promise` 和 `std::future`:**
   你可以使用右值引用来传递 `std::promise` 对象到线程中，并在结束时设置值。右值引用允许将 `std::promise` 对象的所有权从一个线程传递给正在运行的线程，从而避免复制操作。

   ```cpp
   class BigData {};
   BigData calculateData() {}

   int main() {
    std::promise<BigData> promise;
    auto future = promise.get_future();
    std::thread t(
          [](std::promise<BigData>&& prm) {
          BigData bd = calculateData();
          prm.set_value(std::move(bd));
          },
          std::move(promise));  // 注意这里将 promise 作为参数传递进去
    t.detach();
   }
   ```
   
上述场景中通过避免过度的对象复制，右值引用的使用可以大幅降低与线程操作相关的系统资源的消耗，因此提高了整个程序的性能。  


## 完美转发机制

完美转发(Perfect forwarding)是C++11中引入的一个技术，允许我们保持转发给函数的参数的类别（值类别，例如左值、右值、常量等）不变。这是通过模板和右值引用来实现的，特别是通过引用折叠规则和std::forward的使用。这允许开发者编写接受任意参数并将其转发到另一个函数，同时保留其值类别的函数。

完美转发简单demo：
```cpp
#include <iostream>
#include <utility>
#include <string>

void process(std::string& s) {
  std::cout << "Processed lvalue: " << s << std::endl;
}

void process(std::string&& s) {
  std::cout << "Processed rvalue: " << s << std::endl;
}

// 完美转发函数模板
template <typename T>
void logAndProcess(T&& param) {
  // 执行前处理或日志记录...
  std::cout << "Logging parameter" << std::endl;

  // 使用 std::forward 来完美转发参数到另一个函数
  process(std::forward<T>(param));
}

int main() {
  std::string lv = "lvalue";  // lv是左值
  // lvalue 被传递给process，因为lv有名称，是一个左值

  logAndProcess(lv);

  // 字面量是右值，右值版本被调用
  logAndProcess(std::string("rvalue"));

  // 也可以通过 std::move 显示地传递一个右值引用
  logAndProcess(std::move(lv));

  return 0;
}
```
# Code Snippet
## std::function

code refactor 见 [std::forward replaces std::bind](#stdforward-replaces-stdbind)

```cpp
#include <functional>
#include <iostream>

class Foo {
 public:
  Foo(int num) : num_(num) {}
  void print_add(int i) const { std::cout << num_ + i << '\n'; }
  int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum {
  void operator()(int i) const { std::cout << i << '\n'; }
};

int main() {
  // 存储自由函数
  std::function<void(int)> f_display = print_num;
  f_display(-9);

  // 存储 lambda
  std::function<void()> f_display_42 = []() { print_num(42); };
  f_display_42();

  // 存储到 std::bind 调用的结果
  std::function<void()> f_display_31337 = std::bind(print_num, 31337);
  f_display_31337();

  // 存储到成员函数的调用
  std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
  const Foo foo(314159);

  f_add_display(foo, 1);
  f_add_display(314159, 1);

  // 存储到数据成员访问器的调用
  std::function<int(Foo const&)> f_num = &Foo::num_;
  std::cout << "num_: " << f_num(foo) << '\n';

  // 存储到成员函数及对象的调用
  using std::placeholders::_1;
  std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
  f_add_display2(2);

  // 存储到成员函数和对象指针的调用
  std::function<void(int)> f_add_display3 =
      std::bind(&Foo::print_add, &foo, _1);
  f_add_display3(3);

  // 存储到函数对象的调用
  std::function<void(int)> f_display_obj = PrintNum();
  f_display_obj(18);

  auto factorial = [](int n) {
    // 存储 lambda 对象以模拟“递归 lambda ”，注意额外开销
    std::function<int(int)> fac = [&](int n) {
      return (n < 2) ? 1 : n * fac(n - 1);
    };
    // note that "auto fac = [&](int n){...};" does not work in recursive calls
    return fac(n);
  };
  for (int i{5}; i != 8; ++i) {
    std::cout << i << "! = " << factorial(i) << ";  ";
  }
}
```

## std::forward replaces std::bind

```cpp
  //  std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
  std::function<void(int)> f_add_display2 = [foo](auto&& PH1) {
    foo.print_add(std::forward<decltype(PH1)>(PH1));
  };
  ```
代码中的lambda表达式捕获了一个名为foo的外部变量（假设是以值捕获，因为在方括号内没有明确指出是用引用捕获）。  

这个lambda表达式也是一个通用lambda，能够接受任意类型的参数PH1，因为它的参数被声明为auto &&，表示一个完美转发的通用引用。  

Lambda表达式的函数体调用了foo对象的成员函数print_add，并向它传递了PH1参数。此处，std::forward<decltype(PH1)>(PH1)用来完美转发PH1，保持PH1的原始值类别（lvalue或rvalue）。

这意味着如果f_add_display2被以右值引用调用，print_add将接收到一个右值引用，相反如果它被以左值引用调用print_add将接受到一个左值引用。