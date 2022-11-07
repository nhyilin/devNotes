Pointer reference basic usage
<!--more-->
# Table of Contents
<pre>
<a href="#指针引用基础用法">Pointer reference basic usage</a>
    <a href="#指针">pointer</a>
        <a href="#null指针">NULL指针</a>
        <a href="#指针的算术运算">指针的算术运算</a>
        <a href="#指针-vs-数组">指针 vs 数组</a>
        <a href="#指针数组">指针数组</a>
        <a href="#指向指针的指针-多级间接寻址">指向指针的指针(多级间接寻址)</a>
        <a href="#传递指针给函数">传递指针给函数</a>
        <a href="#从函数返回指针">从函数返回指针</a>
    <a href="#引用">reference</a>
        <a href="#把引用做为参数">把引用做为参数</a>
        <a href="#把引用做为返回值">把引用做为返回值</a>
</pre>


# 指针引用基础用法

## 指针
C++中使用指针使用指针时会频繁进行以下几个操作：定义一个指针变量、把变量地址赋值给指针、访问指针变量中可用地址的值。
这些是通过使用一元运算符 *来返回位于操作数所指定地址的变量的值。下面的实例涉及到了这些操作：

```cpp
#include <iostream>

using namespace std;

int main() {
    int var = 20;   // 实际变量的声明
    int *ip;        // 指针变量的声明

    ip = &var;       // 在指针变量中存储 var 的地址

    cout << "Value of var variable: ";
    cout << var << endl;

    // 输出在指针变量中存储的地址
    cout << "Address stored in ip variable: ";
    cout << ip << endl;

    // 访问指针中地址的值
    cout << "Value of *ip variable: ";
    cout << *ip << endl;

    return 0;
}
```
[![top]Goto Top](#table-of-contents)

### null指针
```cpp
int main ()
{
    int  *ptr = NULL;

    cout << "ptr 的值是 " << ptr ;

    return 0;
}
```

当上面的代码被编译和执行时，它会产生下列结果：

`ptr 的值是 0`

在大多数的操作系统上，程序不允许访问地址为 0 的内存，因为该内存是操作系统保留的。然而，内存地址 0 有特别重要的意义，它表明该指针不指向一个可访问的内存位置。但按照惯例，如果指针包含空值（零值），则假定它不指向任何东西。

如需检查一个空指针，可以使用 if 语句，如下所示：

```cpp
if(ptr)     /* 如果 ptr 非空，则完成 */
if(!ptr)    /* 如果 ptr 为空，则完成 */
```
因此，如果所有未使用的指针都被赋予空值，同时避免使用空指针，就可以防止误用一个未初始化的指针。很多时候，未初始化的变量存有一些垃圾值，导致程序难以调试。

[![top]Goto Top](#table-of-contents)

### 指针的算术运算

我们喜欢在程序中使用指针代替数组，因为变量指针可以递增，而数组不能递增，因为数组是一个常量指针。下面的程序递增变量指针，以便顺序访问数组中的每一个元素：

指针递增：
```cpp
const int MAX = 3;

int main() {
    int var[MAX] = {10, 100, 200};
    int *ptr;
    //当然，如果为double类型指针，接下来每次位移将为八个字节
    // 指针中的数组地址
    ptr = var;
    for (int i = 0; i < MAX; i++) {
        cout << "Address of var[" << i << "] = ";
        cout << ptr << endl;

        cout << "Value of var[" << i << "] = ";
        cout << *ptr << endl;

        // 移动到下一个位置
        ptr++;
    }
    return 0;
}
```
指针递减同理。

指针的比较：
```cpp
const int MAX = 3;

int main() {
    int var[MAX] = {10, 100, 200};
    int *ptr;

    // 指针中第一个元素的地址
    ptr = var;
    int i = 0;
    while (ptr <= &var[MAX - 1]) {//其实这里的ptr限制，也就单纯为了限制ptr的index限制在数组内，不跑飞

        cout << "Address of var[" << i << "] = ";
        cout << ptr << endl;

        cout << "Value of var[" << i << "] = ";
        cout << *ptr << endl;

        // 指向上一个位置
        ptr++;
        i++;
    }
    return 0;
}
```
[![top]Goto Top](#table-of-contents)

### 指针 vs 数组

指针和数组是密切相关的。事实上，指针和数组在很多情况下是可以互换的。例如，一个指向数组开头的指针，可以通过使用指针的算术运算或数组索引来访问数组。

```cpp
const int MAX = 3;

int main() {
    int var[MAX] = {10, 100, 200};
    int *ptr;

    // 指针中的数组地址
    ptr = var;
    for (int i = 0; i < MAX; i++) {
        cout << "var[" << i << "]的内存地址为 ";
        cout << ptr << endl;

        cout << "var[" << i << "] 的值为 ";
        cout << *ptr << endl;

        // 移动到下一个位置
        ptr++;
    }
    return 0;
}
```

然而，指针和数组并不是完全互换的:

```cpp
const int MAX = 3;

int main() {
    int var[MAX] = {10, 100, 200};

    for (int i = 0; i < MAX; i++) {
        *var = i;    // 这是正确的语法
        var++;       // 这是不正确的
    }
    return 0;
}
```

如下， k 是变量, 它存得是地址， 变量可以作为左值，可以自增。

b是数组名，  数组名是地址， 但此时是作为常量，不可作为左值，不可以自增； 数组名是地址 它不是变量 数组才是变量

数组名不是变量 不能做左值。

```cpp
#include <iostream>
using namespace std;
int main() {
    int b[] = {10, 20, 30, 40, 50};
    int i, *k;
    k = &b[4] - 4;
    for (i = 0; i <= 4; i++) {
        cout << *k << " "; //依次输出每一个数组元素
        k++; //k 是变量, 它存得是地址， 变量可以作为左值，可以自增。
    }
    cout << endl;

    cout << "b = " << b + 1 << endl; //输出的是第一个元素地址
    cout << "&b[0] = " << &b[0] + 1 << endl;
    cout << "b = " << b++ << endl; //数组名表示得是地址 不能做为左值 ， b++ 表示的是b=b+1
    cout << "&b[0] = " << &b[0]++ << endl; // &优先级高于++， 同(&b[0])++， 也是地址自增，但此时地址是常量，而不是变量，同上，编译出错
}
```

指针你可以把它看做一个整型（但不是）数据类型 它是一个变量 存储得是一个地址 比如你可以把一个地址赋值给它，这时指针变量就存储这个地址，再把另一个地址赋值给它， 这时指针变量就存另一个地址，它是可以变的，所以可以作为左值。

数组，你声明一个数组，系统就分配了一个内存单元 这时数组名表示得是这个数组首元素得地址，这个地址是不能变得，可以把它看做（但不是）常量，所以不能作为左值 。

[![top]Goto Top](#table-of-contents)

### 指针数组

可能有一种情况，我们想要让数组存储指向 int 或 char 或其他数据类型的指针。下面是一个指向整数的指针数组的声明：

```int *ptr[MAX];```


```cpp
int main ()
{
   int  var[MAX] = {10, 100, 200};
   int *ptr[MAX];

   for (int i = 0; i < MAX; i++)
   {
      ptr[i] = &var[i]; // 赋值为整数的地址
   }
   for (int i = 0; i < MAX; i++)
   {
      cout << "Value of var[" << i << "] = ";
      cout << *ptr[i] << endl;
   }
   return 0;
}
```
也可以用一个指向字符的指针数组来存储一个字符串列表

```cpp
int main() {
    const char *names[MAX] = {
            "Zara Ali",
            "Hina Ali",
            "Nuha Ali",
            "Sara Ali",
    };

    for (int i = 0; i < MAX; i++) {
        cout << "Value of names[" << i << "] = ";
        cout << names[i] << endl;
    }
    return 0;
}
```
这里的报错，需注意：
```cpp
int main() {
    char *pstr = "hello world";
    pstr = "aa";
    pstr[1] = "a";    //报错


    cout << pstr << endl;
}
```
[问题详情](https://blog.csdn.net/yejinxiong001/article/details/78436310)


[![top]Goto Top](#table-of-contents)


### 指向指针的指针-多级间接寻址

指向指针的指针是一种多级间接寻址的形式，或者说是一个指针链。

指针的指针就是将指针的地址存放在另一个指针里面。

通常，一个指针包含一个变量的地址。当我们定义一个指向指针的指针时，第一个指针包含了第二个指针的地址，第二个指针指向包含实际值的位置。

一个指向指针的指针变量必须如下声明，即在变量名前放置两个星号。例如，下面声明了一个指向 int 类型指针的指针：

`int **var;`

当一个目标值被一个指针间接指向到另一个指针时，访问这个值需要使用两个星号运算符：

```cpp
int main() {
    int var;
    int *ptr;
    int **pptr;

    var = 3000;

    // 获取 var 的地址
    ptr = &var;

    // 使用运算符 & 获取 ptr 的地址
    pptr = &ptr;

    // 使用 pptr 获取值
    cout << "var 值为 :" << var << endl;
    cout << "*ptr 值为:" << *ptr << endl;
    cout << "**pptr 值为:" << **pptr << endl;
    return 0;
}
```
- [ ]多级指针的作用，需要整理

[![top]Goto Top](#table-of-contents)

### 传递指针给函数

C++ 允许您传递指针给函数，只需要简单地声明函数参数为指针类型即可。

下面的实例中，我们传递一个无符号的 long 型指针给函数，并在函数内改变这个值

```cpp
void getSecond(unsigned long *ptr) {
    *ptr = time(NULL);
}


int main() {
    unsigned long second;
    getSecond(&second);//这里取地址吗
    cout<<"the real second:"<<second;
    return 0;
}
```


[![top]Goto Top](#table-of-contents)


### 传递指针给函数

传递一个无符号的 long 型指针给函数，并在函数内改变这个值

```cpp
// 在写函数时应习惯性的先声明函数，然后在定义函数
void getSeconds(unsigned long *par);

int main() {
    unsigned long sec;


    getSeconds(&sec);

    // 输出实际值
    cout << "Number of seconds :" << sec << endl;

    return 0;
}

void getSeconds(unsigned long *par) {
    // 获取当前的秒数
    *par = time(NULL);
    return;
}
```

能接受指针作为参数的函数，也能接受数组作为参数:

```cpp
#include <iostream>

using namespace std;

double getAverage(int *arr, int size) {
    int i, sum = 0;
    double avg;

    for (i = 0; i < size; ++i) {
        sum += arr[i];
    }

    avg = double(sum) / size;

    return avg;
}

int main() {
    // 带有 5 个元素的整型数组
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg;

    // 传递一个指向数组的指针作为参数
    avg = getAverage(balance, 5);

    // 输出返回值
    cout << "Average value is: " << avg << endl;

    return 0;
}
```
有一说一，上面的程序感觉可维护性很差，5的指定很随意


[![top]Goto Top](#table-of-contents)


### 从函数返回指针


前面代码中，已经展示了 C++ 中如何从函数返回数组，类似地，C++ 允许您从函数返回指针。为了做到这点，必须声明一个返回指针的函数，如下所示：
```cpp
int *myFunction() {
    .
}
```
**另外，C++ 不支持在函数外返回局部变量的地址，除非定义局部变量为 static变量。**

下面的函数，它会生成 10 个随机数，并使用表示指针的数组名（即第一个数组元素的地址）来返回它们，具体如下：
```cpp
// 要生成和返回随机数的函数
int *getRandom() {
    static int r[10];

    // 设置种子
    srand((unsigned) time(NULL));
    for (int i = 0; i < 10; ++i) {
        r[i] = rand();
        cout << r[i] << endl;
    }

    return r;
}

// 要调用上面定义函数的主函数
int main() {
    // 一个指向整数的指针
    int *p;

    p = getRandom();
    for (int i = 0; i < 10; i++) {
        cout << "*(p + " << i << ") : ";
        cout << *(p + i) << endl;
    }

    return 0;
}
```


[![top]Goto Top](#table-of-contents)


## 引用

```cpp
int main() {
    // 声明简单的变量
    int i;
    double d;

    // 声明引用变量
    int &r = i;
    double &s = d;

    i = 5;
    cout << "Value of i : " << i << endl;
    cout << "Value of i reference : " << r << endl;

    d = 11.7;
    cout << "Value of d : " << d << endl;
    cout << "Value of d reference : " << s << endl;

    return 0;
}
```

[![top]Goto Top](#table-of-contents)


### 把引用做为参数
```cpp
void swap(int &x, int &y) {
    int temp;
    temp = x;
    x = y;
    y = temp;

    return;
}

int main() {
    // 局部变量声明
    int a = 100;
    int b = 200;

    cout << "交换前，a 的值：" << a << endl;
    cout << "交换前，b 的值：" << b << endl;

    /* 调用函数来交换值 */
    swap(a, b);

    cout << "交换后，a 的值：" << a << endl;
    cout << "交换后，b 的值：" << b << endl;

    return 0;
}

```
这里实际上不仅仅是像指针那样，取出所需变量，而是借助swap函数将ab值互换

[![top]Goto Top](#table-of-contents)

### 把引用做为返回值

通过使用引用来替代指针，会使 C++ 程序更容易阅读和维护。C++ 函数可以返回一个引用，方式与返回一个指针类似。

当函数返回一个引用时，则返回一个指向返回值的隐式指针。这样，函数就可以放在赋值语句的左边

```cpp
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double &setValues(int i) {
    double &ref = vals[i];
    return ref;
}

// 引用一般用在基础数据类型，而复合数据类型，指针为主
// return走拷贝


// 要调用上面定义函数的主函数
int main() {

    cout << "改变前的值" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    setValues(1) = 20.23;
    setValues(3) = 70.8;  // 改变第 4 个元素

    cout << "改变后的值" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }
    return 0;
}
```

当返回一个引用时，要注意被引用的对象不能超出作用域。所以返回一个对局部变量的引用是不合法的，但是，可以返回一个对静态变量的引用。

```cpp
int &func() {
    int q;
    //! return q; // 在编译时发生错误
    static int x;
    return x;     // 安全，x 在函数作用域外依然是有效的
}
```
作用域，一般是指可见性，比如private，括号，if内，等

生存周期，是指什么时候释放，static变量生存周期为整个应用程序，可以说：static形容一个变量，可以延长这个变量的生命周期

- [ ] 那么问题来了，static的用法需要额外整理了


[![top]Goto Top](#table-of-contents)



# 指向引用的指针
使用指针的一个简单例子就是：
```cpp
int v = 1;
int *p = &v;
```

需要预先强调的是没有指向引用的指针!因为引用不是对象，没有地址。但是指向引用的指针是什么形式呢？
是对一个引用进行如下取地址吗：

```cpp
int v = 1;
int &ri = v;	// 整型变量v的引用
int *p = &ri;	// 这是指向引用的指针吗？
```

事实上不是，这是一个普通的整型指针，虽然我们说引用没有地址，但是对引用ri的操作实际上是对v的操作。这是是定义了一个整型指针，并且让它指向了v。
那如何定义一个指向引用的指针呢(虽然是不合理的请求)？当我们定义指针的时候，我们用到了`*`，那么当我们定义指向引用的指针时，免不了要用到*和&。

```cpp
int v = 1;
int &ri = v;
// int &*p = &ri;
```

由于引用并不存在地址，因此第三行将会报错。我们可以从右往左读，`*`表明`p`是一个指针，余下的说明了`p`指向类型的类型。

# 指针的引用
之前说到指向引用的指针，现在来说指针的引用就容易多了。

```cpp
int v = 1;
int *p = &v;'
int *&rp = p;
```

`&`明`r`是一个引用。`*`确定`r`引用的类型是一个指针。

# 其他
因为引用不是对象，故无引用的数组，无指向引用的指针，无到引用的引用：

```cpp
int& a[3]; // 错误
int&* p;   // 错误
int& &r;   // 错误
```



[top]: up.png