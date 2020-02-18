#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Wire Structure");

  while(window.isOpen()) {
    sf::Event e;
    while(window.pollEvent(e))
    {
      if(e.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();
    window.display();
  }
}
