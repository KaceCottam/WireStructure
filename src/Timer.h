#ifndef TIMER_H
#define TIMER_H
#include "Gate.h"
class Timer : public Gate {
  public:
    template<class ...Args>
    explicit Timer(Args&&... args) : Gate{std::forward<Args...>(args...)} {}

    [[nodiscard]] virtual bool powered() final {
      return activated;
    }
    void tick() { activated = !activated; }
  private:
    [[nodiscard]] virtual bool powered(const Direction, std::unordered_set<Node*>& visited_nodes) final {
      if(visited_nodes.find(this) != visited_nodes.end()) return false;

      visited_nodes.emplace(this);
      return activated;
    }
    bool activated{false};
};

#endif // ! TIMER_H

