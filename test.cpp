#include <iostream>
//using namespace std;
//#define NOT_PAIR_ALIAS
#include "AVL.cpp"
int main() {
    map<int, int> m;
    m.insert(1, 1);
    m.insert(2, 2);
    m.insert(3, 3);
    m.insert(4, 4);
    m.insert(5, 5);
    m.insert(6, 6);
    m.insert(1, -1);
    m.remove(3);
    m.dfs();
    m.remove(4);
    m.remove(1);
    std::cout << "------------------" << std::endl;
    m.dfs();
    std::cout << "------------------" << std::endl;
    m.remove(2);
    m.remove(5);
    m.remove(6);
    m.dfs();
}