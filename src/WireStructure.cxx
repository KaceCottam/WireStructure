#include "Gates.h"
#include "InputManager.h"
#include "MainWindow.h"
#include "GridView.h"
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
  float zoomLevel = 1.f;
  auto ghostNodes = setupGhostGrid(GridView::getInstance(), 50.f);
  std::unordered_set<std::shared_ptr<Node>> board;
  std::shared_ptr<Node> connect1;
  while(MainWindow::getInstance().isOpen()) {
    sf::Event event;
    while(MainWindow::getInstance().pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        MainWindow::getInstance().close();
      }

      if(event.type == sf::Event::KeyReleased) {
        for(const auto& i : ghostNodes) {
          const auto mousePos = sf::Mouse::getPosition(MainWindow::getInstance());
          const auto iPos = i->getPosition();
          const auto transformedMouse = MainWindow::getInstance().mapPixelToCoords(mousePos, GridView::getInstance());
          const auto distanceToMouse =
            std::sqrt(std::pow(iPos.x - transformedMouse.x, 2) +
                      std::pow(iPos.y - transformedMouse.y, 2));
          const auto isInRange = distanceToMouse < 25.f;

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
          if(isInRange) {
            if(event.key.code == sf::Keyboard::Tilde) {
              auto node = std::find_if(board.begin(), board.end(),
                  [&iPos](auto& x)
                  {return x->pos.x == (int)iPos.x && x->pos.y == (int)iPos.y;});
              if(node != board.end()) {
                board.erase(node);
                std::cout << "Node erased at " << iPos.x << ' ' << iPos.y << '\n';
              } else {
                std::cout << "No nodes found at " << iPos.x << ' ' << iPos.y << '\n';
              }
            }
            if(event.key.code == sf::Keyboard::Num1) {
              board.emplace(new Wire(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new wire at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num2) {
              board.emplace(new Input(W,Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new input at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num3) {
              board.emplace(new Output(E,Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new output at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num4) {
              board.emplace(new Not(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new not at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num5) {
              board.emplace(new And(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new and at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num6) {
              board.emplace(new Or(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new or at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num7) {
              board.emplace(new Nand(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new nand at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num8) {
              board.emplace(new Nor(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new nor at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num9) {
              board.emplace(new Xor(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new xor at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::Num0) {
              board.emplace(new Xnor(Position{(int)iPos.x, (int)iPos.y}));
              std::cout << "Created a new xnor at " << iPos.x << ' ' << iPos.y << '\n';
            }
            if(event.key.code == sf::Keyboard::C) {
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
          }
        }
      }
    }

    const auto moveSpeed = 1.5f;
    const auto moveSpeedFast = 5.0f;
    const auto speed = InputManager::allKeysPressed(sf::Keyboard::LShift) ? moveSpeedFast
                                                            : moveSpeed;
    if(InputManager::anyKeysPressed(sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D,
                      sf::Keyboard::S, sf::Keyboard::Z)) {
        ghostNodes = setupGhostGrid(GridView::getInstance(), 50.f);
    }
    if(InputManager::allKeysPressed(sf::Keyboard::W)) { GridView::getInstance().move(0.f,-1 * speed); }
    if(InputManager::allKeysPressed(sf::Keyboard::A)) { GridView::getInstance().move(-1 * speed, 0.f); }
    if(InputManager::allKeysPressed(sf::Keyboard::S)) { GridView::getInstance().move(0.f, speed); }
    if(InputManager::allKeysPressed(sf::Keyboard::D)) { GridView::getInstance().move(speed, 0.f); }

    const auto zoomFactor = 0.01f *
      (InputManager::allKeysPressed(sf::Keyboard::LShift) ? 1 : -1);

    if(InputManager::allKeysPressed(sf::Keyboard::Z)) {
      const auto zoomHigh = 1.25f;
      const auto zoomLow = 0.45f;
      if(zoomLevel > zoomLow && zoomLevel < zoomHigh) {
        GridView::getInstance().zoom(1.f + zoomFactor);
      }
      zoomLevel = std::clamp(zoomLevel * (1.f + zoomFactor), zoomLow, zoomHigh);
    }

    const auto mousePos = sf::Mouse::getPosition(MainWindow::getInstance());
    for(const auto& i : ghostNodes) {
      const auto iPos = i->getPosition();
      const auto transformedMouse = MainWindow::getInstance().mapPixelToCoords(mousePos, GridView::getInstance());
      const auto distanceToMouse =
        std::sqrt(std::pow(iPos.x - transformedMouse.x, 2) +
                  std::pow(iPos.y - transformedMouse.y, 2));
      const auto isInRange = distanceToMouse < 25.f;
      i->setHighlight(isInRange);
    }

    MainWindow::getInstance().clear();
    for(const auto& i : ghostNodes) {
      MainWindow::getInstance().draw(*i);
    }
    MainWindow::getInstance().setView(GridView::getInstance());
    MainWindow::getInstance().display();
  }
}
