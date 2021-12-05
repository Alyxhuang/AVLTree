// vector.cpp
#pragma once

#include <string.h>
#include <cstdint>
#include "error.h"
#define DEBUG
#include "debug.h"
#include "iterator.h"

namespace alyx {
template <class T>
class vectorIterator {
  T* pointer;
  bool in_asc;

 public:
  vectorIterator(T* p = nullptr, bool d = true) : pointer(p), in_asc(d) {}
  vectorIterator& operator++() {
    in_asc ? (pointer++) : (pointer--);
    return *this;
  }
  vectorIterator& operator++(int) {
    vectorIterator* it_helper = new vectorIterator(this->pointer, this->in_asc);
    in_asc ? (pointer++) : (pointer--);
    return *it_helper;
  }
  bool operator!=(const vectorIterator& rhs) { return this->pointer != rhs.pointer; }
  bool operator==(const vectorIterator& rhs) { return this->pointer != rhs.pointer; }
  T operator*() { return *pointer; }
};
template <class T>
class vector {
#define DEFAULT_CAPACITY 8
#define LOWER_BOUND 0.25
#define UPPER_BOUND 0.75
#define EXPAND_BASE 1.5
#define SHRINK_BASE 0.5
 private:
  T* _data;
  uint32_t _size;
  uint32_t _capacity;

 public:
  vector() : _size(0), _capacity(DEFAULT_CAPACITY) { _data = new T[DEFAULT_CAPACITY]; }
  ~vector() {}

 private:
  void copy(T* from, uint32_t fromSize, T* to) {
    for (int i = 0; i < fromSize; ++i) {
      to[i] = from[i];
    }
  }
  // 扩容
  uint32_t expand() {
    PRINT_DBG("_size:%d,cap:%d", _size, _capacity)
    if (_size <= UPPER_BOUND * _capacity) {
      return _capacity;
    }
    PRINT_DBG("limit is %f, going to expand...", UPPER_BOUND * _capacity)
    int newCapacity = _capacity * EXPAND_BASE;
    T* newData = new T[newCapacity];
    memset(newData, 0, sizeof(T) * newCapacity);
    copy(_data, _capacity, newData);
    delete[] _data;

    _capacity = newCapacity;
    _data = newData;
    return _capacity;
  }
  // 缩容
  uint32_t shrink() {
    PRINT_DBG("_size:%d,cap:%d", _size, _capacity)
    if (_capacity <= DEFAULT_CAPACITY || _size >= LOWER_BOUND * _capacity) {
      return _capacity;
    }
    PRINT_DBG("limit is %f, going to shrink...", LOWER_BOUND * _capacity)
    int newCapacity = _capacity * SHRINK_BASE;
    T* newData = new T[newCapacity];
    memset(newData, 0, sizeof(T) * newCapacity);
    copy(_data, _capacity, newData);
    delete[] _data;

    _capacity = newCapacity;
    _data = newData;
    return _capacity;
  }

 public:
  vectorIterator<T> begin() { return vectorIterator<T>(_data, true); }
  vectorIterator<T> end() { return vectorIterator<T>(_data + _size, true); }
  uint32_t size() { return _size; }
  uint32_t capacity() { return _capacity; }
  T* data() { return _data; }
  //下标访问
  T& operator[](uint32_t i) {
    if (i >= _size || i < 0) {
      ERROR("Out of the boundary")
      throw("Out of the boundary");
    }
    return _data[i];
  }
  //尾插入
  uint32_t push_back(T t) {
    expand();
    _data[_size] = t;
    return ++_size;
  }
  //尾删除
  T pop_back() {
    if (_size == 0) return T();
    T r = _data[_size - 1];
    _size--;
    shrink();
    return r;
  }

  //遍历打印
  void for_each_printf() {
    for (int i = 0; i < _size; ++i) {
      std::cout << _data[i] << "\t";
    }
  }
};

}  // namespace alyx
