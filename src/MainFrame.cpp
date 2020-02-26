#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos,
    const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos , size)
{
  SetupMenuBar();
  BindEvents();
  CreateStatusBar();

  m_mgr.SetManagedWindow(this);

  wxPanel* properties = new wxPanel(this, wxID_ANY);
  properties->SetSize(300,250);
  wxPanel* toolbox = new wxPanel(this, wxID_ANY);
  toolbox->SetSize(300,250);

  m_notebookCenter = new wxAuiNotebook(this, wxID_FILE1);
  wxStaticText* helpText = new wxStaticText(m_notebookCenter, wxID_ANY,
      "Please go to 'File->New Canvas' in order to get started!");
  m_notebookCenter->AddPage(helpText, "Welcome Screen", true);

  m_mgr.AddPane(m_notebookCenter, wxCENTER, "Welcome Screen");
  m_mgr.AddPane(properties, wxRIGHT, "Properties");
  m_mgr.AddPane(toolbox, wxLEFT, "Toolbox");

  m_mgr.Update();
}

void MainFrame::SetupMenuBar()
{
  wxMenu* menuFile = new wxMenu;
  menuFile->Append(ID_NewCanvas, "&New Canvas\tCtrl-N", "Create a new canvas.");
  menuFile->Append(ID_SaveCanvas, "&Save Canvas\tCtrl-S", "Save the current canvas.");
  menuFile->Append(ID_ExportCanvas, "&Export Canvas\tCtrl-E", "Export the canvas to an image.");
  menuFile->Append(ID_LoadCanvas, "&Load Canvas\tCtrl-L", "Load an old canvas.");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu* menuView = new wxMenu;
  menuView->Append(ID_LoadConfiguration, "Load &Configuration File",
      "Loads a color configuration file.");
  menuView->Append(ID_ResetConfiguration, "Load &Default Configuration",
      "Loads the default color configuration.");

  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuView, "&View");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);
}
void MainFrame::BindEvents()
{
  const auto notImplemented = [](wxCommandEvent& WXUNUSED(event))
  {
    wxMessageBox("This feature is currently not implemented.",
        "Not Implemented", wxICON_ERROR);
  };
  Bind(wxEVT_MENU, [&](wxCommandEvent& WXUNUSED(event))
    {
      CanvasHolder* canvas = new CanvasHolder(this, wxID_ANY);
      wxString canvasName;
      canvasName.Printf("Canvas %d", -canvas->GetId());
      m_notebookCenter->AddPage(canvas, canvasName, true);
    }, ID_NewCanvas);
  Bind(wxEVT_MENU, notImplemented, ID_SaveCanvas);
  Bind(wxEVT_MENU, notImplemented, ID_ExportCanvas);
  Bind(wxEVT_MENU, notImplemented, ID_LoadCanvas);
  Bind(wxEVT_MENU, [&](wxCommandEvent& WXUNUSED(event)){ Close(); }, wxID_EXIT);
  Bind(wxEVT_MENU, &MainFrame::OnLoadConfiguration, this, ID_LoadConfiguration);
  Bind(wxEVT_MENU, &MainFrame::OnResetConfiguration, this, ID_ResetConfiguration);
  Bind(wxEVT_MENU,
    [](wxCommandEvent& WXUNUSED(event))
    {
      wxMessageBox("This application is used to create and simulate circuit diagrams.",
          "Wire Structure", wxOK|wxICON_INFORMATION);
    }, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainFrame::OnUpdateStatusBar, this, kcEVT_STATUS_BAR_UPDATE);
  Bind(wxEVT_TIMER,
      [&](wxTimerEvent& WXUNUSED(event)){ SetStatusText("Ready!"); });
}

void MainFrame::OnLoadConfiguration(wxCommandEvent& WXUNUSED(event))
{
  auto file = wxFileSelector("Please load a configuration file.", "config",
      "WireStructure.config", "config");
  wxCommandEvent myEvent(kcEVT_STATUS_BAR_UPDATE);
  if(file.IsEmpty())
  {
    myEvent.SetString("Default configuration loaded.");
  } else if(Configuration::GetInstance().LoadConfiguration(file))
  {
    wxString string;
    string.Printf("Loaded configuration from \"%s\"!", file);
    myEvent.SetString(string);
  } else {
    Configuration::GetInstance().LoadDefaultConfiguration();
    wxString string;
    string.Printf("Failed to load configuration from \"%s\", loading default configuration.", file);
    myEvent.SetString(string);
  }
  wxPostEvent(this, myEvent);
  Refresh();
}

void MainFrame::OnResetConfiguration(wxCommandEvent& WXUNUSED(event))
{
  Configuration::GetInstance().LoadDefaultConfiguration();
  wxCommandEvent myEvent(kcEVT_STATUS_BAR_UPDATE);
  myEvent.SetString("Default configuration loaded.");
  wxPostEvent(this, myEvent);
  Refresh();
}

void MainFrame::OnUpdateStatusBar(wxCommandEvent& event)
{
  static wxTimer timer(this);
  static constexpr int timeToRun = 5000;
  this->SetStatusText(event.GetString());
  timer.StartOnce(timeToRun);
}

MainFrame::~MainFrame()
{
  m_mgr.UnInit();
}
