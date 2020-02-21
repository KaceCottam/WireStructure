Roadmap
===

Using the [standard semantic versioning scheme](https://semver.org/),
V<MAJOR>.<MINOR>[.<PATCH>]  
- _italicized_ items are not prioritized-- they may happen and they may not.

V1.0 "DRAWABLE CIRCUITS"
---
Drawing of circuit diagrams, with some basic gates, multiplexers.
The goal at this point is to be able to draw a MIPS architecture diagram,
like as presented in the picture below.

![http://www.cise.ufl.edu/~mssz/CompOrg/Fig4.16-MIPS-MCDP-Diagr.gif]

_V1.1_
---
Variable-input gates for `AND`, `OR`, `NAND`, `XOR`, `XNOR`, `MULTIPLEXER`, etc.

V1.2 "LOGIC CIRCUITS"
---
Adding on to drawing: We can now simulate basic on and off functionality
through wires. We should be able to color wires based on their state (if wanted)
and we should be able to generate input sequences through manual activation.
The goal at this point is to simulate basic logic circuits that use single-bit
wires.

_V1.3_
---
Generate input sequences using function-based activation (such as a waveform).

_V1.4_
---
See resulting boolean algebra at the output. Insert a sequence of gates using
boolean algebra.

V1.5 "COMPUTER ARCHITECTURE"
---
We should be able to make wires with multiple bits, and split those wires.
The goal at this point is to fully simulate a MIPS architecture diagram.

V2.0 "MORE THAN LOGIC"
---
We should be able to add other circuit components based in physics, as well
as measure voltage, current, etc.
