#include "GhostNode.h"

GhostNode::GhostNode(const sf::Vector2f& location, const float size) noexcept
    : CircleShape{size}
{
  CircleShape::setPosition({50 * location.x, 50 * location.y});
  CircleShape::setFillColor(sf::Color(55, 55, 55, 255));
}

void GhostNode::setHighlight(const bool value) noexcept
{
  highlighted = value;
  if (highlighted)
    {
      sf::CircleShape::setOutlineColor(sf::Color::White);
      sf::CircleShape::setOutlineThickness(2.F);
    }
  else
    {
      sf::CircleShape::setOutlineColor(sf::Color::Transparent);
    }
}

[[nodiscard]] auto GhostNode::getHighlight() const noexcept -> bool
{
  return highlighted;
}
