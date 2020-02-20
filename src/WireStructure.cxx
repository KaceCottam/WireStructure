#include "WireStructure.h"
#include <wx/sizer.h>

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame(NULL, wxID_ANY, "Wire Structure");

  Canvas* canvas = new Canvas(frame);

  sizer->Add(canvas, 1, wxEXPAND | wxALL, 5);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show(true);
  return true;
}
