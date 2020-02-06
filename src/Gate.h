#ifndef GATE_H
#define GATE_H
#include "Node.h"
class Gate : public Node {
  public:
    virtual bool powered() = delete;
  private:
};

#endif // ! GATE_H

