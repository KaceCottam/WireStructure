#include "VisualGates.h"

VisualGateDatabase& VisualGateDatabase::GetInstance()
{
  static VisualGateDatabase s_db;
  return s_db;
}

VisualGateDatabase::VisualGateDatabase()
{
  RerenderBitmaps();
}

void VisualGateDatabase::RerenderBitmaps()
{
  wxMemoryDC dc;
  dc.SetLogicalOrigin(-25, -25);
  dc.SetPen(wxPen(WIRE_NORMAL_COLOR, 5));
  dc.SetBrush(wxBrush(CANVAS_BACKGROUND_COLOR));
  m_notGate.Create(150, 150);
  m_andGate.Create(150, 150);
  m_orGate.Create(150, 150);
  m_norGate.Create(150, 150);
  m_xorGate.Create(150, 150);
  m_xnorGate.Create(150, 150);
  m_nandGate.Create(150, 150);
  m_input.Create(150, 150);
  m_output.Create(150, 150);
  m_multiplexer.Create(150, 150);
  dc.SelectObject(m_notGate);
  RenderNotGate(dc);
  dc.SelectObject(m_andGate);
  RenderAndGate(dc);
  dc.SelectObject(m_orGate);
  RenderOrGate(dc);
  dc.SelectObject(m_norGate);
  RenderNorGate(dc);
  dc.SelectObject(m_xorGate);
  RenderXorGate(dc);
  dc.SelectObject(m_xnorGate);
  RenderXnorGate(dc);
  dc.SelectObject(m_nandGate);
  RenderNandGate(dc);
  dc.SelectObject(m_input);
  RenderInput(dc);
  dc.SelectObject(m_output);
  RenderOutput(dc);
  dc.SelectObject(m_multiplexer);
  RenderMultiplexer(dc);
}

wxBitmap VisualGateDatabase::GetNotGate()
{
  return m_notGate;
}
wxBitmap VisualGateDatabase::GetAndGate()
{
  return m_andGate;
}
wxBitmap VisualGateDatabase::GetOrGate()
{
  return m_orGate;
}
wxBitmap VisualGateDatabase::GetNorGate()
{
  return m_norGate;
}
wxBitmap VisualGateDatabase::GetXorGate()
{
  return m_xorGate;
}
wxBitmap VisualGateDatabase::GetXnorGate()
{
  return m_xnorGate;
}
wxBitmap VisualGateDatabase::GetNandGate()
{
  return m_nandGate;
}
wxBitmap VisualGateDatabase::GetInput()
{
  return m_input;
}
wxBitmap VisualGateDatabase::GetOutput()
{
  return m_output;
}
wxBitmap VisualGateDatabase::GetMultiplexer()
{
  return m_multiplexer;
}

void VisualGateDatabase::RenderNotGate(wxDC& dc)
{
  wxPoint points[] =
  {
    wxPoint(0, 0),
    wxPoint(0, 100),
    wxPoint(100, 50),
  };
  dc.DrawPolygon(3, points);
  dc.DrawCircle(110, 50, 10);
}
void VisualGateDatabase::RenderAndGate(wxDC& dc)
{
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
void VisualGateDatabase::RenderOrGate(wxDC& dc)
{
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
void VisualGateDatabase::RenderNorGate(wxDC& dc)
{
  RenderOrGate(dc);
  dc.DrawCircle(110, 50, 10);
}
void VisualGateDatabase::RenderXorGate(wxDC& dc)
{
  RenderOrGate(dc);
  wxPoint spline[] =
  {
    wxPoint(-10, 100),
    wxPoint(15, 50),
    wxPoint(-10, 0),
  };
  dc.DrawSpline(3, spline);
}
void VisualGateDatabase::RenderXnorGate(wxDC& dc)
{
  RenderXorGate(dc);
  dc.DrawCircle(110, 50, 10);
}
void VisualGateDatabase::RenderNandGate(wxDC& dc)
{
  RenderAndGate(dc);
  dc.DrawCircle(110, 50, 10);
}
void VisualGateDatabase::RenderInput(wxDC& dc)
{
  dc.SetFont({32, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.DrawCircle(50, 50, 25);
  dc.DrawLabel("I", wxRect(0,0,100,100), wxALIGN_CENTER);
}
void VisualGateDatabase::RenderOutput(wxDC& dc)
{
  dc.SetFont({32, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.DrawCircle(50, 50, 25);
  dc.DrawLabel("O", wxRect(0,0,100,100), wxALIGN_CENTER);
}
void VisualGateDatabase::RenderMultiplexer(wxDC& dc)
{
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
