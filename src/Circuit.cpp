#include "Circuit.h"

void Circuit::addNode(typename NodeSet::key_type key) {
  containedNodes.emplace(key);
  if(auto in = static_cast<const Input*>(key)) {
    if(inputs.count(in->inputDir) != 0) { throw in; }
    inputs[in->inputDir] = in;
  } else if(auto out = static_cast<const Output*>(key)) {
    if(outputs.count(out->outputDir) != 0) { throw out; }
    outputs[out->outputDir] = out;
  }
}
