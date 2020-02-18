#include <catch.hpp>

#include <BaseGate.h>

TEST_CASE("or gates work")
{
  OutputGate out;
  OrGate o;
  InputGate in;
  out.inputs.push_back(&o);
  o.inputs.push_back(&in);
  REQUIRE(out.powered() == false);
  in.active = true;
  REQUIRE(out.powered() == true);
}
TEST_CASE("not gates work")
{
  OutputGate out;
  NotGate n;
  InputGate in;
  out.inputs.push_back(&n);
  n.inputs.push_back(&in);
  REQUIRE(out.powered() == true);
  in.active = true;
  REQUIRE(out.powered() == false);
}
TEST_CASE("and gates work")
{
  OutputGate out;
  AndGate a;
  InputGate in;
  InputGate in2;
  out.inputs.push_back(&a);
  a.inputs.push_back(&in);
  a.inputs.push_back(&in2);
  REQUIRE(out.powered() == false);
  in.active = true;
  REQUIRE(out.powered() == false);
  in2.active = true;
  REQUIRE(out.powered() == true);
}
