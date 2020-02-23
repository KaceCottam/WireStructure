#ifndef GATES_H
#define GATES_H
#include "GateBase.h"

struct NotGate : public GateBase
{
  void render(wxDC& dc) override;
  using GateBase::GateBase;
};
struct AndGate : public GateBase
{
  void render(wxDC& dc) override;
  using GateBase::GateBase;
};
struct OrGate : public GateBase
{
  void render(wxDC& dc) override;
  using GateBase::GateBase;
};
struct NorGate : public OrGate
{
  void render(wxDC& dc) override;
  using OrGate::OrGate;
};
struct XorGate : public OrGate
{
  void render(wxDC& dc) override;
  using OrGate::OrGate;
};
struct XnorGate : public XorGate
{
  void render(wxDC& dc) override;
  using XorGate::XorGate;
};
struct NandGate : public AndGate
{
  void render(wxDC& dc) override;
  using AndGate::AndGate;
};
struct InputGate : public GateBase
{
  void render(wxDC& dc) override;
  using GateBase::GateBase;
};
struct OutputGate : public GateBase
{
  void render(wxDC& dc) override;
  using GateBase::GateBase;
};
struct Multiplexer : public GateBase
{
  void render(wxDC& dc) override;
  using GateBase::GateBase;
};
struct Label : public GateBase
{
  explicit Label(wxFrame* parent);

  wxString labelText = "New Label";
  void render(wxDC& dc) override;

  void onLeftDClick(wxMouseEvent&);
  void onContextMenu(wxContextMenuEvent&);
  void addLabel(wxCommandEvent&);

  DECLARE_EVENT_TABLE()
};

#endif // ! GATES_H

