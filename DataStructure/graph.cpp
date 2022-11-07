//
// Created by 裴奕霖 on 2022/10/10.
//

#include "graph.h"

namespace Breadth_First_Search {
#define MAX_VERTEX_SIZE 13
bool visited[MAX_VERTEX_SIZE];
void visit(int v) { std::cout << "hello world\n"; }

void BFS(Adjacency_matrix_method::MGraph G, int v) {
    // 广度优先遍历
    visit(v);
    visited[v] = true;
    LinkQueue Q{};
    EnQueue(Q, v);
    while (!IsEmpty(Q)) {
        DeQueue(Q, v);  // 出列，先出列再访问出列的结点的Neighbor
        for (int w = FirstNeighbor(G, v); w > -1; w = NextNeibor(G, v, w)) {
            if (!visited[w]) {
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
                // 只要是访问完成，两个操作，1.访问数组改为true，2.入队
            }
        }
    }
}
void BFSTravel(Adjacency_matrix_method::MGraph G) {
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;
    LinkQueue Q{};
    InitQueue(Q);
    for (int i = 0; i < G.vexnum; ++i) {
        // 这里遍历数组的目的是查看Visited数组是否还有为false的值
        // 以免漏掉某个连通分量
        if (visited[i]) BFS(G, i);  // 对每个连通分量调用一次BFS
    }
}
}  // namespace Breadth_First_Search
namespace Depth_first_traversal {
bool Visited[MAX_VERTEX_SIZE];
void visit(int v) { std::cout << "hello world\n"; }
void DFS(Adjacency_matrix_method::MGraph G, int v) {
    visit(v);
    Visited[v] = true;
    for (int w = FirstNeighbor(G, v); w > -1; w = NextNeibor(G, v, w)) {
        if (!Visited[w]) DFS(G, w);
    }
}
void DFSTravel(Adjacency_matrix_method::MGraph G, bool (&visited)[]) {
    for (int i = 0; i < G.vexnum; ++i) Visited[i] = false;
    for (int i = 0; i < G.vexnum; ++i) {
        // 这里调用DFS次数等于森林中树的个数，因为他们各不互相连通
        if (!Visited[i]) DFS(G, i);  // TODO 这里要注意起始点在哪里，0还是1
    }
}
/**
 * 时间空间复杂度，没有特殊说明，需要指出最坏复杂度
 * 广度优先、深度优先，基本逻辑一致，
 * 但是广度优先需要额外的队列来辅助实现先将横向的所有结点访问
 * 也许这就是队列的存在意义，将代码进程严格卡死在当前任务类型，直至所有满足该条件的数据遍历完成
 * 另外，需要掌握手动推导访问序列
 * 邻接表法可能得到不同的访问序列，这和邻接表实际存储的序列有关
 */
}  // namespace Depth_first_traversal
namespace Minimum_Spanning_Trees {}  // namespace Minimum_Spanning_Trees

namespace Directed_Acyclic_Graph {
/**
 * 基与邻接表来实现
 */
int indegree[MaxSize] = {};  // 记录每个结点入度
int print[MaxSize] = {};     // 记录拓扑排序序列，记录结点编号
bool TopologicalSort(Adjacency_list_method::ALGraph G) {
    SqStack S{};  // 栈在这里用作保存度为零的结点，当然也可用堆或数组来代替
    InitStack(S);
    for (auto &p : print) print[p] = -1;
    for (auto &p : indegree) {
        if (indegree[p] == 0) Push(S, p);
    }
    int count = 0;
    int i = 0;
    while (!IsEmpty(S)) {
        Pop(S, i);
        print[count++] = i;
        for (Adjacency_list_method::ArcNode *p = G.vertices[i].firstArc; p;
             p = p->nextArc) {
            int v = p->advex;
            if (!(--indegree[v])) Push(S, v);
        }
    }
    if (count < G.vexnum)
        return false;
    else
        return true;
}

/*
 * 以下这个例子是基与深度优先遍历(DFS)来实现的逆拓扑排序
 */
//bool indegree_DFS[MaxSize];
//int print_DFS[MaxSize];
//bool Visit[MaxSize];
//void visit(int v) { std::cout << "hello world!\n"; }
//void DFS(Adjacency_matrix_method::MGraph G, int v) {
//    visit(v);
//    Visit[v] = true;
//    for (int w = Depth_first_traversal::FirstNeighbor(G, v); w >= 0;
//         w = Depth_first_traversal::NextNeibor(G, v, w)) {
//        if ()
//    }
//}
//void DFSTransfer(Adjacency_list_method::ALGraph G) {
//    for (auto &p : indegree_DFS) indegree_DFS[p] = false;
//
//    {
//        if (indegree_DFS[p] == false) DFS(p);
//    }
//}

}  // namespace Directed_Acyclic_Graph