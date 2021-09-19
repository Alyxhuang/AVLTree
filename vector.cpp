//vector.cpp
#pragma once

#include <string.h>
#include "error.h"
#define DEBUG
#include "debug.h"
#include "iterator.h"

template<class T>
class vectorIterator: public iteratorBase<T> {
    T* pointer;
public:
    vectorIterator(T* p = nullptr): pointer(p){}
    iteratorBase<T>& operator++(){
        p++;
        return this;
    }
    iteratorBase<T>& operator++(int) {
        iteratorBase<T>* ret = new(this);
        return this;
    }
    bool hasNext() = 0;
    bool operator!=() = 0;
};
template<class T>
class vector {
    typedef unsigned uint32;
    #define DEFAULT_CAPACITY 8
    #define LOWER_BOUND 0.25
    #define UPPER_BOUND 0.75
    #define EXPAND_BASE 1.5
    #define SHRINK_BASE 0.5
private:
    T* data;
    uint32 size;
    uint32 capacity;
public:
    vector():size(0), capacity(DEFAULT_CAPACITY) {data = new T[DEFAULT_CAPACITY];}
    ~vector() { }
private:
    void copy(T *from, uint32 fromSize, T *to) {
        for(int i = 0; i < fromSize; ++ i) {
            to[i] = from[i];
        }
    }
    //扩容
    uint32 expand() {
        PRINT_DBG("size:%d,cap:%d", size, capacity)
        if(size <= UPPER_BOUND * capacity) {
            return capacity;
        }
        PRINT_DBG("limit is %f, going to expand...", UPPER_BOUND * capacity)
        int newCapacity = capacity * EXPAND_BASE;
        T* newData = new T[newCapacity];
        memset(newData, 0, sizeof(T) * newCapacity);
        copy(data, capacity, newData);
        delete [] data;

        capacity = newCapacity;
        data = newData;
        return capacity;
    }
    //缩容
    uint32 shrink() {
        PRINT_DBG("size:%d,cap:%d", size, capacity)
        if(capacity <= DEFAULT_CAPACITY || size >= LOWER_BOUND * capacity) {
            return capacity;
        }
        PRINT_DBG("limit is %f, going to shrink...", LOWER_BOUND * capacity)
        int newCapacity = capacity * SHRINK_BASE;
        T* newData = new T[newCapacity];
        memset(newData, 0, sizeof(T) * newCapacity);
        copy(data, capacity, newData);
        delete [] data;

        capacity = newCapacity;
        data = newData;
        return capacity;
    }
public:
    begin() {

    }
    uint32 getSize() {
        return size;
    }
    uint32 getCapacity() {
        return capacity;
    }
    T* getData() {
        return data;
    }
    //下标访问
    T& operator[](uint32 i) {
        if(i >= size || i < 0) {
            ERROR("Out of the boundary")
            throw("Out of the boundary");
        }
        return data[i];
    }
    //尾插入
    uint32 push_back(T t) {
        expand();
        data[size] = t;
        ++size;
    }
    //尾删除
    T pop_back() {
        if(size == 0) return T();
        T r = data[size - 1];
        size -= 1;
        shrink();
        return r;
    }

    //遍历打印
    void for_each() {
        for(int i = 0; i < size; ++ i) {
            std::cout << data[i] << "\t";
        }
    }
};

