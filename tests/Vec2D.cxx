//#define CATCH_CONFIG_MAIN
#include <Vec2D.h>

#include <catch.hpp>
TEST_CASE("Vec2D can be created")
{
  int x = GENERATE(
      123456789, 87654334568, 6432432, 2141325, 75, -123512, -32143214);
  int y = GENERATE(
      123456789, 87654334568, 6432432, 2141325, 75, -123512, -32143214);

  SECTION("Using a pair of points")
  {
    auto vec = Vec2D(x, y);
    REQUIRE(vec.x == x);
    REQUIRE(vec.y == y);
  }
  SECTION("Using an initializer list")
  {
    auto vec = Vec2D({x, y});
    REQUIRE(vec.x == x);
    REQUIRE(vec.y == y);
  }
}
TEST_CASE("Vec2D can be compared")
{
  auto  bigger  = GENERATE(chunk(2, values({1000, 1001, 1002, 1003})));
  auto  smaller = GENERATE(chunk(2, values({10, 11, 12, 13})));
  Vec2D v1      = Vec2D(bigger);
  Vec2D v2      = Vec2D(smaller);

  REQUIRE(v1 > v2);
  REQUIRE(v1 >= v2);
  REQUIRE(v2 < v1);
  REQUIRE(v2 <= v1);
  REQUIRE(v1 != v2);
  REQUIRE(v2 != v1);
  REQUIRE(v1 == v1);
  REQUIRE(v1 <= v1);
  REQUIRE(v1 >= v1);
  REQUIRE(v2 == v2);
  REQUIRE(v2 <= v2);
  REQUIRE(v2 >= v2);
}
TEST_CASE("Vec2D can be operated upon mathematically")
{
  int x = GENERATE(
      123456789, 87654334568, 6432432, 2141325, 75, -123512, -32143214);
  int y = GENERATE(
      123456789, 87654334568, 6432432, 2141325, 75, -123512, -32143214);
  Vec2D v1 = Vec2D(x, y);
  REQUIRE(v1 + Vec2D{0, 0} == v1);
  REQUIRE(v1 + Vec2D{1, 0} == Vec2D{x + 1, y});
  REQUIRE(v1 + Vec2D{1, -1} == Vec2D{x + 1, y - 1});
  REQUIRE(v1 * 1 == v1);
  REQUIRE(1 * v1 == v1);
  REQUIRE(v1 * 0 == Vec2D{0, 0});
  REQUIRE(0 * v1 == Vec2D{0, 0});
  REQUIRE(v1 - Vec2D{1, -1} == Vec2D{x - 1, y + 1});
  REQUIRE(Vec2D{1, -1} - v1 == Vec2D{1 - x, -1 - y});
  REQUIRE(abs(v1) == Vec2D{abs(x), abs(y)});
}
