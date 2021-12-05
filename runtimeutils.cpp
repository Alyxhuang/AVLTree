/*
 * @Author: alyxhuang
 * @Date: 2021-12-03 16:25:06
 */

#ifndef TEST_RUN_TIME
#define TEST_RUN_TIME
#include <stdio.h>
#include <time.h>
#include <cstdint>

template <class FunctionType>
class TestRunTime {
  FunctionType* _func;
  int _loop_times;
  double _run_stat_time_secs;
  uint64_t _run_stat_time_mius;

 public:
  TestRunTime(FunctionType& func, int loop_times = 10)
      : _func(&func), _loop_times(loop_times), _run_stat_time_secs(0), _run_stat_time_mius(0) {
    Test();
  }
  void Test() {
    clock_t start, end;
    start = clock();
    for (int i = 0; i < _loop_times; ++i) {
      (*_func)();
    }
    end = clock();
    _run_stat_time_mius = end - start;
    _run_stat_time_secs = (double)_run_stat_time_mius / 1.0e9;
    printf("Use time is: %lu\n", _run_stat_time_mius);
  }
};
#endif  // TEST_RUN_TIME

#ifndef __MAIN__
#define __MAIN__

#include <assert.h>
#include <vector>

int main() {
  {
    auto testFunc = []() {
      std::vector<int> vec(10000000, 0);
      for (auto it = vec.begin(); it != vec.end(); it++) {
        *it = 200;
      }
    };
    TestRunTime<decltype(testFunc)> testRunTime(testFunc);
    // testRunTime.Test();
  }
  {
    auto testFunc = []() {
      std::vector<int> vec(10000000, 0);
      auto end = vec.end();
      for (auto it = vec.begin(); it != end; it++) {
        *it = 200;
      }
    };
    TestRunTime<decltype(testFunc)> testRunTime(testFunc);
    // testRunTime.Test();
  }
}
#endif  // __MAIN__