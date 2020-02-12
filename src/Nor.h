#ifndef NOR_H
#define NOR_H
#include "Node.h"
class Nor : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;
  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};
#endif // ! NOR_H

