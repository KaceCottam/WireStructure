#include "And.h"
DirectionFlagSet And::OutputDirections() const noexcept {
  return E;
}

bool And::powered(NodeSet& visited_nodes) const noexcept {
  return numberPowered(visited_nodes) == numberConnected();
}
