#include <catch.hpp>

#include <Xor.h>
#include <Input.h>
#include <Output.h>

TEST_CASE("Xor statements work") {
  Xor a = Xor({0, 0});
  Input l1 = Input(N, Position{0, 1});
  Input l2 = Input(W, Position{-1,0});
  Input l3 = Input(S, Position{0,-1});
  Output r = Output(E, Position{1, 0});
  REQUIRE(connect(a, l1) == true);
  REQUIRE(connect(a, l2) == true);
  REQUIRE(connect(a, l3) == true);
  REQUIRE(connect(a, r) == true);

  REQUIRE(r.query() == false);
  l1.on();
  REQUIRE(r.query() == true);
  l1.off();
  l2.on();
  REQUIRE(r.query() == true);
  l1.on();
  REQUIRE(r.query() == false);
}
