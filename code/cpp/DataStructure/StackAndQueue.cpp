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
    if (S.top = MaxSize - 1) return false;
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
    //栈满条件: top0 + 1 = top1
};
void InitStack(ShStack& S) {
    S.top0 = -1;
    S.top1 = MaxSize;
}
}  // namespace Sharing_Stack
}  // namespace Sequence_Stack

}  // namespace  stack_and_queue
