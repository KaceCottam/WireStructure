#include <catch.hpp>

#include <Node.h>

TEST_CASE("Nodes can be created") {
  SECTION("Using default values")
  {
    Node node = Node();
    REQUIRE(node.pos == Vec2D{0,0});
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
  REQUIRE(node1.nw == nullptr);
  REQUIRE(node1.n  == &node2);
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
  REQUIRE(node2.s  == &node1);
  REQUIRE(node2.se == nullptr);
}
TEST_CASE("Nodes cannot be connected if they are not adjacent") {
  Node node1 = Node({0,-1});
  Node node2 = Node({0, 1});
  auto valid = connect(node1, node2);
  REQUIRE(valid == false);
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
