#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <wx/wx.h>
#include <wx/textfile.h>
#include <map>
#include <string>
class Configuration
{
 private:
  std::map<const wxString, wxColour> keywordConverter;

 public:
  static Configuration& GetInstance()
  {
     static Configuration s_mainInstance;
    return s_mainInstance;
  }

  void LoadDefaultConfiguration()
  {
    keywordConverter.insert({"CANVAS_BACKGROUND_COLOR" , wxColour(0xfd,0xf6,0xe3)});
    keywordConverter.insert({"CANVAS_GRID_COLOR" , wxColour(0xee,0xe8,0xd5)});
    keywordConverter.insert({"WIRE_ON_COLOR" , wxColour(0x85,0x99,0x00)});
    keywordConverter.insert({"WIRE_OFF_COLOR" , wxColour(0xdc,0x32,0x2f)});
    keywordConverter.insert({"WIRE_NORMAL_COLOR" , wxColour(0x58,0x6e,0x75)});
    keywordConverter.insert({"WIRE_TEXT_ON_COLOR" , wxColour(0x65,0x7b,0x83)});
    keywordConverter.insert({"WIRE_TEXT_OFF_COLOR" , wxColour(0x65,0x7b,0x83)});
    keywordConverter.insert({"SELECT_COLOR" , wxColour(0x26,0x8b,0xd2)});
    keywordConverter.insert({"ANCHOR_CONNECTED_COLOR" , wxColour(0x58,0x6e,0x75)});
    keywordConverter.insert({"ANCHOR_BROKEN_COLOR" , wxColour(0xcb,0x4b,0x16)});
    keywordConverter.insert({"ANCHOR_HIGHLIGHT_COLOR" , wxColour(0x2a,0xa1,0x98)});
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
       key = line.BeforeFirst('=');
       value = line.AfterFirst('#');
       int r = wxHexToDec(value(0, 1));
       int g = wxHexToDec(value(2, 3));
       int b = wxHexToDec(value(4, 5));
       keywordConverter[key] = wxColour(r,g,b);
     }
     return true;
  }

  wxColour operator[](const wxString& key) const
  {
    return keywordConverter.at(key);
  }
};
#endif // ! CONFIGURATION_H

