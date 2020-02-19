#ifndef VISUALGATES_H
#define VISUALGATES_H
#include "Gates.h"

#include <wx/wx.h>
#include <vector>

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

  bool dragging = false;
  DECLARE_EVENT_TABLE()
};

struct VisualNotGate : public VisualGateBase, public NotGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
struct VisualAndGate : public VisualGateBase, public AndGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
struct VisualOrGate : public VisualGateBase, public OrGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
struct VisualNorGate : public VisualGateBase, public NorGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
struct VisualXorGate : public VisualGateBase, public XorGate
{
  void render(wxDC& dc) const override;
};
struct VisualXnorGate : public VisualGateBase, public XnorGate
{
  void render(wxDC& dc) const override;
};
struct VisualNandGate : public VisualGateBase, public NandGate
{
  void render(wxDC& dc) const override;
};
struct VisualInputGate : public VisualGateBase, public InputGate
{
  void render(wxDC& dc) const override;
};
struct VisualOutputGate : public VisualGateBase, public OutputGate
{
  void render(wxDC& dc) const override;
};
struct VisualMultiplexer : public VisualGateBase, public Multiplexer
{
  void render(wxDC& dc) const override;
};
#endif // ! VISUALGATES_H

