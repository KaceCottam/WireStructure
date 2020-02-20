#ifndef CANVAS_H
#define CANVAS_H
#include "VisualGates.h"

#include <wx/wx.h>

#include <vector>

enum GateAddIDs
{
  NotID = 101,
  AndID,
  OrID,
  NorID,
  XorID,
  XnorID,
  NandID,
  InputID,
  OutputID,
  MultiplexerID
};

class Canvas : public wxPanel
{
  int space = 25;
  wxPoint contextMenuOpenPos;

  void addGate(wxCommandEvent& event);

  std::vector<VisualGateBase*> gates;
 public:
  Canvas(wxFrame* parent);

  void onContextMenu(wxContextMenuEvent& event);
  void onPaint(wxPaintEvent& event);

  void render(wxDC& dc);
  DECLARE_EVENT_TABLE()
};
#endif // ! CANVAS_H

