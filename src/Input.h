#ifndef LEVER_H
#define LEVER_H
#include "Node.h"
#include <string>
class Input : public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;

  bool activated = false;

  virtual bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  template<class... Args>
  explicit Input(const std::string& id, Args&&... args) noexcept;

  const std::string id;

  void on() noexcept;
  void off() noexcept;
  void toggle() noexcept;
};

#endif // ! LEVER_H

