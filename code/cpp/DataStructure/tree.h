//
// Created by 裴奕霖 on 2022/10/4.
//

#ifndef DATASTRUCTURE__TREE_H_
#define DATASTRUCTURE__TREE_H_

#define ElemType int

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

//bool DeQueue(LinkQueue &Q, ElemType &x) {
//    // 队头元素出队
//    // TODO
//    // 易错，要搞清楚出列时，出的是哪一个节点，不能把头节点当成第一个元素移出去
//    if (Q.rear == Q.front) return false;
//    LinkNode *p = Q.front->next;  // 这里Q.front其实是头节点
//    x = p->data;
//    Q.front->next = p->next;
//    if (Q.front == p) Q.front = Q.rear;
//    delete p;
//    return true;
//}

#endif  // DATASTRUCTURE__TREE_H_
