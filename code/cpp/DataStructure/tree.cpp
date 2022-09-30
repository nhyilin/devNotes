//
// Created by 裴奕霖 on 2022/9/30.
//
namespace tree {
#define Elemtype int
#define MaxSize 10
namespace ordered_tree {

struct TreeNode {
    Elemtype data;
    bool isEmpty;

    /**
     * i 的左孩子一[2i]
     * i 的右孩子一[2i+1]
     * i 的父节点一[i/2]
     */

    /**
     * 若完全二叉树中共有 n 个结点，则
     * 判断 i 是否有左孩子？一[2i]≤n?
     * 判断 i 是否有右孩子？一[2i+1]≤n?
     * 判断i是否是叶子/分支结点？一i>[n/2]?
     */

    /**
     * 正因为有上述限制，一般不采取顺序结构的完全二叉树，因为必须每个节点放置在指定位序
     */
};

struct BiTree {
    Elemtype data;
    BiTree *lchild, *rchild;
    /**
     * n个节点有2n个指针域，除了根节点之外，每个节点脑袋上都有一根指针，即n-1个脑袋上指针
     * 所以一定有n+1个空链域，后面会用于构造线索二叉树，所以本构造方式也称二叉链表
     */

    /**
     * 该构造难找父节点，若常找父节点，最好再构造一个父节点指针，
     */
    BiTree *parent;  // 三叉链表，考试时一般不考这个
};
void testNode() {
    TreeNode t[MaxSize];  // 使用时，将第一个位置留出来，使得下标和编号相同
    for (auto &i : t)
        i.isEmpty = true;  // TODO 按道理这里从1开始，但是书上是0，保险起见从0吧
};
}  // namespace ordered_tree

}  // namespace tree