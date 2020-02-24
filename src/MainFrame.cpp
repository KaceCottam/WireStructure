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

  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Ready!");

  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  wxSplitterWindow* mainSplitter = new wxSplitterWindow(this, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE);
  mainSplitter->SetSashGravity(0.25);
  mainSplitter->SetMinimumPaneSize(1);
  mainSizer->Add(mainSplitter, 1, wxALL|wxEXPAND, 5);

  wxWindow* canvasPanel = new Canvas(mainSplitter, wxID_ANY);

  wxSplitterWindow* leftSplitter = new wxSplitterWindow(mainSplitter, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH|wxSP_LIVE_UPDATE);
  leftSplitter->SetSashGravity(1.0);
  leftSplitter->SetMinimumPaneSize(1);

  wxWindow* propertiesPanel = new wxWindow(leftSplitter, wxID_ANY);
  wxStaticBoxSizer* propertiesSizer = new wxStaticBoxSizer(wxVERTICAL,
      propertiesPanel, "Properties");
  propertiesPanel->SetSizer(propertiesSizer);

  wxSplitterWindow* outputInputSplitter = new wxSplitterWindow(leftSplitter, wxID_ANY,
      wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH|wxSP_LIVE_UPDATE);
  outputInputSplitter->SetSashGravity(1.0);
  outputInputSplitter->SetMinimumPaneSize(1);

  wxWindow* inputPanel = new wxWindow(outputInputSplitter, wxID_ANY);
  wxStaticBoxSizer* inputSizer = new wxStaticBoxSizer(wxVERTICAL,
      inputPanel, "Advanced Input Options");
  inputPanel->SetSizer(inputSizer);

  wxWindow* outputPanel = new wxWindow(outputInputSplitter, wxID_ANY);
  wxStaticBoxSizer* outputSizer = new wxStaticBoxSizer(wxVERTICAL,
      outputPanel, "Outputs");
  outputPanel->SetSizer(outputSizer);

  outputInputSplitter->SplitHorizontally(outputPanel, inputPanel);
  leftSplitter->SplitHorizontally(propertiesPanel, outputInputSplitter);
  mainSplitter->SplitVertically(leftSplitter, canvasPanel);

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
