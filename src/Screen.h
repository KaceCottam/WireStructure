#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_SCREEN_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_SCREEN_H
#include <SFML/Graphics.hpp>
class Screen : public sf::Drawable
{
 public:
  using sf::Drawable::draw;
  virtual void loadResources()                = 0;
  virtual void update(const sf::Event& event) = 0;
  virtual void unloadResources()              = 0;
  ~Screen() override;
};
#endif // _HOME_KC_DEV_WIRESTRUCTURE_SRC_SCREEN_H
