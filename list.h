// list.cpp
#pragma once

#include <string.h>
#include "error.h"
#define DEBUG
#include "debug.h"

template <class T>
struct Node {
  Node* prev;
  Node* succ;
  T data;
  Node(T d, Node* p = nullptr, Node* s = nullptr) : data(d), prev(p), succ(s) {}
};

template <class T>
class list {
  typedef unsigned uint32;
  using listNodePointer = Node<T>*;

 private:
  //哨兵
  listNodePointer head;
  listNodePointer tail;
  uint32 listSize;

 private:
  void connectNode(listNodePointer before, listNodePointer after) {
    if (before) {
      before->succ = after;
    }
    if (after) {
      after->prev = before;
    }
  }
  void disConnectNode(listNodePointer before, listNodePointer after) {
    if (before) {
      before->succ = nullptr;
    }
    if (after) {
      after->prev = nullptr;
    }
  }
  void insertAsPrev(listNodePointer node, listNodePointer insertion) {
    listNodePointer before = node->prev;
    connectNode(before, insertion);
    connectNode(insertion, node);
  }
  void insertAsSucc(listNodePointer node, listNodePointer insertion) {
    listNodePointer after = node->succ;
    connectNode(node, insertion);
    connectNode(insertion, after);
  }
  listNodePointer remove(listNodePointer rm) {
    listNodePointer before = rm->prev;
    listNodePointer after = rm->succ;
    disConnectNode(before, rm);
    disConnectNode(rm, after);
    connectNode(before, after);
    return rm;
  }
  listNodePointer removePrev(listNodePointer node) {
    listNodePointer rm = node->prev;
    if (rm == head) {
      return nullptr;
    }
    return remove(rm);
  }
  listNodePointer removeSucc(listNodePointer node) {
    listNodePointer rm = node->succ;
    if (rm == tail) {
      return nullptr;
    }
    return remove(rm);
  }

 public:
  Node() : head(nullptr), tail(nullptr), listSize(0) { connectNode(head, succ); }
  uint32 size() { return listSize; }

  void insert(listNodePointer node, T value) {
    listNodePointer insertion = new listNodePointer(value);
    insertAsSucc(node, insertion);
  }
  void push_back() {}

  void pop_back() {}

  void push_front() {}

  void pop_front() {}
};
