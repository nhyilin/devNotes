//
// Created by 裴奕霖 on 2022/9/26.
//
#define ElemType int
namespace stack_and_queue {
namespace Sequence_Stack {
#define MaxSize 10
struct SqStack {
    ElemType data[MaxSize];  // 静态数组存放栈中元素
    int top;                 // 栈顶指针
};
void InitStack(SqStack& S) { S.top = -1; }
bool Empty(SqStack& S) {
    if (S.top == -1)
        return true;
    else
        return false;
}
bool Push(SqStack& S, ElemType e) {
    // 进栈操作
    if (S.top == MaxSize - 1) return false;
    S.top++;  // TODO 易错，指针先上移，再赋值
    S.data[S.top] = e;
    return true;
}
bool Pop(SqStack& S, ElemType e) {
    if (S.top == -1) return false;
    e = S.data[S.top];  // 先出栈，指针再下移
    S.top--;
    return true;
}

bool GetTop(SqStack& S, ElemType e) {
    if (S.top == -1) return false;
    e = S.data[S.top];  // e记录栈顶元素
    return true;
}

namespace Sharing_Stack {
// 共享栈
// 两个栈共享一片空间
struct ShStack {
    ElemType data[MaxSize];
    int top0;  // 0号栈栈顶指针
    int top1;  // 1号栈栈顶指针
    // 栈满条件: top0 + 1 = top1
};
void InitStack(ShStack& S) {
    S.top0 = -1;
    S.top1 = MaxSize;
}
}  // namespace Sharing_Stack
}  // namespace Sequence_Stack
namespace link_stack {
struct Linknode {
    ElemType data;
    Linknode* next;
};

}  // namespace link_stack

namespace sequential_queue {
#define MaxSize 10
struct SqQueue {
    ElemType data[MaxSize];
    int front, rear;
};
void InitQueue(SqQueue& Q) { Q.rear = Q.front = 0; };
bool QueueEmpty(SqQueue& Q) {
    if (Q.rear == Q.front)  // TODO 无需等于零
        return true;
    else
        return false;
}
bool EnQueue(SqQueue& Q, ElemType x) {
    if ((Q.rear + 1) % MaxSize == Q.front) return false;
    Q.data[Q.rear] = x;
    Q.rear =
        (Q.rear++) %
        MaxSize;  // TODO 取余运算，将存储空间逻辑上划为环状，而非线性不断增长
    // TODO 这也为判队满提供了条件，即队尾指针下一个为队头
    // TODO 即(Q.rear + 1) % MaxSize == Q.front;
    return true;
}

bool DeQueue(SqQueue& Q, ElemType& x) {
    // 出队（删除一个队头元素，并用x返回）
    if (Q.rear == Q.front) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front - 1) % MaxSize;
    return true;
}
bool GetHead(SqQueue& Q, ElemType& x) {
    // 获得队头元素的值，用x返回
    if (Q.front == Q.rear) return false;
    x = Q.data[Q.front];
    return true;
}
/**
 * 判断队列是否满,若是以EnQueue里的环状存储时,则存在浪费一个数组空间的问题
 * 另一个方案是结构体中保存队列长度变量
 * 初始化时令size=0
 * 队满条件size==MaxSize，队空条件size==0
 * 插入成功size++，出队成功size--
 */
struct SqQueue2 {
    ElemType data[MaxSize];
    int front, rear;
    int size;
};

struct SqQueue3 {
    ElemType data[MaxSize];
    int front, rear;
    int tag;
};
/**
 * 另一种方式，当队空队满，都是rear==front
 * 设置tag变量记录最后一次操作是插入还是删除
 * 入队为1出队为0
 * 只有入队才能导致队满，出队才能导致队空
 * 队满:(front==rear&&tag==1)，队空:(front==rear&&tag==0)
 */

/*
 * 注意队尾指针指向即将插入元素的位置还是指向最后一个元素
 * 这种情况就无法通过判断队头队尾指针来判断了
 * 只能通过size法或者空出来一个，或者tag法
 * 另外，这时入队、出队操作语句需要重写
 */
}  // namespace sequential_queue

namespace linked_queue {
struct LinkNode {
    // 链式队列节点
    ElemType data;
    LinkNode* next;
};
struct LinkQueue {
    // 链式队列
    LinkNode *front, *rear;
};

void InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = new LinkNode;
    Q.rear->next = nullptr;
    Q.front->next = nullptr;
}
bool IsEmpty(const LinkQueue& Q) {
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

namespace linked_queue_nohead {

void InitQueue(LinkQueue& Q) {
    // 初始化队列(不带头节点)
    Q.front = nullptr;
    Q.rear = nullptr;
}
bool IsEmpty(const LinkQueue& Q) {
    //    if (Q.rear == nullptr && Q.front == nullptr)
    if (Q.front == nullptr)  // 无需两个都判断
        return true;
    else
        return false;
}

}  // namespace linked_queue_nohead
}  // namespace linked_queue

}  // namespace  stack_and_queue
