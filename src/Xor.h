#ifndef OR_H
#define OR_H
#include "Node.h"
class Xor : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;
  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};
#endif // ! OR_H

