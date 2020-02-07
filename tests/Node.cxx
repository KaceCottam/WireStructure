#include <catch.hpp>

#include <Node.h>
#include <Switch.h>

TEST_CASE("Nodes can be created") {
  SECTION("Using default values")
  {
    Node node = Node();

    REQUIRE(node.pos == Vec2D{0,0});
    REQUIRE(node.powered() == false);
    REQUIRE(node.nw == nullptr);
    REQUIRE(node.n  == nullptr);
    REQUIRE(node.ne == nullptr);
    REQUIRE(node.w  == nullptr);
    REQUIRE(node.e  == nullptr);
    REQUIRE(node.sw == nullptr);
    REQUIRE(node.s  == nullptr);
    REQUIRE(node.se == nullptr);
  }
  SECTION("Using container values")
  {
    Node node = Node({0,0});

    REQUIRE(node.pos == Vec2D{0,0});
    REQUIRE(node.powered() == false);
    REQUIRE(node.nw == nullptr);
    REQUIRE(node.n  == nullptr);
    REQUIRE(node.ne == nullptr);
    REQUIRE(node.w  == nullptr);
    REQUIRE(node.e  == nullptr);
    REQUIRE(node.sw == nullptr);
    REQUIRE(node.s  == nullptr);
    REQUIRE(node.se == nullptr);
  }
}
TEST_CASE("Nodes can be connected if they are adjacent") {
  Node node1 = Node({0,0});
  Node node2 = Node({0,1});
  auto valid = connect(node1, node2);

  REQUIRE(valid == true);
  REQUIRE(node1.pos == Vec2D{0,0});
  REQUIRE(node1.powered() == false);
  REQUIRE(node1.nw == nullptr);
  REQUIRE(node1.n  == &node2);
  REQUIRE(node1.ne == nullptr);
  REQUIRE(node1.w  == nullptr);
  REQUIRE(node1.e  == nullptr);
  REQUIRE(node1.sw == nullptr);
  REQUIRE(node1.s  == nullptr);
  REQUIRE(node1.se == nullptr);

  REQUIRE(node2.pos == Vec2D{0,1});
  REQUIRE(node2.powered() == false);
  REQUIRE(node2.nw == nullptr);
  REQUIRE(node2.n  == nullptr);
  REQUIRE(node2.ne == nullptr);
  REQUIRE(node2.w  == nullptr);
  REQUIRE(node2.e  == nullptr);
  REQUIRE(node2.sw == nullptr);
  REQUIRE(node2.s  == &node1);
  REQUIRE(node2.se == nullptr);

  SECTION("Nodes in the same spot can not be connected") {
    Node node1Copy = Node({0,0});
    auto valid = connect(node1, node1Copy);

    REQUIRE(valid == false);
    REQUIRE(node1Copy.nw == nullptr);
    REQUIRE(node1Copy.n  == nullptr);
    REQUIRE(node1Copy.ne == nullptr);
    REQUIRE(node1Copy.w  == nullptr);
    REQUIRE(node1Copy.e  == nullptr);
    REQUIRE(node1Copy.sw == nullptr);
    REQUIRE(node1Copy.s  == nullptr);
    REQUIRE(node1Copy.se == nullptr);
  }
  SECTION("Testing circular connections") {
    Node node3 = Node({1,0});
    auto valid1 = connect(node1, node3);
    auto valid2 = connect(node2, node3);
    REQUIRE(valid1 == true);
    REQUIRE(valid2 == true);

    REQUIRE(node1.nw == nullptr);
    REQUIRE(node1.n  == &node2);
    REQUIRE(node1.ne == nullptr);
    REQUIRE(node1.w  == nullptr);
    REQUIRE(node1.e  == &node3);
    REQUIRE(node1.sw == nullptr);
    REQUIRE(node1.s  == nullptr);
    REQUIRE(node1.se == nullptr);

    REQUIRE(node2.nw == nullptr);
    REQUIRE(node2.n  == nullptr);
    REQUIRE(node2.ne == nullptr);
    REQUIRE(node2.w  == nullptr);
    REQUIRE(node2.e  == nullptr);
    REQUIRE(node2.sw == nullptr);
    REQUIRE(node2.s  == &node1);
    REQUIRE(node2.se == &node3);

    REQUIRE(node3.nw == &node2);
    REQUIRE(node3.n  == nullptr);
    REQUIRE(node3.ne == nullptr);
    REQUIRE(node3.w  == &node1);
    REQUIRE(node3.e  == nullptr);
    REQUIRE(node3.sw == nullptr);
    REQUIRE(node3.s  == nullptr);
    REQUIRE(node3.se == nullptr);
  }
}
TEST_CASE("Wires can be disconnected") {
  Node node1 = Node({0,0});
  Node node2 = Node({0,1});
  auto valid1 = connect(node1, node2);
  REQUIRE(valid1 == true);

  auto valid2 = disconnect(node1, node2);
  REQUIRE(valid2 == true);
  REQUIRE(node1.nw == nullptr);
  REQUIRE(node1.n  == nullptr);
  REQUIRE(node1.ne == nullptr);
  REQUIRE(node1.w  == nullptr);
  REQUIRE(node1.e  == nullptr);
  REQUIRE(node1.sw == nullptr);
  REQUIRE(node1.s  == nullptr);
  REQUIRE(node1.se == nullptr);

  REQUIRE(node2.nw == nullptr);
  REQUIRE(node2.n  == nullptr);
  REQUIRE(node2.ne == nullptr);
  REQUIRE(node2.w  == nullptr);
  REQUIRE(node2.e  == nullptr);
  REQUIRE(node2.sw == nullptr);
  REQUIRE(node2.s  == nullptr);
  REQUIRE(node2.se == nullptr);
}
TEST_CASE("Nodes cannot be connected if they are not adjacent") {
  Node node1 = Node({0,-1});
  Node node2 = Node({0, 1});
  auto valid = connect(node1, node2);

  REQUIRE(valid == false);
  REQUIRE(node1.pos == Vec2D{0,-1});
  REQUIRE(node1.powered() == false);
  REQUIRE(node1.nw == nullptr);
  REQUIRE(node1.n  == nullptr);
  REQUIRE(node1.ne == nullptr);
  REQUIRE(node1.w  == nullptr);
  REQUIRE(node1.e  == nullptr);
  REQUIRE(node1.sw == nullptr);
  REQUIRE(node1.s  == nullptr);
  REQUIRE(node1.se == nullptr);

  REQUIRE(node2.pos == Vec2D{0, 1});
  REQUIRE(node2.powered() == false);
  REQUIRE(node2.nw == nullptr);
  REQUIRE(node2.n  == nullptr);
  REQUIRE(node2.ne == nullptr);
  REQUIRE(node2.w  == nullptr);
  REQUIRE(node2.e  == nullptr);
  REQUIRE(node2.sw == nullptr);
  REQUIRE(node2.s  == nullptr);
  REQUIRE(node2.se == nullptr);
}
TEST_CASE("Functions can be dispatched through connected wires") {
  Switch button = Switch(Vec2D{-1, 0});
  Node node1 = Node({0,0});
  Node node2 = Node({0,1});
  Node node3 = Node({1,0});

  REQUIRE(connect(button, node1) == true);
  REQUIRE(node1.powered() == false);
  button.on();
  REQUIRE(node1.powered() == true);
  button.off();
  REQUIRE(node1.powered() == false);

  auto valid1 = connect(node1, node2);
  REQUIRE(valid1 == true);
  REQUIRE(node1.powered() == false);
  REQUIRE(node2.powered() == false);

  button.on();
  REQUIRE(node1.powered() == true);
  REQUIRE(node2.powered() == true);
  button.off();

  auto valid2 = connect(node1, node3);
  REQUIRE(valid2 == true);
  
  button.toggle();
  REQUIRE(node1.powered() == true);
  REQUIRE(node2.powered() == true);
  REQUIRE(node3.powered() == true);

  button.toggle();
  REQUIRE(node1.powered() == false);
  REQUIRE(node2.powered() == false);
  REQUIRE(node3.powered() == false);

  SECTION("Testing circular connections") {
    auto valid3 = connect(node2, node3);
    REQUIRE(valid3 == true);

    button.on();
    REQUIRE(node1.powered() == true);
    REQUIRE(node2.powered() == true);
    REQUIRE(node3.powered() == true);

    button.off();
    REQUIRE(node1.powered() == false);
    REQUIRE(node2.powered() == false);
    REQUIRE(node3.powered() == false);
  }
}
TEST_CASE("Wires that are connected to powered() wires automatically become powered") {
  Switch button = Switch(Vec2D{0,-1});
  Node node1 = Node({0,0});
  Node node2 = Node({0,1});

  REQUIRE(connect(button, node1) == true);

  button.on();
  REQUIRE(node1.powered() == true);
  REQUIRE(node2.powered() == false);

  auto valid = connect(node1, node2);
  REQUIRE(valid == true);
  REQUIRE(node1.powered() == true);
  REQUIRE(node2.powered() == true);

  SECTION("This connection is dispatched throughout multiple connections") {
    Node node3 = Node({1,0});
    Node node4 = Node({2, 0});

    auto valid1 = connect(node3, node4);
    REQUIRE(valid1 == true);

    auto valid2 = connect(node1, node3);
    REQUIRE(valid2 == true);
    REQUIRE(node3.powered() == true);
    REQUIRE(node4.powered() == true);
  }
}
TEST_CASE("Wires that are disconnected from powered() wires automatically become unpowered (if there is not another source of power)") {
  Switch button = Switch(Vec2D{0,-1});
  Node node1 = Node({0,0});
  Node node2 = Node({0,1});
  REQUIRE(connect(button, node1) == true);
  auto valid1 = connect(node1, node2);
  REQUIRE(valid1 == true);

  button.on();
  REQUIRE(node1.powered() == true);
  REQUIRE(node2.powered() == true);

  auto valid2 = disconnect(node1, node2);
  REQUIRE(valid2 == true);
  REQUIRE(node1.powered() == true);
  REQUIRE(node2.powered() == false);
}
