#ifndef NODE_H
#define NODE_H

#include "Vec2D.h"

#include <optional>
#include <unordered_set>
#include <utility>
#include <mutex>
#include <future>

using std::optional;
using std::pair;
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

class Node {
 protected:
  using node_ptr = Node*;
  using Position = Vec2D<int>;

  virtual DirectionFlagSet OutputDirections() const noexcept = 0;
  unsigned rotation = 0;
  bool isOutputtingInDirection(DirectionFlags dir) const noexcept {
    auto newDirection = toIndex(dir) - rotation;
    auto newFlag = toDirectionFlags(newDirection);
    return (OutputDirections() & newFlag) == newFlag;

  }

  static void safeAddToSet(unordered_set<const Node*>& set, const Node* added) noexcept {
    static std::mutex mux;
    mux.lock();
    set.emplace(added);
    mux.unlock();
  }
  
 public:
  void rotate45ccw() {
    rotation = (rotation + 1) % 8;
    // need to reconnect
    pointers.w  = nullptr;
    pointers.nw = nullptr;
    pointers.e  = nullptr;
    pointers.sw = nullptr;
    pointers.ne = nullptr;
    pointers.e  = nullptr;
    pointers.se = nullptr;
    pointers.s  = nullptr;
  }

  auto numberConnected() const noexcept -> unsigned {
    auto sum = 0u;
    if(pointers.nw) sum++;
    if(pointers.n ) sum++;
    if(pointers.ne) sum++;
    if(pointers.w ) sum++;
    if(pointers.e ) sum++;
    if(pointers.sw) sum++;
    if(pointers.s ) sum++;
    if(pointers.se) sum++;
    return sum;
  }

  auto powered() const noexcept
    -> bool { return powered(unordered_set<const Node*>()); }

  auto numberPowered(unordered_set<const Node*> visited_nodes) const noexcept
    -> unsigned {
      if(visited_nodes.count(this) >= 1) return 0;

      unsigned sum = 0;
      safeAddToSet(visited_nodes, this);

      auto makeIsPoweredFunction = [&visited_nodes](const Node* ptr){
        return [ptr,&visited_nodes]{return ptr->powered(visited_nodes);};
      };

      std::future<bool> nwPowered, nPowered, nePowered, wPowered, ePowered, swPowered, sPowered, sePowered;

      if(pointers.nw) { nwPowered = std::async(makeIsPoweredFunction(pointers.nw)); }
      if(pointers.n)  { nPowered = std::async(makeIsPoweredFunction(pointers.n));   }
      if(pointers.ne) { nePowered = std::async(makeIsPoweredFunction(pointers.ne)); }
      if(pointers.w)  { wPowered = std::async(makeIsPoweredFunction(pointers.w)); }
      if(pointers.e)  { ePowered = std::async(makeIsPoweredFunction(pointers.e)); }
      if(pointers.sw) { swPowered = std::async(makeIsPoweredFunction(pointers.sw)); }
      if(pointers.s)  { sPowered = std::async(makeIsPoweredFunction(pointers.s)); }
      if(pointers.se) { sePowered = std::async(makeIsPoweredFunction(pointers.se)); }

      if(nwPowered.valid() && nwPowered.get()) sum++;
      if(nPowered.valid() && nPowered.get()) sum++;
      if(nePowered.valid() && nePowered.get()) sum++;
      if(wPowered.valid() && wPowered.get()) sum++;
      if(ePowered.valid() && ePowered.get()) sum++;
      if(swPowered.valid() && swPowered.get()) sum++;
      if(sPowered.valid() && sPowered.get()) sum++;
      if(sePowered.valid() && sePowered.get()) sum++;

      return sum;
    }

  virtual auto powered(unordered_set<const Node*> visited_nodes) const noexcept
    -> bool {
    return numberPowered(visited_nodes) >= 1;
  }
  struct {
    // These will be used when finding if something is powered
    node_ptr nw{nullptr}, n{nullptr}, ne{nullptr},
              w{nullptr},              e{nullptr},
             sw{nullptr}, s{nullptr}, se{nullptr};
  } pointers;

