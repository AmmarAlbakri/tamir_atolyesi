#include <iostream>

template <typename T>
class Stack {
 private:
  struct Node {
    T data;
    Node* next;
  };

  Node* top_;

 public:
  Stack() : top_(nullptr) {}

  ~Stack() {
    while (!empty()) {
      pop();
    }
  }

  void push(T val) {
    Node* node = new Node{val, top_};
    top_ = node;
  }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }

    Node* old_top = top_;
    top_ = top_->next;
    delete old_top;
  }

  T& top() {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }

    return top_->data;
  }

  const T& top() const {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }

    return top_->data;
  }

  bool empty() const {
    return top_ == nullptr;
  }
};

int main() {
  Stack<double> stack;
  stack.push(1.5);
  stack.push(2.4);
  stack.push(3.0);

  std::cout << stack.top() << std::endl;
  stack.pop();
  std::cout << stack.top() << std::endl;
  stack.pop();
  std::cout << stack.top() << std::endl;
  stack.pop();

  return 0;
}
