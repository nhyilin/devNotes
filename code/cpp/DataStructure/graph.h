//
// Created by 裴奕霖 on 2022/10/10.
//

#ifndef DATASTRUCTURE_GRAPH_H_
#define DATASTRUCTURE_GRAPH_H_

namespace Adjacency_matrix_method {
//邻接矩阵法
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
//邻接表法
using VertexType = char;
struct ArcNode {
    //"边/弧"
    int advex;  //"边/弧"指向哪个结点
    ArcNode* next;
    // InfoType info;//边权值
};
typedef struct VNode {
    // 顶点
    VertexType data;  // 顶点信息
    ArcNode* first;   // 第一条边/弧
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
namespace crossword_list_method{
//十字链表法，用于存储有向图

}//namespace crossword_list_method
#endif  // DATASTRUCTURE_GRAPH_H_
