#ifndef NODE_H
#define NODE_H

#include "Vec2D.h"
#include <unordered_set>

enum Direction {
  NW,N,NE,W,E,SW,S,SE
};

Direction reverse(const Direction from) {
  switch(from) {
    case NW:  return SE;
    case N:   return S;
    case NE:  return SW;
    case W:   return E;
    case E:   return W;
    case SW:  return NE;
    case S:   return N;
    case SE:  return NW;
  }
  throw from;
}

using isSuccessful = bool;

class Node
{
  using node_ptr = Node*;
 public:
  explicit Node(const Vec2D& pos = Vec2D{0,0}) : pos{pos} {}

  // Connections
  node_ptr nw{nullptr}, n{nullptr}, ne{nullptr},
           w{nullptr}, e{nullptr},
           sw{nullptr}, s{nullptr}, se{nullptr};

  Vec2D pos;
  bool powered{false};

  [[nodiscard]] friend isSuccessful connect(Node& a, Node& b) {
    auto relative_pos = b.pos - a.pos;
    if(abs(relative_pos) <= Vec2D{1,1} && relative_pos != Vec2D{0,0}) {
      auto powerOn = [](auto& n){n.powered = true;};
      if(a.powered) b.dispatch(powerOn);
      if(b.powered) a.dispatch(powerOn);
      /**/ if(relative_pos == Vec2D{-1,  1}) {a.nw = &b; b.se = &a;}
      else if(relative_pos == Vec2D{ 0,  1}) {a.n  = &b; b.s  = &a;}
      else if(relative_pos == Vec2D{ 1,  1}) {a.ne = &b; b.sw = &a;}
      else if(relative_pos == Vec2D{-1,  0}) {a.w  = &b; b.e  = &a;}
      else if(relative_pos == Vec2D{ 1,  0}) {a.e  = &b; b.w  = &a;}
      else if(relative_pos == Vec2D{-1, -1}) {a.sw = &b; b.ne = &a;}
      else if(relative_pos == Vec2D{ 0, -1}) {a.s  = &b; b.n  = &a;}
      else if(relative_pos == Vec2D{ 1, -1}) {a.se = &b; b.nw = &a;}
    } else return false;
    return true;
  }

  [[nodiscard]] friend isSuccessful disconnect(Node& a, Node& b) {
    auto relative_pos = b.pos - a.pos;
    if(abs(relative_pos) <= Vec2D{1,1} && relative_pos != Vec2D{0,0}) {
      /**/ if(relative_pos == Vec2D{-1,  1}) {a.nw = nullptr; b.se = nullptr;}
      else if(relative_pos == Vec2D{ 0,  1}) {a.n  = nullptr; b.s  = nullptr;}
      else if(relative_pos == Vec2D{ 1,  1}) {a.ne = nullptr; b.sw = nullptr;}
      else if(relative_pos == Vec2D{-1,  0}) {a.w  = nullptr; b.e  = nullptr;}
      else if(relative_pos == Vec2D{ 1,  0}) {a.e  = nullptr; b.w  = nullptr;}
      else if(relative_pos == Vec2D{-1, -1}) {a.sw = nullptr; b.ne = nullptr;}
      else if(relative_pos == Vec2D{ 0, -1}) {a.s  = nullptr; b.n  = nullptr;}
      else if(relative_pos == Vec2D{ 1, -1}) {a.se = nullptr; b.nw = nullptr;}
    } else return false;
    return true;
  }

  template<class Callable>
  void dispatch(Callable&& func) {
    func(*this);
    auto visited_nodes = std::unordered_set<node_ptr>();
    visited_nodes.emplace(this);
    if(nw) { nw->dispatch(func, NW, visited_nodes); }
    if(n)  { n->dispatch(func, N, visited_nodes);   }
    if(ne) { ne->dispatch(func, NE, visited_nodes); }
    if(w)  { w->dispatch(func, W, visited_nodes);   }
    if(e)  { e->dispatch(func, E, visited_nodes);   }
    if(sw) { sw->dispatch(func, SW, visited_nodes); }
    if(s)  { s->dispatch(func, S, visited_nodes);   }
    if(se) { se->dispatch(func, SE, visited_nodes); }
  }

 protected:
  template<class Callable>
  void dispatch(Callable&& func, const Direction incoming, std::unordered_set<node_ptr>& visited_nodes) {
    if(visited_nodes.find(this) != visited_nodes.end()) return;

    func(*this);
    visited_nodes.emplace(this);

    auto from = reverse(incoming);
    if(nw && from != NW) { nw->dispatch(func, NW, visited_nodes); }
    if(n && from != N)   { n->dispatch(func, N, visited_nodes);   }
    if(ne && from != NE) { ne->dispatch(func, NE, visited_nodes); }
    if(w && from != W)   { w->dispatch(func, W, visited_nodes);   }
    if(e && from != E)   { e->dispatch(func, E, visited_nodes);   }
    if(sw && from != SW) { sw->dispatch(func, SW, visited_nodes); }
    if(s && from != S)   { s->dispatch(func, S, visited_nodes);   }
    if(se && from != SE) { se->dispatch(func, SE, visited_nodes); }
  }
};
#endif  // ! NODE_H
