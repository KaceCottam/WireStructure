#ifndef VISUALGATES_H
#define VISUALGATES_H
#include "Gates.h"

#include <wx/wx.h>
#include <vector>

struct VisualGateBase : public wxPanel
{
  bool selected = false;

  explicit VisualGateBase(wxFrame* parent);

  virtual void render(wxDC& dc) = 0;
  void dcSetup(wxDC& dc) const;
  void renderNow();
  void resetColors(wxDC& dc) const;

  void onPaint(wxPaintEvent& event);

  DECLARE_EVENT_TABLE()
};

struct VisualNotGate : public VisualGateBase, public NotGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualAndGate : public VisualGateBase, public AndGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualOrGate : public VisualGateBase, public OrGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualNorGate : public VisualOrGate, public NorGate
{
  using VisualOrGate::VisualOrGate;
  void render(wxDC& dc) override;
};
struct VisualXorGate : public VisualOrGate, public XorGate
{
  using VisualOrGate::VisualOrGate;
  void render(wxDC& dc) override;
};
struct VisualXnorGate : public VisualXorGate, public XnorGate
{
  using VisualXorGate::VisualXorGate;
  void render(wxDC& dc) override;
};
struct VisualNandGate : public VisualAndGate, public NandGate
{
  using VisualAndGate::VisualAndGate;
  void render(wxDC& dc) override;
};
struct VisualInputGate : public VisualGateBase, public InputGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualOutputGate : public VisualGateBase, public OutputGate
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualMultiplexer : public VisualGateBase, public Multiplexer
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
#endif // ! VISUALGATES_H

