#include "Canvas.h"
#include <algorithm>
#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(Canvas, wxPanel)
  EVT_CONTEXT_MENU(Canvas::onContextMenu)
  EVT_MENU(wxID_ANY, Canvas::addGate)
  EVT_LEFT_UP(Canvas::onLeftUp)
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
    case OrID:
      newGate = new VisualOrGate((wxFrame*)GetParent());
      break;
    case NorID:
      newGate = new VisualNorGate((wxFrame*)GetParent());
      break;
    case XorID:
      newGate = new VisualXorGate((wxFrame*)GetParent());
      break;
    case XnorID:
      newGate = new VisualXnorGate((wxFrame*)GetParent());
      break;
    case NandID:
      newGate = new VisualNandGate((wxFrame*)GetParent());
      break;
    case InputID:
      newGate = new VisualInputGate((wxFrame*)GetParent());
      break;
    case OutputID:
      newGate = new VisualOutputGate((wxFrame*)GetParent());
      break;
    case MultiplexerID:
      newGate = new VisualMultiplexer((wxFrame*)GetParent());
      break;
  }
  newGate->SetPosition(contextMenuOpenPos - newGate->GetSize().Scale(0.5, 0.5));
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
  contextMenuOpenPos = ScreenToClient(event.GetPosition());
  PopupMenu(&menu, ScreenToClient(event.GetPosition()));
}
void Canvas::onPaint(wxPaintEvent& WXUNUSED(event))
{
  wxBufferedPaintDC dc(this);
  render(dc);
}
void Canvas::onLeftUp(wxMouseEvent& event)
{
  for(const auto& i : gates)
  {
    auto rect = i->GetScreenRect();
    if(rect.Contains(event.GetPosition()))
    {
      i->selected = !i->selected;
      Refresh();
    }
  }
}

void Canvas::render(wxDC& dc)
{
  dc.Clear();
  dc.SetPen(wxPen(wxColour(0xdddddd), 2, wxPENSTYLE_SOLID));
  const auto [width, height] = wxPanel::GetSize();

  for(auto j = 0; j <= height + space; j += space)
      dc.DrawLine(0, j, width + space, j);
  for(auto i = 0; i <= width + space; i += space)
      dc.DrawLine(i, 0, i, height + space);

  for(auto i : gates) i->renderNow();
}
