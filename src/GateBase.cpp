#include "GateBase.h"
#include <algorithm>

BEGIN_EVENT_TABLE(GateBase, wxPanel)
  EVT_PAINT(GateBase::onPaint)
END_EVENT_TABLE()

GateBase::GateBase(wxFrame* parent)
  : wxPanel(parent)
{
  SetSize(150, 150);
}

void GateBase::resetColors(wxDC& dc) const
{
  dc.SetPen(wxPen(*wxBLACK, 5));
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
}

void GateBase::setupDC(wxDC& dc, const wxPoint& offset)
{
  const auto [w, h] = GetSize();
  dc.SetLogicalOrigin(offset.x, offset.y);
}

void GateBase::onPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
  event.Skip();
}

void GateBase::renderNow()
{
  wxClientDC dc(this);
  render(dc);
}

