#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_DRAWHANDLER_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_DRAWHANDLER_H
#include <SFML/Graphics.hpp>
template<class NodeType>
class DrawHandler : public sf::Drawable, public NodeType
{
};
#endif // _HOME_KC_DEV_WIRESTRUCTURE_SRC_DRAWHANDLER_H
