#include "BaseGate.h"

#include <algorithm>

unsigned BaseGate::countPowered() const
{
  unsigned result = 0;
  for(auto i : inputs)
  {
    if(i->powered()) result++;
  }
  return result;
}

bool NotGate::powered() const { return inputs.size() == 1 && countPowered() == 0; }
bool AndGate::powered() const { return countPowered() == inputs.size(); }
bool OrGate::powered() const { return countPowered() >= 1; }
bool NorGate::powered() const { return countPowered() == 0; }
bool XorGate::powered() const { return countPowered() == 1; }
bool XnorGate::powered() const { return countPowered() > 1; }
bool NandGate::powered() const { return countPowered() != inputs.size(); }
bool InputGate::powered() const { return active; }

