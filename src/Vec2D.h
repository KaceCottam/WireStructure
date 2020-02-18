#ifndef VEC2D_H
#define VEC2D_H
#include <cmath>
#include <utility>

template<class T>
struct Vec2D
{
  Vec2D(const T x, const T y)
      : x{x}
      , y{y}
  {
  }

  T x, y;

  template<class Callable>
  friend inline auto mapIt(Callable&& fn, const Vec2D<T>& a) noexcept
      -> Vec2D<decltype(fn(T{}))>
  {
    return {fn(a.x), fn(a.y)};
  }
  template<class Callable>
  friend inline auto foldIt(Callable&& fn, const Vec2D<T>& a) noexcept
      -> decltype(fn(T{}, T{}))
  {
    return fn(a.x, a.y);
  }

  friend inline auto operator+(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> Vec2D<T>
  {
    return {a.x + b.x, a.y + b.y};
  }
  friend inline auto operator-(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> Vec2D<T>
  {
    return {a.x - b.x, a.y - b.y};
  }
  friend inline auto operator*(const int scal, const Vec2D<T>& a) noexcept
      -> Vec2D<T>
  {
    return {a.x * scal, a.y * scal};
  }
  friend inline auto operator*(const Vec2D<T>& a, const int scal) noexcept
      -> Vec2D<T>
  {
    return scal * a;
  }
  friend inline auto magnitude(const Vec2D<T>& a) noexcept -> double
  {
    return sqrt(static_cast<double>(a.x * a.x + a.y * a.y));
  }

  friend inline auto operator==(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> bool
  {
    return a.x == b.x && a.y == b.y;
  }
  friend inline auto operator!=(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> bool
  {
    return !(a == b);
  }
  friend inline auto operator<(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> Vec2D<bool>
  {
    return {a.x < b.x, a.y < b.y};
  }
  friend inline auto operator>(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> Vec2D<bool>
  {
    return {a.x > b.x, a.y > b.y};
  }
  friend inline auto operator<=(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> Vec2D<bool>
  {
    return mapIt([](bool a) { return !a; }, a > b);
  }
  friend inline auto operator>=(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
      -> Vec2D<bool>
  {
    return mapIt([](bool a) { return !a; }, a < b);
  }
};
inline auto closestPoint(const Vec2D<double>& a) noexcept -> Vec2D<int>
{
  return mapIt([](auto a) { return (int) round(a); }, a);
}
using Position  = Vec2D<int>;
using Magnitude = Vec2D<double>;

#endif  // ! VEC2D_H
