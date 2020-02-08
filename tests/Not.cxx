#include <catch.hpp>

#include <Not.h>
#include <Lever.h>
#include <OutputReader.h>
#include <Wire.h>

TEST_CASE("Wires can be flipped with not gates") {
  Lever l = Lever("Input", Position{-1,0});
  Not n = Not({0,0});
  OutputReader r = OutputReader("Output", Position{1,0});
  REQUIRE(connect(l, n) == true);
  REQUIRE(connect(n, r) == true);
  REQUIRE(r.query() == true);
  l.on();
  REQUIRE(r.query() == false);
  l.off();
  REQUIRE(r.query() == true);
}
