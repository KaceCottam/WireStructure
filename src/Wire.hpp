#ifndef WIRE_HPP
#define WIRE_HPP
#include <stdexcept>

#include "Vec2D.h"
using isSuccessful = bool;

class Wire
{
  using wire_ptr = Wire*;

 public:
  union
  {
    struct
    {
      wire_ptr nw, n, ne, w, e, sw, s, se;
    };
    wire_ptr connections[7];
  };
  Vec2D pos;
};

[[nodiscard]] isSuccessful connect(Wire& from, Wire& to) noexcept
{
  const auto relative_position = from.pos - to.pos;
  if (abs(relative_position) <= Vec2D(1, 1))
    {
      if (relative_position == Vec2D(-1, 1))
        {
          from.nw = &to;
          to.se   = &from;
        }
      else if (relative_position == Vec2D(0, 1))
        {
          from.n = &to;
          to.s   = &from;
        }
      else if (relative_position == Vec2D(1, 1))
        {
          from.ne = &to;
          to.sw   = &from;
        }
      else if (relative_position == Vec2D(-1, 0))
        {
          from.w = &to;
          to.e   = &from;
        }
      else if (relative_position == Vec2D(1, 0))
        {
          from.e = &to;
          to.w   = &from;
        }
      else if (relative_position == Vec2D(-1, -1))
        {
          from.sw = &to;
          to.ne   = &from;
        }
      else if (relative_position == Vec2D(0, -1))
        {
          from.s = &to;
          to.n   = &from;
        }
      else if (relative_position == Vec2D(1, -1))
        {
          from.se = &to;
          to.nw   = &from;
        }
    }
  else
    {
      return false;
    }
  return true;
}
#endif  // ! WIRE_HPP
