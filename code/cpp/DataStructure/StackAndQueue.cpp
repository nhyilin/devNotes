//
// Created by 裴奕霖 on 2022/9/26.
//
#define ElemType char
namespace stack_and_queue {
namespace Sequence_Stack {
#define MaxSize 10
struct SqStack {
    ElemType data[MaxSize];  // 静态数组存放栈中元素
    int top;                 // 栈顶指针
};

void InitStack(SqStack &S) { S.top = -1; }

bool Empty(SqStack &S) {
    if (S.top == -1)
        return true;
    else
        return false;
}

bool Push(SqStack &S, ElemType e) {
    // 进栈操作
    if (S.top == MaxSize - 1) return false;
    S.top++;  // TODO 易错，指针先上移，再赋值
    S.data[S.top] = e;
    return true;
}

bool Pop(SqStack &S, ElemType &e) {
    if (S.top == -1) return false;
    e = S.data[S.top];  // 先出栈，指针再下移
    S.top--;
    return true;
}

bool GetTop(SqStack &S, ElemType e) {
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

void InitStack(ShStack &S) {
    S.top0 = -1;
    S.top1 = MaxSize;
}
}  // namespace Sharing_Stack
}  // namespace Sequence_Stack
namespace link_stack {
struct Linknode {
    ElemType data;
    Linknode *next;
};

}  // namespace link_stack

namespace sequential_queue {
#define MaxSize 10
struct SqQueue {
    ElemType data[MaxSize];
    int front, rear;
};

void InitQueue(SqQueue &Q) { Q.rear = Q.front = 0; };

bool QueueEmpty(SqQueue &Q) {
    if (Q.rear == Q.front)  // TODO 无需等于零
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q, ElemType x) {
    if ((Q.rear + 1) % MaxSize == Q.front) return false;
    Q.data[Q.rear] = x;
    Q.rear =
        (Q.rear++) %
        MaxSize;  // TODO 取余运算，将存储空间逻辑上划为环状，而非线性不断增长
    // TODO 这也为判队满提供了条件，即队尾指针下一个为队头
    // TODO 即(Q.rear + 1) % MaxSize == Q.front;
    return true;
}

bool DeQueue(SqQueue &Q, ElemType &x) {
    // 出队（删除一个队头元素，并用x返回）
    if (Q.rear == Q.front) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front - 1) % MaxSize;
    return true;
}

bool GetHead(SqQueue &Q, ElemType &x) {
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

namespace linked_queue_nohead {
void InitQueue(LinkQueue &Q) {
    // 初始化队列(不带头节点)
    Q.front = nullptr;
    Q.rear = nullptr;
}

bool IsEmpty(const LinkQueue &Q) {
    //    if (Q.rear == nullptr && Q.front == nullptr)
    if (Q.front == nullptr)  // 无需两个都判断
        return true;
    else
        return false;
}

void EnQueue(LinkQueue &Q, ElemType &x) {
    // TODO 易漏
    LinkNode *s = new LinkNode;
    s->data = x;
    s->next = nullptr;
    if (Q.front == nullptr) {
        Q.rear = s;
        Q.front = s;
    } else {
        Q.rear->next = s;
        Q.rear = s;
    }
}

bool DeQueue(LinkQueue &Q, ElemType &x) {
    if (Q.front == nullptr) return false;
    LinkNode *p = Q.front;
    x = p->data;
    Q.front = p->next;
    if (Q.rear == p) {
        Q.front = nullptr;
        Q.rear = nullptr;
    }
    delete p;
    return true;
}
}  // namespace linked_queue_nohead
}  // namespace linked_queue

namespace double_ended_queue {
/**
 * 这部分只需要带入验证即可
 *
 */
}  // namespace double_ended_queue

}  // namespace  stack_and_queue

