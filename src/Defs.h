#ifndef DEFS_H
#define DEFS_H
#include <wx/wx.h>
extern wxColourDatabase* wxTheColourDatabase;
enum MainFrameMenuEvents
{
  ID_NewCanvas = wxID_HIGHEST,
  ID_SaveCanvas,
  ID_ExportCanvas,
  ID_LoadCanvas,

  ID_ResetWorkspace,
  ID_LoadConfiguration,
  ID_ResetConfiguration,
};

enum CanvasMenuEvents
{
  ID_ToggleWireColors = wxID_HIGHEST,
  ID_ToggleBooleanAlgebra,
  ID_GridOptions,
  ID_ToggleGrid,
  ID_CheckLineGrid,
  ID_CheckDotGrid
};

#define CANVAS_BACKGROUND_COLOR wxTheColourDatabase->Find("CANVAS_BACKGROUND_COLOR")
#define CANVAS_GRID_COLOR wxTheColourDatabase->Find("CANVAS_GRID_COLOR")
#define WIRE_ON_COLOR wxTheColourDatabase->Find("WIRE_ON_COLOR")
#define WIRE_OFF_COLOR wxTheColourDatabase->Find("WIRE_OFF_COLOR")
#define WIRE_NORMAL_COLOR wxTheColourDatabase->Find("WIRE_NORMAL_COLOR")
#define WIRE_TEXT_ON_COLOR wxTheColourDatabase->Find("WIRE_TEXT_ON_COLOR")
#define WIRE_TEXT_OFF_COLOR wxTheColourDatabase->Find("WIRE_TEXT_OFF_COLOR")
#define SELECT_COLOR wxTheColourDatabase->Find("SELECT_COLOR")
#define ANCHOR_CONNECTED_COLOR wxTheColourDatabase->Find("ANCHOR_CONNECTED_COLOR")
#define ANCHOR_BROKEN_COLOR wxTheColourDatabase->Find("ANCHOR_BROKEN_COLOR")
#define ANCHOR_HIGHLIGHT_COLOR wxTheColourDatabase->Find("ANCHOR_HIGHLIGHT_COLOR")
#endif // ! DEFS_H

