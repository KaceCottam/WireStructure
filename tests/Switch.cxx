#include <catch.hpp>

#include <Switch.h>
#include <Node.h>

TEST_CASE("Switches can be connected to nodes") {
  Switch button = Switch(Vec2D{0,0}); // TODO: Vec2D needed -- fix
  Node node = Node({0,1});
  REQUIRE(connect(node, button) == true);
}
TEST_CASE("Switches can affect Nodes") {
  Switch button = Switch(Vec2D{0,0}); // TODO: Vec2D needed -- fix
  Node node = Node({0,1});
  REQUIRE(connect(node, button) == true);
  REQUIRE(node.powered() == false);
  button.on();
  REQUIRE(node.powered() == true);
  button.off();
  REQUIRE(node.powered() == false);
  button.toggle();
  REQUIRE(node.powered() == true);
  button.toggle();
  REQUIRE(node.powered() == false);
}
TEST_CASE("Multiple switches do not affect each other.") {
  Switch button1 = Switch(Vec2D{-1,1});
  Switch button2 = Switch(Vec2D{ 0,1});
  Switch button3 = Switch(Vec2D{ 1,1});
  Node nodes[] = {
    Node({-1,  0}), Node({ 0,  0}), Node({ 1,  0}),
                    Node({ 0, -1})
  };
  Node& node = nodes[3];
  REQUIRE(connect(nodes[0],button1) == true);
  REQUIRE(connect(nodes[1],button2) == true);
  REQUIRE(connect(nodes[2],button3) == true);
  REQUIRE(connect(nodes[1], nodes[0]) == true);
  REQUIRE(connect(nodes[1], nodes[2]) == true);
  REQUIRE(connect(nodes[1], nodes[3]) == true);

  REQUIRE(node.powered() == false);
  button1.on();
  REQUIRE(node.powered() == true);
  button1.off();
  REQUIRE(node.powered() == false);
  button1.toggle();
  REQUIRE(node.powered() == true);
  button1.toggle();
  REQUIRE(node.powered() == false);

  button2.on();
  REQUIRE(node.powered() == true);
  button2.off();
  REQUIRE(node.powered() == false);
  button2.toggle();
  REQUIRE(node.powered() == true);
  button2.toggle();
  REQUIRE(node.powered() == false);

  button3.on();
  REQUIRE(node.powered() == true);
  button3.off();
  REQUIRE(node.powered() == false);
  button3.toggle();
  REQUIRE(node.powered() == true);
  button3.toggle();
  REQUIRE(node.powered() == false);

  button1.on();
  button2.on();
  REQUIRE(node.powered() == true);
  button2.off();
  REQUIRE(node.powered() == true);
}
