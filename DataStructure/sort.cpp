//
// Created by 裴奕霖 on 2022/11/7.
//

#include "sort.h"

#include <algorithm>
#define size 10

void Print(int A[], int n) {
  for (int i = 0; i < n; i++) std::cout << A[i] << "\t";
  std::cout << std::endl;
}


namespace Insertion_sort {
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

namespace shell_sort {
// 希尔排序
void ShellSort(int (&A)[size]) {
  int d = 0;
  int i = 0, j = 0;  // 这里还是初始赋值为安全

  for (d = size / 2; d >= 1; d = d / 2) {
    for (i = d + 1; i < size; ++i) {
      // 这里的++i是值得学习的
      if (A[i] < A[i - d]) {
        A[0] = A[i];
        for (j = i - d; j > 0 && A[0] < A[j]; j -= d) A[j + d] = A[j];
        A[j + d] = A[0];
      }
    }
  }
}
}  // namespace shell_sort

namespace Bubble_Sort {
void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void BubbleSort(int (&A)[size]) {
  // 冒泡算法
  // TODO 这里第一次搞错了，错在没弄清楚哪一部份是拍好的，哪一部份是未排序的
  for (int i = 0; i < size; ++i) {
    bool flag = false;
    for (int j = size - 1; j > i; j--) {
      if (A[j] < A[j - 1]) {
        Swap(A[j], A[j - 1]);
        flag = true;
      }
    }
    if (!flag) return;
  }
}

}  // namespace Bubble_Sort
namespace Quicksort {
int Partition(int (&A)[], int low, int high) {
  // 用第一个元素将待排序列表分成左右两个部分
  int pivot = A[low];
  while (low < high) {
    while (low < high && A[high] > pivot) --high;  // TODO
    // 这里的目的是移动high指针，下同，赋值语句其实不参与循环
    // TODO 这里这三个while循环的真是巧妙，可以达到彻底循环的效果
    A[low] = A[high];
    while (low < high && A[low] < pivot) low++;
    A[high] = A[low];
    // 这两个内循环while分次序
  }
  A[low] = pivot;
  return low;
}
void QuickSort(int (&A)[], int low, int high) {
  if (low < high) {  // 跳出递归条件
    int pivot = Partition(A, low, high);
    QuickSort(A, low, pivot - 1);
    QuickSort(A, pivot + 1, high);
  }
}
}  // namespace Quicksort
namespace Selection_sort {
void SelectionSort(int (&A)[size]) {
  // 简单选择排序，实现很简单，但是容易错，易错点在swap，而不能直接替换
  // 排序不稳定
  for (int i = 0; i < size; ++i) {
    int pivot = 0, n = 0;
    for (int j = i; j < size; ++j) {
      if (A[j] > pivot) {
        pivot = A[j];
        n = j;
      }
    }
    Bubble_Sort::Swap(A[i], A[n]);
  }
}

}  // namespace Selection_sort
namespace Heapsort {
// 堆排序
// 简单选择排序和堆排序都属于选择排序
// 堆在物理结构上看起来是连续数组，在逻辑上是顺序存储的二叉树

void my_HeadAdjust(int (&A)[], int root) {
  // 将以k为根的子树调整为大根堆
  if (A[root] < A[2 * root] || A[root] < A[2 * root + 1])
    Bubble_Sort::Swap(
        A[root], A[2 * root] > A[2 * root + 1] ? A[2 * root] : A[2 * root + 1]);
}

void my_BuildMaxHeap(int (&A)[], int len) {
  // 建立大根堆，从后往前调整所有非终端结点
  for (int i = (len - 1) / 2; i > -1; --i) {
    my_HeadAdjust(A, i);
  }
  for (int i = 0; i < (len - 1) / 2 + 1; ++i) {
    my_HeadAdjust(A, i);
  }
}

void HeadAdjust(int (&A)[], int k, int len) {
  A[0] = A[k];
  for (int i = 2 * k; i <= len; i *= 2) {
    if (i < len && A[i] < A[i + 1]) i++;
    if (A[0] >= A[i])
      break;
    else {
      A[k] = A[i];
      k = i;
    }
  }
  A[k] = A[0];
}

void BuildMaxHeap(int (&A)[], int len) {
  for (int i = len / 2; i > 0; --i) {
    HeadAdjust(A, i, len);
  }
}
/*
 哈工大课件的实现
 感觉王道的虽然对，但是逻辑很混乱
 */

void x_Swap(int* array, int i, int j) {
  assert(array);
  int tmp;
  tmp = array[j];
  array[j] = array[i];
  array[i] = tmp;
}

/*大根堆调整*/
void MaxHeapify(int* array, int heapSize, int currentNode) {
  int leftChild, rightChild, largest;
  leftChild = 2 * currentNode;
  rightChild = 2 * currentNode + 1;
  if (leftChild < heapSize && array[leftChild] > array[currentNode])
    largest = leftChild;
  else
    largest = currentNode;
  if (rightChild < heapSize && array[rightChild] > array[largest])
    largest = rightChild;
  if (largest != currentNode) {
    x_Swap(array, largest, currentNode);
    MaxHeapify(array, heapSize, largest);
  }
}
/*构建大根堆*/
void MaxHeapCreat(int* array, int heapSize) {
  int i;
  for (i = (heapSize - 1) / 2; i >= 0; i--) {
    MaxHeapify(array, heapSize, i);
  }
}

void HeapSort(int* array, int heapSize) {
  for (int i = heapSize; i > 0; --i) {
    int head = array[1];
    x_Swap(array, head, array[i]);
    MaxHeapify(array, heapSize, 1);
  }
}

}  // namespace Heapsort

namespace MergeSort {

int* B = new int[size];
void Merge(int* A, int low, int mid, int high) {
  int i, j, k;
  for (k = low; k <= high; k++) B[k] = A[k];
  for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
    if (B[i] <= B[j])
      A[k] = B[i++];
    else
      A[k] = B[j++];
  }
  while (i <= mid) A[k++] = B[i++];
  while (j <= high) A[k++] = B[j++];
}
void MergeSort(int* A, int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;  // TODO 这样写是为了后面可读性强
    MergeSort(A, low, mid);
    MergeSort(A, mid + 1, high);
    Merge(A, low, mid, high);
  }
}
void T_MergeSort() {
  int A_12[9] = {0, 87, 45, 78, 32, 17, 65, 53, 9};
  Print(A_12, 9);
  MergeSort::MergeSort(A_12, 0, 9);
  Print(A_12, 9);
}
}  // namespace MergeSort
