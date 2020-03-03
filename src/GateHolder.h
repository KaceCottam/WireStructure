#ifndef GATEHOLDER_H
#define GATEHOLDER_H
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
#endif // ! GATEHOLDER_H

