#ifndef OR_H
#define OR_H
#include "Node.h"
class Or : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override { return E; }

  virtual bool powered(unordered_set<const Node*> visited_nodes) const noexcept override {
    return numberPowered(visited_nodes) >= 1;
  }
 public:
  using Node::Node;
};
#endif // ! OR_H

