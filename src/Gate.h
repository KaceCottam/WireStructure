#ifndef GATE_H
#define GATE_H
#include "Node.h"
class Gate : public Node {
  public:
    template<class ...Args>
    explicit Gate(Args&&... args) : Node{std::forward<Args...>(args...)} {}
    [[nodiscard]] virtual bool powered() override = 0;
  protected:
    [[nodiscard]] virtual bool powered(const Direction incoming, std::unordered_set<node_ptr>& visited_nodes) override = 0;
};

#endif // ! GATE_H

