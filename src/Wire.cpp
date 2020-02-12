#include "Wire.h"

DirectionFlagSet Wire::OutputDirections() const noexcept {
  return NW|N|NE|W|E|SW|S|SE;
}
