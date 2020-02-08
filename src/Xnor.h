#ifndef OR_H
#define OR_H
#include "Node.h"
class Xnor : public Node {
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
    return numberPowered(visited_nodes) != 1;
  }
 public:
  using Node::Node;
};
#endif // ! OR_H

