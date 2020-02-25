#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>
#include <wx/splitter.h>

#include "Canvas.h"
#include "Configuration.h"
#include "StatusBarEvent.h"

class MainFrame : public wxFrame
{
 public:
  MainFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize);

 private:
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnConfigurationLoad(wxCommandEvent& event);
  void OnDefaultConfiguration(wxCommandEvent& event);
  void OnStatusBarUpdate(wxCommandEvent& event);

  DECLARE_EVENT_TABLE();
};
#endif // ! MAINFRAME_H

