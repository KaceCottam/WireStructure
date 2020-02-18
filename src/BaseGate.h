#ifndef BASEGATE_H
#define BASEGATE_H
#include <vector>
struct BaseGate { std::vector<BaseGate*> inputs; };
unsigned countPowered(const BaseGate*);

struct NotGate    : public BaseGate {};
struct AndGate    : public BaseGate {};
struct OrGate     : public BaseGate {};
struct NorGate    : public BaseGate {};
struct XorGate    : public BaseGate {};
struct XnorGate   : public BaseGate {};
struct NandGate   : public BaseGate {};
struct InputGate  : public BaseGate { bool active; };
struct OutputGate : public BaseGate {};
#endif // ! BASEGATE_H

