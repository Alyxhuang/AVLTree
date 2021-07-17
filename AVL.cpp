// AVL.cpp
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
        a->left = T0; if(T0) T0->father = a;
        a->right = T1; if(T1) T1->father = a;
        c->left = T2; if(T2) T2->father = c;
        c->right = T3; if(T3) T3->father = c;
        b->left = a; a->father = b;
        b->right = c; c->father = b;
        //updateHeight a,b,c
        // updateHeightAbove(a);
        a->height = avlMax(getHeight(a->left), getHeight(a->right)) + 1;
        updateHeightAbove(c);
        return b;
    }
    NodePointer reBalance(NodePointer v) {
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
        std::cout << "dfs: " << std::endl;
        dfsHelper(getHead());
    }
    void dfsHelper(NodePointer x) {
        if(!x) return;
        std::cout << "current node:" << x->Key <<  "\t" << x->Value << std::endl;
        std::cout << "current height: " << (int)x->height << std::endl;
        std::cout << "left:";
        if(x->left) std::cout << x->left->Key;
        std::cout << "\tright:";
        if(x->right) std::cout << x->right->Key;
        std::cout << std::endl;
        dfsHelper(x->left);
        dfsHelper(x->right);
    }
    NodePointer insert(T key, U value) {
        NodePointer g = nullptr;
        NodePointer v = find(key, g);
        if(v != nullptr) {
            v->Value = value;
            return v;
        }
        pair<T, U> Ele(key, value);
        NodePointer insertionNode = new Node<pair<T, U>>(Ele);
        if(!head) {
            head = insertionNode;
            return head;
        } else { 
            if(g->Key > insertionNode->Key) {
                g->left = insertionNode;
                insertionNode->father = g;
            } else {
                g->right = insertionNode;
                insertionNode->father = g;
            }
        }
        updateHeightAbove(insertionNode);
        for(g = insertionNode->father; g; g = g->father) {
            if(!isBalanced(g)) {
                g = reBalance(tallerChild(tallerChild(g)));
            }
        } 
        return insertionNode;
    }
    bool remove(T key) {
        NodePointer g = nullptr;
        NodePointer v = find(key);
        std::cout << "remove:" << key << std::endl;
        if(v == nullptr) {
            return false;
        }
        removeNode(v, g);
        updateHeightAbove(g);
        for(; g; g = g->father) {
            if(!isBalanced(g)) {
                g = reBalance(tallerChild(tallerChild(g)));
            }
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
        if(x->left) {
            rhs = maxNode(x->left);
        } else if(x->right) {
            rhs = minNode(x->right);
        }
        if(rhs != x){
            avlSwap(x->Key, rhs->Key);
            avlSwap(x->Value, rhs->Value);
        }
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