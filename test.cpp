#include <iostream>
//using namespace std;
//#define NOT_PAIR_ALIAS
#include "AVL.cpp"
// #undef NOT_PAIR_ALIAS
// #define DEBUG

// #define PRINT_DBG(...) {fprintf(stderr, "%s %s [%d]:", __FILE__, __FUNCTION__, __LINE__);fprintf(stderr, __VA_ARGS__);fprintf(stderr, "\n");}
// #define PRINTF(s, ...) printf(s, ##__VA_ARGS__) 
// int main() 
// { 
// int i =100; 
// PRINT_DBG("hello")
// PRINT_DBG("world, %d\t,%s",i,"1w12w1"); 
// // MACRO("hello, world\n"); //这里没有可变参数， 所以要用##__VA_ARGS__ 
// // MACRO("hello, %s\n", "fanrey"); 
// return 0; 
// } 
int main() {
    // PRINT_DBG(1,"hello\n"); 
    //Node<int> a(10);
    //pair<int, double> b(10, 20);
    //string s;
    // DEBUG_LOG(123);

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
    // std::cout << "------------------" << std::endl;
    m.dfs();
    // std::cout << "------------------" << std::endl;
    m.remove(2);
    m.remove(5);
    m.remove(6);
    m.dfs();
}