  const Position pos;

  explicit Node(const Position& position = Position{0,0}) noexcept
    : pos{position} {}

  virtual ~Node() noexcept = default;

  friend auto connect(Node& a, Node& b) noexcept
    -> bool {
    auto result = false;
    auto relative_pos = a.pos - b.pos;
    if(relative_pos != Position{0,0} && magnitude(relative_pos) <= magnitude(Position{1,1})) {
      if(relative_pos.x == -1 || relative_pos == Position{0,-1}) { return connect(b, a); }

      if(relative_pos == Position{0, 1}) {
        if(b.pointers.n != &a && a.isOutputtingInDirection(S)) { b.pointers.n = &a; result = true; }
        if(a.pointers.s != &b && b.isOutputtingInDirection(N)) { a.pointers.s = &b; result = true; }
      }
      else if(relative_pos == Position{1, 1}) {
        if(b.pointers.ne != &a && a.isOutputtingInDirection(SW)) { b.pointers.ne = &a; result = true; }
        if(a.pointers.sw != &b && b.isOutputtingInDirection(NE)) { a.pointers.sw = &b; result = true; }
      }
      else if(relative_pos == Position{1, 0}) {
        if(b.pointers.e != &a && a.isOutputtingInDirection(W)) { b.pointers.e = &a; result = true; }
        if(a.pointers.w != &b && b.isOutputtingInDirection(E)) { a.pointers.w = &b; result = true; }
      }
      else if(relative_pos == Position{1,-1}) {
        if(b.pointers.se != &a && a.isOutputtingInDirection(NW)) { b.pointers.se = &a; result = true; }
        if(a.pointers.nw != &b && b.isOutputtingInDirection(SE)) { a.pointers.nw = &b; result = true; }
      }
    }
    return result;
  }

  template<class... Nodes>
  friend auto connect(Node& a, Node& b, Nodes&&... other) noexcept
    -> bool {
      auto result = connect(a, b);
      return connect(b, other...) | result;
  }

  friend auto disconnect(Node& a, Node& b) noexcept
    -> bool {
    auto result = false;
    auto relative_pos = a.pos - b.pos;
    if(relative_pos != Position{0,0} && magnitude(relative_pos) <= magnitude(Position{1,1})) {
      if(relative_pos.x == -1 || relative_pos == Position{0,-1}) { return disconnect(b, a); }

      if(relative_pos == Position{0, 1}) {
        if(b.pointers.n != nullptr && a.isOutputtingInDirection(S)) { b.pointers.n = nullptr; result = true; }
        if(a.pointers.s != nullptr && b.isOutputtingInDirection(N)) { a.pointers.s = nullptr; result = true; }
      }
      else if(relative_pos == Position{1, 1}) {
        if(b.pointers.ne != nullptr && a.isOutputtingInDirection(SW)) { b.pointers.ne = nullptr; result = true; }
        if(a.pointers.sw != nullptr && b.isOutputtingInDirection(NE)) { a.pointers.sw = nullptr; result = true; }
      }
      else if(relative_pos == Position{1, 0}) {
        if(b.pointers.e != nullptr && a.isOutputtingInDirection(W)) { b.pointers.e = nullptr; result = true; }
        if(a.pointers.w != nullptr && b.isOutputtingInDirection(E)) { a.pointers.w = nullptr; result = true; }
      }
      else if(relative_pos == Position{1,-1}) {
        if(b.pointers.se != nullptr && a.isOutputtingInDirection(NW)) { b.pointers.se = nullptr; result = true; }
        if(a.pointers.nw != nullptr && b.isOutputtingInDirection(SE)) { a.pointers.nw = nullptr; result = true; }
      }
    }
  return result;
  }

  template<class... Nodes>
  friend auto disconnect(Node& a, Node& b, Nodes&&... other) noexcept
    -> bool {
    auto result = disconnect(a, b);
    return disconnect(b, other...) | result;
  }
};
#endif  // ! NODE_H

