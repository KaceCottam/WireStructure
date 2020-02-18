#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
class Screen : public sf::Drawable
{
 public:
  using sf::Drawable::draw;
  virtual void loadResources()                = 0;
  virtual void update(const sf::Event& event) = 0;
  virtual void unloadResources()              = 0;
  virtual ~Screen();
};
#endif  // ! SCREEN_H
