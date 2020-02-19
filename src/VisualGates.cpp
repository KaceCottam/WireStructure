#include "VisualGates.h"

BEGIN_EVENT_TABLE(VisualGateBase, wxPanel)
  EVT_PAINT(VisualGateBase::onPaint)
  EVT_LEFT_DOWN(VisualGateBase::onMouseDown)
  EVT_LEFT_UP(VisualGateBase::onMouseUp)
  EVT_MOTION(VisualGateBase::onMouseMove)
END_EVENT_TABLE()

VisualGateBase::VisualGateBase(wxFrame* parent) : wxPanel(parent) {}

void VisualGateBase::onPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
}
void VisualGateBase::onMouseDown(wxMouseEvent& event)
{
  dragging = true;
}
void VisualGateBase::onMouseUp(wxMouseEvent& event)
{
  dragging = false;
}
void VisualGateBase::onMouseMove(wxMouseEvent& event)
{
  if(dragging)
  {
    this->Move(event.GetPosition() - this->GetPosition());
  }
  wxClientDC dc(this);
  render(dc);
}
void VisualGateBase::setupColors(wxDC& dc) const
{
  static auto pen = wxPen(*wxBLACK, 5, wxPENSTYLE_SOLID);
  pen.SetCap(wxCAP_ROUND);
  dc.SetPen(pen);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
}

void VisualNotGate::render(wxDC& dc) const
{
  setupColors(dc);
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
  setupColors(dc);
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
  setupColors(dc);
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
  setupColors(dc);
  wxPoint point = wxPoint(0,0) + GetPosition();
  dc.DrawCircle(point, 25);
  dc.DrawText(wxT("I"), point);
}
void VisualOutputGate::render(wxDC& dc) const
{
  setupColors(dc);
  wxPoint point = wxPoint(0,0) + GetPosition();
  dc.DrawCircle(point, 25);
  dc.DrawText(wxT("O"), point);
}
void VisualMultiplexer::render(wxDC& dc) const
{
  setupColors(dc);
  wxPoint points[] =
  {
    wxPoint(-50, -50) + GetPosition(),
    wxPoint( 50, -50) + GetPosition(),
    wxPoint( 50,  50) + GetPosition(),
    wxPoint(-50,  50) + GetPosition()
  };
  dc.DrawPolygon(4, points);
}
