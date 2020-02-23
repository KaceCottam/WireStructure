#include "Canvas.h"
#include <wx/dcbuffer.h>
#include <algorithm>

BEGIN_EVENT_TABLE(Canvas, wxPanel)
  EVT_PAINT(Canvas::onPaint)
  EVT_CONTEXT_MENU(Canvas::onContextMenu)
  EVT_MENU(wxID_ANY, Canvas::addGate)
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
  GateBase* newGate;
  switch(event.GetId())
  {
    case NotID:
      newGate = new NotGate((wxFrame*)this);
      break;
    case AndID:
      newGate = new AndGate((wxFrame*)this);
      break;
    case OrID:
      newGate = new OrGate((wxFrame*)this);
      break;
    case NorID:
      newGate = new NorGate((wxFrame*)this);
      break;
    case XorID:
      newGate = new XorGate((wxFrame*)this);
      break;
    case XnorID:
      newGate = new XnorGate((wxFrame*)this);
      break;
    case NandID:
      newGate = new NandGate((wxFrame*)this);
      break;
    case InputID:
      newGate = new InputGate((wxFrame*)this);
      break;
    case OutputID:
      newGate = new OutputGate((wxFrame*)this);
      break;
    case MultiplexerID:
      newGate = new Multiplexer((wxFrame*)this);
      break;
    case LabelID:
      newGate = new Label((wxFrame*)this);
      break;
  }
  newGate->SetPosition(contextMenuOpenPos - newGate->GetSize().Scale(0.5, 0.5));
  gates.push_back(newGate);

  Refresh();
}

void Canvas::onPaint(wxPaintEvent&)
{
  wxBufferedPaintDC dc(this);
  render(dc);
}

void Canvas::onContextMenu(wxContextMenuEvent& event)
{
  wxMenu menu;
  menu.Append(NotID, "Add NOT Gate");
  menu.Append(AndID, "Add AND Gate");
  menu.Append(OrID, "Add OR Gate");
  menu.Append(NorID, "Add NOR Gate");
  menu.Append(XorID, "Add XOR Gate");
  menu.Append(XnorID, "Add XNOR Gate");
  menu.Append(NandID, "Add NAND Gate");
  menu.Append(InputID, "Add INPUT");
  menu.Append(OutputID, "Add OUTPUT");
  menu.Append(MultiplexerID, "Add MULTIPLEXER");
  menu.Append(LabelID, "Add LABEL");

  const auto pos = ScreenToClient(event.GetPosition());
  contextMenuOpenPos = pos;
  PopupMenu(&menu, pos);
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

  for(auto& i : gates) i->renderNow();
}
