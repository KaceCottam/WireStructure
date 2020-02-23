#include "Gates.h"

void NotGate::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);

  wxPoint points[] =
  {
    wxPoint(0, 0),
    wxPoint(0, 100),
    wxPoint(100, 50),
  };
  dc.DrawPolygon(3, points);
  dc.DrawCircle(110, 50, 10);
}

void AndGate::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);

  wxPoint points[] =
  {
    wxPoint(50, 100),
    wxPoint(0, 100),
    wxPoint(0, 0),
    wxPoint(50, 0),
    wxPoint(50, 50),
  };
  dc.DrawLines(4,points);
  dc.DrawArc(points[0], points[3], points[4]);
}

void OrGate::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);

  wxPoint spline1[] =
  {
    wxPoint(0, 100),
    wxPoint(25, 50),
    wxPoint(0, 0),
  };
  dc.DrawSpline(3,spline1);
  wxPoint spline2[] =
  {
    wxPoint(0, 100),
    wxPoint(25, 90),
    wxPoint(100, 50),
  };
  dc.DrawSpline(3, spline2);
  wxPoint bottomPoints[] =
  {
    wxPoint(0, 0),
    wxPoint(25, 10),
    wxPoint(100, 50),
  };
  dc.DrawSpline(3, bottomPoints);
}

void NorGate::render(wxDC& dc)
{
  OrGate::render(dc);
  dc.DrawCircle(110, 50, 10);
}

void XorGate::render(wxDC& dc)
{
  OrGate::render(dc);
  wxPoint spline[] =
  {
    wxPoint(-10, 100),
    wxPoint(15, 50),
    wxPoint(-10, 0),
  };
  dc.DrawSpline(3, spline);
}

void XnorGate::render(wxDC& dc)
{
  XorGate::render(dc);
  dc.DrawCircle(110, 50, 10);
}

void NandGate::render(wxDC& dc)
{
  AndGate::render(dc);
  dc.DrawCircle(110, 50, 10);
}

void InputGate::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);
  dc.SetFont({32, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawCircle(50, 50, 25);
  dc.DrawLabel("I", wxRect(0, 0, 100, 100),wxALIGN_CENTER);
}

void OutputGate::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);
  dc.SetFont({32, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawCircle(50, 50, 25);
  dc.DrawLabel("O", wxRect(0,0,100,100), wxALIGN_CENTER);
}

void Multiplexer::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);
  dc.SetFont({24, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.SetBrush(*wxWHITE_BRUSH);
  wxPoint points[] =
  {
    wxPoint(25, 100),
    wxPoint(25, 0),
    wxPoint(75, 0),
    wxPoint(75, 100),
  };
  dc.DrawPolygon(4, points);
  dc.DrawLabel("0", wxRect(25, 0, 75, 50), wxALIGN_CENTER);
  dc.DrawLabel("1", wxRect(25, 50, 75, 50), wxALIGN_CENTER);
}

BEGIN_EVENT_TABLE(Label, GateBase)
  EVT_LEFT_DCLICK(Label::onLeftDClick)
  EVT_CONTEXT_MENU(Label::onContextMenu)
  EVT_MENU(wxID_ANY, Label::addLabel)
END_EVENT_TABLE()

Label::Label(wxFrame* parent)
  : GateBase(parent)
{
  SetSize(5000, 32);
}

void Label::render(wxDC& dc)
{
  setupDC(dc, {-25, -25});
  resetColors(dc);
  dc.SetFont({24, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});
  dc.SetTextForeground(*wxBLACK);
  dc.DrawLabel(labelText, wxRect(-25, -25, 125, 125), wxALIGN_CENTER);
}

void Label::onLeftDClick(wxMouseEvent& event)
{
  wxCommandEvent cmdEvent;
  addLabel(cmdEvent);
  event.Skip();
}

void Label::onContextMenu(wxContextMenuEvent& event)
{
  wxMenu menu;
  menu.Append(wxID_ANY, "Rename Label");
  PopupMenu(&menu, ScreenToClient(event.GetPosition()));
  event.Skip();
}

void Label::addLabel(wxCommandEvent& event)
{
  auto newLabel = wxGetTextFromUser("Please enter a new label.");
  if(newLabel != "") labelText = newLabel;
  //event.Skip();
}

