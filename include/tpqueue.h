// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct Item {
        T data;
        Item* next;
        Item* early;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);
 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};
struct SYM {
    char ch;
    int prior;
};
template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item*name = new Item;
    name->data = data;
    name->next = nullptr;
    name->early = nullptr;
    return name;
}

template <typename T>
void TPQueue<T>::push(const T& values) {
  if (head == nullptr) {
    head = create(values);
    tail = head;
  } else if (tail->data.prior >= values.prior) {
    if (tail->data.ch == values.ch) {
      tail->data = values;
    } else {
      tail->next = create(values);
      tail->next->early = tail;
      tail = tail->next;
    }
  } else if (head == tail) {
    tail->early = create(values);
    head = tail->early;
    head->next = tail;
  } else {
    Item* tm = tail;
    while (tm != head && tm->data.prior < values.prior) {
      tm = tm->early;
    }
    if (tm->data.prior > values.prior) {
      Item* el = new Item;
      el->next = tm->next;
      el->early = tm;
      el->data = values;
      tm->next->early = el;
      tm->next = el;
    }
    if (tm == head && tm->data.prior < values.prior) {
      head->early = create(values);
      head = head->early;
      tm = head->next;
    }
  }
}
template <typename T>
T TPQueue<T>::pop() {
  if (!head) {
    throw std::string("EMPTY!");
  } else {
    Item* temps = head->next;
    T data = head->data;
    delete head;
    head = temps;
    return data;
  }
}
template <typename T>
TPQueue<T>::~TPQueue() {
  while (head) {
    pop();
  }
}
template <typename T>
void TPQueue<T>::print() const {
  Item* temps1 = head;
  while (temps1) {
    std::cout << temps->data << " ";
    temps = temps1->next;
  }
  std::cout << std::endl;
}
#endif  // INCLUDE_TPQUEUE_H_
