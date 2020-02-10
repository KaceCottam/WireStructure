#ifndef NOR_H
#define NOR_H
#include "Node.h"
class Nor : public Node {
 protected:
  virtual bool wantOutputToNW() const noexcept override { return false; }
  virtual bool wantOutputToN() const noexcept  override { return false; }
  virtual bool wantOutputToNE() const noexcept override { return false; }
  virtual bool wantOutputToW() const noexcept  override { return false; }
  virtual bool wantOutputToE() const noexcept  override { return true; }
  virtual bool wantOutputToSW() const noexcept override { return false; }
  virtual bool wantOutputToS() const noexcept  override { return false; }
  virtual bool wantOutputToSE() const noexcept override { return false; }

  virtual bool powered(unordered_set<const Node*> visited_nodes) const noexcept override {
    return numberPowered(visited_nodes) < 1;
  }
 public:
  using Node::Node;
};
#endif // ! NOR_H

