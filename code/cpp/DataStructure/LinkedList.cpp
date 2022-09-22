#include <iostream>

namespace list {
namespace ordered_list {
#define MaxSize 10
struct SqList {
    int data[MaxSize];
    int length
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

/* 静态分配顺序表  */

struct SeqList {
    int *data;
    int max_size;
    int length;
};

// 扩容需要复制粘贴
bool IncreaseSize(SeqList &L, int len) {
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
    //以下部分可以调用InsertNextNode函数来实现
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
}  // namespace list
int _main() {}