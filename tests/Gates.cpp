#include <catch.hpp>

#include <Gates.h>

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
  Input lever = Input(W, Position{-1, 0});
  Wire wires[] =
    { Wire({0, 0}),
      Wire({1, 0}),
      Wire({0,-1}) };
  Output ors[] =
    { Output(E, Position{0, 1}),
      Output(N, Position{1, 1}),
      Output(S, Position{1,-1}) };

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

TEST_CASE("Wires can be flipped with not gates") {
  Input l = Input(W, Position{-1,0});
  Not n = Not({0,0});
  Output r = Output(E, Position{1,0});
  REQUIRE(connect(l, n) == true);
  REQUIRE(connect(n, r) == true);
  REQUIRE(r.query() == true);
  l.on();
  REQUIRE(r.query() == false);
  l.off();
  REQUIRE(r.query() == true);
}

TEST_CASE("not gates can be rotated") {
  Input l = Input(W, Position{0,-1});
  Not n = Not({0,0});
  Output r = Output(E, Position{0,1});
  n.rotate45ccw();
  n.rotate45ccw();
  REQUIRE(connect(l, n) == true);
  REQUIRE(connect(n, r) == true);
  REQUIRE(r.query() == true);
  l.on();
  REQUIRE(r.query() == false);
  l.off();
  REQUIRE(r.query() == true);
}

TEST_CASE("And statements work") {
  And a = And({0, 0});
  Input l1 = Input(N, Position{0, 1});
  Input l2 = Input(S, Position{0,-1});
  Output r = Output(E, Position{1, 0});
  REQUIRE(connect(a, l1) == true);
  REQUIRE(connect(a, l2) == true);
  REQUIRE(connect(a, r) == true);

  REQUIRE(r.query() == false);
  l1.on();
  REQUIRE(r.query() == false);
  l1.off();
  l2.on();
  REQUIRE(r.query() == false);
  l1.on();
  REQUIRE(r.query() == true);
}

TEST_CASE("Or statements work") {
  Or a = Or({0, 0});
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
  REQUIRE(r.query() == true);
}

TEST_CASE("Nor statements work") {
  Nor a = Nor({0, 0});
  Input l1 = Input(N, Position{0, 1});
  Input l2 = Input(W, Position{-1,0});
  Input l3 = Input(S, Position{0,-1});
  Output r = Output(E, Position{1, 0});
  REQUIRE(connect(a, l1) == true);
  REQUIRE(connect(a, l2) == true);
  REQUIRE(connect(a, l3) == true);
  REQUIRE(connect(a, r) == true);

  REQUIRE(r.query() == true);
  l1.on();
  REQUIRE(r.query() == false);
  l1.off();
  l2.on();
  REQUIRE(r.query() == false);
  l1.on();
  REQUIRE(r.query() == false);
}

TEST_CASE("Xnor statements work") {
  Xnor a = Xnor({0, 0});
  Input l1 = Input(N, Position{0, 1});
  Input l2 = Input(W, Position{-1,0});
  Input l3 = Input(S, Position{0,-1});
  Output r = Output(E, Position{1, 0});
  REQUIRE(connect(a, l1) == true);
  REQUIRE(connect(a, l2) == true);
  REQUIRE(connect(a, l3) == true);
  REQUIRE(connect(a, r) == true);

  REQUIRE(r.query() == true);
  l1.on();
  REQUIRE(r.query() == false);
  l1.off();
  l2.on();
  REQUIRE(r.query() == false);
  l1.on();
  REQUIRE(r.query() == true);
}

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

TEST_CASE("Nand statements work") {
  Nand a = Nand({0, 0});
  Input l1 = Input(N, Position{0, 1});
  Input l2 = Input(S, Position{0,-1});
  Output r = Output(E, Position{1, 0});
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
