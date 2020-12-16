#ifndef _COLLECTION_HPP_
#define _COLLECTION_HPP_

// Daniel Hinz
// Lab 3
// 9-14-2020

#include "list.hpp"
#include <iostream>

// class definition for Collection of nodes
template <typename T>
class Collection {
public:
  Collection () : top(nullptr) {}
  void add   (const T&);
  void remove(const T&);
  void print ();
  T    last  () { return top->getData(); }

  // general template to define friend to all classes
  template <typename U>
  friend bool equal(const Collection<U>&, const Collection<U>&);

private:
  node<T> *top;
};

// function to add node to list
template <typename T>
void Collection<T>::add(const T &item) {
  node<T> *n = new node<T>;
  n->setData(item);
  n->setNext(top);
  top = n;
}

// function to remove node from list
template <typename T>
void Collection<T>::remove(const T &item) {
  node<T> *prevPtr = nullptr, *currentPtr = top, *nextPtr = nullptr;

  // loop through collection
  while (currentPtr != nullptr) {
    nextPtr = currentPtr->getNext();
    // delete all instances of item from collection
    if (currentPtr->getData() == item) {
      if (prevPtr != nullptr)
	prevPtr->setNext(currentPtr->getNext());
      delete currentPtr;
    }
    if (currentPtr != nullptr)
      prevPtr = currentPtr;
    currentPtr = nextPtr;
  }
}

// outputs the collection
template <typename T>
void Collection<T>::print() {
  node<T> *currentPtr = top;

  std::cout << std::endl;
  while (currentPtr != nullptr) {
    std::cout << currentPtr->getData() << std::endl;
    currentPtr = currentPtr->getNext();
  }
  std::cout << std::endl;
}

// function to compare two collections, return true if they're the same
template <typename U>
bool equal(const Collection<U> &l, const Collection<U> &r) {
  node<U> *rhs = r.top, *lhs = l.top;

  // compares size of the collections, return false if theyre different
  if (rhs == nullptr && lhs == nullptr) return true;
  if (rhs != nullptr && lhs == nullptr) return false;
  if (rhs == nullptr && lhs != nullptr) return false;

  // loop through collection, if data in rhs != lhs, return false
  while (rhs != nullptr && lhs != nullptr) {
    if (rhs->getData() != lhs->getData())
      return false;
    rhs = rhs->getNext();
    lhs = lhs->getNext();
  }
  return true;  // else return true
}

#endif // _COLLECTION_HPP_

