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

  void setupColors(wxDC& dc) const;

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
struct VisualNorGate : public VisualOrGate, public NorGate
{
  using VisualOrGate::VisualOrGate;
  void render(wxDC& dc) const override;
};
struct VisualXorGate : public VisualOrGate, public XorGate
{
  using VisualOrGate::VisualOrGate;
  void render(wxDC& dc) const override;
};
struct VisualXnorGate : public VisualXorGate, public XnorGate
{
  using VisualXorGate::VisualXorGate;
  void render(wxDC& dc) const override;
};
struct VisualNandGate : public VisualAndGate, public NandGate
{
  using VisualAndGate::VisualAndGate;
  void render(wxDC& dc) const override;
};
struct VisualInputGate : public VisualGateBase, public InputGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
struct VisualOutputGate : public VisualGateBase, public OutputGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
struct VisualMultiplexer : public VisualGateBase, public Multiplexer
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) const override;
};
#endif // ! VISUALGATES_H

