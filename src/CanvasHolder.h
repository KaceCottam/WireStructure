#ifndef CANVASHOLDER_H
#define CANVASHOLDER_H
#include <wx/wx.h>
#include <wx/splitter.h>
#include "Canvas.h"

class CanvasHolder : public wxWindow
{
 public:
  explicit CanvasHolder(wxWindow* parent, wxWindowID id = wxID_ANY);
};
#endif // ! CANVASHOLDER_H

