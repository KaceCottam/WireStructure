#include "Canvas.h"

Canvas::Canvas(wxFrame* parent) : wxPanel(parent)
{
  this->SetBackgroundColour(wxColour(255,255,255));
}

BEGIN_EVENT_TABLE(Canvas, wxPanel)
  EVT_MOTION(Canvas::onMouseMove)
  EVT_LEFT_DOWN(Canvas::onMouseDown)
  EVT_LEFT_UP(Canvas::onMouseUp)
  EVT_MOUSEWHEEL(Canvas::onMouseWheel)
  EVT_PAINT(Canvas::onPaint)
END_EVENT_TABLE()

void Canvas::onMouseMove(wxMouseEvent& WXUNUSED(event)) {}
void Canvas::onMouseDown(wxMouseEvent& WXUNUSED(event)) {}
void Canvas::onMouseUp(wxMouseEvent& WXUNUSED(event)) {}
void Canvas::onMouseWheel(wxMouseEvent& WXUNUSED(event)) {}
void Canvas::onPaint(wxPaintEvent& WXUNUSED(event))
{
  wxPaintDC dc(this);
  dc.SetPen(wxPen(wxColour(0xdddddd), 2, wxPENSTYLE_SOLID));
  int width, height;
  wxPanel::GetSize(&width, &height);
  for(auto i = 0; i < width + space; i += space)
  {
    for(auto j = 0; j < height + space; j += space)
    {
      dc.DrawLine(wxPoint(i,0), wxPoint(i,j));
      dc.DrawLine(wxPoint(0,j), wxPoint(i,j));
    }
  }
}
