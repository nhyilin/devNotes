//
// Created by 裴奕霖 on 2022/9/30.
//
#include "StdAfx.h"

namespace tree {

#define MaxSize 10
namespace ordered_tree {
#define Elemtype int
struct TreeNode {
    Elemtype data;
    bool isEmpty;

    /**
     * i 的左孩子一[2i]
     * i 的右孩子一[2i+1]
     * i 的父节点一[i/2]
     */

    /**
     * 若完全二叉树中共有 n 个结点，则
     * 判断 i 是否有左孩子？一[2i]≤n?
     * 判断 i 是否有右孩子？一[2i+1]≤n?
     * 判断i是否是叶子/分支结点？一i>[n/2]?
     */

    /**
     * 正因为有上述限制，一般不采取顺序结构的完全二叉树，因为必须每个节点放置在指定位序
     */
};

}  // namespace ordered_tree
namespace linked_tree {
struct BiTree {
    Elemtype data;
    BiTree *lchild, *rchild;
    /**
     * n个节点有2n个指针域，除了根节点之外，每个节点脑袋上都有一根指针，即n-1个脑袋上指针
     * 所以一定有n+1个空链域，后面会用于构造线索二叉树，所以本构造方式也称二叉链表
     */

    /**
     * 该构造难找父节点，若常找父节点，最好再构造一个父节点指针，
     */
    BiTree *parent;  // 三叉链表，考试时一般不考这个
};

}  // namespace linked_tree

namespace traversing_binary_tree {
#define ElemType tree::linked_tree::BiTree
struct LinkNode {
    // 链式队列节点
    ElemType data;
    LinkNode *next;
};
struct LinkQueue {
    // 链式队列
    LinkNode *front, *rear;
};

void InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = new LinkNode;
    Q.rear->next = nullptr;
    Q.front->next = nullptr;
}

bool IsEmpty(const LinkQueue &Q) {
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

void EnQueue(LinkQueue &Q, ElemType &x) {
    LinkNode *s = new LinkNode;
    s->data = x;
    s->next = nullptr;  // TODO 很容易漏
    Q.rear->next = s;
    Q.rear = s;  // TODO 很容易漏
}

bool DeQueue(LinkQueue &Q, ElemType &x) {
    // 队头元素出队
    // TODO
    // 易错，要搞清楚出列时，出的是哪一个节点，不能把头节点当成第一个元素移出去
    if (Q.rear == Q.front) return false;
    LinkNode *p = Q.front->next;  // 这里Q.front其实是头节点
    x = p->data;
    Q.front->next = p->next;
    if (Q.front == p) Q.front = Q.rear;
    delete p;
    return true;
}

namespace threaded_binary_tree {
typedef struct ThreadNode {
    Elemtype data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;  // 左右线索标志
} ThreadNode, *ThreadTree;

}  // namespace threaded_binary_tree

}  // namespace traversing_binary_tree
namespace storage_structure {
#define MAX_TREE_SIZE 10
/****** 双亲表示法(顺序存储)，每个节点保存指向双亲的"指针" *****/
struct PTNode {
    ElemType data;
    int parent;
};
struct PTree {
    PTNode nodes[MAX_TREE_SIZE];
    int n;  // 结点数
};

/****** 孩子表示法(顺序+链式存储) *****/
// 这种结构找孩子方便但是找双亲不方便
struct CTNode {
    int child;  // 孩子节点在数组中位置
    CTNode *next;
};
struct CTBox {
    // 结构中数据实际存储位置
    ElemType data;
    CTNode *firstChild;  // 指向第一个孩子
};
struct CTree {
    CTBox nodes[MAX_TREE_SIZE];
    int n, r;  // 结点数和根的位置
};

/****** 孩子兄弟表示法(链式存储) *****/

typedef struct CSNode {
    // 这个结构很像二叉链表
    ElemType data;
    struct CSNode *firstChild, *nextsibling;  // 第一个孩子和右兄弟指针
} CSNode, *CSTree;

}  // namespace storage_structure
namespace binary_sort_tree {
typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;
}  // namespace binary_sort_tree

namespace Huffman_tree {}  // namespace Huffman_tree
namespace Disjoint_set {

}  // namespace Disjoint_set
}  // namespace tree
