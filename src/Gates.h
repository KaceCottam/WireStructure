#include <unordered_set>

#include "Vec2D.h"

using std::unordered_set;
using DirectionFlagSet = unsigned char;

enum DirectionFlags : DirectionFlagSet {
  E  = 1 << 0,
  NE = 1 << 1,
  N  = 1 << 2,
  NW = 1 << 3,
  W  = 1 << 4,
  SW = 1 << 5,
  S  = 1 << 6,
  SE = 1 << 7
};
unsigned toIndex(const DirectionFlags& i);
inline DirectionFlags toDirectionFlags(const unsigned i);

template<class NodeSet>
auto safeAddToSet(NodeSet& set, typename NodeSet::key_type added) noexcept -> void;

class Node {
 protected:
  using NodePtr = const Node*;
  using NodeSet = unordered_set<NodePtr>;

  virtual DirectionFlagSet OutputDirections() const noexcept = 0;
  bool isOutputtingInDirection(DirectionFlags dir) const noexcept;

  // input node ptrs
  struct {
    NodePtr nw{nullptr}, n{nullptr}, ne{nullptr},
             w{nullptr},              e{nullptr},
            sw{nullptr}, s{nullptr}, se{nullptr};
  } pointers;

  unsigned rotation = 0;
  const Position pos;

 public:
  explicit Node(const Position& position = {0,0}) noexcept;

  void rotate45ccw() noexcept;
  auto numberConnected() const noexcept -> unsigned;
  auto numberPowered(NodeSet& visited_nodes) const noexcept -> unsigned;
  auto powered() const noexcept -> bool;
  virtual auto powered(NodeSet& visited_nodes) const noexcept -> bool;

  friend auto connect(Node& a, Node& b) noexcept -> bool;
  friend auto disconnect(Node& a, Node& b) noexcept -> bool;


  virtual ~Node() noexcept = default;
};

class And : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};

class Input : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool activated = false;

  bool powered(NodeSet& visited_nodes) const noexcept override;

  const DirectionFlags inputDir;
 public:
  template<class... Args>
  explicit Input(const DirectionFlags inputDir, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), inputDir{inputDir} {}

  void on() noexcept;
  void off() noexcept;
  void toggle() noexcept;
};

class Output : public Node {
 protected:
  DirectionFlags outputDir;
  DirectionFlagSet OutputDirections() const noexcept override;
 public:
  template<class... Args>
  explicit Output(const DirectionFlags outputDir, Args&&... args) noexcept
    : Node(std::forward<Args>(args)...), outputDir{outputDir} {}

  bool query() const noexcept;

};

class Nand : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};


class Nor : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};

class Not : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};

class Or : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};

class Wire : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;

 public:
  using Node::Node;
};

class Xnor : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};

class Xor : public Node {
 protected:
  DirectionFlagSet OutputDirections() const noexcept override;
  bool powered(NodeSet& visited_nodes) const noexcept override;

 public:
  using Node::Node;
};
