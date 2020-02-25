#ifndef CANVAS_H
#define CANVAS_H
#include <wx/wx.h>

#include <optional>

#include "Defs.h"
#include "StatusBarEvent.h"

class Canvas : public wxWindow
{
 public:
  explicit Canvas(wxWindow* parent, wxWindowID id);

 private:
  const int m_space = 20;
  wxRect m_viewRegion;
  std::optional<wxPoint> m_mouseClickedPlace;

  double GetXScaleFactor() const;
  double GetYScaleFactor() const;
  double GetScaleFactor() const;
  wxPoint RegionToClient(const wxPoint&) const;
  wxPoint ClientToRegion(const wxPoint&) const;

  void OnResize(wxSizeEvent& event);
  void OnEraseBackground(wxEraseEvent& event);
  void OnRightDown(wxMouseEvent& event);
  void OnRightUp(wxMouseEvent& event);
  void OnMouseMove(wxMouseEvent& event);
  void OnWheel(wxMouseEvent& event);

  void RenderBackground(wxDC& dc);
  void Render(wxDC& dc);

  DECLARE_EVENT_TABLE()
};
#endif // ! CANVAS_H

