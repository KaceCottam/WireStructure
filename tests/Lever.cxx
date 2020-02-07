#include <catch.hpp>

#include <Lever.h>
#include <Node.h>

TEST_CASE("Leveres can be connected to nodes") {
  Lever lever = Lever(Vec2D{0,0}); // TODO: Vec2D needed -- fix
  Node node = Node({0,1});
  REQUIRE(connect(node, lever) == true);
}
TEST_CASE("Leveres can affect Nodes") {
  Lever lever = Lever(Vec2D{0,0}); // TODO: Vec2D needed -- fix
  Node node = Node({0,1});
  REQUIRE(connect(node, lever) == true);
  REQUIRE(node.powered() == false);
  lever.on();
  REQUIRE(node.powered() == true);
  lever.off();
  REQUIRE(node.powered() == false);
  lever.toggle();
  REQUIRE(node.powered() == true);
  lever.toggle();
  REQUIRE(node.powered() == false);
}
TEST_CASE("Multiple switches do not affect each other.") {
  Lever lever1 = Lever(Vec2D{-1,1});
  Lever lever2 = Lever(Vec2D{ 0,1});
  Lever lever3 = Lever(Vec2D{ 1,1});
  Node nodes[] = {
    Node({-1,  0}), Node({ 0,  0}), Node({ 1,  0}),
                    Node({ 0, -1})
  };
  Node& node = nodes[3];
  REQUIRE(connect(nodes[0],lever1) == true);
  REQUIRE(connect(nodes[1],lever2) == true);
  REQUIRE(connect(nodes[2],lever3) == true);
  REQUIRE(connect(nodes[1], nodes[0]) == true);
  REQUIRE(connect(nodes[1], nodes[2]) == true);
  REQUIRE(connect(nodes[1], nodes[3]) == true);

  REQUIRE(node.powered() == false);
  lever1.on();
  REQUIRE(node.powered() == true);
  lever1.off();
  REQUIRE(node.powered() == false);
  lever1.toggle();
  REQUIRE(node.powered() == true);
  lever1.toggle();
  REQUIRE(node.powered() == false);

  lever2.on();
  REQUIRE(node.powered() == true);
  lever2.off();
  REQUIRE(node.powered() == false);
  lever2.toggle();
  REQUIRE(node.powered() == true);
  lever2.toggle();
  REQUIRE(node.powered() == false);

  lever3.on();
  REQUIRE(node.powered() == true);
  lever3.off();
  REQUIRE(node.powered() == false);
  lever3.toggle();
  REQUIRE(node.powered() == true);
  lever3.toggle();
  REQUIRE(node.powered() == false);

  lever1.on();
  lever2.on();
  REQUIRE(node.powered() == true);
  lever2.off();
  REQUIRE(node.powered() == true);
}
