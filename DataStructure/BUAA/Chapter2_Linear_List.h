//
// Created by 裴奕霖 on 2023/4/23.
//

#ifndef DATASTRUCTURE_BUAA_CHAPTER2_LINEAR_LIST_H_
#define DATASTRUCTURE_BUAA_CHAPTER2_LINEAR_LIST_H_

#define ELEMENT_TYPE int
#define MAX_SIZE 100

namespace LinkedList {
struct Node {
  ELEMENT_TYPE data;
  Node *link;
};

using LNode = Node;
using LinkList = Node *;
};//namespace LinkedList



typedef struct node {
  ELEMENT_TYPE data;
  struct node *link;
}LNode, *LinkList;

#endif //DATASTRUCTURE_BUAA_CHAPTER2_LINEAR_LIST_H_
