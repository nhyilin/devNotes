//
// Created by 裴奕霖 on 2022/9/30.
//
#include "tree.h"

#include "../StdAfx.h"
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
void visit_0(linked_tree::BiTree *&q) {
    if (p == q)
        final = pre;
    else
        pre = q;
}
void FindPre(linked_tree::BiTree *&T) {
    // 找前驱的函数，土办法
    if (T != nullptr) {
        InOrder(T->lchild);
        visit_0(T);
        InOrder(T->rchild);
    }
}

namespace threaded_binary_tree {
// 设置几个全局变量
traversing_binary_tree::threaded_binary_tree::ThreadNode *p;  // 指向目标节点
traversing_binary_tree::threaded_binary_tree::ThreadNode *pre =
    nullptr;  // 指向当前访问节点的前驱
traversing_binary_tree::threaded_binary_tree::ThreadNode *final =
    nullptr;  // 用于记录最终结果
void visit_1(traversing_binary_tree::threaded_binary_tree::ThreadNode *q) {
    if (q->lchild == nullptr) {
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre != nullptr && pre->lchild == nullptr) {
        pre->rchild = q;
        pre->rtag = 1;
    }
    pre = q;  // TODO 很容易漏，最后一步
}
void InThread(ThreadTree T) {
    // 中序线索化
    if (T != nullptr) {
        InThread(T->lchild);
        visit_1(T);
        // 其实中序线索话的过程就是中序遍历的过程
        // 只不过在访问该节点时进行一定处理
        InThread(T->rchild);
    }
}
void PreThread(ThreadTree T) {
    // 先序线索化
    if (T != nullptr) {
        visit_1(T);
        if (T->ltag == 0) PreThread(T->lchild);  // lchild不是前驱线索
        // TODO 先序特有的检查，很易错，防止爱滴魔力转圈圈
        PreThread(T->rchild);
    }
}
void CreatInThread(ThreadTree T) {
    pre = nullptr;  // 初始化为空指针
    if (T != nullptr) {
        InThread(T);
        if (pre->rchild == nullptr)
            pre->rtag = 1;  // TODO 很易漏，处理遍历的最后一个节点
    }
}
}  // namespace threaded_binary_tree

namespace find_precursor_and_successor_in_threaded_binary_tree {
using ThreadNode = traversing_binary_tree::threaded_binary_tree::ThreadNode;
void DoJob(ThreadNode *p) { std::cout << "hello world!\n"; }

// 中序找前驱后继

ThreadNode *FirstNode(ThreadNode *p) {
    // 找以p为根的子树中，第一个被中序遍历的节点
    while (p->ltag != 0) p = p->lchild;
    return p;
}
ThreadNode *NextNode(ThreadNode *p) {
    // 在中序线索二叉树中找到节点p的后继节点
    // 右子树的最左下角
    if (p->ltag == 0)
        return FirstNode(p->rchild);
    else
        return p->rchild;
}
void InOrder(ThreadNode *T) {
    // 对中序线索二叉树进行中序遍历(利用线索实现的非递归算法)
    // 时间复杂度O(1)
    for (ThreadNode *p = FirstNode(T); p != nullptr; p = NextNode(p)) {
        DoJob(p);
    }
}

ThreadNode *LastNode(ThreadNode *p) {
    // 找到p为根的子树中，最后一个被中序遍历的节点
    // 循环找到p最右下的节点(不一定是叶节点)
    while (p->rtag == 0) p = p->rchild;
    return p;
}
ThreadNode *PreNode(ThreadNode *p) {
    if (p->ltag == 0)
        return LastNode(p->lchild);
    else
        return p->lchild;
}
void RevInOrder(ThreadNode *T) {
    // 对中序线索二叉树进行逆向中序遍历(利用线索实现的非递归算法)
    // 时间复杂度O(1)
    for (ThreadNode *p = LastNode(T); p != nullptr; p = PreNode(p)) {
        DoJob(p);
    }
}

// 先序找前驱后继

/**
 * 先序遍历中，左右子树中的结点只可能是根的后继，不可能是前驱，无法在子结点中找到前驱
 * 除非用土办法从头开始先序遍历
 * 或者用三叉链表
 *      ①如果能找到 p 的父节点，且 p 是左孩子，P 的父节点即为其前驱
 *      ②如果能找到 p 的父节点，且 p 是右孩子，其左兄弟为空，P
 * 的父节点即为其前驱 ③如果能找到 p 的父节点，且 p 是右孩子，其左兄弟非空，P
 * 的前驱为左兄弟子树中最后一个被先序遍历的结点
 */

// 后序找前驱后继

/**
 * 后序遍历中，左右子树中的结点只可能是根的前驱，不可能是后继
 * 除非用土办法从头开始先序遍历
 */

// ...还是现推比较好

}  // namespace find_precursor_and_successor_in_threaded_binary_tree
}  // namespace traversing_binary_tree
namespace storage_structure {}  // namespace storage_structure

