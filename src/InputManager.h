#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_INPUTMANAGER_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_INPUTMANAGER_H
#include <SFML/Window.hpp>
struct InputManager
{
  [[nodiscard]] static auto allKeysPressed(
      const sf::Mouse::Button& key) noexcept -> bool
  {
    return sf::Mouse::isButtonPressed(key);
  }
  [[nodiscard]] static auto allKeysPressed(
      const sf::Keyboard::Key& key) noexcept -> bool
  {
    return sf::Keyboard::isKeyPressed(key);
  }
  [[nodiscard]] static auto anyKeysPressed(
      const sf::Mouse::Button& key) noexcept -> bool
  {
    return sf::Mouse::isButtonPressed(key);
  }
  [[nodiscard]] static auto anyKeysPressed(
      const sf::Keyboard::Key& key) noexcept -> bool
  {
    return sf::Keyboard::isKeyPressed(key);
  }
  template<class T, class... Keys>
  [[nodiscard]] static auto allKeysPressed(
      const T& key,
      const Keys&... keys) noexcept -> bool
  {
    return allKeysPressed(key) && allKeysPressed(keys...);
  }
  template<class T, class... Keys>
  [[nodiscard]] static auto anyKeysPressed(
      const T& key,
      const Keys&... keys) noexcept -> bool
  {
    return anyKeysPressed(key) || anyKeysPressed(keys...);
  }
};
#endif // _HOME_KC_DEV_WIRESTRUCTURE_SRC_INPUTMANAGER_H
