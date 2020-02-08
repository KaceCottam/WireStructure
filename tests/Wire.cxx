#include <catch.hpp>

#include <Lever.h>
#include <OutputReader.h>
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
  Lever lever = Lever("Input", Position{-1, 0});
  Wire wires[] =
    { Wire({0, 0}),
      Wire({1, 0}),
      Wire({0,-1}) };
  OutputReader ors[] =
    { OutputReader("0", Position{0, 1}),
      OutputReader("1", Position{1, 1}),
      OutputReader("2", Position{1,-1}) };

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
    REQUIRE(connect(wires[1], wires[2]) == true);

    REQUIRE(ors[0].query() == true);
    REQUIRE(ors[1].query() == true);
    REQUIRE(ors[2].query() == true);

    lever.toggle();
    REQUIRE(ors[0].query() == false);
    REQUIRE(ors[1].query() == false);
    REQUIRE(ors[2].query() == false);
  }
}
//TEST_CASE("Wires that are connected to powered() wires automatically become powered") {
  //Lever lever = Lever("Input", Position{0,-1});
  //Wire wire1 = Wire({0,0});
  //Wire wire2 = Wire({0,1});

  //REQUIRE(connect(lever, wire1) == true);

  //lever.on();
  //REQUIRE(wire1.powered() == true);
  //REQUIRE(wire2.powered() == false);

  //auto valid = connect(wire1, wire2);
  //REQUIRE(valid == true);
  //REQUIRE(wire1.powered() == true);
  //REQUIRE(wire2.powered() == true);

  //SECTION("This connection is dispatched throughout multiple connections") {
    //Wire wire3 = Wire({1,0});
    //Wire wire4 = Wire({2, 0});

    //auto valid1 = connect(wire3, wire4);
    //REQUIRE(valid1 == true);

    //auto valid2 = connect(wire1, wire3);
    //REQUIRE(valid2 == true);
    //REQUIRE(wire3.powered() == true);
    //REQUIRE(wire4.powered() == true);
  //}
//}
//TEST_CASE("Wires that are disconnected from powered() wires automatically become unpowered (if there is not another source of power)") {
  //Lever lever = Lever(Vec2D{0,-1});
  //Wire wire1 = Wire({0,0});
  //Wire wire2 = Wire({0,1});
  //REQUIRE(connect(lever, wire1) == true);
  //auto valid1 = connect(wire1, wire2);
  //REQUIRE(valid1 == true);

  //lever.on();
  //REQUIRE(wire1.powered() == true);
  //REQUIRE(wire2.powered() == true);

  //auto valid2 = disconnect(wire1, wire2);
  //REQUIRE(valid2 == true);
  //REQUIRE(wire1.powered() == true);
  //REQUIRE(wire2.powered() == false);
//}
