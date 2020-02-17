#include "Gates.h"
#include "InputManager.h"
#include "GhostNode.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <cmath>
#include <utility>
#include <unordered_set>
#include <iostream>

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

  auto ghostNodes = setupGhostGrid(view, 50.f);
  float zoomLevel = 1.f;
  std::unordered_set<std::shared_ptr<Node>> board;
  std::shared_ptr<Node> connect1;
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }
    }

    const auto moveSpeed = 1.5f;
    const auto moveSpeedFast = 5.0f;
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
      i->setHighlight(isInRange);

      if(isInRange) {
        auto buttonHeld = false;
        // (Key, NodeType)
        // ~, GhostNode
        // 1, Wire
        // 2, Input
        // 3, Output
        // 4, Not
        // 5, And
        // 6, Or
        // 7, Nand
        // 8, Nor
        // 9, Xor
        // 0, Xnor
        if(anyKeysPressed(sf::Keyboard::Tilde)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.erase(std::find_if(board.begin(), board.end(),
            [&iPos](auto& x)
            {return x->pos.x == (int)iPos.x && x->pos.y == (int)iPos.y;}));
          }
        } else if(buttonHeld) buttonHeld = false; 

        if(anyKeysPressed(sf::Keyboard::Num1)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Wire(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new wire at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num2)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Input(W,Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new input at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num3)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Output(E,Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new output at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num4)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Not(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new not at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num5)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new And(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new and at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num6)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Or(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new or at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num7)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Nand(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new nand at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num8)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Nor(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new nor at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num9)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Xor(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new xor at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::Num0)) {
          if(buttonHeld) {
          buttonHeld = true;
          board.emplace(new Xnor(Position{(int)iPos.x, (int)iPos.y}));
          std::cout << "Created a new xnor at " << iPos.x << ' ' << iPos.y << '\n';
          }
        } else if(buttonHeld) buttonHeld = false; 
        if(anyKeysPressed(sf::Keyboard::C)) {
          if(buttonHeld) {
          buttonHeld = true;
          if(!connect1) {
            connect1 =
              *std::find_if(board.begin(), board.end(),
                [&iPos](auto& x)
                {return x->pos.x == (int)iPos.x && x->pos.y == (int)iPos.y;});
            std::cout << "Starting first connection at " << iPos.x << ' ' << iPos.y << '\n';
          } else {
            auto connect2 = 
            *std::find_if(board.begin(), board.end(),
              [&iPos](auto& x)
              {return x->pos.x == (int)iPos.x && x->pos.y == (int)iPos.y;});
            auto valid = connect(*connect1, *connect2);
            if(valid) {
              std::cout << "Connected to " << iPos.x << ' ' << iPos.y << '\n';
            } else {
              std::cout << "Tried connecting to " << iPos.x << ' ' << iPos.y <<
                ", but failed!\n";
            }
            connect1 = nullptr;
          }
          }
        } else if(buttonHeld) buttonHeld = false; 
      }
    }

    window.clear();
    for(const auto& i : ghostNodes) {
      window.draw(*i);
    }
    window.setView(view);
    window.display();
  }
}
