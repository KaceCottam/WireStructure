#include "WireStructure.h"

DECLARE_APP(WireStructure)
IMPLEMENT_APP(WireStructure)

bool WireStructure::OnInit()
{
  wxString configStatus;
  if(wxApp::argv.GetArguments().Count() == 1)
  {
    Configuration::GetInstance().LoadDefaultConfiguration();
    configStatus = "Loaded default configuration!";
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
  wxCommandEvent* myEvent = new wxCommandEvent(kcEVT_STATUS_BAR_UPDATE);
  myEvent->SetString(configStatus);
  parentFrame->Show();
  wxPostEvent(parentFrame, *myEvent);

  return true;
}
