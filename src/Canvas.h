#ifndef CANVAS_H
#define CANVAS_H
#include <wx/wx.h>

class Canvas : public wxPanel
{
  static constexpr int space = 50;
 public:
  Canvas(wxFrame* parent);

  void onMouseMove(wxMouseEvent& event);
  void onMouseDown(wxMouseEvent& event);
  void onMouseUp(wxMouseEvent& event);
  void onMouseWheel(wxMouseEvent& event);
  void onPaint(wxPaintEvent& event);

  DECLARE_EVENT_TABLE()
};
#endif // ! CANVAS_H

