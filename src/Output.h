#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H
#include "Node.h"
#include <string_view>
class Output: public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;

 public:
  template<class... Args>
  explicit Output(const DirectionFlags inputDir, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), inputDir{inputDir} {}

  const DirectionFlags inputDir;

  bool query() const noexcept;
};
#endif // ! OUTPUTREADER_H

