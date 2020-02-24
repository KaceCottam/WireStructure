#ifndef CANVAS_H
#define CANVAS_H
#include <wx/wx.h>

#include <optional>

#include "Configuration.h"

class Canvas : public wxWindow
{
 public:
  explicit Canvas(wxWindow* parent, wxWindowID id);

 private:
  const int m_space = 20;
  wxPoint m_panningOffset = {0, 0};
  std::optional<wxPoint> m_mouseClickedPlace;

  void OnEraseBackground(wxEraseEvent& event);
  void OnRightDown(wxMouseEvent& event);
  void OnRightUp(wxMouseEvent& event);
  void OnMouseMove(wxMouseEvent& event);

  void RenderBackground(wxDC& dc);
  void Render(wxDC& dc);

  DECLARE_EVENT_TABLE()
};
#endif // ! CANVAS_H

