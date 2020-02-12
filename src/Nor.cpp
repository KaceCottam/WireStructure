#include "Nor.h"

DirectionFlagSet Nor::OutputDirections() const noexcept {
  return E;
}

bool Nor::powered(NodeSet& visited_nodes) const noexcept {
  return numberPowered(visited_nodes) < 1;
}
