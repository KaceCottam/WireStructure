#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
class Scene : public sf::Drawable
{
 public:
  virtual bool load() { return true; };
  virtual bool update(const sf::Event& e) = 0;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  virtual bool unload() { return true; };
};
#endif // ! SCENE_H

