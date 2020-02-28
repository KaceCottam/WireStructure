#ifndef VISUALGATES_H
#define VISUALGATES_H
#include <wx/wx.h>
#include "Defs.h"

class VisualGateDatabase
{
 public:
  static VisualGateDatabase& GetInstance();

  VisualGateDatabase();

  void RerenderBitmaps();

  wxBitmap GetNotGate();
  wxBitmap GetAndGate();
  wxBitmap GetOrGate();
  wxBitmap GetNorGate();
  wxBitmap GetXorGate();
  wxBitmap GetXnorGate();
  wxBitmap GetNandGate();
  wxBitmap GetInput();
  wxBitmap GetOutput();
  wxBitmap GetMultiplexer();

 private:
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

  wxBitmap m_notGate;
  wxBitmap m_andGate;
  wxBitmap m_orGate;
  wxBitmap m_norGate;
  wxBitmap m_xorGate;
  wxBitmap m_xnorGate;
  wxBitmap m_nandGate;
  wxBitmap m_input;
  wxBitmap m_output;
  wxBitmap m_multiplexer;
};
#endif // ! VISUALGATES_H

