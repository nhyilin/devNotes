# Table of Contents
- [Table of Contents](#table-of-contents)
- [侯捷C++之C++ STL](#侯捷c之c-stl)
  - [1. 认识headers、版本、重要资源](#1-认识headers版本重要资源)
  - [2. STL体系结构基础介绍](#2-stl体系结构基础介绍)
  - [3. 容器之分类与各种测试（一）](#3-容器之分类与各种测试一)
  - [4. 容器之分类与各种测试（二）](#4-容器之分类与各种测试二)
  - [5. 容器之分类与各种测试（三）](#5-容器之分类与各种测试三)
  - [6. 容器之分类与各种测试（四）](#6-容器之分类与各种测试四)
  - [7. 分配器之测试](#7-分配器之测试)
  - [8. 源代码之分布 (VC, GCC)](#8-源代码之分布-vc-gcc)
  - [9. OOP (面向对象编程) vs. GP (泛型编程）](#9-oop-面向对象编程-vs-gp-泛型编程)
  - [10. 技术基础：操作符重载and模板(泛化, 全特化, 偏特化)](#10-技术基础操作符重载and模板泛化-全特化-偏特化)
  - [11. 分配器](#11-分配器)
  - [12. 容器之间的实现关系与分类](#12-容器之间的实现关系与分类)
  - [13. 深度探索list（上）](#13-深度探索list上)
  - [14. 深度探索list（下）](#14-深度探索list下)
  - [15. 迭代器的设计原则和Iterator Traits的作用与设计](#15-迭代器的设计原则和iterator-traits的作用与设计)
  - [16. vector深度探索](#16-vector深度探索)
  - [17. array、forward\_list深度探索](#17-arrayforward_list深度探索)
  - [18. deque、queue和 stack深度探索（上）](#18-dequequeue和-stack深度探索上)
  - [19. deque、queue和 stack深度探索（下）](#19-dequequeue和-stack深度探索下)
  - [20. RB-tree 深度探索](#20-rb-tree-深度探索)
  - [21. set、multiset深度探索](#21-setmultiset深度探索)
  - [22. map、multimap深度探索](#22-mapmultimap深度探索)
  - [23. hashtable深度探索（上）](#23-hashtable深度探索上)
  - [24. hashtable深度探索（下）](#24-hashtable深度探索下)
  - [25. hash\_set、hash\_multiset, hash\_map、hash\_multimap概念](#25-hash_sethash_multiset-hash_maphash_multimap概念)
  - [26. unordered容器概念](#26-unordered容器概念)
  - [27. 算法的形式](#27-算法的形式)
  - [28. 迭代器的分类（category）](#28-迭代器的分类category)
  - [29. 迭代器分类（category）对算法的影响](#29-迭代器分类category对算法的影响)
  - [30. 算法源代码剖析（11个例子）](#30-算法源代码剖析11个例子)
  - [31. 仿函数和函数对象](#31-仿函数和函数对象)
  - [32. 存在多种Adapter](#32-存在多种adapter)
  - [33. Binder2nd](#33-binder2nd)
  - [34. not1](#34-not1)
  - [35. bind](#35-bind)
  - [36. reverse\_iterator](#36-reverse_iterator)
  - [37. inserter](#37-inserter)
  - [38. ostream\_iterator](#38-ostream_iterator)
  - [39. istream\_iterator](#39-istream_iterator)
  - [40. 一个万用的hash function](#40-一个万用的hash-function)
  - [41. Tuple 用例](#41-tuple-用例)
  - [42. type traits](#42-type-traits)
  - [43. type traits 实现](#43-type-traits-实现)
  - [44. cout](#44-cout)
  - [45. movable元素对于deque速度效能的影响](#45-movable元素对于deque速度效能的影响)
  - [46. 测试函数](#46-测试函数)


# 侯捷C++之C++ STL

## 1. 认识headers、版本、重要资源


[![top] Goto Top](#table-of-contents)

## 2. STL体系结构基础介绍

STL提供了六大组件，彼此组合套用协同工作。 容器(containers)，算法(algorithm)，迭代器(iterator)， 仿函数(functors)，适配器(adapters)，配置器(allocators)

迭代器(iterator)是前闭后开，也就是`c.end()`解引用，得到内容，得到的其实是容器最后一位的下一位，这样是非法的。

遍历容器的方式：

1. 老式

```cpp
  Container<T> c;
  ...
  Container<T>::iterator ite = c.begin();
  for (; ite != c.end(); iter++)
      ...
```

2. c++11

```cpp
// coll是指collection，容器
for (decl : coll){
    statements
}
```
例如：

```cpp
for (int i : {2, 3, 4, 5, 6, 9}) {
 std::cout << i << std::endl;
}
```

又如：
```cpp
  for (auto elem : vec) std::cout << elem << std::endl;

  for (auto &elem : vec) elem *= 3;
```

第一个就是常规取出元素，第二个则是取出一个引用，可以遍历容器内每个元素的引用，并可对其修改。

[![top] Goto Top](#table-of-contents)

## 3. 容器之分类与各种测试（一）

容器分为两类，Sequence Containers（序列容器），Associative Containers（关联式容器），Unordered Containers（不定序容器）

序列容器包括Array、Vector、Deque、List、Fastforward-List

关联式容器主要特点是有key和value，适合做要素查找，包括Set/Multiset（底层是由红黑树实现）、Map/Multimap（底层也是由红黑树实现)。二者区别是节点。

[set和map的区别](https://www.geeksforgeeks.org/set-vs-map-c-stl/)：区别在于set只用来存储键，而map则用来存储键值对。例如，考虑到在打印排序的不同元素的问题中，我们使用set，因为有一个键需要值。而如果我们把问题改为打印不同排序元素的频率，我们就使用map。我们需要map来存数组的值作为键，频率作为值。

不定序容器底部是由哈希表（Separating Chaining）实现

[![top] Goto Top](#table-of-contents)

## 4. 容器之分类与各种测试（二）

[![top] Goto Top](#table-of-contents)

## 5. 容器之分类与各种测试（三）

[![top] Goto Top](#table-of-contents)

## 6. 容器之分类与各种测试（四）

[![top] Goto Top](#table-of-contents)

## 7. 分配器之测试

[![top] Goto Top](#table-of-contents)

## 8. 源代码之分布 (VC, GCC)

[![top] Goto Top](#table-of-contents)

## 9. OOP (面向对象编程) vs. GP (泛型编程）

标准库采用泛型编程，因为想让容器、迭代器、算法、仿函数之间可以独立开发，互不影响，闭门造车。

所有algorithm，其内最终涉及元素本身的操作，无非就是比大小。如排序。

当一个容器没有自带sort时，才能用全局`::sort()`，比如`list`，因为源码中list的迭代器无法满足全局的`sort`函数。其他容器同理。而`vector`和`deque`可以用全局`sort`


[![top] Goto Top](#table-of-contents)

## 10. 技术基础：操作符重载and模板(泛化, 全特化, 偏特化)

[![top] Goto Top](#table-of-contents)

## 11. 分配器

[![top] Goto Top](#table-of-contents)

## 12. 容器之间的实现关系与分类

[![top] Goto Top](#table-of-contents)

## 13. 深度探索list（上）

[![top] Goto Top](#table-of-contents)

## 14. 深度探索list（下）

[![top] Goto Top](#table-of-contents)

## 15. 迭代器的设计原则和Iterator Traits的作用与设计

[![top] Goto Top](#table-of-contents)

## 16. vector深度探索

[![top] Goto Top](#table-of-contents)

## 17. array、forward_list深度探索

[![top] Goto Top](#table-of-contents)

## 18. deque、queue和 stack深度探索（上）

[![top] Goto Top](#table-of-contents)

## 19. deque、queue和 stack深度探索（下）

[![top] Goto Top](#table-of-contents)
 
## 20. RB-tree 深度探索

[![top] Goto Top](#table-of-contents)

## 21. set、multiset深度探索

[![top] Goto Top](#table-of-contents)

## 22. map、multimap深度探索

[![top] Goto Top](#table-of-contents)

## 23. hashtable深度探索（上）

[![top] Goto Top](#table-of-contents)

## 24. hashtable深度探索（下）

[![top] Goto Top](#table-of-contents)

## 25. hash_set、hash_multiset, hash_map、hash_multimap概念

[![top] Goto Top](#table-of-contents)

## 26. unordered容器概念

[![top] Goto Top](#table-of-contents)

## 27. 算法的形式

[![top] Goto Top](#table-of-contents)

## 28. 迭代器的分类（category）

[![top] Goto Top](#table-of-contents)

## 29. 迭代器分类（category）对算法的影响

[![top] Goto Top](#table-of-contents)

## 30. 算法源代码剖析（11个例子）

[![top] Goto Top](#table-of-contents)

## 31. 仿函数和函数对象

[![top] Goto Top](#table-of-contents)

## 32. 存在多种Adapter

[![top] Goto Top](#table-of-contents)

## 33. Binder2nd

[![top] Goto Top](#table-of-contents)

## 34. not1

[![top] Goto Top](#table-of-contents)

## 35. bind

[![top] Goto Top](#table-of-contents)

## 36. reverse_iterator

[![top] Goto Top](#table-of-contents)

## 37. inserter

[![top] Goto Top](#table-of-contents)

## 38. ostream_iterator

[![top] Goto Top](#table-of-contents)

## 39. istream_iterator

[![top] Goto Top](#table-of-contents)


## 40. 一个万用的hash function

[![top] Goto Top](#table-of-contents)

## 41. Tuple 用例

[![top] Goto Top](#table-of-contents)

## 42. type traits

[![top] Goto Top](#table-of-contents)

## 43. type traits 实现

[![top] Goto Top](#table-of-contents)

## 44. cout

[![top] Goto Top](#table-of-contents)

## 45. movable元素对于deque速度效能的影响

[![top] Goto Top](#table-of-contents)

## 46. 测试函数

[![top] Goto Top](#table-of-contents)




[![top] Goto Top](#table-of-contents)

[top]: up.png
[top]: https://upload.nhyilin.cn/2021-11-19-up.png