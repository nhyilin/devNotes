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
    if (S.top = MaxSize - 1) return false;
    S.top++;//TODO 易错，指针先上移，再赋值
    S.data[S.top] = e;
    return true;
}
}  // namespace Sequence_Stack

}  // namespace  stack_and_queue
