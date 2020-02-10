#ifndef NAND_H
#define NAND_H
#include "Node.h"
class Nand : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override { return E; }

  virtual bool powered(unordered_set<const Node*> visited_nodes) const noexcept override {
    return numberPowered(visited_nodes) != numberConnected();
  }
 public:
  using Node::Node;
};
#endif // ! NAND_H

