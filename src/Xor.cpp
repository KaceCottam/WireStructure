#include "Xor.h"

DirectionFlagSet Xor::OutputDirections() const noexcept { return E; }

bool Xor::powered(NodeSet& visited_nodes) const noexcept {
  return numberPowered(visited_nodes) == 1;
}
