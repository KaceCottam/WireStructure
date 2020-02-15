#ifndef GHOSTNODE_H
#define GHOSTNODE_H
#include <SFML/Graphics.hpp>
class GhostNode : public sf::CircleShape {
  public:
    GhostNode(const sf::Vector2f& location, const float size)
    : CircleShape{size} {
      CircleShape::setPosition(location);
      CircleShape::setFillColor(sf::Color(55,55,55,255));
    }

    void Highlight(bool value = false) {
      if(value) {
        CircleShape::setOutlineColor(sf::Color::White);
        CircleShape::setOutlineThickness(2.f);
      } else {
        CircleShape::setOutlineColor(sf::Color::Transparent);
      }
    }
};
#endif // ! GHOSTNODE_H

