//
// Created by 裴奕霖 on 2022/12/22.
//

#ifndef DATASTRUCTURE_DSACPP_CHAP1_CPPREVIEW_FIRST_H_
#define DATASTRUCTURE_DSACPP_CHAP1_CPPREVIEW_FIRST_H_
#include <algorithm>
#include <numeric>
// 1. x,y均为形式参数，函数内实参为复制得来，而非参数本体
void swap(int& x, int& y) {
    x = x ^ y;
    y = y ^ x;
    x = x ^ y;
}
// 2
template <class T>
int count(const T& array) {
    int time = 0;
    for (auto i : array) time++;
    return time;
}

// 3
template <class Ta>
void fill(Ta* array, int max, Ta& x) {
    for (int i = 0; i < max; i++) {
        array[i] = x;
    }
}

// 4
template <class Ta>
Ta inner_prodcut(Ta* list01, Ta* list02, int max) {
    Ta sum = 0;
    for (int i = 0; i < max; i++) {
        sum += list01[i] * list02[i];
    }
    return sum;
}

// 5
template <class T>
void iota(T* a, int n,
          const T& value) {  // Set a[i] = a[i] + value, 0 <= i < n.
    // 个人感觉这里答案和题意是不同的，暂时先按答案这么写吧
    for (int i = 0; i < n; i++) a[i] += value;
}

// 6
template <class T>
bool is_sorted(const T& list, int max) {
    for (int i = 0; i < max - 1; i++) {
        if (list[i] < list[i + 1])
            continue;
        else
            return false;
    }
    return true;
}

// 7
template <class T>
int mismatch(const T& list_a, const T& list_b, int max) {
    for (int i = 0; i < max; ++i) {
        if (list_a[i] == list_b[i]) {
            continue;
        } else
            return i + 1;
    }
    return -1;
}

// 程序1-10 为一个二维数组分配存储空间
template <class T>
bool make2dArray(T**& x, int numberOfRows, int numberOfColumns) {
    try {
        // 创建行指针
        x = new T*[numberOfRows];
        // 为每一行分配空间
        for (int i = 0; i < numberOfRows; i++) x[i] = new int[numberOfColumns];
        return true;
    } catch (const std::bad_alloc&) {
        return false;
    }
}
// 程序1-12 释放在函数make2dArray中分配的空间
template <class T>
void delete2dArray(T**& x, int numberOfRows) {
    // 删除二维数组x
    // 删除行数组空间
    for (int i = 0; i < numberOfRows; i++) delete[] x[i];

    // 删除行指针
    delete[] x;
    x = nullptr;
}

// 12
template <class T>
void myMake2dArray(T**& x, int numberOfRows, T* rowSize) {
    x = new T*[numberOfRows];
    for (int i = 0; i < numberOfRows; ++i) {
        rowSize = new T[rowSize[i]];
    }
}
template <class T>
void myDelete2dArray(T**& x, int numberOfRows, T* rowSize) {
    for (int i = 0; i < numberOfRows; i++) delete[] x[i];
    delete[] x;
    x = nullptr;  // 这里删除之后还要设置为空不太理解...
}

// 13
template <class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    if (newLength < 0) std::cerr << "new length must be >= 0";

    T* temp = new T[newLength];                   // new array
    int number = std::min(oldLength, newLength);  // number to copy
    copy(a, a + number, temp);
    delete[] a;  // deallocate old memory
    a = temp;
}
// 14
template <class T>
T* changeLength2D(T*& a, int old_x, int old_y, int new_x, int new_y) {
    if (new_x < 0 || new_y < 0) std::cerr << "new length must be >= 0";

    int** new_array;
    make2dArray(new_array, new_x, new_y);

    for (int i = 0; i < std::min(old_x, new_x); ++i) {
        for (int j = 0; j < std::min(old_y, new_y); ++j) {
            new_array[i][j] = a[i][j];
        }
    }
    delete2dArray(a, old_x);
    return new_array;
}
// 程序1-33
template <class T>
T sum(T* a, int n) {
    // stl accumulate算法
    T theSum = 0;
    return std::accumulate(a, a + n, theSum);
}

// 程序1-34
template <class T>
T Prodect(T* a, int n) {
    // stl Prodect算乘法
    T prodect = 1;
    return std::accumulate(a, a + n, prodect,std::multiplies<T>());
}
#endif  // DATASTRUCTURE_DSACPP_CHAP1_CPPREVIEW_FIRST_H_
