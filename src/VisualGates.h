#ifndef VISUALGATES_H
#define VISUALGATES_H
#include <wx/wx.h>
#include "Defs.h"

class VisualGateDatabase
{
 public:
  static VisualGateDatabase& GetInstance();

  VisualGateDatabase();

  static void RenderNotGate(wxDC& dc);
  static void RenderAndGate(wxDC& dc);
  static void RenderOrGate(wxDC& dc);
  static void RenderNorGate(wxDC& dc);
  static void RenderXorGate(wxDC& dc);
  static void RenderXnorGate(wxDC& dc);
  static void RenderNandGate(wxDC& dc);
  static void RenderInput(wxDC& dc);
  static void RenderOutput(wxDC& dc);
  static void RenderMultiplexer(wxDC& dc);
};
#endif // ! VISUALGATES_H

