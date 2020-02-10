#include <catch.hpp>

#include <Input.h>
#include <Output.h>
#include <Wire.h>

TEST_CASE("Wires can be connected if they are adjacent") {
  Wire wire1 = Wire({0,0});
  Wire wire2 = Wire({0,1});
  REQUIRE(connect(wire1, wire2) == true);

  SECTION("Wires in the same spot can not be connected") {
    Wire wire1Copy = Wire({0,0});
    REQUIRE(connect(wire1, wire1Copy) == false);
  }
  SECTION("Testing circular connections") {
    Wire wire3 = Wire({1,0});
    REQUIRE(connect(wire1, wire3) == true);
    REQUIRE(connect(wire2, wire3) == true);
  }
}
TEST_CASE("Wires can be disconnected if they are connected") {
  Wire wire1 = Wire({0,0});
  Wire wire2 = Wire({0,1});
  REQUIRE(disconnect(wire1, wire2) == false);
  REQUIRE(connect(wire1, wire2) == true);

  REQUIRE(disconnect(wire1, wire2) == true);
}
TEST_CASE("Wires cannot be connected if they are not adjacent") {
  Wire wire1 = Wire({0,-1});
  Wire wire2 = Wire({0, 1});
  REQUIRE(connect(wire1, wire2) == false);
}
TEST_CASE("Functions can be dispatched through connected wires") {
  Input lever = Input("Input", Position{-1, 0});
  Wire wires[] =
    { Wire({0, 0}),
      Wire({1, 0}),
      Wire({0,-1}) };
  Output ors[] =
    { Output("0", Position{0, 1}),
      Output("1", Position{1, 1}),
      Output("2", Position{1,-1}) };

  REQUIRE(connect(lever, wires[0]) == true);
  for(auto i = 0; i < 3; i++) {
    REQUIRE(connect(wires[i], ors[i]) == true);
  }

  REQUIRE(ors[0].query() == false);
  lever.on();
  REQUIRE(ors[0].query() == true);

  REQUIRE(connect(wires[0],wires[1]) == true);
  REQUIRE(ors[0].query() == true);
  REQUIRE(ors[1].query() == true);
  REQUIRE(ors[2].query() == false);
  lever.off();
  REQUIRE(ors[0].query() == false);
  REQUIRE(ors[1].query() == false);
  REQUIRE(ors[2].query() == false);

  REQUIRE(connect(wires[1], wires[2]) == true);
  REQUIRE(ors[0].query() == false);
  REQUIRE(ors[1].query() == false);
  REQUIRE(ors[2].query() == false);
  lever.toggle();
  REQUIRE(ors[0].query() == true);
  REQUIRE(ors[1].query() == true);
  REQUIRE(ors[2].query() == true);
  
  SECTION("Testing circular connections") {
    REQUIRE(connect(wires[0], wires[2]) == true);

    REQUIRE(ors[0].query() == true);
    REQUIRE(ors[1].query() == true);
    REQUIRE(ors[2].query() == true);

    lever.toggle();
    REQUIRE(ors[0].query() == false);
    REQUIRE(ors[1].query() == false);
    REQUIRE(ors[2].query() == false);
  }
  SECTION("Trying to connect to a wire that is already connected is impossible") {
    REQUIRE(connect(wires[1], wires[2]) == false);
  }
}
TEST_CASE("Templated connect/disconnect") {
  Wire w1(Position{0,0}), w2(Position{0,1}), w3(Position{0,2}),
       w4(Position{0,3}), w5(Position{0,4}), w6(Position{0,5}),
       w7(Position{0,6}), w8(Position{0,7}), w9(Position{0,8}),
       w10(Position{0,9}), w11(Position{0,10});

  w2.rotate45ccw();

  REQUIRE(connect(w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11) == true);
  REQUIRE(disconnect(w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11) == true);
}
