//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <Vec2D.h>
TEST_CASE("Vec2D can be created") {
  int x = GENERATE(123456789,87654334568,6432432,2141325,75,-123512,-32143214);
  int y = GENERATE(123456789,87654334568,6432432,2141325,75,-123512,-32143214);

  SECTION("Using a position vector") {
    Vec2D position = Vec2D(x,y);
    REQUIRE(position.x == x);
    REQUIRE(position.y == y);
  }
}
TEST_CASE("Vec2D can be compared") {
  auto bigger = GENERATE(chunk(2,values({1000,1001,1002,1003})));
  auto smaller = GENERATE(chunk(2,values({-1000,-1001,-1002,-1003})));
  Vec2D v1 = Vec2D(bigger[0], bigger[1]);
  Vec2D v2 = Vec2D(smaller[0], smaller[1]);
  
  REQUIRE(v1 > v2);
  REQUIRE(v1 >= v2);
  REQUIRE(v2 < v1);
  REQUIRE(v2 <= v1);
  REQUIRE(v2 != v1);
  REQUIRE(v1 == v1);
  REQUIRE(v2 == v2);
}
