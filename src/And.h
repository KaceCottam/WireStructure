#ifndef AND_H
#define AND_H
#include "Node.h"
class And : public Node {
 protected:
  using Node::pointers;
  virtual DirectionFlagSet OutputDirections() const noexcept override { return E; }

  virtual bool powered(NodeSet& visited_nodes) const noexcept override {
    return numberPowered(visited_nodes) == numberConnected();
  }
 public:
  using Node::Node;
};
#endif // ! AND_H

