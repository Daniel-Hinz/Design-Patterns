#ifndef _LIST_HPP_
#define _LIST_HPP_

// Daniel Hinz
// Lab 3
// 9-14-2020

template <typename T>
class node {
public:
  node() : next_(nullptr) {}

  T getData()const { return data_; }
  void setData(const T& data) { data_ = data; }

  node<T>* getNext() const { return next_; }
  void setNext(node<T> *const next) { next_ = next; }

private:
  T data_;
  node<T> *next_;
};

#endif // LIST_HPP_
