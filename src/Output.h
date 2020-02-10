#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H
#include "Node.h"
#include <string>
class Output: public Node {
 protected:
  virtual bool wantOutputToNW() const noexcept override { return false; }
  virtual bool wantOutputToN() const noexcept  override { return false; }
  virtual bool wantOutputToNE() const noexcept override { return false; }
  virtual bool wantOutputToW() const noexcept  override { return false; }
  virtual bool wantOutputToE() const noexcept  override { return false; }
  virtual bool wantOutputToSW() const noexcept override { return false; }
  virtual bool wantOutputToS() const noexcept  override { return false; }
  virtual bool wantOutputToSE() const noexcept override { return false; }

 public:
  template<class... Args>
  explicit Output(const std::string& id, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), id{id} {}

  const std::string id;

  bool query() const noexcept { return powered(); }
};
#endif // ! OUTPUTREADER_H

