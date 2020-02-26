#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>
#include <wx/aui/aui.h>

#include "Canvas.h"
#include "Configuration.h"
#include "StatusBarEvent.h"

class MainFrame : public wxFrame
{
 public:
  MainFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize);

 private:

  enum MainFrameMenuEvents
  {
    ID_NewCanvas,
    ID_SaveCanvas,
    ID_ExportCanvas,
    ID_LoadCanvas,

    ID_ResetWorkspace,
    ID_LoadConfiguration,
    ID_ResetConfiguration,
    ID_ToggleWireColors,
    ID_ToggleBooleanAlgebra,

    ID_ToggleGrid,
    ID_CheckLineGrid,
    ID_CheckDotGrid
  };

  wxAuiManager m_mgr;

  void SetupMenuBar();
  void BindEvents();

  void OnLoadConfiguration(wxCommandEvent& event);
  void OnResetConfiguration(wxCommandEvent& event);
  void OnUpdateStatusBar(wxCommandEvent& event);

  ~MainFrame();
};
#endif // ! MAINFRAME_H

