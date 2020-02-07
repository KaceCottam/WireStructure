#ifndef VEC2D_H
#define VEC2D_H
#include <utility>
#include <functional>
template<class T>
class Vec2D {
  using base = std::pair<T, T>;
  base pair;

 public:
  template<class... Args>
  Vec2D(Args&&... args) : pair{std::forward<Args>(args)...} {}

  T& x = pair.first;
  T& y = pair.second;

  friend inline auto operator+(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> Vec2D<T> { return {a.x + b.x, a.y + b.y}; }
  friend inline auto operator-(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> Vec2D<T> { return a + (-1)*b; }
  friend inline auto operator*(const int scal, const Vec2D<T>& a) noexcept
    -> Vec2D<T> { return mapIt([&scal](T a){return scal * a;}, a); }
  friend inline auto operator*(const Vec2D<T>& a, const int scal) noexcept
    -> Vec2D<T> { return scal * a; }
  friend inline auto magnitude(const Vec2D<T>& a) noexcept
    -> double {
      return sqrt(foldIt(std::plus<double>{},
        mapIt([](double a){return a * a;},
            mapIt([](T a){return (double)a;}, a))));
    }
  friend inline auto normal(const Vec2D<T>& a) noexcept
    -> Vec2D<double> {
      return mapIt([mag = magnitude(a)](double a){return a / mag;},
          mapIt([](T a){return (double)a;}, a));
    }

  template<class Callable>
  friend inline auto mapIt(Callable&& fn, const Vec2D<T>& a) noexcept
    -> Vec2D<decltype(fn(a.x))> { return {fn(a.x), fn(a.y)}; }
  template<class Callable>
  friend inline auto foldIt(Callable&& fn, const Vec2D<T>& a) noexcept
    -> decltype(fn(a.x, a.y)) { return fn(a.x, a.y); }

  friend inline auto operator==(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> bool { return foldIt(std::logical_and{}, a <= b); }
  friend inline auto operator!=(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> bool { return !(a == b); }
  friend inline auto operator<(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> Vec2D<bool> { return {a.x < b.x, a.y < b.y}; }
  friend inline auto operator>(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> Vec2D<bool> { return {a.x > b.x, a.y > b.y}; }
  friend inline auto operator<=(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> Vec2D<bool> { return mapIt(std::logical_not{}, a > b); }
  friend inline auto operator>=(const Vec2D<T>& a, const Vec2D<T>& b) noexcept
    -> Vec2D<bool> { return mapIt(std::logical_not{}, a < b); }
};
#endif // ! VEC2D_H
