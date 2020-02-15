#include "GhostNode.h"

GhostNode::GhostNode(const sf::Vector2f& location, const float size) noexcept
  : CircleShape{size} {
    CircleShape::setPosition(location);
    CircleShape::setFillColor(sf::Color(55,55,55,255));
  }

void GhostNode::setHighlight(const bool value) noexcept {
  highlighted = value;
  if(highlighted) {
    sf::CircleShape::setOutlineColor(sf::Color::White);
    sf::CircleShape::setOutlineThickness(2.f);
  } else {
    sf::CircleShape::setOutlineColor(sf::Color::Transparent);
  }
}

[[nodiscard]] bool GhostNode::getHighlight() const noexcept {
  return highlighted;
}
