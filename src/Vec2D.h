#ifndef VEC2D_H
#define VEC2D_H
struct Vec2D
{
  Vec2D(int x = 0, int y = 0)
      : x{x} , y{y} { }

  int x, y;

  [[nodiscard]] friend Vec2D operator+(const Vec2D& a, const Vec2D& b) noexcept
  {
    return Vec2D(a.x + b.x, a.y + b.y);
  }
  [[nodiscard]] friend Vec2D operator-(const Vec2D& a, const Vec2D& b) noexcept
  {
    return a + (-1 * b);
  }
  [[nodiscard]] friend Vec2D operator*(const Vec2D& a, const int scal) noexcept
  {
    return Vec2D(a.x * scal, a.y * scal);
  }
  [[nodiscard]] friend Vec2D operator*(const int scal, const Vec2D& a) noexcept
  {
    return a * scal;
  }

  [[nodiscard]] friend bool operator==(const Vec2D& a, const Vec2D& b) noexcept
  {
    return a.x == b.x && a.y == b.y;
  }
  [[nodiscard]] friend bool operator<(const Vec2D& a, const Vec2D& b) noexcept
  {
    return a.x < b.x && a.y < b.y;
  }
  [[nodiscard]] friend bool operator>(const Vec2D& a, const Vec2D& b) noexcept
  {
    return a.x > b.x && a.y > b.y;
  }
  [[nodiscard]] friend bool operator<=(const Vec2D& a, const Vec2D& b) noexcept
  {
    return a < b || a == b;
  }
  [[nodiscard]] friend bool operator>=(const Vec2D& a, const Vec2D& b) noexcept
  {
    return a > b || a == b;
  }
  [[nodiscard]] friend bool operator!=(const Vec2D& a, const Vec2D& b) noexcept
  {
    return !(a == b);
  }
  [[nodiscard]] friend Vec2D abs(const Vec2D& a) noexcept
  {
    const auto bx = a.x < 0 ? -1 * a.x : a.x;
    const auto by = a.y < 0 ? -1 * a.y : a.y;
    return Vec2D(bx, by);
  }
};

#endif  // ! VEC2D_H
