1. 绝对值
```cpp
const double EPS = 0.00001;
if (a - b > EPS || b - a > EPS)
{
	cout << "The difference between the aand b is less than EPS" << endl;
}
```


2. 输入n，输出其因子
```cpp
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        if (n % i == 0)
        {
            cout << i << endl;
        }
    }

    return 0;
```
当然，如果需要递减输出，只需将`for`内改为`(int i = n; i >=1; --i)`



3. 素数
```cpp
#include <iostream>
using namespace std;
const int MAX_NUM = 1000;
bool isPrime[MAX_NUM + 10];
int main()
{
    for (int i = 2; i <= MAX_NUM; ++i)
    {
        isPrime[i] = true;//假设所有都为素数
    }
    for (int i = 2; i <= MAX_NUM; ++i)
    {//每次将素数的所有倍数标记为非素数
        if (isPrime[i])//只标记素数的倍数
        {
            for (int j = 2 * i; j < MAX_NUM; j+=i)
            {
                isPrime[j] = false;
            }
        }
        for (int i = 2; i < MAX_NUM; ++i)
        {
            if (isPrime[i])
            {
                cout << i << endl;
            }
        }
    }
    return 0;
}
```
当然素数的解法不只这一个，这也未必（一定不是最好的），有待查询更优的算法。尤其是标记非素数这一步。


4. 变量互换
按位异或无需中间变量完成变量互换：
```cpp
    int a = 5, b = 7;
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;
    cout<<a<<endl;
```


较为笨拙的交换变量方法，但是如下两种函数请理解其区别：
```cpp

void Swap1(int* p1, int* p2) {//实参是&m，而不是m，形参p1的值是&m的拷贝，所以是传值的
    int tmp = *p1;//将p1指向的变量的值赋给tmp
    *p1 = *p2;//将p2指向的变量的值，赋给p1指向的变量
    *p2 = tmp;//将tmp的值赋给p2指向的变量
}
void Swap2(int* p1, int* p2) {//形参p1是实参pm的拷贝，形参p2是实参pn的拷贝
    int* tmp = p1;//保存p1指向的位置
    p1 = p2;//p1指向p2指向的位置
    p2 = tmp;//p2指向p1原来指向的位置
}



int main()
{
    int m = 3, n = 4;
    Swap1(&m, &n);
    cout << m << " " << n << endl;//输出4 3

    int p = 4, q = 3;
    int* pm = &m;//p1指向m
    int* pn = &n;//p2指向n
    Swap2(pm, pn);
    cout << *pm << "," << *pn;//输出4，3

    return 0;
}

```


5. 左移运算符`<<`
移动n位相当于乘了2的n次方，效率比惩罚效率高很多，`a<<b`意味着将a二进制数向左移动b位。右移同理。但是最好不要用右移乱搞，因为涉及到补齐，总之用起来很可能造成不严谨



6. 求x的n次方的函数：
```cpp
double power(double x, int n) {
    double val = 1.0;
    while (n--)
        val *= x;
    return val;
}
```

7. 二进制转十进制
由此推出下面将二进制数转换为10进制数，重点在`cin`部分，逐个读每一位数据
```cpp
#include <iostream>

using namespace std;

double power(double x, int n) {
    double val = 1.0;
    while (n--)
        val *= x;
    return val;
}

int main() {
    int value = 0;
    cout << "pleast input a 8 bit number" << endl;

    for (int i = 7; i >= 0; i--) {
        char ch;
        cin >> ch;
        if (ch == '1')
            value += static_cast<int>(power(2, i));//double to int

    }
    cout << "Decimal value is " << value << endl;
    return 0;
}
```


8. 遍历二维数组
```cpp
void myFun() {
    const int ROW = 20;
    const int COL = 30;
    int a[ROW][COL];
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            cout << a[i][j];
        }
        cout << endl;
    }
}
```



9. 数组排序

```cpp
#include <iostream>
using namespace std;

void InsertionSort(int a[], int size)
{//插入排序
    int i;//有序区间最后一个位置，i+1也就是无序区间最左元素位置
    for (i = 0; i < size - 1; ++i)
    {
        int tmp = a[i + 1];//tmp是待插入到有序区间的元素，即无序区间最左边元素
        int j = i;
        while (j >= 0 && tmp < a[j])//寻找插入的位置
        {
            a[j + 1] = a[j];//比tmp大的元素往后移
            --j;
        }
        a[j + 1] = tmp;
    }
}
void PrintArray(int a[][5], int row)
{//输出二维数组，row是行数
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    int b[5] = { 50,30,20,10,40 };
    int a2d[3][5] = { {5,3,2,1,4},{10,20,50,40,30},{100,120,50,140,30} };
    InsertionSort(b, 5);
    for (int i = 0; i < 5; ++i)
    {
        cout << b[i] << " ";
    }cout << endl;
    for (int i = 0; i < 3; ++i)
    {
        InsertionSort(a2d[i], 5);
    }
    PrintArray(a2d, 3);
    return 0;
}

```
基本思想如下：将待排序序列分为有序序列和无序序列，有序序列在左边，无序序列在右边。一开始有序部分只有一个元素，反复做下去，直到整个序列都变成有序。
整个插入过程如下：从右往左，依次取有序部分元素和待插入元素左作比较，如果大于待插入元素，则将该元素右移一位；如果该元素不大于待插入元素，则将待插入元素放在该元素右边，插入过程完成。如果有序部分所有元素都大于待插入元素，那么这些元素都会被右移一个位置，待插入元素被放到新的有序部分的最左边。

冒泡排序：
```cpp
void BubbleSort(int* pa, int size)
{
    for (int i =size -1;i>0;--i)//这里的i意为数组长度，需要对每个 元素进行遍历排队
    {
        for (int j=0;j<i;++j)//每个元素跑完整段数组
        {
            if (pa[j] > pa[j + 1]) {
                pa[j] ^= pa[j + 1];//其实就是两者值呼唤，借用了位运算
                pa[j + 1] ^= pa[j];
                pa[j] ^= pa[j + 1];
            }
        }
    }
}
int main()
{
    int a[NUM] = { 5,4,8,2,1 };
    BubbleSort(a, NUM);
    for (int i=0;i<NUM;++i)
    {
        cout << a[i]<<" ";
    }
    return 0;
}
```

10. 函数指针定义
```cpp
void PrintMin(int a, int b);
int main()
{
    void(*pf)(int, int);
    return 0;
}
```











































