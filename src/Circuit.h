#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "Node.h"
#include "Input.h"
#include "Output.h"

#include <unordered_map>
class Circuit : public Node {
  public:
    template<class Arg, class... Args>
    void addNode(Arg&& arg, Args&&... args) {
      addNode(std::forward<Arg>(arg));
      addNode(std::forward<Args>(args)...);
    }

    void addNode(typename NodeSet::key_type key);

  private:
    NodeSet containedNodes;
    std::unordered_map<DirectionFlags, const Input*> inputs;
    std::unordered_map<DirectionFlags, const Output*> outputs;
};
#endif // ! CIRCUIT_H

