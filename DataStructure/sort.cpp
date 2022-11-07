//
// Created by 裴奕霖 on 2022/11/7.
//

#include "sort.h"

namespace Insertion_sort {
#define size 10
void InsertSort(int (&A)[size]) {
    // 直接插入排序，思路是从头开始遍历，然后逐个和前一个元素相比
    // 若比前一个小，则往前插入
    int i, j, temp = 0;
    for (i = 0; i < size; ++i) {
        if (A[i] < A[i - 1]) {
            temp = A[i];
            for (j = i - 1; j > -1 && A[j] > temp; j--) {
                A[j + 1] = A[j];
            }
            A[j] = temp;
        }
    }
}
// 哨兵模式就是将A[0]当作temp，并且判断是否到头不是j>-1，而是和A[0]
void InsertSort_binary_search(int (&A)[size]) {
    // 直接插入排序，相对于上一个方法，这里当发现比前一个元素小时
    // 借助前面的元素已经是排序好的前提，采取折半查找
    int low, high, mid;
    int i, j;
    for (i = 2; i < size; ++i) {
        // TODO 这里i开始条件不是0而是2，可以节省两次运算
        if (A[i] < A[i - 1]) {
            // TODO 书上这里没有做这个if判断
            // 个人觉得还是需要的，否则每次直接进行折半查找，不应该不管不顾就直接花log2n时间
            A[0] = A[i];
            low = 1;
            high = i - 1;
            mid = (low + high) / 2;
            while (low < high) {
                mid = (low + high) / 2;
                // TODO 还是这里写错咯，写在这里可避免每个情况都要写这个除法
                if (A[0] >= A[mid])
                    low = mid + 1;
                else
                    high = mid - 1;
            }

            for (j = i - 1; j >= high + 1; --j) {
                A[j + 1] = A[j];
            }
            A[j + 1] = A[0];
        }
    }
};

}  // namespace Insertion_sort
