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

class Node {
 protected:
  using node_ptr = Node*;
  using Position = Vec2D<int>;

  virtual bool wantOutputToNW() const noexcept = 0;
  virtual bool wantOutputToN() const noexcept = 0;
  virtual bool wantOutputToNE() const noexcept = 0;
  virtual bool wantOutputToW() const noexcept = 0;
  virtual bool wantOutputToE() const noexcept = 0;
  virtual bool wantOutputToSW() const noexcept = 0;
  virtual bool wantOutputToS() const noexcept = 0;
  virtual bool wantOutputToSE() const noexcept = 0;

  static void safeAddToSet(unordered_set<const Node*>& set, const Node* added) noexcept {
    static std::mutex mux;
    mux.lock();
    set.emplace(added);
    mux.unlock();
  }
  
 public:
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
        if(a.wantOutputToS()) { b.pointers.n = &a; result = true; }
        if(b.wantOutputToN()) { a.pointers.s = &b; result = true; }
      }
      else if(relative_pos == Position{1, 1}) {
        if(a.wantOutputToSW()) { b.pointers.ne = &a; result = true; }
        if(b.wantOutputToNE()) { a.pointers.sw = &b; result = true; }
      }
      else if(relative_pos == Position{1, 0}) {
        if(a.wantOutputToW()) { b.pointers.e = &a; result = true; }
        if(b.wantOutputToE()) { a.pointers.w = &b; result = true; }
      }
      else if(relative_pos == Position{1,-1}) {
        if(a.wantOutputToNW()) { b.pointers.se = &a; result = true; }
        if(b.wantOutputToSE()) { a.pointers.nw = &b; result = true; }
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
        if(b.pointers.n != nullptr && a.wantOutputToS()) { b.pointers.n = nullptr; result = true; }
        if(a.pointers.s != nullptr && b.wantOutputToN()) { a.pointers.s = nullptr; result = true; }
      }
      else if(relative_pos == Position{1, 1}) {
        if(b.pointers.ne != nullptr && a.wantOutputToSW()) { b.pointers.ne = nullptr; result = true; }
        if(a.pointers.sw != nullptr && b.wantOutputToNE()) { a.pointers.sw = nullptr; result = true; }
      }
      else if(relative_pos == Position{1, 0}) {
        if(b.pointers.e != nullptr && a.wantOutputToW()) { b.pointers.e = nullptr; result = true; }
        if(a.pointers.w != nullptr && b.wantOutputToE()) { a.pointers.w = nullptr; result = true; }
      }
      else if(relative_pos == Position{1,-1}) {
        if(b.pointers.se != nullptr && a.wantOutputToNW()) { b.pointers.se = nullptr; result = true; }
        if(a.pointers.nw != nullptr && b.wantOutputToSE()) { a.pointers.nw = nullptr; result = true; }
      }
    }
  return result;
  }
};
#endif  // ! NODE_H

