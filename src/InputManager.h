#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Window.hpp>
[[nodiscard]] bool allKeysPressed(const sf::Mouse::Button& key) noexcept;
[[nodiscard]] bool allKeysPressed(const sf::Keyboard::Key& key) noexcept;
[[nodiscard]] bool anyKeysPressed(const sf::Mouse::Button& key) noexcept;
[[nodiscard]] bool anyKeysPressed(const sf::Keyboard::Key& key) noexcept;
template<class T, class... Keys>
[[nodiscard]] bool allKeysPressed(const T& key, const Keys&... keys) noexcept {
  return allKeysPressed(key) && allKeysPressed(keys...);
}
template<class T, class... Keys>
[[nodiscard]] bool anyKeysPressed(const T& key, const Keys&... keys) noexcept {
  return anyKeysPressed(key) || anyKeysPressed(keys...);
}
#endif // ! INPUTMANAGER_H

