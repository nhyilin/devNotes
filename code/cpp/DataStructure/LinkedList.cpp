#include "StdAfx.h"

namespace list {
namespace ordered_list {
#define MaxSize 10
struct SqList {
    int data[MaxSize];
    int length;
};
void InitList(SqList &L) {
    for (int i = 0; i < L.length; ++i) {
        L.data[i] = 0;
    }
    L.length = 0;
}

bool InsertList(SqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1) return false;
    if (L.length >= MaxSize) return false;
    for (int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j - 1];  // 这里可以取极限方式思考，如令i=j
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool DeleteList(SqList &L, int i, int e) {
    if (i < 1 || i > L.length) return false;
    if (L.length <= 0) return false;
    for (int j = i; j <= L.length; ++j) {
        L.data[j - 1] = L.data[j];  // 同上，可以取极限方式来界定是否有等号
    }
    L.length--;
    return true;
}

int GetElem(const SqList &L, int i) { return L.data[i - 1]; }

struct SeqList {
    // 动态分配顺序表
    int *data;
    int max_size;
    int length;
};

bool IncreaseSize(SeqList &L, int len) {
    // 扩容需要复制粘贴
    if (len < 0) return false;

    int *p = L.data;
    L.data = new int[L.max_size * sizeof(int)];
    for (int i = 0; i < L.length; ++i) {
        L.data[i] = p[i];
    }
    L.max_size = L.max_size + len;
    delete[] p;
    return true;
}
}  // namespace ordered_list

namespace singly_linked_list {
struct LNode {
    int data;
    LNode *next;
};

bool InitList(LNode *&L) {
    // 初始化
    L = new LNode;
    if (L == nullptr) return false;
    L->next = nullptr;
    return true;
}

// 插入
bool ListInsert(LNode *&L, int i, int e) {
    if (i < 1) return false;
    LNode *p = new LNode;  // 工作指针
    p = L;
    int j = 0;
    while (p != nullptr && j < i - 1) {
        p = p->next;
        j++;
    }
    // 以下部分可以调用InsertNextNode函数来实现
    if (p == nullptr) return false;
    LNode *s = new LNode;
    s->next = p->next;
    p->next = s;  // 顺序不能颠倒
    s->data = e;
    return true;
}
/*  使用 */
// int main() {
//     LNode *L;
//     List_HeadInsert(L);
// }

bool InsertNextNode(LNode *p, int element) {
    // 指定节点的后插操作
    if (p == nullptr) return false;
    LNode *s = new LNode;
    if (s == nullptr) return false;
    s->data = element;
    s->next = p->next;
    p->next = s;
    return true;
}
bool InsertPriorNode(LNode *p, int element) {
    // 指定节点前插操作，其实是将p复制了一份给s，p本身作为前继节点
    if (p == nullptr) return false;
    LNode *s = new LNode;
    s->data = p->data;
    s->next = p->next;

    p->data = element;
    p->next = s;

    return true;
}
bool ListDelete(LNode *L, int i, int element) {
    // 按位序删除
    if (i < 1) return false;
    LNode *p;
    p = L;
    int j = 1;
    while (p != nullptr && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p == nullptr || p->next == nullptr) return false;
    p->next = p->next->next;
    element = p->next->data;

    delete p->next;
    return true;
}
bool DeleteNode(LNode *p) {
    // 指定节点的删除
    // 这里请注意，若p就是最后一个节点，那么无法采取下面取巧的办法
    // 只能规规矩矩从头节点找到p的上一节点
    if (p == nullptr) return false;
    p->next = p->next->next;
    p->data = p->next->data;
    delete p->next;
    return true;
}

LNode *GetElem(LNode *L, int i) {
    // 按位查找
    if (i < 0) return nullptr;
    LNode *p = new LNode;
    p = L;
    int j = 1;
    while (p != nullptr && j < i + 1) {
        // 这里j的取值很容易错，带个固定值试一试
        p = p->next;
        j++;
    }
    return p;
}
LNode *GetElem(LNode *&L, int element) {
    // 按值查找
    LNode *p;
    p = L->next;  // 这里很容易忽略，从L的第一个节点开始查找
    while (element != p->data && p != nullptr) {
        p = p->next;
    }
    return p;
}
// TODO 若这时候传入的L并非头节点
//  那么就无法遍历查找所有连链表节点了,考试这样就可以了
LNode *LocateElem(LNode *&L, int element) {
    // 按值查找
    LNode *p = new LNode;
    while (p != nullptr && p->data != element) p = p->next;
    return p;
}

int length(LNode *&L) {
    // 求链表长度
    int len = 0;
    LNode *p = new LNode;
    while (p != nullptr) {
        p = p->next;
        len++;
    }
    return len;
}

LNode *List_TailInsert(LNode *&L) {
    // 尾插法建立链表
    // TODO 反正自己写的时候思路不太一样，但是方法都是一样的
    L = new LNode;
    L->next = nullptr;
    // 这里尽量初始化，因为后面会有指定的next操作
    // 但头插法一定要初始化
    LNode *s, *r = L;
    int element = 0;
    std::cin >> element;
    while (element != 999) {
        LNode *s = new LNode;
        s->data = element;
        r->next = s;
        r = s;
    }
    r->next = nullptr;
    return L;
}
void List_HeadInsert(LNode *&L) {
    // 这个函数是一整个建立单链表的过程，用的方法是头插建立，应该说这个函数包含初始化
    LNode *s;
    int x;
    L = new LNode;
    L->next = nullptr;

    std::cin >> x;
    while (x != 999) {
        s = new LNode;
        s->data = x;
        L->next = s;
        s->next = nullptr;
        std::cin >> x;
    }
}

namespace singly_linked_list_no_head {
bool InitList(LNode *&L) {
    L = nullptr;
    return true;
}

bool IsEmpty(LNode *&L) { return (L == nullptr); }

// 不带头节点时，当插入第一个元素时，需要特殊处理
bool ListInsert(LNode *&L, int i, int e) {
    if (i <= 1) return false;
    if (i == 1) {
        LNode *s = new LNode;
        s->next = L;
        s->data = e;
        L = s;
        return true;
    }

    LNode *p = new LNode;
    int j = 1;
    while (p != nullptr && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p == nullptr) return false;
    LNode *s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
}  // namespace singly_linked_list_no_head
}  // namespace singly_linked_list
namespace double_linked_list {
// 双链表
struct DNode {
    int data;
    struct DNode *prior, *next;
};

bool InitDLinklist(DNode *&L) {
    // 初始化双链表
    L = new DNode;
    if (L == nullptr) return false;
    L->prior = nullptr;
    L->next = nullptr;
    return true;
}
bool Empty(const DNode *&L) {
    // 判断是否为空，带头节点
    if (L->next == nullptr)
        return true;
    else
        return false;
}
bool InsertDNode(DNode *&p, DNode *&s) {
    // 在p节点之后插入节点s
    if (p == nullptr || s == nullptr) return false;  // TODO 易错
    s->next = p;
    s->prior = p->prior;
    if (p->next != nullptr) p->next->prior = s;  // TODO 易错
    p->next = s;
    return true;
}

bool DeleteNextNode(DNode *p) {
    if (p == nullptr) return false;
    if (p->next == nullptr) return false;
    p->next = p->next->next;
    p->next->prior = p;
    delete p->next;
    return true;
}
void DestoryList(DNode *&L) {
    while (L->next != nullptr) {
        DeleteNextNode(L);
    }
}
void Traverse(DNode *p) {
    // 向后遍历
    //...对p处理过程
    while (p != nullptr) p = p->next;

    // 向前遍历
    //...对p处理过程
    while (p != nullptr) p = p->prior;

    // 向前遍历，跳过头节点
    //...对p处理过程
    while (p->prior != nullptr) p = p->next;
}

void testDLinkList() { DNode *L; }

namespace singly_linked_circular_list {

struct LNode {
    int data;
    LNode *next;
};

bool InitList(LNode *&L) {
    L = new LNode;
    if (L == nullptr) return false;
    L->next = L;
    return true;
}

bool Empty(LNode *L) {
    if (L->next == L)
        return true;
    else
        return false;
}
bool isTail(LNode *&L, LNode *p) {
    if (p->next == L)
        return true;
    else
        return false;
}
}  // namespace singly_linked_circular_list
namespace double_linked_circular_list {
struct DNode {
    int data;
    DNode *next, *prior;
};
bool InitDLinkList(DNode *&L) {
    L = new DNode;
    if (L == nullptr) return false;
    L->next = L;
    L->prior = L;  // 这里需要注意，头节点初始值为L
    return true;
}
bool Empty(DNode *&L) {
    // 判断循环双链表是否为空
    //     if (L->next==L&&L->prior==L)return true;
    if (L->next == L)
        return true;
    else
        return false;
}
bool IsTail(DNode *&L, DNode *p) {
    // 判断节点p是否为循环列表的尾节点
    if (p->next == L)
        return true;
    else
        return false;
}
bool InsertNextNode(DNode *p, DNode *s) {
    // 在p节点之后c插入s节点
    s->next = p->next;
    p->next->prior = s;  // TODO 容易漏
    s->prior = p;
    p->next = s;
    return true;
}
bool DeleteNode(DNode *p) {
    // 删除p的后继节点
    p->next = p->next->next;
    p->next->next->prior = p;
    return true;
}
namespace static_linked_list {
// 静态链表
#define MaxSize 10
struct Node {
    int data;
    int next;
};
void test() {
    // 初始化方式值得体会
    //  ppt中列举了Node在定义时可定义为SLinkList[MaxSize]的方式可读性更佳
    Node node[MaxSize];
}

}  // namespace static_linked_list
}  // namespace double_linked_circular_list
}  // namespace double_linked_list
}  // namespace list
void _main() {}