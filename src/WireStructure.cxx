#include "WireStructure.h"
#include <wx/sizer.h>

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame(NULL, wxID_ANY, wxT("Wire Structure"));

  Canvas* canvas = new Canvas(frame);

  sizer->Add(canvas, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show(true);
  return true;
}
