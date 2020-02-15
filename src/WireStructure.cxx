#include "Gates.h"
#include "InputManager.h"
#include "GhostNode.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <cmath>
#include <utility>
#include <unordered_set>

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


int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Wire Structure");
  sf::View view = window.getDefaultView();
  // i will want a qtree for this eventually
  auto ghostNodes = setupGhostGrid(view, 50.f);
  float zoomLevel = 1.f;
  std::unordered_set<std::unique_ptr<Node>> board;
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }

      if(event.type == sf::Event::MouseButtonPressed) {
      }
    }

    const auto moveSpeed = 1.5f;
    const auto moveSpeedFast = 10.0f;
    const auto speed = allKeysPressed(sf::Keyboard::LShift) ? moveSpeedFast
                                                            : moveSpeed;
    if(anyKeysPressed(sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D,
                      sf::Keyboard::S, sf::Keyboard::Z)) {
        ghostNodes = setupGhostGrid(view, 50.f);
    }
    if(allKeysPressed(sf::Keyboard::W)) { view.move(0.f,-1 * speed); }
    if(allKeysPressed(sf::Keyboard::A)) { view.move(-1 * speed, 0.f); }
    if(allKeysPressed(sf::Keyboard::S)) { view.move(0.f, speed); }
    if(allKeysPressed(sf::Keyboard::D)) { view.move(speed, 0.f); }

    const auto zoomFactor = 0.01f *
      (allKeysPressed(sf::Keyboard::LShift) ? 1 : -1);

    if(allKeysPressed(sf::Keyboard::Z)) {
      const auto zoomHigh = 1.25f;
      const auto zoomLow = 0.45f;
      if(zoomLevel > zoomLow && zoomLevel < zoomHigh) {
        view.zoom(1.f + zoomFactor);
      }
      zoomLevel = std::clamp(zoomLevel * (1.f + zoomFactor), zoomLow, zoomHigh);
    }

    const auto mousePos = sf::Mouse::getPosition(window);
    for(const auto& i : ghostNodes) {
      const auto iPos = i->getPosition();
      const auto transformedMouse = window.mapPixelToCoords(mousePos, view);
      const auto distanceToMouse =
        std::sqrt(std::pow(iPos.x - transformedMouse.x, 2) +
                  std::pow(iPos.y - transformedMouse.y, 2));
      const auto isInRange = distanceToMouse < 25.f;
      i->Highlight(isInRange);

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
