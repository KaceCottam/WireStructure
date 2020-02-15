#include "GhostNode.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <cmath>

auto setupGhostGrid(const sf::View& view, const float distance) {
  std::vector<std::unique_ptr<GhostNode>> ghostNodes{};
  const sf::Vector2i offset = {(int)view.getCenter().x % 50, (int)view.getCenter().y % 50};
  const auto viewCenter = view.getCenter();
  const auto viewSize = view.getSize();
  for(auto x = viewCenter.x - viewSize.x / 2 - offset.x; x < viewCenter.x + viewSize.x / 2 + offset.x*2; x += distance) {
    for(auto y = viewCenter.y - viewSize.y / 2 - offset.y; y < viewCenter.y + viewSize.y / 2 + offset.y*2; y += distance) {
      ghostNodes.emplace_back(new GhostNode({x, y}, 5.f));
    }
  }
  return ghostNodes;
}

bool allKeysPressed(const sf::Keyboard::Key& key) {
  return sf::Keyboard::isKeyPressed(key);
}
template<class... Keys>
bool allKeysPressed(const sf::Keyboard::Key& key, Keys&&... keys) {
  bool result = allKeysPressed(key) && allKeysPressed(keys...);
  return result;
}
bool anyKeysPressed(const sf::Keyboard::Key& key) {
  return sf::Keyboard::isKeyPressed(key);
}
template<class... Keys>
bool anyKeysPressed(const sf::Keyboard::Key& key, Keys&&... keys) {
  bool result = anyKeysPressed(key) || anyKeysPressed(keys...);
  return result;
}

int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Wire Structure");
  sf::View view = window.getDefaultView();
  // i will want a qtree for this eventually
  auto ghostNodes = setupGhostGrid(view, 50.f);
  const auto moveSpeed = 0.2f;
  const auto moveSpeedFast = 1.0f;
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }
    }
    const auto speed = allKeysPressed(sf::Keyboard::LShift) ? moveSpeedFast
                                                            : moveSpeed;
    if(anyKeysPressed(sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D,
                      sf::Keyboard::S, sf::Keyboard::Z)) {
        ghostNodes = setupGhostGrid(view, 50.f);
    }
    if(allKeysPressed(sf::Keyboard::W)) {
      view.move(0.f,-1 * speed);
    }
    if(allKeysPressed(sf::Keyboard::A)) {
      view.move(-1 * speed, 0.f);
    }
    if(allKeysPressed(sf::Keyboard::D)) {
      view.move(speed, 0.f);
    }
    if(allKeysPressed(sf::Keyboard::S)) {
      view.move(0.f, speed);
    }
    const auto zoomFactor = 0.001f *
      (allKeysPressed(sf::Keyboard::LShift) ? 1 : -1);
    if(allKeysPressed(sf::Keyboard::Z)) {
      view.zoom(1.f + zoomFactor);
    }
    const auto mousePos = sf::Mouse::getPosition(window);
    for(const auto& i : ghostNodes) {
      auto iPos = i->getPosition();
      auto transformedMouse = window.mapPixelToCoords(mousePos, view);
      auto distanceToMouse =
        std::sqrt(std::pow(iPos.x - transformedMouse.x, 2) +
                  std::pow(iPos.y - transformedMouse.y, 2));
      if(distanceToMouse < 25.f &&
         distanceToMouse < 25.f)
        i->Highlight(true);
      else i->Highlight(false);
    }

    window.clear();
    for(const auto& i : ghostNodes) {
      window.draw(*i);
    }
    window.setView(view);
    window.display();
  }

  return 0;
}