namespace application {
namespace BracketCheck {
#define length 10
bool BracketCheck(const char (&bracket)[length], int len) {
    // 括号匹配检查算法，入参为顺序栈，以及该栈数组的长度，感觉len这个参数挺无脑的
    stack_and_queue::Sequence_Stack::SqStack S;
    stack_and_queue::Sequence_Stack::InitStack(S);
    for (int i = 0; i < len; ++i) {
        if (bracket[i] == '{' || bracket[i] == '[' || bracket[i] == '(')
            stack_and_queue::Sequence_Stack::Push(S, bracket[i]);
        else {
            if (stack_and_queue::Sequence_Stack::Empty(S)) return false;
        }
        char topElem = {};
        stack_and_queue::Sequence_Stack::GetTop(S, topElem);
        if (bracket[i] == topElem)
            stack_and_queue::Sequence_Stack::Pop(S, topElem);
        else
            return false;
        // 书中关于出栈这部分比较的写法有些累赘
        // TODO 整体逻辑还是需要整理一下
        // 在考试中，基本操作手写函数即可，入出栈等
    }
    return true;
}
}  // namespace BracketCheck

namespace Calculated_Expressions {

/**
 * 用栈实现后缀表达式的计算(机算)：
 * ①从左往右扫描下一个元素，直到处理完所有元素
 * ②若扫描到操作数则压入栈，并回到①；否则执行③
 * ③若扫描到运算符，则弹出两个栈顶元素，执行相应运算，运算结果压回栈顶，回到①
 * 注意：先出栈的是“右操作数
 */

/**
 * 用栈实现前缀表达式的计算：
 * ①从右往左扫描下一个元素，直到处理完所有元素
 * ②若扫描到操作数则压入栈，并回到①；否则执行③
 * ③若扫描到运算符，则弹出两个栈顶元素，执行相应运算，运算结果压回栈顶，回到①
 * 注意：先出栈的是“左操作数”
 */

/**
 * 中缀表达式转后缀表达式（机算）
 * 初始化一个栈，用于保存暂时还不能确定运算顺序的运算符。
 * 从左到右处理各个元素，直到末尾。可能遇到三种情况：
 * ①遇到操作数。直接加入后缀表达式。
 * ②遇到界限符。遇到“（”直接入栈；遇到“）”则依次弹出栈内运算符并加入后缀表达式，直到弹出“（”为止。注意：“（”不加入后缀表达式。
 * ③遇到运算符。依次弹出栈中优先级高于或等于当前运算符的所有运算符，并加入后缀表达式，若碰到“（”或栈空则停止。之后再把当前运算符入栈。
 * 按上述方法处理完所有字符后，将栈中剩余运算符依次弹出，并加入后缀表达式。
 */

/**
 * 中缀表达式的计算（用栈实现）
 * 用栈实现中缀表达式的计算：
 * 初始化两个栈，操作数栈和运算符栈
 * 若扫描到操作数，压入操作数栈
 * 若扫描到运算符或界限符，则按照“中缀转后缀”相同的逻辑压入运算符栈（期间也会弹出运算符，每当弹出一个运算符时，
 * 就需要再弹出两个操作数栈的栈顶元素并执行相应运算，运算结果再压回操作数栈）
 */

}  // namespace Calculated_Expressions
namespace stack_to_recursive_calls{

/**
 * 函数调用特点：最后调用最先执行结束LIFO
 * 函数调用时，需要一个栈来存储
 * 1 调用返回值
 * 2 实参
 * 3 局部变量
 * 适用场景：把原始问题转化为属性相同，但规模较小(n-1)的问题
 */

/**
 * 每进入一层递归，就将递归调用所需信息压入栈顶
 * 每推出一层递归，就从栈顶弹出相应信息
 * 缺点，效率低，太多层递归可能会导致栈溢出，可能包含很多重复机酸
 * 也可自定义栈，将递归算法改造成非递归算法
 */
}//namespace stack_to_recursive_calls

namespace queue_application{
/**
 * 队列应用，树的层次遍历。多个进程争抢使用有限资源时，FCFS，先来先服务
 */

}//namespace queue_application

}  // namespace application
