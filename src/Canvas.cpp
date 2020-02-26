#include "Canvas.h"

Canvas::Canvas(wxWindow* parent, wxWindowID id)
  : wxWindow(parent, id), m_viewRegion{GetClientRect()}
{
  BindEvents();
}

void Canvas::BindEvents()
{
  Bind(wxEVT_SIZE, &Canvas::OnResize, this);
  Bind(wxEVT_ERASE_BACKGROUND, &Canvas::OnEraseBackground, this);
  Bind(wxEVT_RIGHT_DOWN, &Canvas::OnRightDown, this);
  Bind(wxEVT_RIGHT_UP, &Canvas::OnRightUp, this);
  Bind(wxEVT_MOTION, &Canvas::OnMouseMove, this);
  Bind(wxEVT_MOUSEWHEEL, &Canvas::OnWheel, this);
}

double Canvas::GetXScaleFactor() const
{
  const auto [rw, rh] = m_viewRegion.GetSize();
  const auto [w, h] = GetClientSize();

  return (double)rw/(double)w;
}
double Canvas::GetYScaleFactor() const
{
  const auto [rw, rh] = m_viewRegion.GetSize();
  const auto [w, h] = GetClientSize();
  return (double)rh/(double)h;
}
double Canvas::GetScaleFactor() const
{
  return GetXScaleFactor();
}
wxPoint Canvas::RegionToClient(const wxPoint& point) const
{
  return point * GetScaleFactor() + m_viewRegion.GetTopLeft();
}
wxPoint Canvas::ClientToRegion(const wxPoint& point) const
{
  return (point - m_viewRegion.GetTopLeft()) * (1/GetScaleFactor());
}

void Canvas::OnResize(wxSizeEvent& event)
{
  m_viewRegion = {GetClientRect()};
  Refresh();
}
void Canvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  wxClientDC dc(this);
  RenderBackground(dc);
}

void Canvas::OnRightDown(wxMouseEvent& event)
{
  CaptureMouse();
  m_mouseClickedPlace = event.GetPosition();
  SetCursor(wxCURSOR_HAND);
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
  } else {
    SetCursor(wxNullCursor);
  }
  Refresh();
}
void Canvas::OnWheel(wxMouseEvent& event)
{
  static constexpr double maxFactor = 5;
  static constexpr double minFactor = 0.80;

  SetCursor(wxCURSOR_MAGNIFIER);
  const auto rot = event.GetWheelRotation();
  auto& box = m_viewRegion;
  const auto sf = GetScaleFactor();

  if(sf < maxFactor && sf > minFactor) box.Inflate(rot);
  else if(rot < 0 && sf > minFactor) box.Inflate(rot); // Small limit
  else if(rot > 0 && sf < maxFactor) box.Inflate(rot); // Big limit

  Refresh();
}
void Canvas::OnRequestAddMenu()
{
  wxLogMessage("Adding menu");
}
void Canvas::OnRequestDeleteMenu()
{
  wxLogMessage("Deleting menu");
}

void Canvas::RenderBackground(wxDC& dc)
{
  dc.SetBackground(CANVAS_BACKGROUND_COLOR);
  dc.SetPen(wxPen(CANVAS_GRID_COLOR, 2, wxPENSTYLE_SOLID));

  const auto [x1, y1] = m_viewRegion.GetTopLeft();
  const auto [width, height] = GetClientSize();
  const auto space = m_space*GetScaleFactor();

  dc.SetLogicalOrigin(std::fmod(x1, space), std::fmod(y1, space));

  Freeze();
  dc.Clear();
  if(gridType == LINE)
  {
    for(auto j = -space; j <= height + space; j += space)
      dc.DrawLine(-space, j, width + space, j);
    for(auto i = -space; i <= width + space; i += space)
      dc.DrawLine(i, -space, i, height + space);
  } else if(gridType == DOTMATRIX)
  {
    for(auto i = -space; i <= width + space; i += space)
      for(auto j = -space; j <= height + space; j += space)
        dc.DrawPoint(i, j);
  }
  Thaw();
}

void Canvas::Render(wxDC& dc)
{
  RenderBackground(dc);
}
