//
// Created by 裴奕霖 on 2023/4/23.
//

#include "Chapter2_Linear_List.h"

namespace LinearList {
void INSERTLIST(ELEMENT_TYPE *list, const ELEMENT_TYPE item, const int &position, int &length) {
  //在长度为length的表中的position位置插入元素item
  int j;
  if (length == MAX_SIZE || position > length + 1 || position < 1)std::cerr << "插入失败\n";
  for (int i = length; i > position - 2; --i)
    list[i + 1] = list[i];

  list[position - 1] = item;

  length += 1;
}

void DELETELIST(ELEMENT_TYPE *list, int &length, const int &position) {
  //删除长度为length的线性表中position位置元素
  if (length < 1 || position > MAX_SIZE)std::cerr << "failed to delete\n";
  for (int i = position; i < length; ++i) {
    list[i - 1] = list[i];
  }
  list[length - 1] = 0;
  length--;
}

int LOCATE(ELEMENT_TYPE *list, const int &length, const int &item) {
  //确定元素item在长度为length的表中的位置
  for (int i = 0; i < length + 1; ++i) {
    if (list[i] == item)
      return (i + 1);
  }
  return -1;
}

void PURGE(ELEMENT_TYPE *list, int &length) {
  //删除重复元素
  for (int i = 0; i < length - 1; ++i) {
    ELEMENT_TYPE _temp = list[i];
    for (int j = i + 1; j < length; ++j) {
      if (list[j] == _temp)DELETELIST(list, length, j);
    }
  }
}

void SELECTSORT(ELEMENT_TYPE *list, const int &length) {
  //对线性表中元素进行排序复杂度为O(n2)
  for (int i = 0; i < length - 1; ++i) {
    int _min_position = i;

    for (int j = i + 1; j < length; ++j) {
      if (list[j] < list[_min_position])
        _min_position = j;
    }
    if (_min_position != i) {
      ELEMENT_TYPE _temp = list[i];
      list[i] = list[_min_position];
      list[_min_position] = _temp;
    }
  }
}
void DELETEITEM1(ELEMENT_TYPE *list, int &length, const int &item) {
// 已知表长为length，删除表中数据为item的元素，复杂度为O(n)
  for (int i = 0; i < length; ++i) {
    if (item == list[i])
      DELETELIST(list, length, i);
  }
}
void DELETEITEM2(ELEMENT_TYPE *list, int &length, const int &item) {
// 已知表长为length，删除表中数据为item的元素

  int delta = 0;
  for (int i = 0; i < length; ++i) {
    if (item == list[i])
      delta++;
    else
      list[i - delta] = list[i];
  }
  length++;
//TODO 书上此处有问题：
/*test case：
  ELEMENT_TYPE testlist[] = {1, 1, 2, 3, 4};
  DELETEITEM2(testlist, length, 1);
  for (auto iter : testlist)std::cout << iter << std::endl;
  输出结果：2, 3, 4，3， 4。显然后两位需要删除
*/
}
};//namespace LinearList

namespace LinkedList {

int LENGTH(const LinkedList::LinkList &list) {
  //链表长度（带头节点）
  if (list == nullptr)
    return -1;
  int length{0};
  for (auto _p = list; _p != nullptr; _p = _p->link) {
    length++;
  }
  return length;
}

LinkedList::LinkList FIND(const LinkedList::LinkList &list, const ELEMENT_TYPE &item) {
//  元素item在链表中的位置
  if (list == nullptr)
    return list;
  for (LinkedList::LinkList _p = list; _p != nullptr; _p = _p->link) {
    if (_p->data == item)
      return _p;
  }
  return nullptr;
}

void INSERTLINK3(LinkedList::LinkList &list, LinkedList::LinkList q, const ELEMENT_TYPE &item) {
  // 在线性链表中由指针q 指出的链结点后面插入一个数据信息为item的链结点
  if (list == nullptr) {
    list->data = item;
    q = list;
  } else {
    for (auto _p = list; _p == q; _p = _p->link) {
      LinkedList::LinkList _temp = new LinkedList::LNode;
      _temp->link = _p->link;
      _temp->data = item;
      _p->link = _temp;
    }//TODO 书上这里没有遍历，直接从q入手，我觉得没毛病
  }

}
void INSERTLINK5(LinkedList::LinkList &list, ELEMENT_TYPE item) {
// 在按值有序链接的线性链表中插入一个数据信息为item的链结点
// 假设有序链表为其链结点是按照数据域值的大小从小到大非递减链接的一个链表
  if (list == nullptr || item < list->data) {
    LinkedList::LinkList _temp = new LinkedList::LNode;
    _temp->data = item;
    _temp->link = list;//TODO 这里写的很好
  } else {
    LinkedList::LinkList _p = list;
    while (_p->data < item) {
      _p = _p->link;
    }
    LinkedList::LinkList _new = new LinkedList::LNode;
    _new->link = _p->link;
    _new->data = item;
    _p->link = _new;

  }
}

//TODO 算法13

void REVERSE(LinkList &list) {
  LinkList after, now, before;
  after = list;
  now = NULL;
  while (after != NULL) {
    before = now;
    now = after;
    after = after->link;
    now->link = before;
  }
  list = now;
}

LinkedList::LinkList MERGELIST(const LinkedList::LinkList &lista, const LinkedList::LinkList &listb) {
  LinkedList::LinkList listc, a = lista, b = listb, r;
  if (lista->data <= listb->data) {
    listc = lista;
    r = lista;
    a = lista->link;
  } else {
    listc = listb;
    r = listb;
    b = listb->link;
  }
  while (a != nullptr && b != nullptr) {
    if (a->data <= b->data) {
      r->link = a;
      r = a;
      a = a->link;
    } else {
      r->link = b;
      r = b;
      b = b->link;
    }
  }
}

LinkedList::LinkList MERGELIST2(const LinkedList::LinkList &lista, const LinkedList::LinkList &listb) {
  LinkedList::LinkList p_listc, p_lista = lista, p_listb = listb, _p;
  if (lista->data <= listb->data) {
    p_listc = lista;
    _p = p_lista;
    p_lista = p_lista->link;
  } else {
    p_listc = p_listb;
    _p = p_listb;
    p_listb = p_listb->link;
  }
  while (p_lista != nullptr && p_listb != nullptr) {

  }

}
};//namespace LinkedList



int main() {
#ifdef LinearList
  ELEMENT_TYPE _list[MAX_SIZE] = {1, 5, 6, 9, 10};
  int lenth = 5;
  INSERTLIST(_list, 99, 2, lenth);
  for (auto iter : _list) { if (iter != 0) std::cout << iter << std::endl; }
  std::cout << std::endl;

  DELETELIST(_list, lenth, 2);

  for (auto iter : _list) { if (iter != 0) std::cout << iter << std::endl; }

  ELEMENT_TYPE _list2[MAX_SIZE] = {1, 1, 6, 9, 10};
  int length2 = 5;
  PURGE(_list2, length2);
  for (auto iter : _list2) { if (iter != 0) std::cout << iter << std::endl; }


  ELEMENT_TYPE _list3[MAX_SIZE] = {1, 1, 6, 9, 10};
  int length3 = 5;
  LinearList::DELETEITEM2(_list3, length3, 1);
  for (auto iter : _list3) { if (iter != 0) std::cout << iter << std::endl; }
#endif

}