#ifndef LEVER_H
#define LEVER_H
#include "Node.h"
class Input : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;

  bool activated = false;

  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  template<class... Args>
  explicit Input(const DirectionFlags inputDir, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), inputDir{inputDir} {}

  const DirectionFlags inputDir;

  void on() noexcept;
  void off() noexcept;
  void toggle() noexcept;
};

#endif // ! LEVER_H

