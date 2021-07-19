// AVL.cpp
#pragma once

#include<iostream>
#include <string.h>
#include "error.h"
#define DEBUG
#include "log.h"


template<class T>
struct Node {
    Node(T d, Node<T>* f = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, unsigned char h = 1):
        data(d), father(f), left(l), right(r), height(h) {}
    T data;
    Node<T>* father;
    Node<T>* left;
    Node<T>* right;
    unsigned char height;
};

template<class T, class U>
struct pair {
#ifndef NOT_PAIR_ALIAS
#define NOT_PAIR_ALIAS
    #define fir first
    #define sec second
    #define key first
    #define value second
#endif
    T first;
    U second;
    pair(T t = nullptr, U u = nullptr): first(t), second(u) {}
};

template<class T, class U>
class map {
    //无重复元素的map
    using NodePointer = Node<pair<T, U>>*;
    #define Key data.first
    #define Value data.second
public:
    map(): head(nullptr){}
private:
    NodePointer head;
private:
    NodePointer rebuild34(NodePointer a, NodePointer b, NodePointer c,
        NodePointer T0, NodePointer T1, NodePointer T2, NodePointer T3) {
        // 3 + 4 重构 
        PRINT_DBG("----3 + 4 rebuild:")
        PRINT_DBG("a=%d, b=%d, c=%d", a->Key, b->Key, c->Key)

        a->left = T0; if(T0) T0->father = a;
        a->right = T1; if(T1) T1->father = a;
        c->left = T2; if(T2) T2->father = c;
        c->right = T3; if(T3) T3->father = c;
        b->left = a; a->father = b;
        b->right = c; c->father = b;
        //updateHeight a,b,c
        //updateHeightAbove(a);
        a->height = avlMax(getHeight(a->left), getHeight(a->right)) + 1;
        updateHeightAbove(c);
        return b;
    }
    NodePointer reBalance(NodePointer v) {
        PRINT_DBG("reBalance")
        NodePointer p = v->father;
        NodePointer g = p->father;
        if(isLeftChild(p)) {
            if(isLeftChild(v)) {
                //      g
                //     / \
                //    p   T3
                //   / \
                //  v   T2
                // / \
                //T0 T1
                p->father = g->father;
                if(g->father) isLeftChild(g) ? (g->father->left = p) : (g->father->right = p);
                return rebuild34(v, p, g, v->left, v->right, p->right, g->right);
            } else {
                //      g
                //     / \
                //    p   T3
                //   / \
                //  T0  v
                //     / \
                //    T1 T2
                v->father = g->father;
                if(g->father) isLeftChild(g) ? (g->father->left = v) : (g->father->right = v);
                return rebuild34(p, v, g, p->left, v->left, v->right, g->right);
            }
        } else {
            if(isRightChild(v)) {
                //      g
                //     / \
                //    T0  p
                //       / \
                //      T1  v
                //         / \
                //        T2 T3
                p->father = g->father;
                if(g->father) isLeftChild(g) ? (g->father->left = p) : (g->father->right = p);
                return rebuild34(g, p, v, g->left, p->left, v->left, v->right);
            } else {
                //      g
                //     / \
                //    T0  p
                //       / \
                //      v   T3
                //     / \
                //    T1 T2
                v->father = g->father;
                if(g->father) isLeftChild(g) ? (g->father->left = v) : (g->father->right = v);
                return rebuild34(p, v, g, g->left, v->left, v->right, p->right);
            }
        }
    }
    bool isLeftChild(NodePointer cur) {
        if(cur == nullptr || cur->father == nullptr) return false;
        return cur->father->left == cur;
    }
    bool isRightChild(NodePointer cur) {
        if(cur == nullptr || cur->father == nullptr) return false;
        return cur->father->right == cur;
    }
    bool isLeaf(NodePointer cur) { 
        return cur && (cur->left == nullptr) && (cur->right == nullptr);
    }
    NodePointer tallerChild(NodePointer v) {
        if(!v) return v;
        int ha = getHeight(v->left), hb = getHeight(v->right);
        if(ha > hb) {
            return v->left;
        } else if(ha < hb) {
            return v->right;
        }
        return nullptr;
    }
    bool isBalanced(NodePointer v) {
        return (v == nullptr) || ( avlAbs(getHeight(v->left) - getHeight(v->right)) < 2 );
    }
    NodePointer getHead() {
        while(head && head->father) {
            head = head->father;
        }
        return head;
    }
    int getHeight(NodePointer v) {
        return v == nullptr ? 0 : v->height;
    }
    int avlAbs(int a) {
        return a > 0 ? a : -a;
    }
    int avlMax(int a, int b) {
        return a > b ? a : b;
    }
    template<class T1>
    void avlSwap(T1& a, T1& b) {
        T1 t = a;
        a = b;
        b = t;
    }
    NodePointer minNode(NodePointer v) {
        if(!v) return v;
        while(v->left) {
            v = v->left;
        }
        return v;
    }
    NodePointer maxNode(NodePointer v) {
        if(!v) return v;
        while(v->right) {
            v = v->right;
        }
        return v;
    }
    void updateHeightAbove(NodePointer g) {
        for(; g; g = g->father) {
            int newH = avlMax(getHeight(g->left), getHeight(g->right)) + 1;
            if(newH == g->height) break;
            g->height = newH;
        }
    }
    void dfsHelper(NodePointer x) {
        if(!x) return;
        PRINT_DBG("dfsHelper()")

        std::cout << "current node:" << x->Key <<  "\t" << x->Value << std::endl;
        std::cout << "current height: " << (int)x->height << std::endl;
        std::cout << "left:";
        if(x->left) std::cout << x->left->Key;
        else std::cout << "null";
        std::cout << "\tright:";
        if(x->right) std::cout << x->right->Key;
        else std::cout << "null";
        std::cout << std::endl;

        dfsHelper(x->left);
        dfsHelper(x->right);
    }
public:
    //递归dfs遍历打印AVL树
    void dfs() {
        PRINT_DBG("dfs()")
        dfsHelper(getHead());
    }

