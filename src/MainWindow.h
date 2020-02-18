#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <SFML/Graphics.hpp>
struct MainWindow
{
  static sf::RenderWindow& getInstance()
  {
    static sf::RenderWindow window
        = sf::RenderWindow{sf::VideoMode::getDesktopMode(), "Wire Structure"};
    return window;
  }
};
#endif  // ! MAINWINDOW_H
