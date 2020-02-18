#include "Gates.h"

#include <future>

auto And::OutputDirections() const noexcept -> DirectionFlagSet { return E; }

auto And::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) == numberConnected();
}

auto Input::OutputDirections() const noexcept -> DirectionFlagSet
{
  return NW | N | NE | W | E | SW | S | SE;
}

auto Input::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  if (visited_nodes.count(this) >= 1) { return false; }
  safeAddToSet(visited_nodes, this);
  return activated;
}

void Input::on() noexcept { activated = true; }
void Input::off() noexcept { activated = false; }
void Input::toggle() noexcept { activated = !activated; }

auto Output::OutputDirections() const noexcept -> DirectionFlagSet { return 0; }
auto Output::query() const noexcept -> bool { return Node::powered(); }

auto Nand::OutputDirections() const noexcept -> DirectionFlagSet { return E; }

auto Nand::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) != numberConnected();
}

auto Node::isOutputtingInDirection(DirectionFlags dir) const noexcept -> bool
{
  auto newDirection = toIndex(dir) - rotation;
  auto newFlag      = toDirectionFlags(newDirection);
  return (OutputDirections() & newFlag) == newFlag;
}

auto Node::rotate45ccw() noexcept -> void
{
  rotation = (rotation + 1) % 8;
  // need to reconnect
  pointers.w  = nullptr;
  pointers.nw = nullptr;
  pointers.e  = nullptr;
  pointers.sw = nullptr;
  pointers.ne = nullptr;
  pointers.e  = nullptr;
  pointers.se = nullptr;
  pointers.s  = nullptr;
}

auto Node::numberConnected() const noexcept -> unsigned
{
  auto sum = 0U;
  if (pointers.nw != nullptr) { sum++; }
  if (pointers.n != nullptr) { sum++; }
  if (pointers.ne != nullptr) { sum++; }
  if (pointers.w != nullptr) { sum++; }
  if (pointers.e != nullptr) { sum++; }
  if (pointers.sw != nullptr) { sum++; }
  if (pointers.s != nullptr) { sum++; }
  if (pointers.se != nullptr) { sum++; }
  return sum;
}

auto Node::powered() const noexcept -> bool
{
  NodeSet ns{};
  return powered(ns);
}

auto Node::numberPowered(NodeSet& visited_nodes) const noexcept -> unsigned
{
  if (visited_nodes.count(this) >= 1) { return 0; }

  unsigned sum = 0;
  safeAddToSet(visited_nodes, this);

  auto makeIsPoweredFunction = [&visited_nodes](const NodePtr ptr) {
    return [ptr, &visited_nodes] { return ptr->powered(visited_nodes); };
  };

  std::future<bool> nwPowered;
  std::future<bool> nPowered;
  std::future<bool> nePowered;
  std::future<bool> wPowered;
  std::future<bool> ePowered;
  std::future<bool> swPowered;
  std::future<bool> sPowered;
  std::future<bool> sePowered;

  if (pointers.nw != nullptr)
    { nwPowered = std::async(makeIsPoweredFunction(pointers.nw)); }
  if (pointers.n != nullptr)
    { nPowered = std::async(makeIsPoweredFunction(pointers.n)); }
  if (pointers.ne != nullptr)
    { nePowered = std::async(makeIsPoweredFunction(pointers.ne)); }
  if (pointers.w != nullptr)
    { wPowered = std::async(makeIsPoweredFunction(pointers.w)); }
  if (pointers.e != nullptr)
    { ePowered = std::async(makeIsPoweredFunction(pointers.e)); }
  if (pointers.sw != nullptr)
    { swPowered = std::async(makeIsPoweredFunction(pointers.sw)); }
  if (pointers.s != nullptr)
    { sPowered = std::async(makeIsPoweredFunction(pointers.s)); }
  if (pointers.se != nullptr)
    { sePowered = std::async(makeIsPoweredFunction(pointers.se)); }

  if (nwPowered.valid() && nwPowered.get()) { sum++; }
  if (nPowered.valid() && nPowered.get()) { sum++; }
  if (nePowered.valid() && nePowered.get()) { sum++; }
  if (wPowered.valid() && wPowered.get()) { sum++; }
  if (ePowered.valid() && ePowered.get()) { sum++; }
  if (swPowered.valid() && swPowered.get()) { sum++; }
  if (sPowered.valid() && sPowered.get()) { sum++; }
  if (sePowered.valid() && sePowered.get()) { sum++; }

  return sum;
}

auto Node::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) >= 1;
}

Node::Node(const Position& position) noexcept
    : pos{position}
{
}

