#include "GateStructure.h"

GateHolder::GateHolder(wxFrame* frame, wxWindowID id, const wxString& label)
  : wxWindow{frame, id}, m_labelText{new wxTextCtrl(frame, id)}
{
}

void GateHolder::BindEvents()
{
}

void  GateHolder::OnPaint(wxPaintEvent& event)
{
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
