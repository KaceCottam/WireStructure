#ifndef CANVAS_H
#define CANVAS_H
#include <wx/wx.h>

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
  static constexpr int spaceHigh = 100;
  static constexpr int spaceLow = 12;
  int space = 25;

  //wxPoint offset;
  //wxPoint lastMousePosition;
  //double scaleFactor = 1.0;
  //bool panning = false;
  //bool connecting = false;

 public:
  Canvas(wxFrame* parent);

  //void onMouseMove(wxMouseEvent& event);
  //void onLeftDown(wxMouseEvent& event);
  //void onLeftUp(wxMouseEvent& event);
  //void onMouseWheel(wxMouseEvent& event);
  void onContextMenu(wxContextMenuEvent& event);
  void onPaint(wxPaintEvent& event);

  void render(wxDC& dc) const;
  DECLARE_EVENT_TABLE()
};
#endif // ! CANVAS_H

