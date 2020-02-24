#include "Canvas.h"

BEGIN_EVENT_TABLE(Canvas, wxWindow)
  EVT_ERASE_BACKGROUND(Canvas::OnEraseBackground)
  EVT_RIGHT_DOWN(Canvas::OnRightDown)
  EVT_RIGHT_UP(Canvas::OnRightUp)
  EVT_MOTION(Canvas::OnMouseMove)
END_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent, wxWindowID id)
  : wxWindow(parent, id)
{
}

void Canvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  wxClientDC dc(this);
  Render(dc);
}

void Canvas::OnRightDown(wxMouseEvent& event)
{
  CaptureMouse();
  m_mouseClickedPlace = m_panningOffset + event.GetPosition();
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
    m_panningOffset = event.GetPosition() - *m_mouseClickedPlace;
  }
  Refresh();
}

void Canvas::RenderBackground(wxDC& dc)
{
  const auto [width, height] = GetSize();
  dc.SetBackground(Configuration::GetInstance()["CANVAS_BACKGROUND_COLOR"]);
  dc.SetPen(wxPen(Configuration::GetInstance()["CANVAS_GRID_COLOR"], 2,
    wxPENSTYLE_SOLID));

  dc.SetLogicalOrigin(-m_panningOffset.x % m_space,
      -m_panningOffset.y % m_space);

  Freeze();
  dc.Clear();
  for(auto j = -m_space; j <= height + m_space; j += m_space)
    dc.DrawLine(-m_space, j, width + m_space, j);
  for(auto i = -m_space; i <= width + m_space; i += m_space)
    dc.DrawLine(i, -m_space, i, height + m_space);
  Thaw();
}

void Canvas::Render(wxDC& dc)
{
  RenderBackground(dc);
}
