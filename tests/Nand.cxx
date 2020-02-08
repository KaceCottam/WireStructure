#include <catch.hpp>

#include <Nand.h>
#include <Lever.h>
#include <OutputReader.h>

TEST_CASE("And statements work") {
  Nand a = Nand({0, 0});
  Lever l1 = Lever("Top", Position{0, 1});
  Lever l2 = Lever("Bottom", Position{0,-1});
  OutputReader r = OutputReader("Output", Position{1, 0});
  REQUIRE(connect(a, l1) == true);
  REQUIRE(connect(a, l2) == true);
  REQUIRE(connect(a, r) == true);

  REQUIRE(r.query() == true);
  l1.on();
  REQUIRE(r.query() == true);
  l1.off();
  l2.on();
  REQUIRE(r.query() == true);
  l1.on();
  REQUIRE(r.query() == false);
}
