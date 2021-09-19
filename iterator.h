//iterator.h
//interface
template<class T>
struct iteratorBase {
    //迭代器应该重置前置和后置++
    virtual iteratorBase<T> operator++() = 0;
    virtual iteratorBase<T> operator++(int) = 0;
    virtual bool hasNext() = 0;
    virtual bool operator!=() = 0;
    //unsigned TTL = 0; 
protected:
    iteratorBase() {}
};