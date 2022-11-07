//
// Created by 裴奕霖 on 2022/10/31.
//

#include "search.h"
namespace Sequence_Search {
// int Search_Seq(SSTable ST, ElemType key) {
//     // 没有哨兵
//     int i;
//     for (i = 0; i < ST.TableLen && key != ST.elem[i]; i++)
//         ;
//     // 查找成功返回i，查找失败返回-1
//     return i == ST.TableLen ? -1 : i;
// }
int Search_Seq(SSTable ST, ElemType key) {
    // 带哨兵的顺序查找
    ST.elem[0] = key;  // 0号位置存放哨兵
    int i;
    for (i = ST.TableLen; ST.elem[i] != key; --i)
        ;
    return i;
}
int Binary_Search(SSTable ST, ElemType key) {
    int low = 0, high = ST.TableLen - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        // TODO 这里很容易错，应该放在while里面，这样做的好处是，
        // 1 可以判断low和high的合法性
        // 2 接下来每个判断中无需每个判断都要写mid的赋值语句
        if (key == ST.elem[mid])
            return mid;
        else if (key < ST.elem[mid]) {
            high = mid - 1;
        } else {  // TODO 这里不用else if比较好，省去判断一步
            low = mid + 1;
        }
    }
    return -1;
}

//    这段代码说明c++中，整数除法得到整数，舍掉小数部分
//    std::cout<< (2+9)/2;
//    return 0;
//
}  // namespace Sequence_Search

namespace Binary_sort_tree {
BSTNode *BSTSearch(BSTree T, int key) {
    // 非递归实现二叉排序树中查找值为key的结点
    while (T != nullptr && T->key != key) {
        if (T->key > key)
            T = T->rchild;
        else
            T = T->lchild;
    }
    return T;
    // 数上代码风格喜欢将等于判断放在括号里，而不是while里，实际上对效率区别不大
}
BSTNode *BSTSearch_recursive(BSTree T, int key) {
    // 递归实现二叉排序树中查找值为key的结点
    if (T == nullptr) return nullptr;
    if (T->key == key) return T;
    if (T->key > key)
        BSTSearch_recursive(T->rchild, key);
    else
        BSTSearch_recursive(T->lchild, key);
    // 递归算法思想值得学习，尤其是这里的二叉树
    // 递归算法空间复杂度较高，在这里和树的高度相关
}

}  // namespace Binary_sort_tree