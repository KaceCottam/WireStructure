#include "VisualGates.h"

BEGIN_EVENT_TABLE(BoundingBox, wxPanel)
  EVT_PAINT(BoundingBox::onPaint)
  EVT_LEFT_DOWN(BoundingBox::onMouseDown)
  EVT_LEFT_UP(BoundingBox::onMouseUp)
  EVT_MOTION(BoundingBox::onMouseMove)
END_EVENT_TABLE()

BoundingBox::BoundingBox(wxFrame* parent) : wxPanel(parent) {}

void BoundingBox::onPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
}
void BoundingBox::onMouseDown(wxMouseEvent& event) {}
void BoundingBox::onMouseUp(wxMouseEvent& event) {}
void BoundingBox::onMouseMove(wxMouseEvent& event) {}
void BoundingBox::render(wxDC& dc) const
{
  static ColorData connected{wxColour(0x01440a), wxColour(0x00ff21)};
  static ColorData disconnected{wxColour(0x440401), wxColour(0xfc0c00)};
  ColorData& cd = connection == nullptr ? disconnected : connected;
  dc.SetPen(wxPen(cd.stroke, 3));
  dc.SetBrush(wxBrush(cd.fill));
  dc.DrawCircle(wxPanel::GetPosition(), 5);
}

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
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0)
  };
  dc.DrawPolygon(3, points);
  dc.DrawCircle(wxPoint(6,0), 1);
}
void VisualAndGate::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0)
  };
  dc.DrawLine(points[0], points[1]);
  dc.DrawArc(points[0], points[1], points[2]);
}
void VisualOrGate::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0),
    wxPoint(0,0)
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
}
void VisualNorGate::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0),
    wxPoint( 0, 0),
    wxPoint( 6, 0)
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
  dc.DrawCircle(points[4], 1);
}
void VisualXorGate::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0),
    wxPoint( 0, 0),
    wxPoint( 6, 0),
    wxPoint(-7, 5),
    wxPoint(-7,-5),
    wxPoint( 3, 0)
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
  dc.DrawArc(points[5], points[6], points[7]);
}
void VisualXnorGate::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0),
    wxPoint( 0, 0),
    wxPoint( 6, 0),
    wxPoint(-7, 5),
    wxPoint(-7,-5),
    wxPoint( 3, 0),
    wxPoint( 6, 0)
  };
  dc.DrawLine(points[0], points[2]);
  dc.DrawLine(points[1], points[2]);
  dc.DrawArc(points[0], points[1], points[3]);
  dc.DrawArc(points[5], points[6], points[7]);
  dc.DrawCircle(points[8], 1);
}
void VisualNandGate::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, 5),
    wxPoint(-5,-5),
    wxPoint( 5, 0),
    wxPoint( 6, 0)
  };
  dc.DrawLine(points[0], points[1]);
  dc.DrawArc(points[0], points[1], points[2]);
  dc.DrawCircle(points[3], 1);
}
void VisualInputGate::render(wxDC& dc) const
{
  wxPoint point = wxPoint(0,0);
  dc.DrawCircle(point, 3);
  dc.DrawText(wxT("I"), point);
}
void VisualOutputGate::render(wxDC& dc) const
{
  wxPoint point = wxPoint(0,0);
  dc.DrawCircle(point, 3);
  dc.DrawText(wxT("O"), point);
}
void VisualMultiplexer::render(wxDC& dc) const
{
  wxPoint points[] =
  {
    wxPoint(-5, -5),
    wxPoint( 5, -5),
    wxPoint( 5,  5),
    wxPoint(-5,  5),
  };
  dc.DrawPolygon(4, points);
}
