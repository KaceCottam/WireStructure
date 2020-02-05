//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <Vec2D.h>
TEST_CASE("Vec2D can be created") {
  int x = GENERATE(123456789,87654334568,6432432,2141325,75,-123512,-32143214);
  int y = GENERATE(123456789,87654334568,6432432,2141325,75,-123512,-32143214);

  SECTION("Using a pair of points") {
    Vec2D position = Vec2D(x,y);
    REQUIRE(position.x == x);
    REQUIRE(position.y == y);
  }
  SECTION("Using a std vector") {
    Vec2D position = Vec2D(std::vector(x, y));
    REQUIRE(position.x == x);
    REQUIRE(position.y == y);
  }
  SECTION("Using a size 2 array") {
    int array[2];
    array[0] = x;
    array[1] = y;
    Vec2D position = Vec2D(array);
    REQUIRE(position.x == x);
    REQUIRE(position.y == y);
  }
}
TEST_CASE("Vec2D can be compared") {
  auto bigger = GENERATE(chunk(2,values({1000,1001,1002,1003})));
  auto smaller = GENERATE(chunk(2,values({-1000,-1001,-1002,-1003})));
  Vec2D v1 = Vec2D(bigger);
  Vec2D v2 = Vec2D(smaller);
  
  REQUIRE(v1 > v2);
  REQUIRE(v1 >= v2);
  REQUIRE(v2 < v1);
  REQUIRE(v2 <= v1);
  REQUIRE(v2 != v1);
  REQUIRE(v1 == v1);
  REQUIRE(v2 == v2);
}
TEST_CASE("Vec2D can be operated upon mathematically") {
  int x = GENERATE(123456789,87654334568,6432432,2141325,75,-123512,-32143214);
  int y = GENERATE(123456789,87654334568,6432432,2141325,75,-123512,-32143214);
  Vec2D v1 = Vec2D(x, y);
  REQUIRE(v1 + Vec2D{0,0} == v1);
  REQUIRE(v1 + Vec2D{1,0} == Vec2D{x + 1, y});
  REQUIRE(v1 + Vec2D{1,-1} == Vec2D{x + 1, y - 1});
  REQUIRE(v1 * 1 == v1);
  REQUIRE(1 * v1 == v1);
  REQUIRE(v1 * 0 == Vec2D{0,0});
  REQUIRE(0 * v1 == Vec2D{0,0});
  REQUIRE(v1 - Vec2D{1,-1} == Vec2D{x - 1, y + 1});
  REQUIRE(Vec2D{1,-1} - v1 == Vec2D{1 - x, -1 - y});
  REQUIRE(abs(v1) == Vec2D{abs(x), abs(y)});
}
