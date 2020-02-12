#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H
#include "Node.h"
#include <string>
class Output: public Node {
 protected:
  virtual DirectionFlagSet OutputDirections() const noexcept override;

 public:
  template<class... Args>
  explicit Output(const std::string& id, Args&&... args) noexcept;

  const std::string id;

  bool query() const noexcept;
};
#endif // ! OUTPUTREADER_H

