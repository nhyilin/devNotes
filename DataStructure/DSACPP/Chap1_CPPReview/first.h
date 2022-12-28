//
// Created by 裴奕霖 on 2022/12/22.
//

#ifndef DATASTRUCTURE_DSACPP_CHAP1_CPPREVIEW_FIRST_H_
#define DATASTRUCTURE_DSACPP_CHAP1_CPPREVIEW_FIRST_H_
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
}
#endif  // DATASTRUCTURE_DSACPP_CHAP1_CPPREVIEW_FIRST_H_
