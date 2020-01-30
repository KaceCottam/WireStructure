Display
===


Grid of 10 x 3 without connections
---
We want a *grid* where each point on the grid is clickable, and we can use right-click to drag.
Left-clicking and dragging causes a wire to be made. Wires are 1 or 1+sind(45) units long. 
As we drag, wires are created that snap between the origin point and one of the 8
points around it, and then the snap point is made to be the new origin point. This
is to maintain organization.
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

Wires will be made by clicking and dragging (in order to place nodes following
the path of the mouse) from a node to another node. By clicking once,
and clicking again where the end of the node is, the path will
be determined by rectangular pathfinding, with kinks starting around the middle.

Holding shift while making a wire shall make it go 'under' the other wires, wherein
they will not connect. There will be no change in the pragmatic programming for these
wires, except a flag saying they are 'under.'

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

All gates can be rotated by pressing `r` or by selecting it and rotating it with
the mouse.

Making of a Sub-circuit
---
We should be able to make a sub-circuit easily, and label inputs and outputs.
This sub-circuit should be saved to a sub-citcuit toolbox, but the full circuit
should be visible somewhere on the grid.