auto connect(Node& a, Node& b) noexcept -> bool
{
  auto result       = false;
  auto relative_pos = a.pos - b.pos;
  if (relative_pos != Position{0, 0}
      && magnitude(relative_pos) <= magnitude(Position{1, 1}))
    {
      if (relative_pos.x == -1 || relative_pos == Position{0, -1})
        { return connect(b, a); }

      if (relative_pos == Position{0, 1})
        {
          if (b.pointers.n != &a && a.isOutputtingInDirection(S))
            {
              b.pointers.n = &a;
              result       = true;
            }
          if (a.pointers.s != &b && b.isOutputtingInDirection(N))
            {
              a.pointers.s = &b;
              result       = true;
            }
        }
      else if (relative_pos == Position{1, 1})
        {
          if (b.pointers.ne != &a && a.isOutputtingInDirection(SW))
            {
              b.pointers.ne = &a;
              result        = true;
            }
          if (a.pointers.sw != &b && b.isOutputtingInDirection(NE))
            {
              a.pointers.sw = &b;
              result        = true;
            }
        }
      else if (relative_pos == Position{1, 0})
        {
          if (b.pointers.e != &a && a.isOutputtingInDirection(W))
            {
              b.pointers.e = &a;
              result       = true;
            }
          if (a.pointers.w != &b && b.isOutputtingInDirection(E))
            {
              a.pointers.w = &b;
              result       = true;
            }
        }
      else if (relative_pos == Position{1, -1})
        {
          if (b.pointers.se != &a && a.isOutputtingInDirection(NW))
            {
              b.pointers.se = &a;
              result        = true;
            }
          if (a.pointers.nw != &b && b.isOutputtingInDirection(SE))
            {
              a.pointers.nw = &b;
              result        = true;
            }
        }
    }
  return result;
}

auto disconnect(Node& a, Node& b) noexcept -> bool
{
  auto result       = false;
  auto relative_pos = a.pos - b.pos;
  if (relative_pos != Position{0, 0}
      && magnitude(relative_pos) <= magnitude(Position{1, 1}))
    {
      if (relative_pos.x == -1 || relative_pos == Position{0, -1})
        { return disconnect(b, a); }

      if (relative_pos == Position{0, 1})
        {
          if (b.pointers.n != nullptr && a.isOutputtingInDirection(S))
            {
              b.pointers.n = nullptr;
              result       = true;
            }
          if (a.pointers.s != nullptr && b.isOutputtingInDirection(N))
            {
              a.pointers.s = nullptr;
              result       = true;
            }
        }
      else if (relative_pos == Position{1, 1})
        {
          if (b.pointers.ne != nullptr && a.isOutputtingInDirection(SW))
            {
              b.pointers.ne = nullptr;
              result        = true;
            }
          if (a.pointers.sw != nullptr && b.isOutputtingInDirection(NE))
            {
              a.pointers.sw = nullptr;
              result        = true;
            }
        }
      else if (relative_pos == Position{1, 0})
        {
          if (b.pointers.e != nullptr && a.isOutputtingInDirection(W))
            {
              b.pointers.e = nullptr;
              result       = true;
            }
          if (a.pointers.w != nullptr && b.isOutputtingInDirection(E))
            {
              a.pointers.w = nullptr;
              result       = true;
            }
        }
      else if (relative_pos == Position{1, -1})
        {
          if (b.pointers.se != nullptr && a.isOutputtingInDirection(NW))
            {
              b.pointers.se = nullptr;
              result        = true;
            }
          if (a.pointers.nw != nullptr && b.isOutputtingInDirection(SE))
            {
              a.pointers.nw = nullptr;
              result        = true;
            }
        }
    }
  return result;
}

template<class NodeSet>
auto safeAddToSet(NodeSet& set, typename NodeSet::key_type added) noexcept
    -> void
{
  static std::mutex mux;
  std::lock_guard   guard(mux);
  set.emplace(added);
}
inline auto toDirectionFlags(const unsigned i) -> DirectionFlags
{
  return DirectionFlags(1 << i);
}
auto toIndex(const DirectionFlags& i) -> unsigned
{
  switch (i)
    {
    case E: return 0;
    case NE: return 1;
    case N: return 2;
    case NW: return 3;
    case W: return 4;
    case SW: return 5;
    case S: return 6;
    case SE: return 7;
    }
  throw i;
}

auto Nor::OutputDirections() const noexcept -> DirectionFlagSet { return E; }

auto Nor::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) < 1;
}

auto Not::OutputDirections() const noexcept -> DirectionFlagSet { return E; }

auto Not::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return !Node::powered(visited_nodes);
}
auto Or::OutputDirections() const noexcept -> DirectionFlagSet { return E; }
auto Or::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) >= 1;
}

auto Wire::OutputDirections() const noexcept -> DirectionFlagSet
{
  return NW | N | NE | W | E | SW | S | SE;
}

auto Xnor::OutputDirections() const noexcept -> DirectionFlagSet { return E; }

auto Xnor::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) != 1;
}

auto Xor::OutputDirections() const noexcept -> DirectionFlagSet { return E; }

auto Xor::powered(NodeSet& visited_nodes) const noexcept -> bool
{
  return numberPowered(visited_nodes) == 1;
}
