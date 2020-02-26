#ifndef CANVAS_H
#define CANVAS_H
#include <wx/wx.h>

#include <optional>

#include "Defs.h"
#include "StatusBarEvent.h"

class Canvas : public wxWindow
{
 public:
  explicit Canvas(wxWindow* parent, wxWindowID id = wxID_ANY);

 private:
  const int m_space = 20;
  enum
  {
    HIDDEN, LINE, DOTMATRIX
  } gridType{LINE};
  wxRect m_viewRegion;
  std::optional<wxPoint> m_mouseClickedPlace;

  void BindEvents();

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
  void OnRequestAddMenu();
  void OnRequestDeleteMenu();

  void RenderBackground(wxDC& dc);
  void Render(wxDC& dc);
};
#endif // ! CANVAS_H

