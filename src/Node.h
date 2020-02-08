#ifndef NODE_H
#define NODE_H

#include "Vec2D.h"

#include <optional>
#include <unordered_set>
#include <utility>

using std::optional;
using std::pair;
using std::unordered_set;

enum class DirectionTo : int {
  NW = 0, N, NE,
   W,         E,
  SW,     S, SE,
  None = -1
};
enum class DirectionFrom : int {
  SE = 0, S, SW,
   E,         W,
  NE,     N, NW,
  None = -1
};

class Node {
 protected:
  using node_ptr = Node*;
  using Position = Vec2D<int>;

  virtual bool wantConnectionFromNW() const noexcept = 0;
  virtual bool wantConnectionFromN() const noexcept = 0;
  virtual bool wantConnectionFromNE() const noexcept = 0;
  virtual bool wantConnectionFromW() const noexcept = 0;
  virtual bool wantConnectionFromE() const noexcept = 0;
  virtual bool wantConnectionFromSW() const noexcept = 0;
  virtual bool wantConnectionFromS() const noexcept = 0;
  virtual bool wantConnectionFromSE() const noexcept = 0;

 public:
  auto powered() const noexcept
    -> bool { return powered(unordered_set<const Node*>()); }

  auto numberPowered(unordered_set<const Node*> visited_nodes) const noexcept
    -> unsigned {
      auto sum = 0u;
      if(visited_nodes.count(this) >= 1) return false;

      visited_nodes.emplace(this);

      if(pointers.nw && pointers.nw->powered(visited_nodes)) { sum++; }
      if(pointers.n  && pointers.n->powered(visited_nodes)) { sum++; }
      if(pointers.ne && pointers.ne->powered(visited_nodes)) { sum++; }
      if(pointers.w  && pointers.w->powered(visited_nodes)) { sum++; }
      if(pointers.e  && pointers.e->powered(visited_nodes)) { sum++; }
      if(pointers.sw && pointers.sw->powered(visited_nodes)) { sum++; }
      if(pointers.s  && pointers.s->powered(visited_nodes)) { sum++; }
      if(pointers.se && pointers.se->powered(visited_nodes)) { sum++; }
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
        if(a.wantConnectionFromS()) { b.pointers.n = &a; result = true; }
        if(b.wantConnectionFromN()) { a.pointers.s = &b; result = true; }
      }
      else if(relative_pos == Position{1, 1}) {
        if(a.wantConnectionFromSW()) { b.pointers.ne = &a; result = true; }
        if(b.wantConnectionFromNE()) { a.pointers.sw = &b; result = true; }
      }
      else if(relative_pos == Position{1, 0}) {
        if(a.wantConnectionFromW()) { b.pointers.e = &a; result = true; }
        if(b.wantConnectionFromE()) { a.pointers.w = &b; result = true; }
      }
      else if(relative_pos == Position{1,-1}) {
        if(a.wantConnectionFromNW()) { b.pointers.se = &a; result = true; }
        if(b.wantConnectionFromSE()) { a.pointers.nw = &b; result = true; }
      }
    }
    return result;
  }

  friend auto disconnect(Node& a, Node& b) noexcept
    -> bool {
    auto result = false;
    auto relative_pos = a.pos - b.pos;
    if(relative_pos != Position{0,0} && magnitude(relative_pos) <= magnitude(Position{1,1})) {
      if(relative_pos.x == -1 || relative_pos == Position{0,-1}) { return disconnect(b, a); }

      if(relative_pos == Position{0, 1}) {
        if(b.pointers.n != nullptr && a.wantConnectionFromS()) { b.pointers.n = nullptr; result = true; }
        if(a.pointers.s != nullptr && b.wantConnectionFromN()) { a.pointers.s = nullptr; result = true; }
      }
      else if(relative_pos == Position{1, 1}) {
        if(b.pointers.ne != nullptr && a.wantConnectionFromSW()) { b.pointers.ne = nullptr; result = true; }
        if(a.pointers.sw != nullptr && b.wantConnectionFromNE()) { a.pointers.sw = nullptr; result = true; }
      }
      else if(relative_pos == Position{1, 0}) {
        if(b.pointers.e != nullptr && a.wantConnectionFromW()) { b.pointers.e = nullptr; result = true; }
        if(a.pointers.w != nullptr && b.wantConnectionFromE()) { a.pointers.w = nullptr; result = true; }
      }
      else if(relative_pos == Position{1,-1}) {
        if(b.pointers.se != nullptr && a.wantConnectionFromNW()) { b.pointers.se = nullptr; result = true; }
        if(a.pointers.nw != nullptr && b.wantConnectionFromSE()) { a.pointers.nw = nullptr; result = true; }
      }
    }
  return result;
  }
};
#endif  // ! NODE_H

