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
  NW = (int)DirectionTo::SE, N = (int)DirectionTo::S, NE = (int)DirectionTo::SW,
   W = (int)DirectionTo::E,                            E = (int)DirectionTo::W,
  SW = (int)DirectionTo::NE, S = (int)DirectionTo::N, SE = (int)DirectionTo::NW,
  None = (int)DirectionTo::None
};

class Node {
 protected:
  using node_ptr = Node*;
  using Position = Vec2D<int>;

  struct {
    // These will be used when finding if something is powered
    node_ptr nw{nullptr}, n{nullptr}, ne{nullptr},
              w{nullptr},              e{nullptr},
             sw{nullptr}, s{nullptr}, se{nullptr};
  } pointers;

  virtual bool wantConnectionFromNW() const noexcept = 0;
  virtual bool wantConnectionFromN() const noexcept = 0;
  virtual bool wantConnectionFromNE() const noexcept = 0;
  virtual bool wantConnectionFromW() const noexcept = 0;
  virtual bool wantConnectionFromE() const noexcept = 0;
  virtual bool wantConnectionFromSW() const noexcept = 0;
  virtual bool wantConnectionFromS() const noexcept = 0;
  virtual bool wantConnectionFromSE() const noexcept = 0;


  virtual auto powered() const noexcept
    -> bool {
    auto visited_nodes = unordered_set<const Node*>({this});
    if(pointers.nw &&
       pointers.nw->powered(DirectionTo::NW, visited_nodes)) { return true; }
    if(pointers.n  &&
       pointers.n->powered(DirectionTo::N, visited_nodes)) { return true; }
    if(pointers.ne &&
       pointers.ne->powered(DirectionTo::NE, visited_nodes)) { return true; }
    if(pointers.w  &&
       pointers.w->powered(DirectionTo::W, visited_nodes)) { return true; }
    if(pointers.e  &&
       pointers.e->powered(DirectionTo::E, visited_nodes)) { return true; }
    if(pointers.sw &&
       pointers.sw->powered(DirectionTo::SW, visited_nodes)) { return true; }
    if(pointers.s  &&
       pointers.s->powered(DirectionTo::S, visited_nodes)) { return true; }
    if(pointers.se &&
       pointers.se->powered(DirectionTo::SE, visited_nodes)) { return true; }
    return false;
  }
  virtual auto powered(const DirectionTo incoming, unordered_set<const Node*>& visited_nodes) const noexcept
    -> bool {
    if(visited_nodes.count(this) >= 1) return false;

    visited_nodes.emplace(this);

    auto from = DirectionFrom{incoming};
    if(pointers.nw && from != DirectionFrom::NW &&
       pointers.nw->powered(DirectionTo::NW, visited_nodes)) { return true; }
    if(pointers.n  && from != DirectionFrom::N  &&
       pointers.n->powered(DirectionTo::N, visited_nodes)) { return true; }
    if(pointers.ne && from != DirectionFrom::NE &&
       pointers.ne->powered(DirectionTo::NE, visited_nodes)) { return true; }
    if(pointers.w  && from != DirectionFrom::W  &&
       pointers.w->powered(DirectionTo::W, visited_nodes)) { return true; }
    if(pointers.e  && from != DirectionFrom::E  &&
       pointers.e->powered(DirectionTo::E, visited_nodes)) { return true; }
    if(pointers.sw && from != DirectionFrom::SW &&
       pointers.sw->powered(DirectionTo::SW, visited_nodes)) { return true; }
    if(pointers.s  && from != DirectionFrom::S  &&
       pointers.s->powered(DirectionTo::S, visited_nodes)) { return true; }
    if(pointers.se && from != DirectionFrom::SE &&
       pointers.se->powered(DirectionTo::SE, visited_nodes)) { return true; }
    return false;
  }
 public:
  const Position pos;

  explicit Node(const Position& position = Position{0,0}) noexcept
    : pos{position} {}

  virtual ~Node() noexcept = default;

  friend auto connect(Node& a, Node& b) noexcept
    -> bool {
    auto relative_pos = a.pos - b.pos;
    auto result = false;
    if(relative_pos != Position{0,0}
      && magnitude(relative_pos) <= magnitude(Position{1, 1})) {
      if(relative_pos == Position{-1, 1} || relative_pos == Position{-1,0} ||
         relative_pos == Position{-1,-1} || relative_pos == Position{0,-1}) {
        return connect(b, a);
      }

      /**/ if(relative_pos == Position{ 0, 1}) {
        if(a.wantConnectionFromN()) { b.pointers.s = &a; result = true; }
        if(b.wantConnectionFromS()) { a.pointers.n = &b; result = true; }
      }
      else if(relative_pos == Position{ 1, 1}) {
        if(a.wantConnectionFromNE()) { b.pointers.sw = &a; result = true; }
        if(b.wantConnectionFromSW()) { a.pointers.ne = &b; result = true; }
      }
      else if(relative_pos == Position{ 1, 0}) {
        if(a.wantConnectionFromW()) { b.pointers.e = &a; result = true; }
        if(b.wantConnectionFromE()) { a.pointers.w = &b; result = true; }
      }
      else if(relative_pos == Position{ 1,-1}) {
        if(a.wantConnectionFromSE()) { b.pointers.se = &a; result = true; }
        if(b.wantConnectionFromNW()) { a.pointers.nw = &b; result = true; }
      }
      return result;
    }
    return false;
  }

  friend auto disconnect(Node& a, Node& b) noexcept
    -> bool {
    auto relative_pos = a.pos - b.pos;
    auto result = false;
    if(relative_pos != Position{0,0} &&
       magnitude(relative_pos) <= magnitude(Position{1, 1})) {
      if(relative_pos == Position{-1, 1} || relative_pos == Position{-1,0} ||
         relative_pos == Position{-1,-1} || relative_pos == Position{0,-1}) {
        return disconnect(b, a);
      }

      /**/ if(relative_pos == Position{ 0, 1}) {
        if(a.wantConnectionFromN()) { b.pointers.s = nullptr; result = true; }
        if(b.wantConnectionFromS()) { a.pointers.n = nullptr; result = true; }
      }
      else if(relative_pos == Position{ 1, 1}) {
        if(a.wantConnectionFromNE()) { b.pointers.sw = nullptr; result = true; }
        if(b.wantConnectionFromSW()) { a.pointers.ne = nullptr; result = true; }
      }
      else if(relative_pos == Position{ 1, 0}) {
        if(a.wantConnectionFromW()) { b.pointers.e = nullptr; result = true; }
        if(b.wantConnectionFromE()) { a.pointers.w = nullptr; result = true; }
      }
      else if(relative_pos == Position{ 1,-1}) {
        if(a.wantConnectionFromSE()) { b.pointers.se = nullptr; result = true; }
        if(b.wantConnectionFromNW()) { a.pointers.nw = nullptr; result = true; }
      }
    }
    return result;
  }
};
#endif  // ! NODE_H

