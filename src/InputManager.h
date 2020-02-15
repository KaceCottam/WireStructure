#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Window.hpp>
bool allKeysPressed(const sf::Mouse::Button& key);
bool allKeysPressed(const sf::Keyboard::Key& key);
bool anyKeysPressed(const sf::Mouse::Button& key);
bool anyKeysPressed(const sf::Keyboard::Key& key);
template<class T, class... Keys>
bool allKeysPressed(const T& key, const Keys&... keys) {
  return allKeysPressed(key) && allKeysPressed(keys...);
}
template<class T, class... Keys>
bool anyKeysPressed(const T& key, const Keys&... keys) {
  return anyKeysPressed(key) || anyKeysPressed(keys...);
}
#endif // ! INPUTMANAGER_H

