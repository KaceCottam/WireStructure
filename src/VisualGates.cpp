#include "VisualGates.h"
#include <algorithm>

BEGIN_EVENT_TABLE(VisualGateBase, wxPanel)
  EVT_PAINT(VisualGateBase::onPaint)
END_EVENT_TABLE()

static wxPen deselectedPen(*wxBLACK, 5, wxPENSTYLE_SOLID|wxCAP_ROUND);
static wxPen selectedPen(wxColour(0x00cc00), 5, wxPENSTYLE_SOLID|wxCAP_ROUND);

VisualGateBase::VisualGateBase(wxFrame* parent) : wxPanel(parent)
{
  SetBackgroundStyle(wxBG_STYLE_PAINT);
  SetSize(150,150);
}

void VisualGateBase::dcSetup(wxDC& dc) const
{
  dc.SetLogicalOrigin(-25, -25);
}

void VisualGateBase::renderNow()
{
  wxClientDC dc(this);
  render(dc);
}

void VisualGateBase::resetColors(wxDC& dc) const
{
  dc.SetPen(selected ? selectedPen : deselectedPen);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
}

void VisualGateBase::onPaint(wxPaintEvent& WXUNUSED(event))
{
  wxPaintDC dc(this);
  render(dc);
}

void VisualNotGate::render(wxDC& dc)
{
  resetColors(dc);
  dcSetup(dc);

  wxPoint points[] =
  {
    wxPoint(0, 0),
    wxPoint(0, 100),
    wxPoint(100, 50),
  };
  dc.DrawPolygon(3, points);
  dc.DrawCircle(110, 50, 10);
}
void VisualAndGate::render(wxDC& dc)
{
  resetColors(dc);
  dcSetup(dc);
  wxPoint points[] =
  {
    wxPoint(50, 100),
    wxPoint(0, 100),
    wxPoint(0, 0),
    wxPoint(50, 0),
    wxPoint(50, 50),
  };
  dc.DrawLines(4,points);
  dc.DrawArc(points[0],points[3],points[4]);
}
void VisualOrGate::render(wxDC& dc)
{
  resetColors(dc);
  dcSetup(dc);
  wxPoint spline1[] =
  {
    wxPoint(0, 100),
    wxPoint(25, 50),
    wxPoint(0, 0),
  };
  dc.DrawSpline(3,spline1);
  wxPoint spline2[] =
  {
    wxPoint(0, 100),
    wxPoint(25, 90),
    wxPoint(100, 50),
  };
  dc.DrawSpline(3, spline2);
  wxPoint bottomPoints[] =
  {
    wxPoint(0, 0),
    wxPoint(25, 10),
    wxPoint(100, 50),
  };
  dc.DrawSpline(3, bottomPoints);
}
void VisualNorGate::render(wxDC& dc)
{
  VisualOrGate::render(dc);
  dc.DrawCircle(110, 50, 10);
}
void VisualXorGate::render(wxDC& dc)
{
  VisualOrGate::render(dc);
  wxPoint spline[] =
  {
    wxPoint(-10, 100),
    wxPoint(15, 50),
    wxPoint(-10, 0),
  };
  dc.DrawSpline(3, spline);
}
void VisualXnorGate::render(wxDC& dc)
{
  VisualXorGate::render(dc);
  dc.DrawCircle(110, 50, 10);
}
void VisualNandGate::render(wxDC& dc)
{
  VisualAndGate::render(dc);
  dc.DrawCircle(110, 50, 10);
}
void VisualInputGate::render(wxDC& dc)
{
  resetColors(dc);
  dcSetup(dc);
  dc.SetFont({32, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawCircle(50, 50, 25);
  dc.DrawLabel("I",wxRect(0,0,100,100),wxALIGN_CENTER);
}
void VisualOutputGate::render(wxDC& dc)
{
  resetColors(dc);
  dcSetup(dc);
  dc.SetFont({32, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawCircle(50, 50, 25);
  dc.DrawLabel("O", wxRect(0,0,100,100), wxALIGN_CENTER);
}
void VisualMultiplexer::render(wxDC& dc)
{
  resetColors(dc);
  dc.SetFont({24, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  wxPoint points[] =
  {
    wxPoint(0, 100),
    wxPoint(0, 0),
    wxPoint(50, 0),
    wxPoint(50, 100),
  };
  dc.DrawPolygon(4, points);
  dc.DrawLabel("0", wxRect(0, 0, 50, 50), wxALIGN_CENTER);
  dc.DrawLabel("1", wxRect(0, 50, 50, 50), wxALIGN_CENTER);
}
