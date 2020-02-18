#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Window.hpp>
struct InputManager
{
  [[nodiscard]] static bool allKeysPressed(
      const sf::Mouse::Button& key) noexcept
  {
    return sf::Mouse::isButtonPressed(key);
  }
  [[nodiscard]] static bool allKeysPressed(
      const sf::Keyboard::Key& key) noexcept
  {
    return sf::Keyboard::isKeyPressed(key);
  }
  [[nodiscard]] static bool anyKeysPressed(
      const sf::Mouse::Button& key) noexcept
  {
    return sf::Mouse::isButtonPressed(key);
  }
  [[nodiscard]] static bool anyKeysPressed(
      const sf::Keyboard::Key& key) noexcept
  {
    return sf::Keyboard::isKeyPressed(key);
  }
  template<class T, class... Keys>
  [[nodiscard]] static bool allKeysPressed(
      const T& key,
      const Keys&... keys) noexcept
  {
    return allKeysPressed(key) && allKeysPressed(keys...);
  }
  template<class T, class... Keys>
  [[nodiscard]] static bool anyKeysPressed(
      const T& key,
      const Keys&... keys) noexcept
  {
    return anyKeysPressed(key) || anyKeysPressed(keys...);
  }
};
#endif  // ! INPUTMANAGER_H
