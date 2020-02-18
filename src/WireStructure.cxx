#include "Gates.h"
#include "MainWindow.h"
#include "Screen.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_set>

int main() {
  std::unique_ptr<Screen> currentScreen = InitializeScreen();

  while(MainWindow::getInstance().isOpen()) {
    sf::Event event;
    while(MainWindow::getInstance().pollEvent(event)) {
      currentScreen->update(event);
    }

    MainWindow::getInstance().clear();
    MainWindow::getInstance().draw(*currentScreen);
    MainWindow::getInstance().display();
  }
}
