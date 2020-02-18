#ifndef GATES_H
#define GATES_H
#include <vector>
struct BaseGate
{
  std::vector<BaseGate*> inputs;
  virtual bool powered() const = 0;
  unsigned countPowered() const;
};

struct NotGate     : public BaseGate { bool powered() const final; };
struct AndGate     : public BaseGate { bool powered() const final; };
struct OrGate      : public BaseGate { bool powered() const final; };
struct NorGate     : public BaseGate { bool powered() const final; };
struct XorGate     : public BaseGate { bool powered() const final; };
struct XnorGate    : public BaseGate { bool powered() const final; };
struct NandGate    : public BaseGate { bool powered() const final; };
struct InputGate   : public BaseGate { bool active;  bool powered() const final; };
struct OutputGate  : public OrGate {};
struct Multiplexer : public BaseGate { bool powered() const final; };
#endif // ! GATES_H

