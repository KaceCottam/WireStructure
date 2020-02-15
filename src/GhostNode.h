#ifndef GHOSTNODE_H
#define GHOSTNODE_H
#include <SFML/Graphics.hpp>
class GhostNode : public sf::CircleShape {
 private:
  bool highlighted = false;

 public:
  GhostNode(const sf::Vector2f& location, const float size) noexcept;

  void setHighlight(const bool value) noexcept;
  [[nodiscard]] bool getHighlight() const noexcept;
};
#endif // ! GHOSTNODE_H

