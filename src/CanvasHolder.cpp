#include "CanvasHolder.h"

CanvasHolder::CanvasHolder(wxWindow* parent, wxWindowID id)
  : wxWindow{parent, id}
{
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(sizer);

  wxSplitterWindow* oic = new wxSplitterWindow(this);
  oic->SetSashGravity(0.25);

  Canvas* canvas = new Canvas(oic);

  wxSplitterWindow* oi = new wxSplitterWindow(oic);
  oi->SetSashGravity(0.5);
  oi->SetMinimumPaneSize(300);

  wxStaticText* outputPanel = new wxStaticText(oi, wxID_ANY, "Outputs");
  wxStaticText* inputPanel = new wxStaticText(oi, wxID_ANY, "Inputs");

  oi->SplitHorizontally(outputPanel, inputPanel);
  oic->SplitVertically(oi, canvas);

  sizer->Add(oic, 1, wxEXPAND|wxCENTER, 10);
}
