# 一 指针作为函数参数传递时

1. 类似于值传递，传入函数的指针只是原指针的一个拷贝，所以此时是存在两个指针，同时指向一个内存空间（同时指向原对象）
2. 当在函数中不改变拷贝指针的指向时，修改指针的值，就相当于修改原指针指向的对象
3. 当在函数中改变拷贝指针的指向时，只是改变了拷贝指针的指向，不改变原指针的指向，所以不改变原指针指向的对象。

```cpp
using namespace std;

#include<iostream>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int a = 1, b = 2;
    swap(&a, &b);
    cout << a << " " << b << endl;
    system("pause");
    return 0;
} //结果为2 1
```

此时函数改变了原指针指向的对象的值，正如上述2所说，当在函数中不改变拷贝指针的指向时，修改指针的值，就相当于修改原指针指向的对象。

```cpp
#include<iostream>

using namespace std;

void test(int *p) {
    int a = 1;
    p = &a;
    cout << p << " " << *p << endl;
}

int main(void) {
    int *p = NULL;
    test(p);
    if (p == NULL)
        cout << "指针p为NULL" << endl;
    system("pause");
    return 0;
}
```
```sh
0x7ff7b343e644 1
指针p为NULL
```
结果中，指针p依旧为NULL，并未改变，此时函数未改变原指针指向的对象的值，正如上述3所说，当在函数中改变拷贝指针的指向时，只是改变了拷贝指针的指向，不改变原指针的指向，所以不改变原指针指向的对象。

# 二 引用作为函数参数传递时
实质上传递的是实参本身，即传递进来的不是实参的一个拷贝，因此对形参的修改其实是对实参的修改，所以在用引用进行参数传递时，不仅节约时间，而且可以节约空间。
```cpp
void test(int &a) {
    a++;
    cout << &a << " " << a << endl;
}

int main(void) {
    int a = 1;
    cout << &a << " " << a << endl;
    test(a);
    system("pause");
    return 0;
}
```
```sh
0x7ff7b07b7668 1
0x7ff7b07b7668 2
```

由结果可知，地址相同，值被改变。

# 三 所以在要达到同时修改指针的目的的话，就得使用引用了。
```cpp
#include<iostream>
using namespace std;

void test(int *&p) {
    int a = 1;
    p = &a;
    cout << p << " " << *p << endl;
}

int main(void) {
    int *p = NULL;
    test(p);
    if (p != NULL)
        cout << "指针p不为NULL" << endl;
    system("pause");
    return 0;
}
```
```sh
0x7ff7b19b5644 1
指针p不为NULL
```