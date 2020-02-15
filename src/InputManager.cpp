#include "InputManager.h"
[[nodiscard]] bool allKeysPressed(const sf::Mouse::Button& key) noexcept {
  return sf::Mouse::isButtonPressed(key);
}
[[nodiscard]] bool allKeysPressed(const sf::Keyboard::Key& key) noexcept {
  return sf::Keyboard::isKeyPressed(key);
}
[[nodiscard]] bool anyKeysPressed(const sf::Mouse::Button& key) noexcept {
  return sf::Mouse::isButtonPressed(key);
}
[[nodiscard]] bool anyKeysPressed(const sf::Keyboard::Key& key) noexcept {
  return sf::Keyboard::isKeyPressed(key);
}
