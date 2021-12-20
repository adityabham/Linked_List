#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

class out_of_bounds : public std::exception {
 public:
  const char * what() const throw() { return "Index"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(T d) : data(d), next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);
      std::swap(temp.head, head);
      std::swap(temp.tail, tail);
      std::swap(temp.size, size);
    }
    return *this;
  }

  ~LinkedList() {
    Node * temp = head;
    Node * next_temp = NULL;
    while (temp != NULL) {
      next_temp = temp->next;
      delete temp;
      temp = next_temp;
    }
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    Node * traverse = head;
    while (traverse != NULL && traverse->data != item) {
      traverse = traverse->next;
    }
    if (traverse == NULL) {
      return false;
    }
    Node * nextN = traverse->next;
    Node * prevN = traverse->prev;
    if (nextN != NULL) {
      nextN->prev = prevN;
    }
    else {
      tail = prevN;
    }
    if (prevN != NULL) {
      prevN->next = nextN;
    }
    else {
      head = nextN;
    }
    size--;
    delete traverse;
    return true;
  }

  T & operator[](int index) {
    try {
      if (index < 0 || index > size - 1) {
        throw out_of_bounds();
      }
    }
    catch (std::exception & e) {
      std::cerr << e.what() << std::endl;
    }

    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  const T & operator[](int index) const {
    try {
      if (index < 0 || index > size - 1) {
        throw out_of_bounds();
      }
    }
    catch (std::exception & e) {
      std::cerr << e.what() << std::endl;
    }

    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }

  int getSize() const { return size; }
};

#endif
