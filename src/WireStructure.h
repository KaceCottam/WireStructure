#ifndef WIRESTRUCTURE_H
#define WIRESTRUCTURE_H
#include <wx/wx.h>
#include "Canvas.h"

class MyApp: public wxApp
{
  public:
    virtual bool OnInit();

    wxFrame* frame;
    Canvas* canvas;
};
#endif // ! WIRESTRUCTURE_H

