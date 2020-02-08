#ifndef NOT_H
#define NOT_H
#include "Node.h"
class Not : public Node {
 protected:
  virtual bool wantConnectionFromNW() const noexcept override { return false; }
  virtual bool wantConnectionFromN() const noexcept  override { return false; }
  virtual bool wantConnectionFromNE() const noexcept override { return false; }
  virtual bool wantConnectionFromW() const noexcept  override { return true; }
  virtual bool wantConnectionFromE() const noexcept  override { return false; }
  virtual bool wantConnectionFromSW() const noexcept override { return false; }
  virtual bool wantConnectionFromS() const noexcept  override { return false; }
  virtual bool wantConnectionFromSE() const noexcept override { return false; }
  //virtual bool wantConnectionToNW() const noexcept override { return false; }
  //virtual bool wantConnectionToN() const noexcept  override { return false; }
  //virtual bool wantConnectionToNE() const noexcept override { return false; }
  //virtual bool wantConnectionToW() const noexcept  override { return true; }
  //virtual bool wantConnectionToE() const noexcept  override { return false; }
  //virtual bool wantConnectionToSW() const noexcept override { return false; }
  //virtual bool wantConnectionToS() const noexcept  override { return false; }
  //virtual bool wantConnectionToSE() const noexcept override { return false; }

  virtual bool powered() const noexcept override { return !Node::powered(); }
  virtual bool powered(const DirectionTo incoming, unordered_set<const Node*>& visited_nodes) const noexcept override {
    return !Node::powered(incoming, visited_nodes);
  }
 public:
  using Node::Node;
};
#endif // ! NOT_H

