#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_GHOSTNODE_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_GHOSTNODE_H
#include <SFML/Graphics.hpp>
class GhostNode : public sf::CircleShape
{
 private:
  bool highlighted = false;

 public:
  GhostNode(const sf::Vector2f& location, float size) noexcept;

  void               setHighlight(bool value) noexcept;
  [[nodiscard]] auto getHighlight() const noexcept -> bool;
};
#endif // _HOME_KC_DEV_WIRESTRUCTURE_SRC_GHOSTNODE_H
