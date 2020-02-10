#ifndef WIRE_H
#define WIRE_H
#include "Node.h"
class Wire : public Node {
 protected:
  virtual bool wantOutputToNW() const noexcept override { return true; }
  virtual bool wantOutputToN() const noexcept  override { return true; }
  virtual bool wantOutputToNE() const noexcept override { return true; }
  virtual bool wantOutputToW() const noexcept  override { return true; }
  virtual bool wantOutputToE() const noexcept  override { return true; }
  virtual bool wantOutputToSW() const noexcept override { return true; }
  virtual bool wantOutputToS() const noexcept  override { return true; }
  virtual bool wantOutputToSE() const noexcept override { return true; }

 public:
  using Node::Node;
};
#endif // ! WIRE_H

