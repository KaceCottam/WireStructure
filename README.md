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

