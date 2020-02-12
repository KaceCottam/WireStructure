#include "Xnor.h"

DirectionFlagSet Xnor::OutputDirections() const noexcept { return E; }

bool Xnor::powered(NodeSet& visited_nodes) const noexcept {
  return numberPowered(visited_nodes) != 1;
}
