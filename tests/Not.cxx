#include <catch.hpp>

#include <Not.h>
#include <Input.h>
#include <Output.h>
#include <Wire.h>

TEST_CASE("Wires can be flipped with not gates") {
  Input l = Input("Input", Position{-1,0});
  Not n = Not({0,0});
  Output r = Output("Output", Position{1,0});
  REQUIRE(connect(l, n) == true);
  REQUIRE(connect(n, r) == true);
  REQUIRE(r.query() == true);
  l.on();
  REQUIRE(r.query() == false);
  l.off();
  REQUIRE(r.query() == true);
}
