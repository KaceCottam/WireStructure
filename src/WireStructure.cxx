#include "WireStructure.h"

DECLARE_APP(WireStructure)
IMPLEMENT_APP(WireStructure)

bool WireStructure::OnInit()
{
  wxString configStatus;
  if(wxApp::argv.GetArguments().Count() == 1)
  {
    configStatus = "Loaded default configuration!";
    Configuration::GetInstance().LoadDefaultConfiguration();
  } else {
    auto args = wxApp::argv.GetArguments();
    if(Configuration::GetInstance().LoadConfiguration(args[1]))
    {
      configStatus.Printf("Loaded configuration from \"%s\"!", args[1]);
    } else
    {
      configStatus.Printf("Failed to load configuration from \"%s\", loading default configuration.", args[1]);
      Configuration::GetInstance().LoadDefaultConfiguration();
    }
  }
  wxFrame* parentFrame = new MainFrame("Wire Structure");
  wxLogMessage(configStatus);
  parentFrame->Show();

  return true;
}
