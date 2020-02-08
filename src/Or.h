#ifndef OR_H
#define OR_H
#include "Node.h"
class Or : public Node {
 protected:
  using Node::pointers;
  virtual bool wantConnectionFromNW() const noexcept override { return false; }
  virtual bool wantConnectionFromN() const noexcept  override { return false; }
  virtual bool wantConnectionFromNE() const noexcept override { return false; }
  virtual bool wantConnectionFromW() const noexcept  override { return false; }
  virtual bool wantConnectionFromE() const noexcept  override { return true; }
  virtual bool wantConnectionFromSW() const noexcept override { return false; }
  virtual bool wantConnectionFromS() const noexcept  override { return false; }
  virtual bool wantConnectionFromSE() const noexcept override { return false; }

  virtual bool powered(unordered_set<const Node*> visited_nodes) const noexcept override {
    if(visited_nodes.count(this) >= 1) return false;

    visited_nodes.emplace(this);

    auto sum = 0;
    if(pointers.nw && pointers.nw->powered(visited_nodes)) { sum++; }
    if(pointers.n  && pointers.n->powered(visited_nodes)) { sum++; }
    if(pointers.ne && pointers.ne->powered(visited_nodes)) { sum++; }
    if(pointers.w  && pointers.w->powered(visited_nodes)) { sum++; }
    if(pointers.e  && pointers.e->powered(visited_nodes)) { sum++; }
    if(pointers.sw && pointers.sw->powered(visited_nodes)) { sum++; }
    if(pointers.s  && pointers.s->powered(visited_nodes)) { sum++; }
    if(pointers.se && pointers.se->powered(visited_nodes)) { sum++; }
    return sum >= 1;
  }
 public:
  using Node::Node;
};
#endif // ! OR_H

