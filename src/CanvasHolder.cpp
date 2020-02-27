#include "CanvasHolder.h"

CanvasHolder::CanvasHolder(wxWindow* parent, wxWindowID id)
  : wxWindow{parent, id}
{
  m_mgr.SetManagedWindow(this);

  Canvas* canvas = new Canvas(this);

  wxPanel* properties = new wxPanel(this, wxID_ANY, wxDefaultPosition, {300, 250});
  wxPanel* toolbox = new wxPanel(this, wxID_ANY, wxDefaultPosition, {300, 250});

  m_mgr.AddPane(canvas, wxCENTER);
  m_mgr.AddPane(properties, wxRIGHT, "Properties");
  m_mgr.AddPane(toolbox, wxRIGHT, "Toolbox");

  m_mgr.Update();
}

CanvasHolder::~CanvasHolder()
{
  m_mgr.UnInit();
}
