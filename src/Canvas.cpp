#include "Canvas.h"
#include <algorithm>
#include <wx/dcbuffer.h>

Canvas::Canvas(wxFrame* parent) : wxPanel(parent)
{
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  SetBackgroundColour(wxColour(255,255,255));
  SetExtraStyle(wxRAISED_BORDER);
  SetDoubleBuffered(true);
}

BEGIN_EVENT_TABLE(Canvas, wxPanel)
  //EVT_MOTION(Canvas::onMouseMove)
  //EVT_LEFT_DOWN(Canvas::onLeftDown)
  //EVT_LEFT_UP(Canvas::onLeftUp)
  //EVT_MOUSEWHEEL(Canvas::onMouseWheel)
  EVT_CONTEXT_MENU(Canvas::onContextMenu)
  EVT_PAINT(Canvas::onPaint)
END_EVENT_TABLE()

//void Canvas::onMouseMove(wxMouseEvent& event)
//{
  //if(event.RightDown())
  //{
    //panning = true;
  //}
  //if(event.RightUp())
  //{
    //lastMousePosition = offset + event.GetPosition();
    //panning = false;
  //}
  //if(panning)
  //{
    //auto newPos = event.GetPosition();
    //offset = lastMousePosition - newPos ;
    //wxClientDC dc(this);
    //render(dc);
  //}
  // else if connecting
//}
//void Canvas::onLeftDown(wxMouseEvent& WXUNUSED(event))
//{
//}
//void Canvas::onLeftUp(wxMouseEvent& WXUNUSED(event))
//{
//}
//void Canvas::onMouseWheel(wxMouseEvent& event)
//{
  //auto wheelFactor = event.GetWheelRotation() / event.GetWheelDelta();
  //auto oldScaleFactor = scaleFactor;
  //scaleFactor = std::clamp(scaleFactor + 1*wheelFactor, 0.5, 2.0);
  //wxClientDC dc(this);
  //if(scaleFactor != oldScaleFactor) render(dc);
  //else event.Skip();
//}
void Canvas::onContextMenu(wxContextMenuEvent& event)
{
  wxMenu menu(wxT("Context Menu for adding Gates"));
  menu.Append(NotID, wxT("&Add NOT Gate"));
  menu.Append(AndID, wxT("&Add AND Gate"));
  menu.Append(OrID, wxT("&Add OR Gate"));
  menu.Append(NorID, wxT("&Add NOR Gate"));
  menu.Append(XorID, wxT("&Add XOR Gate"));
  menu.Append(XnorID, wxT("&Add XNOR Gate"));
  menu.Append(NandID, wxT("&Add NAND Gate"));
  menu.Append(InputID, wxT("&Add INPUT"));
  menu.Append(OutputID, wxT("&Add OUTPUT"));
  menu.Append(MultiplexerID, wxT("&Add MULTIPLEXER"));
  //Connect(NotID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addNotGate);
  //Connect(AndID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addAndGate);
  //Connect(OrID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addOrGate);
  //Connect(NorID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addNorGate);
  //Connect(XorID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addXorGate);
  //Connect(XnorID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addXnorGate);
  //Connect(NandID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addNandGate);
  //Connect(InputID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addInput);
  //Connect(OutputID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addOutput);
  //Connect(MultiplexerID, wxEVT_COMMAND_LEFT_CLICK, Canvas::addMultiplexer);
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

    // do something here to fix this when panning
  //for(auto j = 0; j <= height + space; j += space * scaleFactor)
      //dc.DrawLine(0, j - offset.y, width + space * scaleFactor, j - offset.y);
  //for(auto i = 0; i <= width + space; i += space * scaleFactor)
      //dc.DrawLine(i - offset.x, 0, i - offset.x, height + space * scaleFactor);

  for(auto j = 0; j <= height + space; j += space)
      dc.DrawLine(0, j, width + space, j);
  for(auto i = 0; i <= width + space; i += space)
      dc.DrawLine(i, 0, i, height + space);
}
