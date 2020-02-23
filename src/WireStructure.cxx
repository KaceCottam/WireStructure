#include "WireStructure.h"

DECLARE_APP(WireStructure)
IMPLEMENT_APP(WireStructure)

bool WireStructure::OnInit()
{
  wxFrame* parentFrame = new MainFrame("Wire Structure");
  parentFrame->Show();
  return true;
}
