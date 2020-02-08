#include <catch.hpp>

#include <Not.h>
#include <Lever.h>
#include <OutputReader.h>
#include <Wire.h>

TEST_CASE("Wires can be flipped with not gates") {
  Lever l = Lever("Input", Position{0,0});
  Not n = Not({1,0});
  Wire w = Wire({2,0});
  OutputReader r = OutputReader("Output", Position{3,0});
  REQUIRE(connect(l, n) == true);
  REQUIRE(connect(n, w) == true);
  REQUIRE(connect(w, r) == true);
  REQUIRE(r.query() == true);
  l.on();
  REQUIRE(r.query() == false);
  l.off();
  REQUIRE(r.query() == true);
}
