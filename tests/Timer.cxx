#include <catch.hpp>

#include <Timer.h>
#include <Node.h>

TEST_CASE("Timers can be connected to nodes") {
  Timer timer = Timer(Vec2D{0,0}); // TODO: Vec2D needed -- fix
  Node node = Node({0,1});
  REQUIRE(connect(node, timer) == true);
}
TEST_CASE("Timers can affect Nodes") {
  Timer timer = Timer(Vec2D{0,0});
  Node node = Node({0,1});
  REQUIRE(connect(node, timer) == true);
  REQUIRE(node.powered() == false);
  timer.tick();
  REQUIRE(node.powered() == true);
  timer.tick();
  REQUIRE(node.powered() == false);
  timer.tick();
  REQUIRE(node.powered() == true);
  timer.tick();
  REQUIRE(node.powered() == false);
}
TEST_CASE("Multiple timers do not affect each other.") {
  Timer timer1 = Timer(Vec2D{-1,1});
  Timer timer2 = Timer(Vec2D{ 0,1});
  Timer timer3 = Timer(Vec2D{ 1,1});
  Node nodes[] = {
    Node({-1,  0}), Node({ 0,  0}), Node({ 1,  0}),
                    Node({ 0, -1})
  };
  Node& node = nodes[3];
  REQUIRE(connect(nodes[0], timer1) == true);
  REQUIRE(connect(nodes[1], timer2) == true);
  REQUIRE(connect(nodes[2], timer3) == true);
  REQUIRE(connect(nodes[1], nodes[0]) == true);
  REQUIRE(connect(nodes[1], nodes[2]) == true);
  REQUIRE(connect(nodes[1], nodes[3]) == true);

  REQUIRE(node.powered() == false);
  timer1.tick();
  REQUIRE(node.powered() == true);
  timer1.tick();
  REQUIRE(node.powered() == false);
  timer1.tick();
  REQUIRE(node.powered() == true);
  timer1.tick();
  REQUIRE(node.powered() == false);

  timer2.tick();
  REQUIRE(node.powered() == true);
  timer2.tick();
  REQUIRE(node.powered() == false);
  timer2.tick();
  REQUIRE(node.powered() == true);
  timer2.tick();
  REQUIRE(node.powered() == false);

  timer3.tick();
  REQUIRE(node.powered() == true);
  timer3.tick();
  REQUIRE(node.powered() == false);
  timer3.tick();
  REQUIRE(node.powered() == true);
  timer3.tick();
  REQUIRE(node.powered() == false);

  timer1.tick();
  timer2.tick();
  REQUIRE(node.powered() == true);
  timer2.tick();
  REQUIRE(node.powered() == true);
  timer1.tick();
  REQUIRE(node.powered() == false);
}
