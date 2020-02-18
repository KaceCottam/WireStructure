#ifndef GRIDVIEW_H
#define GRIDVIEW_H
#include <SFML/Graphics.hpp>

#include "MainWindow.h"
struct GridView
{
  static sf::View& getInstance()
  {
    static sf::View gridView = MainWindow::getInstance().getDefaultView();
    return gridView;
  }
};
#endif  // ! GRIDVIEW_H
