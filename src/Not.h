#ifndef NOT_H
#define NOT_H
#include "Gate.h"
class Not : public Gate {
  public:
    template<class ...Args>
    explicit Not(Args&&... args) : Gate{std::forward<Args...>(args...)} {}

    [[nodiscard]] virtual bool powered() final {
      return !Node::powered();
    }
  private:
    [[nodiscard]] virtual bool powered(const Direction incoming, std::unordered_set<Node*>& visited_nodes) final {
      return !Node::powered(incoming,visited_nodes);
    }
};
#endif // ! NOT_H

