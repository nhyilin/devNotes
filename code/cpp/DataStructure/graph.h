//
// Created by 裴奕霖 on 2022/10/10.
//

#ifndef DATASTRUCTURE_GRAPH_H_
#define DATASTRUCTURE_GRAPH_H_

namespace Adjacency_matrix_method {
// 邻接矩阵法
#define MaxVertexNum 100  // 顶点最大数
#define INFINITY 9999     // 宏定义常量"无穷"
using EdgeType = int;

struct MGraph {
    char Vex[MaxVertexNum];  // 顶点表
    EdgeType Edge[MaxVertexNum]
                 [MaxVertexNum];  // 邻接矩阵，边表，也可以用bool型,边的权
    int vexnum, arcnum;  // 图当前顶点数和边数/弧数
    /**
     * 空间复杂度只和边数有关，为O(h2)
     * 适用于存储稠密图
     */
};

}  // namespace Adjacency_matrix_method
namespace Adjacency_list_method {
// 邻接表法
using VertexType = char;
struct ArcNode {
    //"边/弧"
    int advex;  //"边/弧"指向哪个结点
    ArcNode *next;
    // InfoType info;//边权值
};
typedef struct VNode {
    // 顶点
    VertexType data;  // 顶点信息
    ArcNode *first;   // 第一条边/弧
} VNode, AdjList[MaxVertexNum];
struct ALGraph {
    // 用邻接表存储的图
    AdjList vertices;
    int vexnum, arcnum;
};
/**
 * 无向边空间复杂度O(2|E|+|V|)
 * 有向边空间复杂度O(|E|+|V|)
 * 区别在边的冗余存储
 */

/**
 * 图的邻接表表示方式并不唯一，因为边链表内的结点顺序无顺序关系
 * 也就是各个边在这个链表出现顺序是任意的
 * 上一个方式邻接矩阵一旦确定编号，则表示方式唯一
 */
}  // namespace Adjacency_list_method
namespace crossword_list_method {
// 十字链表法，用于存储有向图
// 空间复杂度为O(|V|+|E|)
// 具体实现未给出，自己写一下
}  // namespace crossword_list_method
namespace Adjacency_multiple_list {
// 邻接多重表法，用于存储无向图

}  // namespace Adjacency_multiple_list
namespace Depth_first_traversal {
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
    // 初始化队列(不带头节点)
    Q.front = nullptr;
    Q.rear = nullptr;
}
void EnQueue(LinkQueue &Q, ElemType &x) {
    LinkNode *s = new LinkNode;
    s->data = x;
    s->next = nullptr;  // TODO 很容易漏
    Q.rear->next = s;
    Q.rear = s;  // TODO 很容易漏
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
bool IsEmpty(const LinkQueue &Q) {
    //    if (Q.rear == nullptr && Q.front == nullptr)
    if (Q.front == nullptr)  // 无需两个都判断
        return true;
    else
        return false;
}
int FirstNeighbor(Adjacency_matrix_method::MGraph G, int i) {
    return 1;  // 图G中顶点i的第一个临接点，若有则返回顶点号，无则返回-1
    // 具体实现不用写};
}
int NextNeibor(Adjacency_matrix_method::MGraph G, int x, int y) {
    // 假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的
    // 下一个邻接点的顶点号，若y是x的最后一个邻接点，则返回-1
    return 1;
}
}  // namespace Depth_first_traversal
#endif  // DATASTRUCTURE_GRAPH_H_
