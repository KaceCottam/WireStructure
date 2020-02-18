#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
class Scene : public sf::Drawable
{
 public:
  virtual void load() = 0;
  virtual void update(const sf::Event& e) = 0;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  virtual void unload() = 0;
};
#endif // ! SCENE_H

