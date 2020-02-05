#ifndef WIRE_HPP
#define WIRE_HPP
#include <stdexcept>

#include "Vec2D.h"

class Wire
{
 public:
  // Connections
  Vec2D nw, n, ne, w, e, sw, s, se;
  Vec2D pos;

 private:
};
#endif  // ! WIRE_HPP
