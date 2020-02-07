Nodes
===
Nodes can be connected to the 8 adjacent nodes. This connection goes both ways;
think of an 8-way doubly-linked list. Nodes will be a root type that can be
expanded upon using Object Oriented Programming.

Because nodes will have a way to `dispatch` a command that can be modified, it
will be useful to think of these nodes as a "functor" as in graph theory.
Imagine a node as a box that contains something, most likely containing some
indicator that power to the node is on. The `dispatch` function will allow
the contained item to be modified.

Gates
===
Gates will be an expansion upon nodes.

I am planning on designing gate drawings with vector graphics so they are
scalable and customizable.  I will most likely create logic for gates using
methods already mentioned.

Some examples of simple gates: (ideas from <https://en.wikipedia.org/wiki/Logic_gate>)
- [ ] BUFFER: provides one-way signals
- [X] NOT: inverts the power state and dispatches it to connected nodes
- [ ] AND: outputs a signal if and only if all connected inputs are on
- [ ] OR: outputs a signal if any of the connected inputs are on
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
