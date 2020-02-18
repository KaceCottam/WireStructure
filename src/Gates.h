#ifndef _HOME_KC_DEV_WIRESTRUCTURE_SRC_GATES_H
#define _HOME_KC_DEV_WIRESTRUCTURE_SRC_GATES_H

#include <unordered_set>

#include "Vec2D.h"

using std::unordered_set;
using DirectionFlagSet = unsigned char;

enum DirectionFlags : DirectionFlagSet
{
  E  = 1 << 0,
  NE = 1 << 1,
  N  = 1 << 2,
  NW = 1 << 3,
  W  = 1 << 4,
  SW = 1 << 5,
  S  = 1 << 6,
  SE = 1 << 7
};
auto              toIndex(const DirectionFlags& i) -> unsigned;
inline auto toDirectionFlags(unsigned i) -> DirectionFlags;

template<class NodeSet>
auto safeAddToSet(NodeSet& set, typename NodeSet::key_type added) noexcept
    -> void;

class Node
{
 protected:
  using NodePtr = const Node*;
  using NodeSet = unordered_set<NodePtr>;

  [[nodiscard]] virtual auto OutputDirections() const noexcept -> DirectionFlagSet = 0;
  [[nodiscard]] auto isOutputtingInDirection(DirectionFlags dir) const noexcept -> bool;

  // input node ptrs
  struct
  {
    NodePtr nw{nullptr}, n{nullptr}, ne{nullptr}, w{nullptr}, e{nullptr},
        sw{nullptr}, s{nullptr}, se{nullptr};
  } pointers;

  unsigned rotation = 0;

 public:
  const Position pos;

  explicit Node(const Position& position) noexcept;

  void         rotate45ccw() noexcept;
  [[nodiscard]] auto         numberConnected() const noexcept -> unsigned;
  auto         numberPowered(NodeSet& visited_nodes) const noexcept -> unsigned;
  [[nodiscard]] auto         powered() const noexcept -> bool;
  virtual auto powered(NodeSet& visited_nodes) const noexcept -> bool;

  friend auto connect(Node& a, Node& b) noexcept -> bool;
  friend auto disconnect(Node& a, Node& b) noexcept -> bool;

  virtual ~Node() noexcept = default;
};

class And : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

class Input : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  bool             activated = false;

  auto powered(NodeSet& visited_nodes) const noexcept -> bool override;

  const DirectionFlags inputDir;

 public:
  template<class... Args>
  explicit Input(const DirectionFlags inputDir, Args&&... args) noexcept
      : Node(std::forward<Args>(args)...)
      , inputDir{inputDir}
  {
  }

  void on() noexcept;
  void off() noexcept;
  void toggle() noexcept;
};

class Output : public Node
{
 protected:
  DirectionFlags   outputDir;
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;

 public:
  template<class... Args>
  explicit Output(const DirectionFlags outputDir, Args&&... args) noexcept
      : Node(std::forward<Args>(args)...)
      , outputDir{outputDir}
  {
  }

  [[nodiscard]] auto query() const noexcept -> bool;
};

class Nand : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

class Nor : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

class Not : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

class Or : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

class Wire : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;

 public:
  using Node::Node;
};

class Xnor : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

class Xor : public Node
{
 protected:
  [[nodiscard]] auto OutputDirections() const noexcept -> DirectionFlagSet override;
  auto             powered(NodeSet& visited_nodes) const noexcept -> bool override;

 public:
  using Node::Node;
};

#endif
