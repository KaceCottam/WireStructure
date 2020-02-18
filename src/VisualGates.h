#ifndef VISUALGATE_H
#define VISUALGATE_H
#include "Gates.h"

#include <SFML/Graphics.hpp>

#include <variant>

template<class Gate>
class VisualBaseGate
  : public Gate, public sf::Drawable, public sf::Transformable { };

// TODO implement draw functions inside of these
class VisualNotGate     : public VisualBaseGate<NotGate> { };
class VisualAndGate     : public VisualBaseGate<AndGate> { };
class VisualOrGate      : public VisualBaseGate<OrGate> { };
class VisualNorGate     : public VisualBaseGate<NorGate> { };
class VisualXorGate     : public VisualBaseGate<XorGate> { };
class VisualXnorGate    : public VisualBaseGate<XnorGate> { };
class VisualNandGate    : public VisualBaseGate<NandGate> { };
class VisualInputGate   : public VisualBaseGate<InputGate> { };
class VisualOutputGate  : public VisualBaseGate<OutputGate> { };
class VisualMultiplexer : public VisualBaseGate<Multiplexer> { };

using AnyVisualGate = std::variant<
  VisualNotGate, VisualAndGate, VisualOrGate, VisualNorGate, VisualXorGate,
  VisualXnorGate, VisualNandGate, VisualInputGate, VisualOutputGate,
  VisualMultiplexer>;

#endif // ! VISUALGATE_H

