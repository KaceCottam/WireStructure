#include "Canvas.h"
#include <algorithm>
#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(Canvas, wxPanel)
  EVT_CONTEXT_MENU(Canvas::onContextMenu)
  EVT_MENU(wxID_ANY, Canvas::addGate)
  EVT_PAINT(Canvas::onPaint)
END_EVENT_TABLE()

Canvas::Canvas(wxFrame* parent) : wxPanel(parent)
{
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  SetBackgroundColour(wxColour(255,255,255));
  SetExtraStyle(wxRAISED_BORDER);
  SetDoubleBuffered(true);
}

void Canvas::addGate(wxCommandEvent& event)
{
  VisualGateBase* newGate;
  switch(event.GetId())
  {
    case NotID:
      newGate = new VisualNotGate((wxFrame*)GetParent());
      break;
    case AndID:
      newGate = new VisualAndGate((wxFrame*)GetParent());
      break;
  }
  newGate->SetPosition(wxPoint(250,250));
  gates.push_back(newGate);
}

void Canvas::onContextMenu(wxContextMenuEvent& event)
{
  wxMenu menu;
  menu.Append(NotID, wxT("Add NOT Gate"));
  menu.Append(AndID, wxT("Add AND Gate"));
  menu.Append(OrID, wxT("Add OR Gate"));
  menu.Append(NorID, wxT("Add NOR Gate"));
  menu.Append(XorID, wxT("Add XOR Gate"));
  menu.Append(XnorID, wxT("Add XNOR Gate"));
  menu.Append(NandID, wxT("Add NAND Gate"));
  menu.Append(InputID, wxT("Add INPUT"));
  menu.Append(OutputID, wxT("Add OUTPUT"));
  menu.Append(MultiplexerID, wxT("Add MULTIPLEXER"));
  PopupMenu(&menu, ScreenToClient(event.GetPosition()));
}
void Canvas::onPaint(wxPaintEvent& WXUNUSED(event))
{
  wxBufferedPaintDC dc(this);
  render(dc);
}

void Canvas::render(wxDC& dc) const
{
  dc.Clear();
  dc.SetPen(wxPen(wxColour(0xdddddd), 2, wxPENSTYLE_SOLID));
  const auto [width, height] = wxPanel::GetSize();

  for(auto j = 0; j <= height + space; j += space)
      dc.DrawLine(0, j, width + space, j);
  for(auto i = 0; i <= width + space; i += space)
      dc.DrawLine(i, 0, i, height + space);

  for(auto i : gates) i->render(dc);
}
