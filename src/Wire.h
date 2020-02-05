#ifndef WIRE_HPP
#define WIRE_HPP
#include <stdexcept>

#include "Vec2D.h"

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

class Wire
{
  using wire_ptr = Wire*;
 public:
  explicit Wire(const Vec2D& pos = Vec2D{0,0}) : pos{pos} {}

  // Connections
  wire_ptr nw{nullptr}, n{nullptr}, ne{nullptr}, w{nullptr}, e{nullptr}, sw{nullptr}, s{nullptr}, se{nullptr};

  Vec2D pos;
  bool powered{false};

  [[nodiscard]] friend isSuccessful connect(Wire& a, Wire& b) {
    auto relative_pos = b.pos - a.pos;
    if(abs(relative_pos) <= Vec2D{1,1}) {
      /**/ if(relative_pos == Vec2D{-1,  1}) {a.nw = &b; b.se = &a;}
      else if(relative_pos == Vec2D{ 0,  1}) {a.n  = &b; b.s  = &a;}
      else if(relative_pos == Vec2D{ 1,  1}) {a.ne = &b; b.sw = &a;}
      else if(relative_pos == Vec2D{-1,  0}) {a.w  = &b; b.e  = &a;}
      else if(relative_pos == Vec2D{ 1,  0}) {a.e  = &b; b.w  = &a;}
      else if(relative_pos == Vec2D{-1, -1}) {a.sw = &b; b.ne = &a;}
      else if(relative_pos == Vec2D{ 0, -1}) {a.s  = &b; b.n  = &a;}
      else if(relative_pos == Vec2D{ 1, -1}) {a.se = &b; b.nw = &a;}
      else return false;
    } else return false;
    return true;
  }

  template<class Callable>
  void dispatch(Callable&& func) {
    func(*this);

    if(nw) { nw->dispatch(func, NW); }
    if(n)  { n->dispatch(func, N);   }
    if(ne) { ne->dispatch(func, NE); }
    if(w)  { w->dispatch(func, W);   }
    if(e)  { e->dispatch(func, E);   }
    if(sw) { sw->dispatch(func, SW); }
    if(s)  { s->dispatch(func, S);   }
    if(se) { se->dispatch(func, SE); }
  }
 private:
  template<class Callable>
  void dispatch(Callable&& func, const Direction incoming) {
    func(*this);

    auto from = reverse(incoming);
    if(nw && from != NW) { nw->dispatch(func, NW); }
    if(n && from != N)   { n->dispatch(func, N);   }
    if(ne && from != NE) { ne->dispatch(func, NE); }
    if(w && from != W)   { w->dispatch(func, W);   }
    if(e && from != E)   { e->dispatch(func, E);   }
    if(sw && from != SW) { sw->dispatch(func, SW); }
    if(s && from != S)   { s->dispatch(func, S);   }
    if(se && from != SE) { se->dispatch(func, SE); }
  }
};

void powerOn(Wire& wire) {
  wire.dispatch([](Wire& wire){wire.powered = true;});
}
void powerOff(Wire& wire) {
  wire.dispatch([](Wire& wire){wire.powered = false;});
}
void powerToggle(Wire& wire) {
  wire.dispatch([](Wire& wire){wire.powered = !wire.powered;});
}
#endif  // ! WIRE_HPP
