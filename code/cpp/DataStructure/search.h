//
// Created by 裴奕霖 on 2022/10/31.
//

#ifndef DATASTRUCTURE__SEARCH_H_
#define DATASTRUCTURE__SEARCH_H_
namespace Sequence_Search {
#define ElemType int
struct SSTable {
    ElemType* elem;
    int TableLen;
};
}  // namespace Sequence_Search
namespace Block_to_Find {
struct Index {
    ElemType data;
    int low, high;
};
// 顺序表存储实际元素
ElemType List[100];

}  // namespace Block_to_Find
namespace Binary_sort_tree {
typedef struct BSTNode {
    ElemType data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;
}  // namespace Binary_sort_tree
#endif  // DATASTRUCTURE__SEARCH_H_
