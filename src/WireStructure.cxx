#include <SFML/Graphics.hpp>

#include "MainScene.h"

#include <memory>

int main()
{
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Wire Structure");

  std::unique_ptr<Scene> mainScene = std::make_unique<MainScene>();

  if(!mainScene->load())
  {
    window.close();
    return 1;
  }

  while(window.isOpen()) {
    sf::Event e;
    while(window.pollEvent(e))
    {
      if(e.type == sf::Event::Closed && !mainScene->update(e))
      {
        window.close();
      }
    }

    window.clear();
    window.draw(*mainScene);
    window.display();
  }

  if(!mainScene->unload())
  {
    return 1;
  }
}
