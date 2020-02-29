#include "GateStructure.h"

GateHolder::GateHolder(wxFrame* frame, wxWindowID id, const wxString& label)
  : wxWindow{frame, id}, m_labelText{new wxTextCtrl(frame, id)}
{
}

void GateHolder::BindEvents()
{
  Bind(wxEVT_PAINT, &GateHolder::OnPaint, this);
  Bind(wxEVT_LEFT_DCLICK, &GateHolder::OnLeftDClick, this);
  Bind(wxEVT_ENTER_WINDOW, &GateHolder::OnMouseEnter, this);
  Bind(wxEVT_LEAVE_WINDOW, &GateHolder::OnMouseLeave, this);
  Bind(wxEVT_CONTEXT_MENU, &GateHolder::OnMenu, this);
}

void GateHolder::OnLeftDClick(wxMouseEvent& event)
{
}
void GateHolder::OnMouseEnter(wxMouseEvent& event)
{
}
void GateHolder::OnMouseLeave(wxMouseEvent& event)
{
}
void GateHolder::OnMenu(wxContextMenuEvent& event)
{
}
