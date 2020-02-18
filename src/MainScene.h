#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "Scene.h"
#include "VisualGates.h"
class MainScene : public Scene
{
 public:
  bool load() final;
  bool update(const sf::Event& e) final;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
  bool unload() final;
 private:
  std::vector<AnyVisualGate> gates;
};
#endif // ! MAINSCENE_H

