#ifndef NOT_H
#define NOT_H
#include "Node.h"
class Not : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;
  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};
#endif // ! NOT_H

