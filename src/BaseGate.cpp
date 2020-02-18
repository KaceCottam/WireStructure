#include "BaseGate.h"

#include <algorithm>

unsigned countPowered(const BaseGate* bg)
{
  return std::count_if(bg->inputs.begin(),bg->inputs.end(),
      [](auto i){return powered(i);}
      );
}

bool powered(const NotGate& ng) { return countPowered(&ng) == 0; }
bool powered(const AndGate& ag) { return countPowered(&ag) == ag.inputs.size(); }
bool powered(const OrGate& g) { return countPowered(&g) >= 1; }
bool powered(const NorGate& g) { return countPowered(&g) == 0; }
bool powered(const XorGate& g) { return countPowered(&g) == 1; }
bool powered(const XnorGate& g) { return countPowered(&g) > 1; }
bool powered(const NandGate& g) { return countPowered(&g) != g.inputs.size(); }
bool powered(const InputGate& g) { return g.active; }
bool powered(const OutputGate&) { return false; }
