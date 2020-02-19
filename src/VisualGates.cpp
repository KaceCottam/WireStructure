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

//VisualNot
void VisualNotGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition()
  };
  dc.DrawPolygon(3, points);
  dc.DrawCircle(wxPoint(60,0) + GetPosition(), 10);
}
void VisualAndGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition()
  };
  dc.DrawLine(points[0], points[1]);
  dc.DrawArc(points[0], points[1], points[2]);
}
void VisualOrGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition(),
    wxPoint(0,0) + GetPosition()
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
}
void VisualNorGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition(),
    wxPoint( 0, 0) + GetPosition(),
    wxPoint( 6, 0) + GetPosition()
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
  dc.DrawCircle(points[4], 10);
}
void VisualXorGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition(),
    wxPoint( 0, 0) + GetPosition(),
    wxPoint( 60, 0) + GetPosition(),
    wxPoint(-70, 50) + GetPosition(),
    wxPoint(-70,-50) + GetPosition(),
    wxPoint( 30, 0) + GetPosition()
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
  dc.DrawArc(points[5], points[6], points[7]);
}
void VisualXnorGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition(),
    wxPoint( 0, 0) + GetPosition(),
    wxPoint( 60, 0) + GetPosition(),
    wxPoint(-70, 50) + GetPosition(),
    wxPoint(-70,-50) + GetPosition(),
    wxPoint( 30, 0) + GetPosition(),
    wxPoint( 60, 0) + GetPosition()
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
  dc.DrawArc(points[5], points[6], points[7]);
  dc.DrawCircle(points[8], 10);
}
void VisualNandGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, 50) + GetPosition(),
    wxPoint(-50,-50) + GetPosition(),
    wxPoint( 50, 0) + GetPosition(),
    wxPoint( 60, 0) + GetPosition()
  };
  dc.DrawLine(points[0], points[1]);
  dc.DrawArc(points[0], points[1], points[2]);
  dc.DrawCircle(points[3], 10);
}
void VisualInputGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint point = wxPoint(0,0) + GetPosition();
  dc.DrawCircle(point, 3);
  dc.DrawText(wxT("I"), point);
}
void VisualOutputGate::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint point = wxPoint(0,0) + GetPosition();
  dc.DrawCircle(point, 3);
  dc.DrawText(wxT("O"), point);
}
void VisualMultiplexer::render(wxDC& dc) const
{
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxPoint points[] =
  {
    wxPoint(-50, -50) + GetPosition(),
    wxPoint( 50, -50) + GetPosition(),
    wxPoint( 50,  50) + GetPosition(),
    wxPoint(-50,  50) + GetPosition()
  };
  dc.DrawPolygon(4, points);
}
