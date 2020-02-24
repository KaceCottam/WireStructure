#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(wxID_EXIT,  MainFrame::OnExit)
  EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos,
    const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos , size)
{
  wxMenu* menuFile = new wxMenu;
  menuFile->Append(wxID_EXIT);

  wxMenu* menuView = new wxMenu;
  menuView->Append(wxID_ANY, "&Reset View",
      "Resets the viewport to the center.");

  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);


  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuView, "&View");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Ready!");

  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  wxSplitterWindow* mainSplitter = new wxSplitterWindow(this, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE);
  mainSplitter->SetSashGravity(0.10);
  mainSplitter->SetMinimumPaneSize(50);
  mainSizer->Add(mainSplitter, 1, wxALL|wxEXPAND, 5);

  wxSplitterWindow* rightSplitter = new wxSplitterWindow(mainSplitter, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH|wxSP_LIVE_UPDATE);
  rightSplitter->SetSashGravity(1.0);
  rightSplitter->SetMinimumPaneSize(150); 

  wxWindow* canvasPanel = new Canvas(rightSplitter, wxID_ANY);

  wxWindow* propertiesPanel = new wxWindow(rightSplitter, wxID_ANY);
  wxStaticBoxSizer* propertiesSizer = new wxStaticBoxSizer(wxVERTICAL,
      propertiesPanel, "Properties");
  propertiesPanel->SetSizer(propertiesSizer);

  rightSplitter->SplitVertically(canvasPanel, propertiesPanel);

  wxSplitterWindow* leftSplitter = new wxSplitterWindow(mainSplitter, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH|wxSP_LIVE_UPDATE);
  leftSplitter->SetSashGravity(0.5);

  wxWindow* toolboxPanel = new wxWindow(leftSplitter, wxID_ANY);
  wxStaticBoxSizer* toolboxSizer = new wxStaticBoxSizer(wxVERTICAL,
      toolboxPanel, "Toolbox");
  toolboxPanel->SetSizer(toolboxSizer);

  wxSplitterWindow* outputInputSplitter = new wxSplitterWindow(leftSplitter, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH|wxSP_LIVE_UPDATE);
  outputInputSplitter->SetSashGravity(0.5);

  wxWindow* inputPanel = new wxWindow(outputInputSplitter, wxID_ANY);
  wxStaticBoxSizer* inputSizer = new wxStaticBoxSizer(wxVERTICAL,
      inputPanel, "Inputs");
  inputPanel->SetSizer(inputSizer);

  wxWindow* outputPanel = new wxWindow(outputInputSplitter, wxID_ANY);
  wxStaticBoxSizer* outputSizer = new wxStaticBoxSizer(wxVERTICAL,
      outputPanel, "Outputs");
  outputPanel->SetSizer(outputSizer);

  outputInputSplitter->SplitHorizontally(outputPanel, inputPanel);

  leftSplitter->SplitHorizontally(toolboxPanel, outputInputSplitter);

  mainSplitter->SplitVertically(leftSplitter, rightSplitter);

  mainSizer->SetSizeHints(this);
  SetSizer(mainSizer);

  // !PLAN
  // Create a splitter window
  //  left side is a splitter window, into Properties + Input/Output
  //  Properties shows properties of currently selected element
  // Input/Output is a splitter window
  //  top is Output, bottom is Input
  // Output: Show a list wherein for each x in outputs,
  // show x's label, a graph of x's value over a function of time,
  // show x's boolean algebra breakdown, as well as a variable window underneath
  //  to make 1 letter names possible
  // Input: Show a list wherein for each x in inputs,
  // show x's label, a graph of x's value over a function of time t,
  // double clicking on graph opens a dialog box where we can create the function
  //  of x's value to our liking, from a table of 2 values (time, output level)
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
  Close();
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox("This application is used to create and simulate circuit diagrams.",
      "About Wire Structure", wxOK|wxICON_INFORMATION);
}
