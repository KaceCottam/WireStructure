#ifndef LEVER_H
#define LEVER_H
#include "Node.h"
#include <string>
class Lever : public Node {
 protected:
  virtual bool wantConnectionFromNW() const noexcept override { return true; }
  virtual bool wantConnectionFromN() const noexcept  override { return true; }
  virtual bool wantConnectionFromNE() const noexcept override { return true; }
  virtual bool wantConnectionFromW() const noexcept  override { return true; }
  virtual bool wantConnectionFromE() const noexcept  override { return true; }
  virtual bool wantConnectionFromSW() const noexcept override { return true; }
  virtual bool wantConnectionFromS() const noexcept  override { return true; }
  virtual bool wantConnectionFromSE() const noexcept override { return true; }

  bool activated = false;

  virtual bool powered(unordered_set<const Node*> visited_nodes) const noexcept override {
    if(visited_nodes.count(this) >= 1) return false;
    visited_nodes.emplace(this);
    return activated;
  }

 public:
  template<class... Args>
  explicit Lever(const std::string& id, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), id{id} {}

  const std::string id;

  void on() noexcept { activated = true; }
  void off() noexcept { activated = false; }
  void toggle() noexcept { activated = !activated; }
};

#endif // ! LEVER_H

