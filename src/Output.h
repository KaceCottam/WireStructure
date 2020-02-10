#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H
#include "Node.h"
#include <string>
class Output: public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override { return 0; }

 public:
  template<class... Args>
  explicit Output(const std::string& id, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), id{id} {}

  const std::string id;

  bool query() const noexcept { return powered(); }
};
#endif // ! OUTPUTREADER_H

