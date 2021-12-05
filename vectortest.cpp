#include <iostream>
// using namespace std;
// #define NOT_PAIR_ALIAS
#include "vector.cpp"
#define DEBUG
#include "debug.h"

int main() {
  PRINT_DBG("hello")
  alyx::vector<int> dp;
  for (int i = 0; i < 100; ++i) {
    dp.push_back(i);
    std::cout << "push_back:" << i << std::endl;
    std::cout << "cap:" << dp.capacity() << std::endl;
    std::cout << "size:" << dp.size() << std::endl;
  }
  dp.for_each();
  printf("\n\n");

  // std::cout << std::endl;
  // for(int i = 0; i < 100; ++ i) {
  //     //dp.pop_back();
  //     std::cout << "pop_back:" << i << std::endl;
  //     std::cout << "cap:" << dp.capacity() << std::endl;
  //     std::cout << "size:" << dp.size() << std::endl;
  // }
  // dp.push_back(1);
  // dp.push_back(1);
  // dp.push_back(1);
  // fprintf(stdout, "dp[0]=%d\n", dp[0]);
  // dp.pop_back();
  // dp.pop_back();
  // dp.pop_back();
  int i = 0;
  for (auto iter = dp.begin(); i < 100 && iter != dp.end(); i++, ++iter) {
    std::cout << *iter << "\t";
  }
  printf("\n");
  {
    int i = 0;
    for (auto iter = dp.begin(); i < 100 && iter != dp.end(); i++, iter++) {
      std::cout << *iter << "\t";
    }
  }

  return 0;
}