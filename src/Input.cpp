#include "Input.h"

DirectionFlagSet Input::OutputDirections() const noexcept {
  return NW|N|NE|W|E|SW|S|SE;
}

bool Input::powered(NodeSet& visited_nodes) const noexcept {
  if(visited_nodes.count(this) >= 1) return false;
  safeAddToSet(visited_nodes, this);
  return activated;
}

template<class... Args>
Input::Input(const std::string& id, Args&&... args) noexcept
  : Node(std::forward<Args>(args)...), id{id} {}

void Input::on() noexcept { activated = true; }
void Input::off() noexcept { activated = false; }
void Input::toggle() noexcept { activated = !activated; }
