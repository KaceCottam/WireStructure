#ifndef STATUSBAREVENT_H
#define STATUSBAREVENT_H
#include <wx/wx.h>
enum MainFrameMenuEvents
{
  ID_NewCanvas = wxID_HIGHEST,
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

wxDECLARE_EVENT(kcEVT_STATUS_BAR_UPDATE, wxCommandEvent);
#endif // ! STATUSBAREVENT_H

