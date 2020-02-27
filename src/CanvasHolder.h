#ifndef CANVASHOLDER_H
#define CANVASHOLDER_H
#include <wx/wx.h>
#include <wx/aui/aui.h>
#include "Canvas.h"

class CanvasHolder : public wxWindow
{
 public:
  explicit CanvasHolder(wxWindow* parent, wxWindowID id = wxID_ANY);

 private:
  wxAuiManager m_mgr;

  ~CanvasHolder();
};
#endif // ! CANVASHOLDER_H

