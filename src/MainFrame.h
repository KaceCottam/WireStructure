#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>
#include <wx/aui/aui.h>

#include "CanvasHolder.h"
#include "Configuration.h"
#include "StatusBarEvent.h"
#include "Defs.h"

class MainFrame : public wxFrame
{
 public:
  MainFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize);

 private:
  wxAuiManager m_mgr;
  wxAuiNotebook* m_notebookCenter;

  void SetupMenuBar();
  void BindEvents();

  void OnLoadConfiguration(wxCommandEvent& event);
  void OnResetConfiguration(wxCommandEvent& event);
  void OnUpdateStatusBar(wxCommandEvent& event);

  ~MainFrame();
};
#endif // ! MAINFRAME_H