    //插入节点，并将其位置返回
    NodePointer insert(T key, U value) {
        PRINT_DBG("insert()...")
        PRINT_DBG("key:%d, value:%d", key, value)

        NodePointer g = nullptr;
        NodePointer v = find(key, g);
        //找到了该节点，直接修改值并返回即可
        if(v != nullptr) {
            PRINT_DBG("point is existed! Updating ...")

            v->Value = value;
            return v;
        }
        //创建新的节点
        pair<T, U> Ele(key, value);
        NodePointer insertionNode = new Node<pair<T, U>>(Ele);
        //原本AVL树为空
        if(!head) {
            PRINT_DBG("head is null")
            head = insertionNode;
            return head;
        } else { 
            //原本AVL树不空，则根据大小选择插入位置（左or右）
            PRINT_DBG("head is exist")
            if(g->Key > insertionNode->Key) {
                PRINT_DBG("insert to left:%d", g->Key)

                g->left = insertionNode;
                insertionNode->father = g;
            } else {
                PRINT_DBG("insert to right:%d", g->Key)

                g->right = insertionNode;
                insertionNode->father = g;
            }
        }
        //更新高度
        PRINT_DBG("updateHeightAbove")
        updateHeightAbove(insertionNode);
        //重平衡
        int t = 0;
        for(g = insertionNode->father; g; g = g->father) {
            ++t;
            if(!isBalanced(g)) {
                g = reBalance(tallerChild(tallerChild(g)));
            } else if(t > 2) {
                //超过三代都不发生高度改变，说明无需再向上迭代
                updateHeightAbove(g);
                break;
            }
            updateHeightAbove(g);
        }   
        return insertionNode;
    }

    //删除键为key的节点，返回是否删除成功
    bool remove(T key) {
        NodePointer g = nullptr;
        NodePointer v = find(key);
        PRINT_DBG("remove:%d", key)
        //未找到，直接返回false
        if(v == nullptr) {
            return false;
        }
        //前面find已经更新过head，直接检查是否只有head一个节点（即删除head）
        if(!head->left && !head->right) {
            head = nullptr;
            return true;
        }
        //删除节点，更新高度
        removeNode(v, g);
        updateHeightAbove(g);
        //重平衡
        int t = 0;
        for(; g; g = g->father) {
            ++t;
            if(!isBalanced(g)) {
                g = reBalance(tallerChild(tallerChild(g)));
            } else if(t > 2) {
                //超过三代都不发生高度改变，说明无需再向上迭代
                updateHeightAbove(g);
                break;
            }
            updateHeightAbove(g);
        }   
        return true;
    }

    //寻找键为key的节点，并将hot设置为最后找到位置的父亲或者跟丢的位置
    //需要重载小于号<
    NodePointer find(T key, NodePointer& hot) {
        NodePointer cur = getHead();
        while(cur) {
            if(cur->Key > key) {
                hot = cur;
                cur = cur->left;
            } else if(cur->Key < key) {
                hot = cur;
                cur = cur->right;
            } else {
                break;
            }
        }
        return cur;
    }

    //寻找键为key的节点
    //需要重载小于号<
    NodePointer find(T key) {
        NodePointer cur = getHead();
        while(cur) {
            if(key < cur->Key) {
                cur = cur->left;
            } else if(cur->Key < key) {
                cur = cur->right;
            } else {
                break;
            }
        }
        return cur;
    }

    //删除节点x，并将hot节点置为最后删除位置的父亲
    NodePointer removeNode(NodePointer x, NodePointer& hot) {
        NodePointer rhs = x;
        //寻找可交换的边缘节点
        if(x->left) {
            rhs = maxNode(x->left);
        } else if(x->right) {
            rhs = minNode(x->right);
        }
        //交换字段-->交换位置
        if(rhs != x){
            avlSwap(x->Key, rhs->Key);
            avlSwap(x->Value, rhs->Value);
        }
        //在另外一侧，至多有一个节点，若该节点存在，交换位置
        if(rhs->left) {
            avlSwap(rhs->left->Key, rhs->Key);
            avlSwap(rhs->left->Value, rhs->Value);
            rhs = rhs->left;
        } else if (rhs->right) {
            avlSwap(rhs->right->Key, rhs->Key);
            avlSwap(rhs->right->Value, rhs->Value);
            rhs = rhs->right;
        }
        //现在，rhs已经没有后代节点了
        //将hot节点置为最后删除位置的父亲然后将其删除并返回
        hot = rhs->father;
        if(isLeftChild(rhs)) {
            hot->left = nullptr;
        } else if(isRightChild(rhs)){
            hot->right = nullptr;
        } else {
            getHead();
            head = nullptr;
        }
        return rhs;
    }
};