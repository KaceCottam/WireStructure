#ifndef CANVAS_H
#define CANVAS_H
#include "Gates.h"

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
  MultiplexerID,
  LabelID
};

class Canvas : public wxPanel
{
  int space = 25;
  wxPoint contextMenuOpenPos;

  void addGate(wxCommandEvent& event);

  std::vector<GateBase*> gates;

 public:
  Canvas(wxFrame* parent);

  void onPaint(wxPaintEvent&);
  void onContextMenu(wxContextMenuEvent&);

  void render(wxDC& dc);

  DECLARE_EVENT_TABLE()
};
#endif // ! CANVAS_H

