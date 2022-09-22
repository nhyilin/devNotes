#include <iostream>

struct LNode {
    int data;
    LNode *next;
};

bool IsEmpty(LNode *&L) { return (L == nullptr); }

bool InitList(LNode *&L) {
    L = new LNode;
    if (L == nullptr) return false;
    L->next = nullptr;
    return true;
}

bool InsertNextNode() {}

int main() { std::cout << "Hello world!"; }
