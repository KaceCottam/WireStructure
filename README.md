[docs/1-Description.md](docs/1-Description.md)
Description
===
This is a GUI application that allows for construction and simulation of
circuits using simple mouse and keyboard controls. The premise is that there is
a grid of points, where wires can connect. Upon each grid 'node', a gate
can be placed. Sub-Circuits will be supported eventually.

Wanted Features
---
- [X] Generate a grid where we can place nodes
- [X] GUI controls, as well as keyboard where it makes sense.
- [X] Panning and Zooming on 'board'
- [X] Toolbox for simple gates.
- [ ] Rotation of simple gates.
- [ ] Simulate electric charge going through the circuit
- [ ] Sub-circuits
- [X] Cross-Platform, including Web
- [ ] Export to picture, video, and code
- [ ] Wires that can go 'underneath' other wires

More wanted features are shown
[here](https://github.com/KaceCottam/WireStructure/projects/1?add_cards_query=is%3Aopen),
in the project tab of github.

[docs/2-Technologies.md](docs/2-Technologies.md)
Technologies
===
- C++
- C++ STL
- WxWidgets

I am using `C++` and `WxWidgets`.  WxWidgets for graphics is simple, and I am
tutoring in C++. Since this is a teaching tool, it makes sense that I am going
to show the code for making this to my tutees as well.

[docs/3-Roadmap.md](docs/3-Roadmap.md)
Roadmap
===

Using the [standard semantic versioning scheme](https://semver.org/),
V\<MAJOR\>.\<MINOR\>[.\<PATCH\>]  

![Roadmap](http://www.plantuml.com/plantuml/proxy?src=https://raw.github.com/KaceCottam/WireStructure/master/docs/Roadmap.txt?)

[docs/4-Interface.md](docs/4-Interface.md)
Interface
===

The interface is going to be very simplistic and understandable.
There is an emphasis on fluid interaction within the program.

There is also an emphasis on native-looking panels.
Below is an example of the program with ubuntu linux, dark mode.

![Current interface (default)](./docs/interface-default-ubuntu.png)

The interface has customizable color schemes.

![Light interface](./docs/interface-solarized-light.png)

[docs/UML-Canvas.md](docs/UML-Canvas.md)
![Canvas Structure](http://www.plantuml.com/plantuml/proxy?src=https://raw.github.com/KaceCottam/WireStructure/master/docs/Canvas.txt?)

