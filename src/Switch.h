#ifndef SWITCH_H
#define SWITCH_H
#include "Gate.h"
class Switch : public Gate {
  public:
    template<class ...Args>
    explicit Switch(Args&&... args) : Gate{std::forward<Args...>(args...)} {}

    [[nodiscard]] virtual bool powered() final {
      return activated;
    }
    void toggle() { activated = !activated; }
    void on() { activated = true; }
    void off() { activated = false; }
  private:
    [[nodiscard]] virtual bool powered(const Direction, std::unordered_set<Node*>& visited_nodes) final {
      if(visited_nodes.find(this) != visited_nodes.end()) return false;

      visited_nodes.emplace(this);
      return activated;
    }
    bool activated{false};
};
#endif // ! SWITCH_H

