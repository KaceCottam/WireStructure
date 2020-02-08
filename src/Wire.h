#ifndef WIRE_H
#define WIRE_H
#include "Node.h"
class Wire : public Node {
 protected:
  virtual bool wantConnectionFromNW() const noexcept override { return true; }
  virtual bool wantConnectionFromN() const noexcept  override { return true; }
  virtual bool wantConnectionFromNE() const noexcept override { return true; }
  virtual bool wantConnectionFromW() const noexcept  override { return true; }
  virtual bool wantConnectionFromE() const noexcept  override { return true; }
  virtual bool wantConnectionFromSW() const noexcept override { return true; }
  virtual bool wantConnectionFromS() const noexcept  override { return true; }
  virtual bool wantConnectionFromSE() const noexcept override { return true; }
 public:
  using Node::Node;
};
#endif // ! WIRE_H

