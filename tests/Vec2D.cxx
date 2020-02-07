#include <catch.hpp>

#include <Vec2D.h>

template<class T>
using nl = std::numeric_limits<T>;

TEST_CASE("Vec2D can be constructed of multiple types") {
  REQUIRE_NOTHROW([]{ Vec2D<int>{0, 0}; }());
  REQUIRE_NOTHROW([]{ Vec2D<float>{0.0, 0.0}; }());
  REQUIRE_NOTHROW([]{ Vec2D<bool>{false, false}; }());
}
TEMPLATE_TEST_CASE("Vec2D can be operated upon mathematically", "", int, double) {
  Vec2D<TestType> a = {1, 0};
  Vec2D<TestType> b = {0, 1};
  TestType scal = GENERATE(nl<TestType>::min(), -1, 0, 1, nl<TestType>::max());
  REQUIRE(a + b == Vec2D<TestType>{1, 1});
  REQUIRE(b + a == Vec2D<TestType>{1, 1});
  REQUIRE(a - b == Vec2D<TestType>{1,-1});
  REQUIRE(b - a == Vec2D<TestType>{-1,1});
  REQUIRE(scal * a == Vec2D<TestType>{scal, 0});
  REQUIRE(a * scal == Vec2D<TestType>{scal, 0});
  REQUIRE(scal * b == Vec2D<TestType>{0, scal});
  REQUIRE(b * scal == Vec2D<TestType>{0, scal});
  REQUIRE(magnitude(a) == 1.0);
  REQUIRE(magnitude(b) == 1.0);
  REQUIRE(normal(a) == Vec2D<double>(1.0, 0));
  REQUIRE(normal(b) == Vec2D<double>(0, 1.0));
}
TEMPLATE_TEST_CASE("Vec2D can be operated upon logically", "", int, double) {
  Vec2D<TestType> a = {1, 0};
  Vec2D<TestType> b = {0, 1};
  REQUIRE(a == a);
  REQUIRE(b == b);
  REQUIRE(a != b);
  REQUIRE((a < b) == Vec2D<bool>{false, true});
  REQUIRE((a > b) == Vec2D<bool>{true, false});
  REQUIRE((b < a) == Vec2D<bool>{true, false});
  REQUIRE((b > a) == Vec2D<bool>{false, true});
  REQUIRE((a <= a) == Vec2D<bool>{true, true});
  REQUIRE((a >= a) == Vec2D<bool>{true, true});
  REQUIRE((b <= b) == Vec2D<bool>{true, true});
  REQUIRE((b >= b) == Vec2D<bool>{true, true});
  REQUIRE((b <= a) == Vec2D<bool>{true, false});
  REQUIRE((b >= a) == Vec2D<bool>{false, true});
  REQUIRE((a < (a + b)) == Vec2D<bool>{true, true});
  REQUIRE((b < (b + a)) == Vec2D<bool>{true, true});
}
