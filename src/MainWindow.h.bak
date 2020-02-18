#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_MAINWINDOW_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_MAINWINDOW_H
#include <SFML/Graphics.hpp>
struct MainWindow
{
  static auto getInstance() -> sf::RenderWindow&
  {
    static sf::RenderWindow window
        = sf::RenderWindow{sf::VideoMode::getDesktopMode(), "Wire Structure"};
    return window;
  }
};
#endif // _HOME_KC_DEV_WIRESTRUCTURE_SRC_MAINWINDOW_H
