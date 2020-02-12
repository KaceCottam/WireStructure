#ifndef NAND_H
#define NAND_H
#include "Node.h"
class Nand : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;
  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};
#endif // ! NAND_H

