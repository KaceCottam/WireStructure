#ifndef VISUALGATES_H
#define VISUALGATES_H
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

struct VisualNotGate : public VisualGateBase
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualAndGate : public VisualGateBase
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualOrGate : public VisualGateBase
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualNorGate : public VisualOrGate
{
  using VisualOrGate::VisualOrGate;
  void render(wxDC& dc) override;
};
struct VisualXorGate : public VisualOrGate
{
  using VisualOrGate::VisualOrGate;
  void render(wxDC& dc) override;
};
struct VisualXnorGate : public VisualXorGate
{
  using VisualXorGate::VisualXorGate;
  void render(wxDC& dc) override;
};
struct VisualNandGate : public VisualAndGate
{
  using VisualAndGate::VisualAndGate;
  void render(wxDC& dc) override;
};
struct VisualInputGate : public VisualGateBase
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualOutputGate : public VisualGateBase
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
struct VisualMultiplexer : public VisualGateBase
{
  using VisualGateBase::VisualGateBase;
  void render(wxDC& dc) override;
};
#endif // ! VISUALGATES_H

