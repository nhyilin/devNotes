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

























