namespace binary_sort_tree {
BSTNode *BST_Search(BSTree T, int key) {
    // 在二叉排序树中找值为key的结点
    while (T != nullptr && key != T->key) {
        if (key < T->key)
            T = T->lchild;
        else
            T = T->rchild;
    }
    return T;
    // 最坏空间复杂度O(1)
}
BSTNode *BST_Search_2(BSTree T, int key) {
    // 在二叉排序树中找值为key的结点(递归实现)
    if (T == nullptr) return nullptr;
    if (key == T->key)
        return T;
    else if (key < T->key)
        return BST_Search_2(T->lchild, key);  // 在左子树中查找
    else
        return BST_Search_2(T->rchild, key);
    // 最坏空间复杂度O(h)
}

int BST_Insert(BSTree &T, int k) {
    // 在二叉排序树中插入关键字为k的新结点(递归实现)
    // 最坏空间复杂度为O(h)
    if (T == nullptr) {
        T = new BSTNode;
        T->key = k;
        T->lchild = T->rchild = nullptr;
        return 1;
    }
    if (k < T->key)
        BST_Insert(T->lchild, k);
    else if (T->key == k)
        return 0;
    else if (T->key > k)
        BST_Insert(T->rchild, k);
    return 1;
}

void Creat_BST(BSTree &T, int str[], int n) {
    // 按照str[]中的关键字序列建立二叉排序树
    T = nullptr;
    T = new BSTNode;
    for (int i = 0; i < n; ++i) {
        BST_Insert(T, str[i]);
        i++;
    }
}

/**
 * 删除操作代码未给出
 */

}  // namespace binary_sort_tree

namespace balanced_binary_trees {}  // namespace balanced_binary_trees

namespace Disjoint_set {
#define SIZE 13
int UFSet[SIZE];

void Initial(int (&S)[]) {
    for (int i = 0; i < SIZE; ++i) {
        S[i] = -1;
    }
}

int Find(int (&S)[], int x) {
    // 查操作，找x所属集合(返回x所属根节点)
    int root = x;
    while (S[root] > -1) root = S[root];
    while (x != root) {
        // TODO 这个while循环里需要做的事情，请记清楚
        int t = S[x];  // t指向x的父节点
        S[x] = root;   // x直接挂到根结点
        x = t;         // 更新x
    }
    return x;
}

void Union(int (&S)[], int Root1, int Root2) {
    // 并操作，将两个集合合为一个
    if (Root1 == Root2) return;  // TODO 要求不能是同一个结点
    // 将根Root2连接到另一个根Root1下面

    /**
     * 借助find操作找到根结点然后将其合并即可
     * 时间复杂度O(1)
     */
    if (S[Root2] > S[Root1]) {           // Root2节点数更少
        S[Root1] = S[Root1] + S[Root2];  // 累加节点数
        S[Root2] = Root1;

    } else {
        S[Root2] = S[Root1] + S[Root2];
        S[Root1] = Root2;
    }
}

}  // namespace Disjoint_set
}  // namespace tree
