#include <catch.hpp>

#include <Not.h>
#include <Lever.h>

TEST_CASE("Not gates can be made") {
  Not not_gate = Not(Vec2D{0,0});
  REQUIRE(not_gate.powered() == true);
}
TEST_CASE("Not gates output the opposite of what they recieve") {
  Not not_gate = Not(Vec2D{0,0});
  Lever lever = Lever(Vec2D{0,1});
  REQUIRE(connect(not_gate, lever) == true);
  REQUIRE(not_gate.powered() == true);
  lever.on();
  REQUIRE(not_gate.powered() == false);
  REQUIRE(lever.powered() == true);
}
TEST_CASE("Multiple not gates also work") {
  Not not_gate1 = Not(Vec2D{-1,0});
  Not not_gate2 = Not(Vec2D{0,0});
  Lever lever = Lever(Vec2D{1,0});
  REQUIRE(connect(not_gate1, not_gate2) == true);
  REQUIRE(connect(not_gate2, lever) == true);
  REQUIRE(not_gate1.powered() == false);
  lever.on();
  REQUIRE(not_gate1.powered() == true);
}
