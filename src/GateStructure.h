#ifndef GATESTRUCTURE_H
#define GATESTRUCTURE_H
#include <wx/wx.h>
#include "VisualGates.h"
class GateHolder : public wxWindow
{
 public:
  explicit GateHolder(wxFrame* frame, wxWindowID id = wxID_ANY,
    const wxString& label = wxEmptyString);

 private:
  bool m_selected = false;
  wxTextCtrl* m_labelText;

  void BindEvents();

  void OnLeftDClick(wxMouseEvent& event);
  void OnMouseEnter(wxMouseEvent& event);
  void OnMouseLeave(wxMouseEvent& event);
  void OnMenu(wxContextMenuEvent& event);
};
#endif // ! GATESTRUCTURE_H

