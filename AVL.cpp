// AVL.cpp
#define mmmDEBUG
#ifdef mmmDEBUG
#include<stdio.h> 
#define PRINT_DBG(...) {fprintf(stderr, "%s %s [%d]:", __FILE__, __FUNCTION__, __LINE__);fprintf(stderr, __VA_ARGS__);fprintf(stderr, "\n");} 
#else
#define DEBUG_LOG(module) do{}while(0);
#endif

template<class T>
struct Node {
    Node(T d, Node<T>* f = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, unsigned char h = 1):
        data(d), father(f), left(l), right(r), height(h) {    }
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
private:
    NodePointer head;
private:
    NodePointer rebuild34(NodePointer a, NodePointer b, NodePointer c,
        NodePointer T0, NodePointer T1, NodePointer T2, NodePointer T3) {
        // 3 + 4 重构 
        PRINT_DBG("----3 + 4 rebuild:")
        PRINT_DBG("a=%d, b=%d, c=%d", a->Key, b->Key, c->Key)
        // #ifndef BDEBUG
        // #else
        // std::cout << "----3 + 4 rebuild:" << std::endl;
        // std::cout << "a=" << a->Key << ",b=" << b->Key << ",c=" << c->Key << std::endl;
        // // std::cout << "T0=" << a->Key << ",b=" << b->Key << ",c=" << c->Key << std:endl;
        // #endif
        a->left = T0; if(T0) T0->father = a;
        a->right = T1; if(T1) T1->father = a;
        c->left = T2; if(T2) T2->father = c;
        c->right = T3; if(T3) T3->father = c;
        b->left = a; a->father = b;
        b->right = c; c->father = b;
        //updateHeight a,b,c
        updateHeightAbove(a);
        // a->height = avlMax(getHeight(a->left), getHeight(a->right)) + 1;
        updateHeightAbove(c);
        PRINT_DBG("travel mid point:")
        // #ifndef BDEBUG
        // #else
        // std::cout << "--------travel mid point:" << std::endl;
        // #endif
        dfsHelper(b);
        return b;
    }
    NodePointer reBalance(NodePointer v) {
        PRINT_DBG("reBalance")
        // #ifndef BDEBUG
        // #else
        // std::cout << "----reBalance" << std::endl;
        // #endif
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
    
public:
    void dfs() {
        PRINT_DBG("dfs()")
        // #ifndef BDEBUG
        // #else
        // std::cout << "----dfs() " << std::endl;
        // #endif
        dfsHelper(getHead());
    }
    void dfsHelper(NodePointer x) {
        
        // #ifndef BDEBUG
        // #else
        // std::cout << "----dfsHelper()" << std::endl;
        // #endif
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
    NodePointer insert(T key, U value) {
        // DEBUG_LOG("insert key:%d")
        PRINT_DBG("insert()...")
        PRINT_DBG("key:%d, value:%d", key, value)
        // #ifndef BDEBUG
        // #else
        // std::cout << "----insert()..." << std::endl;
        // std::cout << key << ":" << value << std::endl;
        // #endif
        NodePointer g = nullptr;
        NodePointer v = find(key, g);
        if(v != nullptr) {
            PRINT_DBG("point is existed! Updating ...")
            // #ifndef BDEBUG
            // #else
            // std::cout << "--------point is existed! Updating ..." << std::endl;
            // #endif
            v->Value = value;
            return v;
        }
        pair<T, U> Ele(key, value);
        NodePointer insertionNode = new Node<pair<T, U>>(Ele);
        if(!head) {
            PRINT_DBG("head is null")
            // #ifndef BDEBUG
            // #else
            // std::cout << "--------head is null" << std::endl;
            // #endif
            head = insertionNode;
            return head;
        } else { 
            PRINT_DBG("head is exist")
            // #ifndef BDEBUG
            // #else
            // std::cout << "--------head is exist" << std::endl;
            // #endif
            if(g->Key > insertionNode->Key) {
                PRINT_DBG("insert to left:%d", g->Key)
                // #ifndef BDEBUG
                // #else
                // std::cout << "------------insert to left:" << g->Key << std::endl;
                // #endif
                g->left = insertionNode;
                insertionNode->father = g;
            } else {
                PRINT_DBG("insert to right:%d", g->Key)
                // #ifndef BDEBUG
                // #else
                // std::cout << "------------insert to right:" << g->Key << std::endl;
                // #endif
                g->right = insertionNode;
                insertionNode->father = g;
            }
        }
        PRINT_DBG("updateHeightAbove")
        // #ifndef BDEBUG
        // #else
        // std::cout << "--------updateHeightAbove" << std::endl;
        // #endif
        updateHeightAbove(insertionNode);
        dfs();
        // for(g = insertionNode->father; g; g = g->father) {
        //     if(!isBalanced(g)) {
        //         g = reBalance(tallerChild(tallerChild(g)));
        //     }
        //     updateHeightAbove(g);
        // } 
        int t = 0;
        for(g = insertionNode->father; g; g = g->father) {
            ++t;
            if(!isBalanced(g)) {
                g = reBalance(tallerChild(tallerChild(g)));
            } else if(t > 2) {
                updateHeightAbove(g);
                break;
            }
            updateHeightAbove(g);
        }   
        return insertionNode;
    }
    bool remove(T key) {
        NodePointer g = nullptr;
        NodePointer v = find(key);
        PRINT_DBG("remove:%d", key)
        // #ifndef BDEBUG
        // #else
        // std::cout << "remove:" << key << std::endl;
        // #endif
        if(v == nullptr) {
            return false;
        }
        //前面find已经更新过head
        if(!head->left && !head->right) {
            head = nullptr;
            return true;
        }
        removeNode(v, g);
        updateHeightAbove(g);
        int t = 0;
        for(; g; g = g->father) {
            ++t;
            if(!isBalanced(g)) {
                g = reBalance(tallerChild(tallerChild(g)));
            } else if(t > 2) {
                updateHeightAbove(g);
                break;
            }
            updateHeightAbove(g);
        }   
        return true;
    }
    //需要重载小于号<
    NodePointer find(T key, NodePointer& hot) {
        NodePointer cur = getHead();
        while(cur && cur->Key != key) {
            if(cur->Key > key) {
                hot = cur;
                cur = cur->left;
            } else {
                hot = cur;
                cur = cur->right;
            }
        }
        return cur;
    }
    //需要重载小于号<
    NodePointer find(T key) {
        NodePointer cur = getHead();
        while(cur && cur->Key != key) {
            if(cur->Key > key) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return cur;
    }
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
        //在另外一侧，至多有一个节点，交换位置
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