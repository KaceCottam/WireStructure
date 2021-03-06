#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <wx/wx.h>
#include <wx/textfile.h>

class Configuration
{
 public:
  static Configuration& GetInstance()
  {
    static Configuration s_mainInstance;
    return s_mainInstance;
  }

  void LoadDefaultConfiguration()
  {
    wxTheColourDatabase->AddColour("CANVAS_BACKGROUND_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
    wxTheColourDatabase->AddColour("CANVAS_GRID_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    wxTheColourDatabase->AddColour("WIRE_ON_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_3DHIGHLIGHT));
    wxTheColourDatabase->AddColour("WIRE_OFF_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
    wxTheColourDatabase->AddColour("WIRE_NORMAL_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    wxTheColourDatabase->AddColour("WIRE_TEXT_ON_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_3DHIGHLIGHT));
    wxTheColourDatabase->AddColour("WIRE_TEXT_OFF_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
    wxTheColourDatabase->AddColour("SELECT_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    wxTheColourDatabase->AddColour("ANCHOR_CONNECTED_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_3DHIGHLIGHT));
    wxTheColourDatabase->AddColour("ANCHOR_BROKEN_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));
    wxTheColourDatabase->AddColour("ANCHOR_HIGHLIGHT_COLOR" , wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
  }

  bool LoadConfiguration(const wxString& filename)
  {
    wxTextFile file;
    if(!file.Open(filename)) return false;
    for(auto i = 0U; i < file.GetLineCount(); ++i)
    {
      auto line = file[i].Strip();
      if(line.Find('=') == line.Length()) return false;
      wxString key, value;
      key = line.BeforeFirst('=', &value);
      if(value.Len() != 7) return false;
      // TODO add sanity checks here
      unsigned long r, g, b;
      value.Mid(1, 2).ToULong(&r, 16);
      value.Mid(3, 2).ToULong(&g, 16);
      value.Mid(5, 2).ToULong(&b, 16);
      wxTheColourDatabase->AddColour(key, wxColour(r, g, b));
    }
    return true;
  }
};
#endif // ! CONFIGURATION_H

