#include "BaseGate.h"

#include <algorithm>
#include <future>

unsigned BaseGate::countPowered() const
{
  std::vector<std::future<bool>> results; 
  const auto seeIfPowered = [](auto* i){ return i->powered(); };

  std::transform(inputs.begin(), inputs.end(), std::back_inserter(results),
      [&seeIfPowered](auto& i)
      { return std::async(std::launch::async, seeIfPowered, i); });

  return std::count_if(results.begin(), results.end(),
    [](auto& i){ return i.get(); }
    );
}

bool NotGate::powered() const { return inputs.size() == 1 && countPowered() == 0; }
bool AndGate::powered() const { return countPowered() == inputs.size(); }
bool OrGate::powered() const { return countPowered() >= 1; }
bool NorGate::powered() const { return countPowered() == 0; }
bool XorGate::powered() const { return countPowered() == 1; }
bool XnorGate::powered() const { return countPowered() > 1; }
bool NandGate::powered() const { return countPowered() != inputs.size(); }
bool InputGate::powered() const { return active; }

