#include "InputManager.h"
bool allKeysPressed(const sf::Mouse::Button& key) {
  return sf::Mouse::isButtonPressed(key);
}
bool allKeysPressed(const sf::Keyboard::Key& key) {
  return sf::Keyboard::isKeyPressed(key);
}
bool anyKeysPressed(const sf::Mouse::Button& key) {
  return sf::Mouse::isButtonPressed(key);
}
bool anyKeysPressed(const sf::Keyboard::Key& key) {
  return sf::Keyboard::isKeyPressed(key);
}
