#include <catch.hpp>

#include <Wire.h>

TEST_CASE("Wires can be created") {
  Wire wire = Wire({0,0});
  REQUIRE(wire.pos == Vec2D{0,0});
  REQUIRE(wire.nw == nullptr);
  REQUIRE(wire.n  == nullptr);
  REQUIRE(wire.ne == nullptr);
  REQUIRE(wire.w  == nullptr);
  REQUIRE(wire.e  == nullptr);
  REQUIRE(wire.sw == nullptr);
  REQUIRE(wire.s  == nullptr);
  REQUIRE(wire.se == nullptr);
  REQUIRE(wire.powered == false);
}
TEST_CASE("Wires can be connected if they are adjacent") {
  Wire wire1 = Wire({0,0});
  Wire wire2 = Wire({0,1});
  auto valid = connect(wire1, wire2);
  REQUIRE(valid == true);
  REQUIRE(wire1.nw == nullptr);
  REQUIRE(wire1.n  == &wire2);
  REQUIRE(wire1.ne == nullptr);
  REQUIRE(wire1.w  == nullptr);
  REQUIRE(wire1.e  == nullptr);
  REQUIRE(wire1.sw == nullptr);
  REQUIRE(wire1.s  == nullptr);
  REQUIRE(wire1.se == nullptr);
  REQUIRE(wire2.nw == nullptr);
  REQUIRE(wire2.n  == nullptr);
  REQUIRE(wire2.ne == nullptr);
  REQUIRE(wire2.w  == nullptr);
  REQUIRE(wire2.e  == nullptr);
  REQUIRE(wire2.sw == nullptr);
  REQUIRE(wire2.s  == &wire1);
  REQUIRE(wire2.se == nullptr);
}
TEST_CASE("Wires cannot be connected if they are not adjacent") {
  Wire wire1 = Wire({-1,0});
  Wire wire2 = Wire({1,0});
  auto valid = connect(wire1, wire2);
  REQUIRE(valid == false);
  REQUIRE(wire1.nw == nullptr);
  REQUIRE(wire1.n  == nullptr);
  REQUIRE(wire1.ne == nullptr);
  REQUIRE(wire1.w  == nullptr);
  REQUIRE(wire1.e  == nullptr);
  REQUIRE(wire1.sw == nullptr);
  REQUIRE(wire1.s  == nullptr);
  REQUIRE(wire1.se == nullptr);
  REQUIRE(wire2.nw == nullptr);
  REQUIRE(wire2.n  == nullptr);
  REQUIRE(wire2.ne == nullptr);
  REQUIRE(wire2.w  == nullptr);
  REQUIRE(wire2.e  == nullptr);
  REQUIRE(wire2.sw == nullptr);
  REQUIRE(wire2.s  == nullptr);
  REQUIRE(wire2.se == nullptr);
}
