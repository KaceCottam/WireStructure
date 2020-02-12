#ifndef AND_H
#define AND_H
#include "Node.h"
class And : public Node {
 protected:
  using Node::pointers;
  virtual DirectionFlagSet OutputDirections() const noexcept override;
  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};
#endif // ! AND_H

