//
// Created by 裴奕霖 on 2022/10/10.
//

#include "graph.h"

namespace Depth_first_traversal {
#define MAX_VERTEX_SIZE 13
bool visited[MAX_VERTEX_SIZE];
void visit(int v) { std::cout << "hello world\n"; }

void BFS(Adjacency_matrix_method::MGraph G, int v) {
    // 广度优先遍历
    visit(v);
    visited[v] = true;
    LinkQueue Q;
    EnQueue(Q, v);
    while (!IsEmpty(Q)) {
        DeQueue(Q, v);  // 出列，先出列再访问出列的结点的Neighbor
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeibor(G, v, w)) {
            if (!visited[w]) {
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
                // 只要是访问完成，两个操作，1.访问数组改为true，2.入队
            }
        }
    }
}
void BFSTravel(Adjacency_matrix_method::MGraph G, bool (&visited)[]) {
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;
    LinkQueue Q;
    InitQueue(Q);
    for (int i = 0; i < G.vexnum; ++i) {
        if (visited[i]) BFS(G, i);  // 对每个连通分量调用一次BFS
    }
}
namespace Depth_first_traversal {}  // namespace Depth_first_traversal
}  // namespace Depth_first_traversal