#include "Nand.h"

DirectionFlagSet Nand::OutputDirections() const noexcept {
  return E;
}

bool Nand::powered(NodeSet& visited_nodes) const noexcept {
  return numberPowered(visited_nodes) != numberConnected();
}
