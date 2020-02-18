#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_GRIDVIEW_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_GRIDVIEW_H
#include <SFML/Graphics.hpp>

#include "MainWindow.h"
struct GridView
{
  static auto getInstance() -> sf::View&
  {
    static sf::View gridView = MainWindow::getInstance().getDefaultView();
    return gridView;
  }
};
#endif // _HOME_KC_DEV_WIRESTRUCTURE_SRC_GRIDVIEW_H
