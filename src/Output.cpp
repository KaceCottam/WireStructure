
#include "Output.h"
DirectionFlagSet Output::OutputDirections() const noexcept {
  return 0;
}

template<class... Args>
Output::Output(const std::string& id, Args&&... args) noexcept
  : Node(std::forward<Args>(args)...), id{id} {}

bool Output::query() const noexcept {
  return powered();
}
