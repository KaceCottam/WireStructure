#include "VisualGates.h"

BEGIN_EVENT_TABLE(VisualGateBase, wxPanel)
  EVT_PAINT(VisualGateBase::onPaint)
  EVT_MOTION(VisualGateBase::onMotion)
END_EVENT_TABLE()

static wxPen shapePen(*wxBLACK, 5, wxPENSTYLE_SOLID|wxCAP_ROUND);

VisualGateBase::VisualGateBase(wxFrame* parent) : wxPanel(parent) {}

void VisualGateBase::onPaint(wxPaintEvent& WXUNUSED(event))
{
  wxPaintDC dc(this);
  render(dc);
}

void VisualGateBase::onMotion(wxMouseEvent& WXUNUSED(event))
{
}

void VisualGateBase::render(wxDC& dc) const
{
  dc.SetPen(shapePen);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
}

void VisualNotGate::render(wxDC& dc) const
{
  VisualGateBase::render(dc);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50,  0) + GetPosition()
  };
  dc.DrawPolygon(3, points);
  dc.DrawCircle(wxPoint(60,0) + GetPosition(), 10);
}
void VisualAndGate::render(wxDC& dc) const
{
  VisualGateBase::render(dc);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint(  0, 50) + GetPosition(),
    wxPoint(  0,-50) + GetPosition(),
    wxPoint(  0,  0) + GetPosition()
  };
  dc.DrawLine(points[0], points[1]);
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[3]);
  dc.DrawArc(points[2], points[3], points[4]);
}
void VisualOrGate::render(wxDC& dc) const
{
  VisualGateBase::render(dc);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint(-75,  0) + GetPosition()
  };
  dc.DrawArc(points[0], points[1], points[2]);
  wxPoint topPoints[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(  0, 40) + GetPosition(),
    wxPoint( 50,  0) + GetPosition()
  };
  dc.DrawSpline(3, topPoints);
  wxPoint bottomPoints[] =
  {
    wxPoint(-50,-50) + GetPosition(),
    wxPoint(  0,-40) + GetPosition(),
    wxPoint( 50,  0) + GetPosition()
  };
  dc.DrawSpline(3, bottomPoints);
}
void VisualNorGate::render(wxDC& dc) const
{
  VisualOrGate::render(dc); 
  dc.DrawCircle(wxPoint(60,0) + GetPosition(), 10);
}
void VisualXorGate::render(wxDC& dc) const
{
  VisualOrGate::render(dc); 
  wxPoint points[] =
  {
    wxPoint(-70, 50) + GetPosition(),
    wxPoint(-70,-50) + GetPosition(),
    wxPoint(-95,  0) + GetPosition()
  };
  dc.DrawArc(points[0], points[1], points[2]);
}
void VisualXnorGate::render(wxDC& dc) const
{
  VisualXorGate::render(dc);
  dc.DrawCircle(wxPoint(60,0) + GetPosition(), 10);
}
void VisualNandGate::render(wxDC& dc) const
{
  VisualAndGate::render(dc);
  dc.DrawCircle(wxPoint(60,0) + GetPosition(), 10);
}
void VisualInputGate::render(wxDC& dc) const
{
  VisualGateBase::render(dc);
  dc.SetFont(wxFont(32,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawCircle(wxPoint(0,0) + GetPosition(), 25);
  dc.DrawLabel(wxT("I"),wxRect(wxPoint(-25,-25) + GetPosition(), wxSize(50,50)),wxALIGN_CENTER);
}
void VisualOutputGate::render(wxDC& dc) const
{
  VisualGateBase::render(dc);
  dc.SetFont(wxFont(32,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawCircle(wxPoint(0,0) + GetPosition(), 25);
  dc.DrawLabel(wxT("O"),wxRect(wxPoint(-25,-25) + GetPosition(), wxSize(50,50)),wxALIGN_CENTER);
}
void VisualMultiplexer::render(wxDC& dc) const
{
  VisualGateBase::render(dc);
  dc.SetFont(wxFont(24,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-25, -50) + GetPosition(),
    wxPoint( 25, -50) + GetPosition(),
    wxPoint( 25,  50) + GetPosition(),
    wxPoint(-25,  50) + GetPosition()
  };
  dc.DrawPolygon(4, points);
  dc.DrawLabel(wxT("0"),wxRect(wxPoint(-25,-50) + GetPosition(), wxSize(50,50)),wxALIGN_CENTER);
  dc.DrawLabel(wxT("1"),wxRect(wxPoint(-25,  0) + GetPosition(), wxSize(50,50)),wxALIGN_CENTER);
}
