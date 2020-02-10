#ifndef LEVER_H
#define LEVER_H
#include "Node.h"
#include <string>
class Input : public Node {
 protected:
  virtual bool wantOutputToNW() const noexcept override { return true; }
  virtual bool wantOutputToN() const noexcept  override { return true; }
  virtual bool wantOutputToNE() const noexcept override { return true; }
  virtual bool wantOutputToW() const noexcept  override { return true; }
  virtual bool wantOutputToE() const noexcept  override { return true; }
  virtual bool wantOutputToSW() const noexcept override { return true; }
  virtual bool wantOutputToS() const noexcept  override { return true; }
  virtual bool wantOutputToSE() const noexcept override { return true; }

  bool activated = false;

  virtual bool powered(unordered_set<const Node*> visited_nodes) const noexcept override {
    if(visited_nodes.count(this) >= 1) return false;
    safeAddToSet(visited_nodes, this);
    return activated;
  }

 public:
  template<class... Args>
  explicit Input(const std::string& id, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), id{id} {}

  const std::string id;

  void on() noexcept { activated = true; }
  void off() noexcept { activated = false; }
  void toggle() noexcept { activated = !activated; }
};

#endif // ! LEVER_H

