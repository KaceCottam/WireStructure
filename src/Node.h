#ifndef NODE_H
#define NODE_H

#include "Vec2D.h"

#include <unordered_set>
#include <utility>
#include <mutex>
#include <future>

using std::unordered_set;
using DirectionFlagSet = unsigned char;
// Going around a circle counterclockwise from 0 degrees
enum DirectionFlags : DirectionFlagSet {
  E  = 1 << 0,
  NE = 1 << 1,
  N  = 1 << 2,
  NW = 1 << 3,
  W  = 1 << 4,
  SW = 1 << 5,
  S  = 1 << 6,
  SE = 1 << 7
};
inline unsigned toIndex(const DirectionFlags& i) {
  switch(i) {
    case E: return 0;
    case NE: return 1;
    case N: return 2;
    case NW: return 3;
    case W: return 4;
    case SW: return 5;
    case S: return 6;
    case SE: return 7;
  }
  throw i;
}
inline DirectionFlags toDirectionFlags(const unsigned i) {
  return DirectionFlags(1 << i);
}

template<class NodeSet>
auto safeAddToSet(NodeSet& set, typename NodeSet::key_type added) noexcept -> void;

class Node {
 protected:
  using NodePtr = const Node*;
  using NodeSet = unordered_set<NodePtr>;

  virtual DirectionFlagSet OutputDirections() const noexcept = 0;
  bool isOutputtingInDirection(DirectionFlags dir) const noexcept;

 public:
  explicit Node(const Position& position = {0,0}) noexcept;

  void rotate45ccw() noexcept;
  auto numberConnected() const noexcept -> unsigned;
  auto numberPowered(NodeSet& visited_nodes) const noexcept -> unsigned;
  auto powered() const noexcept -> bool;
  virtual auto powered(NodeSet& visited_nodes) const noexcept -> bool;

  friend auto connect(Node& a, Node& b) noexcept -> bool;
  friend auto disconnect(Node& a, Node& b) noexcept -> bool;


  virtual ~Node() noexcept = default;

 protected:
  // These will be used when finding if something is powered
  struct {
    NodePtr nw{nullptr}, n{nullptr}, ne{nullptr},
             w{nullptr},              e{nullptr},
            sw{nullptr}, s{nullptr}, se{nullptr};
  } pointers;

  unsigned rotation = 0;
  const Position pos;
};
#endif  // ! NODE_H

