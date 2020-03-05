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
- _italicized_ items are not prioritized-- they may happen and they may not.

V1.0 "DRAWABLE CIRCUITS"
---
Drawing of circuit diagrams, with some basic gates, multiplexers.
The goal at this point is to be able to draw a MIPS architecture diagram,
like as presented in the picture below.

![MIPS DIAGRAM](http://www.cise.ufl.edu/~mssz/CompOrg/Fig4.16-MIPS-MCDP-Diagr.gif)

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
[![](https://mermaid.ink/img/eyJjb2RlIjoiY2xhc3NEaWFncmFtXG5jbGFzcyBHYXRle1xuICA8PGFic3RyYWN0Pj5cbiAgR2F0ZSgpXG4gIEdhdGUod3hXaW5kb3cgcGFyZW50LCB3eFdpbmRvd0lEIGlkLCB3eFBvaW50IHBvcywgd3hTaXplIHNpemUsIGxvbmcgc3R5bGUsIHd4U3RyaW5nIG5hbWUpXG5cbiAgK0NyZWF0ZSh3eFdpbmRvdyBwYXJlbnQsIHd4V2luZG93SUQgaWQsIHd4UG9pbnQgcG9zLCB3eFNpemUgc2l6ZSwgbG9uZyBzdHlsZSwgd3hTdHJpbmcgbmFtZSkgR2F0ZSRcblxuICAjTGlzdH5HYXRlfiBpbnB1dHNcbiAgI0xpc3R-R2F0ZX4gb3V0cHV0c1xuXG4gICtBZGRJbnB1dChHYXRlKSB2b2lkXG4gICtBZGRPdXRwdXQoR2F0ZSkgdm9pZFxuXG4gICtDb25uZWN0KEdhdGUgdG8pIHZvaWRcbiAgK0Nvbm5lY3QoR2F0ZSBmcm9tLCBHYXRlIHRvKSB2b2lkJFxuICArQ29ubmVjdChMaXN0fkdhdGV-IGdhdGVzKSB2b2lkJFxuICArRGlzY29ubmVjdChHYXRlIHRvKSB2b2lkXG4gICtEaXNjb25uZWN0KEdhdGUgZnJvbSwgR2F0ZSB0bykgdm9pZCRcbiAgK0Rpc2Nvbm5lY3QoTGlzdH5HYXRlfiBnYXRlcykgdm9pZCRcblxuICArUmVuZGVyKHd4REMpIHZvaWQqXG4gIH5HZXRBbmNob3JQb2ludHMoKSBMaXN0fnd4UG9pbnR-KlxuICAjUmVuZGVyQW5jaG9yUG9pbnRzKCkgdm9pZFxuXG4gICNPbk1vdXNlRW50ZXIod3hNb3VzZUV2ZW50KSB2b2lkXG4gICNPbk1vdXNlTGVhdmUod3hNb3VzZUV2ZW50KSB2b2lkXG4gICNPbkxlZnREb3duKHd4TW91c2VFdmVudCkgdm9pZFxuICAjT25MZWZ0VXAod3hNb3VzZUV2ZW50KSB2b2lkXG4gICNPbldpbmRvd1VwZGF0ZSh3eElkbGVFdmVudCkgdm9pZFxufVxuXG5HYXRlIFwiMi4uOFwiIC4ufD4gXCIxXCIgTm90R2F0ZSAgICAgOiAxIGlucHV0LCAxIG91dHB1dFxuR2F0ZSBcIjMuLjhcIiAuLnw-IFwiMVwiIEFuZEdhdGUgICAgIDogMi03IGlucHV0cywgMSBvdXRwdXRcbkdhdGUgXCIzLi44XCIgLi58PiBcIjFcIiBPckdhdGUgICAgICA6IDItNyBpbnB1dHMsIDEgb3V0cHV0XG5HYXRlIFwiMy4uOFwiIC4ufD4gXCIxXCIgWG9yR2F0ZSAgICAgOiAyLTcgaW5wdXRzLCAxIG91dHB1dFxuR2F0ZSBcIjMuLjhcIiAuLnw-IFwiMVwiIE5vckdhdGUgICAgIDogMi03IGlucHV0cywgMSBvdXRwdXRcbkdhdGUgXCIzLi44XCIgLi58PiBcIjFcIiBYbm9yR2F0ZSAgICA6IDItNyBpbnB1dHMsIDEgb3V0cHV0XG5HYXRlIFwiMS4uOFwiIC4ufD4gXCIxXCIgSW5wdXQgICAgICAgOiAwIGlucHV0cywgMS04IG91dHB1dHNcbkdhdGUgXCIxXCIgICAgLi58PiBcIjFcIiBPdXRwdXQgICAgICA6IDEgaW5wdXQsIDAgb3V0cHV0c1xuR2F0ZSBcIjQuLm5cIiAuLnw-IFwiMVwiIE11bHRpcGxleGVyIDogMy1uIGlucHV0cywgMSBvdXRwdXRcblxuY2xhc3MgR2F0ZUxhYmVse1xuICArU3RyaW5nIHRleHRcblxuICBHYXRlTGFiZWwoU3RyaW5nIGRlZmF1bHRUZXh0KVxuXG4gICtDcmVhdGUoU3RyaW5nIGRlZmF1bHRUZXh0KSRcblxuICArT25DaGFuZ2VMYWJlbChTdHJpbmcgdGV4dCkgdm9pZFxufVxuXG5HYXRlSG9sZGVyICotLSBcIjFcIiBHYXRlXG5HYXRlSG9sZGVyICotLSBcIjFcIiBHYXRlTGFiZWxcblxuY2xhc3MgQ2FudmFze1xuICArTGlzdH5HYXRlfiBtX2NoaWxkcmVuXG5cbiAgQ2FudmFzKClcbiAgQ2FudmFzKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKVxuICArQ3JlYXRlKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKSBDYW52YXMkXG5cbiAgK0FkZEdhdGUoR2F0ZSwgd3hQb2ludCBwb3MpXG59XG4gIFxuQ2FudmFzIG8tLSBcIm5cIiBHYXRlSG9sZGVyXG5cbmNsYXNzIENhbnZhc0hvbGRlcntcbiAgQ2FudmFzSG9sZGVyKClcbiAgQ2FudmFzSG9sZGVyKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKVxuICArQ3JlYXRlKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKSBDYW52YXNIb2xkZXIkXG4gIC1-Q2FudmFzSG9sZGVyKClcbn1cbkNhbnZhc0hvbGRlciAqLS0gXCIxXCIgQ2FudmFzXG5cbkdhdGUgLS18PiB3eFdpbmRvd1xuR2F0ZUhvbGRlciAtLXw-IHd4V2luZG93XG5HYXRlTGFiZWwgLS18PiB3eFdpbmRvd1xuQ2FudmFzIC0tfD4gd3hXaW5kb3dcbkNhbnZhc0hvbGRlciAtLXw-IHd4V2luZG93IiwibWVybWFpZCI6eyJ0aGVtZSI6ImRlZmF1bHQifSwidXBkYXRlRWRpdG9yIjpmYWxzZX0)](https://mermaid-js.github.io/mermaid-live-editor/#/edit/eyJjb2RlIjoiY2xhc3NEaWFncmFtXG5jbGFzcyBHYXRle1xuICA8PGFic3RyYWN0Pj5cbiAgR2F0ZSgpXG4gIEdhdGUod3hXaW5kb3cgcGFyZW50LCB3eFdpbmRvd0lEIGlkLCB3eFBvaW50IHBvcywgd3hTaXplIHNpemUsIGxvbmcgc3R5bGUsIHd4U3RyaW5nIG5hbWUpXG5cbiAgK0NyZWF0ZSh3eFdpbmRvdyBwYXJlbnQsIHd4V2luZG93SUQgaWQsIHd4UG9pbnQgcG9zLCB3eFNpemUgc2l6ZSwgbG9uZyBzdHlsZSwgd3hTdHJpbmcgbmFtZSkgR2F0ZSRcblxuICAjTGlzdH5HYXRlfiBpbnB1dHNcbiAgI0xpc3R-R2F0ZX4gb3V0cHV0c1xuXG4gICtBZGRJbnB1dChHYXRlKSB2b2lkXG4gICtBZGRPdXRwdXQoR2F0ZSkgdm9pZFxuXG4gICtDb25uZWN0KEdhdGUgdG8pIHZvaWRcbiAgK0Nvbm5lY3QoR2F0ZSBmcm9tLCBHYXRlIHRvKSB2b2lkJFxuICArQ29ubmVjdChMaXN0fkdhdGV-IGdhdGVzKSB2b2lkJFxuICArRGlzY29ubmVjdChHYXRlIHRvKSB2b2lkXG4gICtEaXNjb25uZWN0KEdhdGUgZnJvbSwgR2F0ZSB0bykgdm9pZCRcbiAgK0Rpc2Nvbm5lY3QoTGlzdH5HYXRlfiBnYXRlcykgdm9pZCRcblxuICArUmVuZGVyKHd4REMpIHZvaWQqXG4gIH5HZXRBbmNob3JQb2ludHMoKSBMaXN0fnd4UG9pbnR-KlxuICAjUmVuZGVyQW5jaG9yUG9pbnRzKCkgdm9pZFxuXG4gICNPbk1vdXNlRW50ZXIod3hNb3VzZUV2ZW50KSB2b2lkXG4gICNPbk1vdXNlTGVhdmUod3hNb3VzZUV2ZW50KSB2b2lkXG4gICNPbkxlZnREb3duKHd4TW91c2VFdmVudCkgdm9pZFxuICAjT25MZWZ0VXAod3hNb3VzZUV2ZW50KSB2b2lkXG4gICNPbldpbmRvd1VwZGF0ZSh3eElkbGVFdmVudCkgdm9pZFxufVxuXG5HYXRlIFwiMi4uOFwiIC4ufD4gXCIxXCIgTm90R2F0ZSAgICAgOiAxIGlucHV0LCAxIG91dHB1dFxuR2F0ZSBcIjMuLjhcIiAuLnw-IFwiMVwiIEFuZEdhdGUgICAgIDogMi03IGlucHV0cywgMSBvdXRwdXRcbkdhdGUgXCIzLi44XCIgLi58PiBcIjFcIiBPckdhdGUgICAgICA6IDItNyBpbnB1dHMsIDEgb3V0cHV0XG5HYXRlIFwiMy4uOFwiIC4ufD4gXCIxXCIgWG9yR2F0ZSAgICAgOiAyLTcgaW5wdXRzLCAxIG91dHB1dFxuR2F0ZSBcIjMuLjhcIiAuLnw-IFwiMVwiIE5vckdhdGUgICAgIDogMi03IGlucHV0cywgMSBvdXRwdXRcbkdhdGUgXCIzLi44XCIgLi58PiBcIjFcIiBYbm9yR2F0ZSAgICA6IDItNyBpbnB1dHMsIDEgb3V0cHV0XG5HYXRlIFwiMS4uOFwiIC4ufD4gXCIxXCIgSW5wdXQgICAgICAgOiAwIGlucHV0cywgMS04IG91dHB1dHNcbkdhdGUgXCIxXCIgICAgLi58PiBcIjFcIiBPdXRwdXQgICAgICA6IDEgaW5wdXQsIDAgb3V0cHV0c1xuR2F0ZSBcIjQuLm5cIiAuLnw-IFwiMVwiIE11bHRpcGxleGVyIDogMy1uIGlucHV0cywgMSBvdXRwdXRcblxuY2xhc3MgR2F0ZUxhYmVse1xuICArU3RyaW5nIHRleHRcblxuICBHYXRlTGFiZWwoU3RyaW5nIGRlZmF1bHRUZXh0KVxuXG4gICtDcmVhdGUoU3RyaW5nIGRlZmF1bHRUZXh0KSRcblxuICArT25DaGFuZ2VMYWJlbChTdHJpbmcgdGV4dCkgdm9pZFxufVxuXG5HYXRlSG9sZGVyICotLSBcIjFcIiBHYXRlXG5HYXRlSG9sZGVyICotLSBcIjFcIiBHYXRlTGFiZWxcblxuY2xhc3MgQ2FudmFze1xuICArTGlzdH5HYXRlfiBtX2NoaWxkcmVuXG5cbiAgQ2FudmFzKClcbiAgQ2FudmFzKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKVxuICArQ3JlYXRlKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKSBDYW52YXMkXG5cbiAgK0FkZEdhdGUoR2F0ZSwgd3hQb2ludCBwb3MpXG59XG4gIFxuQ2FudmFzIG8tLSBcIm5cIiBHYXRlSG9sZGVyXG5cbmNsYXNzIENhbnZhc0hvbGRlcntcbiAgQ2FudmFzSG9sZGVyKClcbiAgQ2FudmFzSG9sZGVyKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKVxuICArQ3JlYXRlKHd4V2luZG93IHBhcmVudCwgd3hXaW5kb3dJRCBpZCwgd3hQb2ludCBwb3MsIHd4U2l6ZSBzaXplLCBsb25nIHN0eWxlLCB3eFN0cmluZyBuYW1lKSBDYW52YXNIb2xkZXIkXG4gIC1-Q2FudmFzSG9sZGVyKClcbn1cbkNhbnZhc0hvbGRlciAqLS0gXCIxXCIgQ2FudmFzXG5cbkdhdGUgLS18PiB3eFdpbmRvd1xuR2F0ZUhvbGRlciAtLXw-IHd4V2luZG93XG5HYXRlTGFiZWwgLS18PiB3eFdpbmRvd1xuQ2FudmFzIC0tfD4gd3hXaW5kb3dcbkNhbnZhc0hvbGRlciAtLXw-IHd4V2luZG93IiwibWVybWFpZCI6eyJ0aGVtZSI6ImRlZmF1bHQifSwidXBkYXRlRWRpdG9yIjpmYWxzZX0)

