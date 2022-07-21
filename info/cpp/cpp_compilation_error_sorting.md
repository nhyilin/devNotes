# 编译
1. error "extra qualification ‘student::’ on member ‘student’ [-fpermissive] "

[In-class definitions of member function(s)/constructor(s)/destructor don't require qualification](https://stackoverflow.com/questions/11692806/error-extra-qualification-student-on-member-student-fpermissive)

2. C++非const引用问题：error: cannot bind non-const lvalue reference of type

https://stackoverflow.com/questions/18565167/non-const-lvalue-references

3. Copy&paste complete error messages!

```cpp
class MyClass {
public:
    MyClass(MyClass &vc);
    
    MyClass(float x, float y, float z);
    
    MyClass operator+(MyClass obj) {// + Operator overload
        
        MyClass newObj(0, 0, 0);
        newObj.x = x + obj.x;
        newObj.y = y + obj.y;
        newObj.z = z + obj.z;
        
        return newObj;
    }

private:
    float x;
    float y;
    float z;
};

MyClass::MyClass(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// Copy constructor
MyClass::MyClass(MyClass &vc) {
    x = vc.x;
    y = vc.y;
    z = vc.z;
}

int main() {
    MyClass myClassObject1(1.0, 2.0, 3.0);
    MyClass myClassObject2(2.0, 3.0, 4.0);
    MyClass myClassObject3 = myClassObject1 + myClassObject2;
    // Why does this give me an error? "no matching constructor for initialization of 'MyClass'"
    
    return 0;
}
```
修改为`MyClass::MyClass(const MyClass &vc)`为解决方案之一，这里gcc默认不开启多线程编译是原罪，当然，你也可以开启`-j 6`之类的编译选项甚至还msvc、clang等编译器也可解决。当然这个非必需是`const`，它不需要是常数。但是你不允许在临时变量不存在的情况下使用它作为参数。你的加法的结果是一个临时的。

只有当你想改变参数的值时，你才需要一个非const引用。这在复制构造函数中似乎是非常罕见的，如果你这样做的话，也很罕见。

# 链接

1. Undefined symbols for architecture x86_64

编译过程中链接错误
```bash
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```
这种情况我碰到的原因是函数只有声明没有实现，但是被调用了。



[![top] Goto Top](#table-of-contents)


<!-- figures -->
[top]: up.png