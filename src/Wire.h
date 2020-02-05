#ifndef WIRE_HPP
#define WIRE_HPP
#include <stdexcept>

#include "Position.h"
struct InvalidConnectionException : std::logic_error
{
} class Wire
{
 public:
  union
  {
    Position connected[7];
    struct
    {
      Position nw, n, ne, w, e, sw, s, se;
    };
  };
  Position pos;

 private:
};
#endif  // ! WIRE_HPP
