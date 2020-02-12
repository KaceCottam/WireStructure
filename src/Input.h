#ifndef LEVER_H
#define LEVER_H
#include "Node.h"
#include <string_view>
class Input : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;

  bool activated = false;

  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  template<class... Args>
  explicit Input(const std::string_view id, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), id{id} {}

  const std::string_view id;

  void on() noexcept;
  void off() noexcept;
  void toggle() noexcept;
};

#endif // ! LEVER_H

