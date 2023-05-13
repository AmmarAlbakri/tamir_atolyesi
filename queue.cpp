#include <iostream>

template <typename T>
class Queue {
 private:
  struct Node {
    T data;
    Node* next;
  };

  Node* front_;
  Node* back_;

 public:
  Queue() : front_(nullptr), back_(nullptr) {}

  ~Queue() {
    while (!empty()) {
      pop();
    }
  }

  void push(T val) {
    Node* node = new Node{val, nullptr};
    if (empty()) {
      front_ = node;
    } else {
      back_->next = node;
    }
    back_ = node;
  }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }

    Node* old_front = front_;
    front_ = front_->next;
    delete old_front;

    if (empty()) {
      back_ = nullptr;
    }
  }

  T& front() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }

    return front_->data;
  }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }

    return front_->data;
  }

  bool empty() const {
    return front_ == nullptr;
  }
};

int main() {
  Queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  std::cout << queue.front() << std::endl;
  queue.pop();
  std::cout << queue.front() << std::endl;
  queue.pop();
  std::cout << queue.front() << std::endl;
  queue.pop();

  return 0;
}
