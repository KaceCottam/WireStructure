[1-Description.md](docs/1-Description.md)  
Description
===
This is a GUI application that allows for construction and simulation of circuits using simple mouse and keyboard controls. The premise is that there is a grid of points, where wires can connect. The columns on these grids can be toggled to be parallel-- such as in a breadboard. Upon each grid 'node', a gate can be placed. Sub-Circuits will be supported eventually.

Wanted Features
---
- Generate a grid of 'nodes'
- GUI controls, as well as keyboard where it makes sense.
- Panning and Zooming on 'board'
- Toolbox for simple gates.
- Simulate electric charge going through the circuit
- Connect nodes on a column.
- Sub-circuits
- Cross-Platform, including Web
- Export to picture and video

Dependencies
---
- WxWidgets
- Nim
- WxNim
___
[Grid.md](docs/Grid.md)  
Display
===

We want a *grid* where each point on the grid is clickable, and we can use right-click to drag.
Left-clicking and dragging causes a wire to be made. Wires are 1 or 1+sind(45) units long. 
As we drag, wires are created that snap between the origin point and one of the 8
points around it, and then the snap point is made to be the new origin point. This
is to maintain organization.

Grid of 10 x 3 without connections
---
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
where branches are different wire paths. These branches will be used to determine
the path of charge. Since charge can travel two ways, these sub-trees must have
a parent pointer.

Holding right click while hovering over anything deletes it.

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
___
