#include <iostream>
//using namespace std;
//#define NOT_PAIR_ALIAS
#include "vector.cpp"

int main() {
    vector<int> dp;
    // for(int i = 0; i < 100; ++ i) {
    //     dp.push_back(i);
    //     std::cout << "push_back:" << i << std:: endl;
    //     std::cout << "cap:" << dp.getCapacity() << std::endl;
    //     std::cout << "size:" << dp.getSize() << std::endl;
    // }
    // dp.for_each();
    
    // std::cout << std::endl;
    // for(int i = 0; i < 100; ++ i) {
    //     //dp.pop_back();
    //     std::cout << "pop_back:" << i << std::endl;
    //     std::cout << "cap:" << dp.getCapacity() << std::endl;
    //     std::cout << "size:" << dp.getSize() << std::endl;
    // }
    dp.push_back(1);
    dp.push_back(1);
    dp.push_back(1);
    dp.pop_back();
    dp.pop_back();
    dp.pop_back();
    dp[0];
    return 0;
}