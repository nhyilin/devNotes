50 Specific Ways to Improve Your Use of the Standard Template Library.

<!--more-->

[《Effective STL》 Chapter 1: Containers（1-6）](https://nhyilin.cn/default/23.html)

---

### Item 7: 在使用存储`new`出来的指针的容器时，记得在容器销毁之前`delete`这些指针

> When using containers of newed pointers, remember to delete the pointers before the container is destroyed.


STL中的容器非常智能。它们可以提供用于正向和反向遍历的迭代器（通过`begin`、`end`、`rbegin`等函数）；它们可以告诉你容器中存储了什么类型的对象（通过它们的`value_type` typedef）；在插入和删除元素时，它们会自动处理必要的内存管理；它们可以报告容器中当前有多少元素以及最多可以容纳多少元素（分别通过`size`和`max_size`）；当然，当容器本身被销毁时，它们会自动销毁它们所包含的每个对象。

考虑到这些智能容器，许多程序员就不再为清理资源而担忧了。他们会想：“嘿，我的容器会替我处理这些问题。” 在很多情况下，他们是对的，但当容器中存储的是通过`new`动态分配的指针时，他们的想法就不够正确了。是的，指针容器会在它们（容器）被销毁时销毁它们所包含的每个元素，但指针的“析构函数”什么都不会做！它当然不会调用`delete`。

因此，以下代码会导致资源泄漏：

```cpp
void doSomething() {
    vector<Widget*> vwp;
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
        vwp.push_back(new Widget);
    ...
    // 使用vwp
}
// 在这里，Widget对象会泄漏！
```

当`vwp`超出作用域时，它的每个元素都会被销毁，但这并不能改变这样一个事实：`new`出来的对象从未被`delete`。这种删除操作是你的责任，而不是容器的责任。这其实是特意设计的功能。只有你知道这些指针是否需要被删除。

通常情况下，你希望它们被删除。当确实需要删除时，实现这一点看起来似乎很简单：

```cpp
void doSomething() {
    vector<Widget*> vwp;
    ...
    // 如前所述
    for (vector<Widget*>::iterator i = vwp.begin(); i != vwp.end(); ++i)
        delete *i;
}
```

这段代码是可以工作的，但前提是你对“工作”并没有太高的要求。这里有两个问题。一个问题是，这个新的`for`循环实际上与`for_each`的功能几乎相同，但它并不像直接使用`for_each`那么清晰（参见第43条）。另一个问题是，这段代码并不是异常安全的。如果在填充`vwp`的指针到删除它们之间抛出了异常，资源仍然会泄漏。幸运的是，这两个问题都可以解决。

要将你的类似`for_each`的循环变成真正的`for_each`调用，你需要将`delete`转化为一个函数对象。这是小菜一碟，假设你有一个喜欢玩STL的孩子：

```cpp
template<typename T>
struct DeleteObject : public unary_function<const T*, void> {
    void operator()(const T* ptr) const {
        delete ptr;
    }
};
```

现在你可以这样写：

```cpp
void doSomething() {
    ...
    // 如前所述
    for_each(vwp.begin(), vwp.end(), DeleteObject<Widget>());
}
```

不幸的是，这样做需要你显式地指定`DeleteObject`将删除的对象的类型（在这里是`Widget`）。这很烦人。`vwp`已经是一个`vector<Widget*>`，所以显然`DeleteObject`会删除`Widget*`指针！这显得很多余。这种冗余不仅令人厌烦，还可能导致难以追踪的错误。例如，假设有人不明智地决定从`string`继承：

```cpp
class SpecialString : public string { ... };
```

从一开始这就是危险的，因为`string`（和所有标准STL容器一样）没有虚析构函数，而从没有虚析构函数的类继承是C++中的一个重大禁忌。（详细信息可以参考任何一本好的C++书。在《Effective C++》中，可以参考第14条。）尽管如此，有些人仍然会这样做，所以让我们看看以下代码会如何表现：

```cpp
void doSomething() {
    deque<SpecialString*> dssp;
    ...
    for_each(dssp.begin(), dssp.end(), DeleteObject<string>());
    // 未定义行为！通过基类指针删除派生对象，
    // 而基类没有虚析构函数。
}
```

注意，`dssp`被声明为存储`SpecialString*`指针，但`for_each`循环的作者告诉`DeleteObject`它将删除`string*`指针。可以理解的是，这样的错误很容易发生。`SpecialString`无疑与`string`非常相似，因此可以原谅它的用户偶尔忘记他们使用的是`SpecialString`而不是`string`。

我们可以通过让编译器推导出传递给`DeleteObject::operator()`的指针类型来消除错误（以及减少`DeleteObject`的用户需要敲击的键数）。我们所需要做的就是将模板化从`DeleteObject`移到它的`operator()`中：

```cpp
struct DeleteObject {
    template<typename T>
    void operator()(const T* ptr) const {
        delete ptr;
    }
};
```

编译器知道传递给`DeleteObject::operator()`的指针的类型，因此我们让它们自动实例化一个接受该类型指针的`operator()`。这种类型推导的缺点是我们放弃了让`DeleteObject`适配器化的能力（参见第40条）。考虑到`DeleteObject`的设计用途，很难想象这会成为一个问题。

使用这个新的`DeleteObject`版本，`SpecialString`用户的代码看起来像这样：

```cpp
void doSomething() {
    deque<SpecialString*> dssp;
    ...
    for_each(dssp.begin(), dssp.end(), DeleteObject());
    // 啊！行为是定义的！
}
```

简单明了，类型安全，就像我们希望的那样。

但仍然不是异常安全的。如果在`SpecialString`对象被`new`出来后但在调用`for_each`之前抛出了异常，就会发生资源泄漏。这个问题可以通过多种方式解决，但最简单的可能是用智能指针替换指针容器，通常是引用计数指针。（如果你不了解智能指针的概念，你应该能在任何一本中高级C++书中找到相关描述。在《More Effective C++》中，相关内容在第28条。）

STL本身不包含引用计数智能指针，编写一个好的智能指针（一个始终正确工作的智能指针）是很棘手的，你不想在没有必要的情况下自己去写一个。幸运的是，经过验证的实现并不难找到。一个这样的智能指针是Boost库中的`shared_ptr`（参见第50条）。使用Boost的`shared_ptr`，本条开头的例子可以重写成如下形式：

```cpp
void doSomething() {
    typedef boost::shared_ptr<Widget> SPW;
    // SPW = “shared_ptr to Widget”
    vector<SPW> vwp;
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
        vwp.push_back(SPW(new Widget));
    // 创建一个SPW对象并将其push_back到vwp中。
    ...
    // 使用vwp
}
// 在这里没有Widget泄漏，即使上面的代码抛出了异常。
```

有一件事你绝对不能做，那就是认为可以通过创建`auto_ptr`的容器来自动删除指针。这是一个糟糕的想法，如此危险，以至于我专门用第8条来解释为什么要避免它。

你真正需要记住的是，STL容器虽然智能，但它们还不足以知道是否应该删除它们包含的指针。为了避免资源泄漏，当你使用包含需要删除的指针的容器时，你必须要么用智能引用计数指针对象（如Boost的`shared_ptr`）替换这些指针，要么在容器销毁之前手动删除每个指针。

最后，你可能会想到，如果像`DeleteObject`这样的结构可以让包含对象指针的容器更容易避免资源泄漏，那么类似的`DeleteArray`结构也可以让包含数组指针的容器更容易避免资源泄漏。当然这是可能的，但是否值得建议则是另一回事。第13条解释了为什么动态分配的数组几乎总是劣于`vector`和`string`对象，因此在你坐下来编写`DeleteArray`之前，请先阅读第13条。希望你能决定`DeleteArray`是一个永远不需要实现的结构。
