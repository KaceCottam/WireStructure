#ifndef VISUALGATES_H
#define VISUALGATES_H
#include "Gates.h"

#include <wx/wx.h>
#include <vector>

struct BoundingBox : public wxPanel
{
  struct ColorData { wxColour stroke, fill; };

  explicit BoundingBox(wxFrame* parent);

  void onPaint(wxPaintEvent& event);
  // Used for connections
  void onMouseDown(wxMouseEvent& event);
  void onMouseUp(wxMouseEvent& event);
  // Highlight based on if connected
  void onMouseMove(wxMouseEvent& event);

  void render(wxDC& dc) const;

  BoundingBox* connection;

  DECLARE_EVENT_TABLE()
};

struct VisualGateBase : public wxPanel
{
  explicit VisualGateBase(wxFrame* parent);

  void onPaint(wxPaintEvent& event);
  // Used for dragging
  void onMouseDown(wxMouseEvent& event);
  void onMouseUp(wxMouseEvent& event);
  // Highlight
  void onMouseMove(wxMouseEvent& event);

  virtual void render(wxDC& dc) const = 0;
  virtual std::vector<BoundingBox*> getInputAnchors() = 0;
  virtual std::vector<BoundingBox*> getOutputAnchors() = 0;

  bool dragging = false;
  DECLARE_EVENT_TABLE()
};

struct VisualNotGate : public VisualGateBase, public NotGate
{
  explicit VisualNotGate(wxFrame* parent);
  void render(wxDC& dc) const override = 0;
  BoundingBox input, output;
};
struct VisualAndGate : public VisualGateBase, public AndGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override = 0;
};
struct VisualOrGate : public VisualGateBase, public OrGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override = 0;
};
struct VisualNorGate : public VisualGateBase, public NorGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override = 0;
};
struct VisualXorGate : public VisualGateBase, public XorGate
{
  void render(wxDC& dc) const override = 0;
};
struct VisualXnorGate : public VisualGateBase, public XnorGate
{
  void render(wxDC& dc) const override = 0;
};
struct VisualNandGate : public VisualGateBase, public NandGate
{
  void render(wxDC& dc) const override = 0;
};
struct VisualInputGate : public VisualGateBase, public InputGate
{
  void render(wxDC& dc) const override = 0;
};
struct VisualOutputGate : public VisualGateBase, public OutputGate
{
  void render(wxDC& dc) const override = 0;
};
struct VisualMultiplexer : public VisualGateBase, public Multiplexer
{
  void render(wxDC& dc) const override = 0;
};
#endif // ! VISUALGATES_H

