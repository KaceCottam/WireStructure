#include "Canvas.h"

BEGIN_EVENT_TABLE(Canvas, wxWindow)
  EVT_SIZE(Canvas::OnResize)
  EVT_ERASE_BACKGROUND(Canvas::OnEraseBackground)
  EVT_RIGHT_DOWN(Canvas::OnRightDown)
  EVT_RIGHT_UP(Canvas::OnRightUp)
  EVT_MOTION(Canvas::OnMouseMove)
  EVT_MOUSEWHEEL(Canvas::OnWheel)
END_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent, wxWindowID id)
  : wxWindow(parent, id), m_viewRegion{GetClientRect()}
{
}

wxPoint Canvas::GetRegionTopLeft() const
{
  return m_viewRegion.GetBox().GetPosition();
}
wxPoint Canvas::GetRegionBottomRight() const
{
  return m_viewRegion.GetBox().GetPosition() + m_viewRegion.GetBox().GetSize();
}
double Canvas::GetXScaleFactor() const
{
  const auto [rw, rh] = m_viewRegion.GetBox().GetSize();
  const auto [w, h] = GetClientSize();
  return (double)rw/(double)w;
}
double Canvas::GetYScaleFactor() const
{
  const auto [rw, rh] = m_viewRegion.GetBox().GetSize();
  const auto [w, h] = GetClientSize();
  return (double)rh/(double)h;
}
wxPoint Canvas::RegionToClient(const wxPoint& point) const
{
  return point * GetXScaleFactor() + GetRegionTopLeft();
}
wxPoint Canvas::ClientToRegion(const wxPoint& point) const
{
  return (point - GetRegionTopLeft()) * (1/GetXScaleFactor());
}

void Canvas::OnResize(wxSizeEvent& event)
{
  m_viewRegion = {GetClientRect()};
  Refresh();
}
void Canvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  wxClientDC dc(this);
  Render(dc);
}

void Canvas::OnRightDown(wxMouseEvent& event)
{
  CaptureMouse();
  // need to calculate delta pos
  m_mouseClickedPlace = event.GetPosition();
  SetCursor(*wxCROSS_CURSOR);
}
void Canvas::OnRightUp(wxMouseEvent& WXUNUSED(event))
{
  if (!HasCapture()) return;
  ReleaseMouse();
  m_mouseClickedPlace = {};
  SetCursor(wxNullCursor);
}
void Canvas::OnMouseMove(wxMouseEvent& event)
{
  if(m_mouseClickedPlace)
  {
    // offset region
    auto mouseClickedPlace = event.GetPosition();
    auto posDelta = mouseClickedPlace - *m_mouseClickedPlace;
    m_viewRegion.Offset(-posDelta);
    m_mouseClickedPlace = mouseClickedPlace;
  }
  Refresh();
}
void Canvas::OnWheel(wxMouseEvent& event)
{
  const auto rot = event.GetWheelRotation();
  auto box = m_viewRegion.GetBox();
  box.Inflate(rot);
  box.Union(GetClientRect());

  m_viewRegion = wxRegion{box};

  Refresh();
}

void Canvas::RenderBackground(wxDC& dc)
{
  dc.SetBackground(CANVAS_BACKGROUND_COLOR);
  dc.SetPen(wxPen(CANVAS_GRID_COLOR, 2, wxPENSTYLE_SOLID));

  const auto [x1, y1] = GetRegionTopLeft();
  const auto [x2, y2] = GetRegionBottomRight();

  dc.SetLogicalOrigin(x1 % m_space, y1 % m_space);
  dc.SetUserScale(GetXScaleFactor(), GetYScaleFactor());

  Freeze();
  dc.Clear();
  for(auto j = -m_space; j <= y2 - y1 + m_space; j+=m_space)
    dc.DrawLine(-m_space, j, x2 - x1 + m_space, j);
  for(auto i = -m_space; i <= x2 - x1 + m_space; i+=m_space)
    dc.DrawLine(i, -m_space, i, y2 - y1 + m_space);
  Thaw();
}

void Canvas::Render(wxDC& dc)
{
  RenderBackground(dc);
}
