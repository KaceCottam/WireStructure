Nodes
===
Nodes can be connected to the 8 adjacent nodes. This connection goes both ways;
think of an 8-way doubly-linked list. Nodes will be a root type that can be
expanded upon using Object Oriented Programming.

Gates
===
Gates will be an expansion upon nodes.

I am planning on designing gate drawings with vector graphics so they are
scalable and customizable.  I will most likely create logic for gates using
methods already mentioned.

Some examples of simple gates: (ideas from <https://en.wikipedia.org/wiki/Logic_gate>)
- [X] NOT: inverts the power state and dispatches it to connected nodes
- [X] AND: outputs a signal if and only if all connected inputs are on
- [X] OR: outputs a signal if any of the connected inputs are on
- [ ] NAND: opposite of AND gate
- [ ] NOR: opposite of OR gate
- [ ] XOR: outputs a signal if only _one_ of the connected inputs are on
- [ ] XNOR: opposite of XOR gate
- [X] LEVER: has no inputs but can set the power state with mouse control
- [ ] TIMER: has no inputs but can set the power state after time intervals

And we can also make multi-nodal gate with sub-circuits in order to expand upon
our capabilities.

Some examples of complex gates:
- [ ] MULTIPLEXER: takes multiple inputs and allows picking of an input to output
- [ ] MONOSTABLE: upon recieving a signal converts it into a pulse
- [ ] PULSE_EXTENDER: extends a pulse; can be used to convert a constant pulse  
  into a constant powering state
- [ ] various latches and flip-flops for storing information

Directionality
===
All nodes will have 8 possible connections. All nodes have a function wherein
it is defined whether or not that node can be connected to from a given
direction.

Grid of 3x3 centered on a node where `connectFromN` is true
---
The node can be checked if it is powered from the top, but from the bottom it
cannot check if it is powered from the bottom
```
* * *
  v  
* o *
  v  
* * *
```
