#ifndef GATE_H
#define GATE_H
#include "Node.h"
class Gate : public Node {
  public:
    template<class ...Args>
    explicit Gate(Args&&... args) : Node{std::forward<Args...>(args...)} {}
    [[nodiscard]] virtual bool powered() override {
      return Node::powered();
    }
  protected:
    [[nodiscard]] virtual bool powered(const Direction incoming, std::unordered_set<node_ptr>& visited_nodes) override {
      return Node::powered(incoming, visited_nodes);
    }
};

#endif // ! GATE_H

