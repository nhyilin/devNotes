//
// Created by 裴奕霖 on 2022/9/30.
//
#include "tree.h"

#include "StdAfx.h"
namespace tree {
#define Elemtype int
#define MaxSize 10
namespace ordered_tree {

void testNode() {
    TreeNode t[MaxSize];  // 使用时，将第一个位置留出来，使得下标和编号相同
    for (auto &i : t)
        i.isEmpty = true;  // TODO 按道理这里从1开始，但是书上是0，保险起见从0吧
};
}  // namespace ordered_tree
namespace linked_tree {}  // namespace linked_tree

namespace traversing_binary_tree {
void DoJob(linked_tree::BiTree *&T) {
    //    while (T->lchild!= nullptr)
    //        DoJob(T->lchild);
    std::cout << "hello world\n";
}
void PreOrder(linked_tree::BiTree *&T) {
    /**
     * 先序遍历（PreOrder）的操作过程如下：
     * 1. 若二叉树为空，则什么也不做；
     * 2. 若二叉树非空：
     *      ①访问根结点；
     *      ②先序遍历左子树；
     *      ③先序遍历右子树。
     */
    if (T != nullptr) {
        DoJob(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
    // 空间复杂度O(h)
}
void InOrder(linked_tree::BiTree *&T) {
    /**
     * 中序遍历（InOrder）的操作过程如下：1. 若二叉树为空，则什么也不做；
     * 2. 若二叉树非空：
     *      ①中序遍历左子树;
     *      ②访问根结点;
     *      ③中序遍历右子树
     */
    if (T != nullptr) {
        InOrder(T->lchild);
        DoJob(T);
        InOrder(T->rchild);
    }
}
void PostOrder(linked_tree::BiTree *&T) {
    /**
     * 后序遍历（InOrder）的操作过程如下：
     * 1. 若二叉树为空，则什么也不做；
     * 2. 若二叉树非空：
     *      ①后序遍历左子树；
     *      ②后序遍历右子树；
     *      ③访问根结点。
     */
    if (T != nullptr) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        DoJob(T);
    }
}

int treeDepth(linked_tree::BiTree *&T) {
    if (T == nullptr)
        return 0;
    else {
        int l = treeDepth(T->lchild);
        int r = treeDepth(T->rchild);
        return l > r ? l + 1 : r + 1;
    }
}

void LevelOrder(linked_tree::BiTree *&T) {
    LinkQueue Q{};
    InitQueue(Q);
    linked_tree::BiTree p{};
    EnQueue(Q, p);
    while (!IsEmpty(Q)) {
        DeQueue(Q, p);
        linked_tree::BiTree *_p = &p;  // 防止临时变量的非静态访问
        DoJob(_p);
        if (p.lchild != nullptr)
            EnQueue(Q, *p.lchild);  // 左孩子入队
        else
            EnQueue(Q, *p.rchild);  // 右孩子入队
    }
}

// 设置几个全局变量
linked_tree::BiTree *p;                // 指向目标节点
linked_tree::BiTree *pre = nullptr;    // 指向当前访问节点的前驱
linked_tree::BiTree *final = nullptr;  // 用于记录最终结果
void visit(linked_tree::BiTree *&q) {
    if (p == q)
        final = pre;
    else
        pre = q;
}
void FindPre(linked_tree::BiTree *&T) {
    //找前驱函数
    if (T != nullptr) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

}  // namespace traversing_binary_tree

}  // namespace tree
