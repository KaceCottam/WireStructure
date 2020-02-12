
#include "Output.h"
DirectionFlagSet Output::OutputDirections() const noexcept {
  return 0;
}

bool Output::query() const noexcept {
  return powered();
}
