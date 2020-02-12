#include "Or.h"
DirectionFlagSet Or::OutputDirections() const noexcept {
  return E;
}
bool Or::powered(NodeSet& visited_nodes) const noexcept {
  return numberPowered(visited_nodes) >= 1;
}
