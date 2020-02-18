#ifndef BASEGATE_H
#define BASEGATE_H
#include <vector>
struct BaseGate
{
  std::vector<BaseGate*> inputs;
  virtual bool powered() const = 0;
  unsigned countPowered() const;
};

struct NotGate     : public BaseGate { bool powered() const override; };
struct AndGate     : public BaseGate { bool powered() const override; };
struct OrGate      : public BaseGate { bool powered() const override; };
struct NorGate     : public BaseGate { bool powered() const override; };
struct XorGate     : public BaseGate { bool powered() const override; };
struct XnorGate    : public BaseGate { bool powered() const override; };
struct NandGate    : public BaseGate { bool powered() const override; };
struct InputGate   : public BaseGate { bool active;  bool powered() const override; };
struct OutputGate  : public OrGate {};
struct Multiplexer : public BaseGate { bool powered() const override; };
#endif // ! BASEGATE_H

