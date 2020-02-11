#ifndef NOT_H
#define NOT_H
#include "Node.h"
class Not : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override { return E; }

  virtual bool powered(NodeSet& visited_nodes) const noexcept override {
    return !Node::powered(visited_nodes);
  }
 public:
  using Node::Node;
};
#endif // ! NOT_H

