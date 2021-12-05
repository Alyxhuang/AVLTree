// iterator.h
// interface
#pragma once
template <class T>
struct iteratorBase {
 public:
  //迭代器应该重置前置和后置++
  virtual iteratorBase& operator++() = 0;
  virtual const iteratorBase& operator++(int) = 0;
  virtual bool operator==(const iteratorBase& rhs) = 0;
  virtual bool operator!=(const iteratorBase& rhs) = 0;

 protected:
  iteratorBase() {}
};

class Base {
 public:
  // 应该实现前置和后置++
  virtual Base& operator++() = 0;
  virtual const Base& operator++(int) = 0;
  virtual bool operator==(const Base& rhs) = 0;
  virtual bool operator!=(const Base& rhs) = 0;

 protected:
  Base() {}
};
