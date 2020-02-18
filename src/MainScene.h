#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "Scene.h"
class MainScene : public Scene
{
 public:
  void load() final;
  void update(const sf::Event& e) final;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
  void unload() final;
};
#endif // ! MAINSCENE_H

