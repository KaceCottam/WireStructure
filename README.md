[docs/1-Description.md](docs/1-Description.md)
Description
===
This is a GUI application that allows for construction and simulation of
circuits using simple mouse and keyboard controls. The premise is that there is
a grid of points, where wires can connect. Upon each grid 'node', a gate
can be placed. Sub-Circuits will be supported eventually.

Wanted Features
---
- [ ] Generate a grid of 'nodes'
- [ ] GUI controls, as well as keyboard where it makes sense.
- [ ] Panning and Zooming on 'board'
- [X] Toolbox for simple gates.
- [ ] Rotation of simple gates.
- [X] Simulate electric charge going through the circuit
- [ ] Sub-circuits
- [ ] Cross-Platform, including Web
- [ ] Export to picture, video, and code
- [ ] Wires that can go 'underneath' other wires

More wanted features are shown
[here](https://github.com/KaceCottam/WireStructure/projects/1?add_cards_query=is%3Aopen),
in the project tab of github.

[docs/2-Technologies.md](docs/2-Technologies.md)
Technologies
===
- C++
- C++ STL - unordered_set, mutex, future, async, functional
- WxWidgets

I am using `C++` and `WxWidgets`.  WxWidgets for graphics is simple, and I am
tutoring in C++. Since this is a teaching tool, it makes sense that I am going
to show the code for making this to my tutees as well.

[docs/3-Grid.md](docs/3-Grid.md)
Display
===


Grid of 10 x 3 without connections
---
We want a *grid* where each point on the grid is clickable, and we can use
right-click to drag.  Left-clicking and dragging causes a wire to be made.
Wires are 1 or 1+sind(45) units long.  As we drag, wires are created that snap
between the origin point and one of the 8 points around it, and then the snap
point is made to be the new origin point. This is to maintain organization.
```
* * * * * * * * * *

* * * * * * * * * *

* * * * * * * * * *
```

Grid of 10 x 3 with wire connections
---
```
*-*-*-*-* * * * * *
        |
* * *-*-*-*-*-* * *
   /           \
* * * * * * * * * *
```

This grid is infinite, and wires are stored using an tree of (x,y) positions,
where branches are different wire paths. These branches will be used to
determine the path of charge. Since charge can travel two ways, these sub-trees
must have a parent pointer.

Holding right click while hovering over anything deletes it.

Wires will be made by clicking and dragging (in order to place nodes following
the path of the mouse) from a node to another node. By clicking once,
and clicking again where the end of the node is, the path will be determined by
rectangular pathfinding, with kinks starting around the middle.

Holding shift while making a wire shall make it go 'under' the other wires,
wherein they will not connect. There will be no change in the pragmatic
programming for these wires, except a flag saying they are 'under.'

Grid of 10 x 3 with parallel connections and wire connections
---
Each column can be toggled to be connected inherently.
```
* @-*-*-*-* * * * *
  +      /
* @ * * *-*-* * * *
  +
* @-*-*-*-*-* * * *
```

Grid of 10 x 3 with a NOT gate
---
Simple gates can be placed on top of nodes, where no wires are.
```
* * * * * * * * * *

*-*-*->-*-*-* * * *

* * * * * * * * * *
```

More advanced gates will have to take up multiple nodes, as many as it needs
for inputs. Inputs should be labeled inside of the gate and on hover.

All gates can be rotated by pressing `r` or by selecting it and rotating it
with the mouse.

Making of a Sub-circuit
---
We should be able to make a sub-circuit easily, and label inputs and outputs.
This sub-circuit should be saved to a sub-citcuit toolbox, but the full circuit
should be visible somewhere on the grid.

[docs/4-Nodes.md](docs/4-Nodes.md)
Nodes
===
Nodes can be connected to the 8 adjacent nodes. This connection goes both ways;
think of an 8-way doubly-linked list. Nodes will be a root type that can be
expanded upon using Object Oriented Programming.

Wire nodes will be able to go 'underneath' other wire nodes by creating a wire
node at the same position as other node, and not connecting to it. This will
require one node for every sublevel. Using this strategy, we can make
connections up to four levels deep (since every wire needs 2 connections to be
useful)! How this will be handled in the gui is either going to be a modified
button press sequence or cocentric circles of varying radii, where the smallest
radius is the uppermost level.

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
- [X] NAND: opposite of AND gate
- [X] NOR: opposite of OR gate
- [X] XOR: outputs a signal if only _one_ of the connected inputs are on
- [X] XNOR: opposite of XOR gate
- [X] INPUT: has no inputs but can set a power state
- [X] OUTPUT: has no outputs but can read a power state

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
it is defined whether or not that node 'can be connected to' from a given
direction.

For now all nodes cannot be rotated, but this may change. The default 'output'
of a simple gate is to the east (right).

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

