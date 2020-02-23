#ifndef VISUALGATES_H
#define VISUALGATES_H
#include <wx/wx.h>

class GateBase : public wxPanel
{
 protected:
  void resetColors(wxDC& dc) const;

 public:
  void setupDC(wxDC& dc, const wxPoint& offset);

  wxString labelText = "";

  void onPaint(wxPaintEvent&);
  void renderNow();
  virtual void render(wxDC& dc) = 0;

  explicit GateBase(wxFrame* parent);

  DECLARE_EVENT_TABLE()
};
#endif  // ! VISUALGATES_H
