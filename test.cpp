#include <iostream>
//using namespace std;
//#define NOT_PAIR_ALIAS
#include "AVL.cpp"
// #undef NOT_PAIR_ALIAS
int main() {
    
    Node<int> a(10);
    pair<int, double> b(10, 20);
    
    std:: cout << b.fir;

    map<int, int> m;
    m.insert(1, 1);
    m.insert(2, 2);
    m.insert(3, 3);
    m.insert(4, 4);
    m.insert(5, 5);
    m.insert(6, 6);
    //m.insert(1, -1);
    //m.remove(3);
    m.dfs();
}