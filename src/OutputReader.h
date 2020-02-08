#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H
#include "Node.h"
#include <string>
class OutputReader : public Node {
 protected:
  virtual bool wantConnectionFromNW() const noexcept override { return false; }
  virtual bool wantConnectionFromN() const noexcept  override { return false; }
  virtual bool wantConnectionFromNE() const noexcept override { return false; }
  virtual bool wantConnectionFromW() const noexcept  override { return false; }
  virtual bool wantConnectionFromE() const noexcept  override { return false; }
  virtual bool wantConnectionFromSW() const noexcept override { return false; }
  virtual bool wantConnectionFromS() const noexcept  override { return false; }
  virtual bool wantConnectionFromSE() const noexcept override { return false; }

 public:
  template<class... Args>
  explicit OutputReader(const std::string& id, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), id{id} {}

  const std::string id;

  bool query() const noexcept { return powered(); }
};
#endif // ! OUTPUTREADER_H

