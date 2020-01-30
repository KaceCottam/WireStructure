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
