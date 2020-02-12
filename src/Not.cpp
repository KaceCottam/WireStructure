
#include "Not.h"
DirectionFlagSet Not::OutputDirections() const noexcept {
 return E;
}

bool Not::powered(NodeSet& visited_nodes) const noexcept {
  return !Node::powered(visited_nodes);
}
