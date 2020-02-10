#ifndef WIRE_H
#define WIRE_H
#include "Node.h"
class Wire : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override { return NW|N|NE|W|E|SW|S|SE; }

 public:
  using Node::Node;
};
#endif // ! WIRE_H

