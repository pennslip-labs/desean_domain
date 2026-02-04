// TODO: implement header file and class def. get to a point where file list is visible and interactable

#include "dFile_FileListPanel.hpp"
#include "dFile_DefSize.cpp"

using namespace std;

dFile_FileListPanel::dFile_FileListPanel(wxWindow* parent, wxWindowID id = wxID_ANY) : wxPanel(parent, id) {
    listCtrl = new wxListCtrl( // initializing the listctrl with def settings
        parent,
        id,
        def_position,
        def_size,
        wxLC_REPORT | wxLC_SINGLE_SEL // this line ensures that reporting is set,
                                      // as well as we only have sinlge select on
                                      // for simpler ui design
    );

    // setting up list ctrl columns with their titles, text positioning, and width autosising.
    // though will have to manually refresh upon list udates for column width
    listCtrl -> InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    listCtrl -> InsertColumn(1, "TYPE", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    listCtrl -> InsertColumn(2, "SIZE", wxLIST_FORMAT_RIGHT, wxLIST_AUTOSIZE);
    listCtrl -> InsertColumn(3, "DATE", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);

    auto* sizer = new wxBoxSizer(wxVERTICAL); // using wxVERTICAL to stack children vertically
    // adding the list ctrl, allowing it to take up the entire proportion of the box (1),
    // stretch the widget so it takes up all width and height, while also applying a 
    // 5 pixel padding on all sides
    sizer -> Add(listCtrl, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer); // set the sizer we just created to manage the layout out of this panel

    // from here on wxWidgets handles resizing automatically for us
}   

void PopulateListCtrl() { // TODO: finish implementing list population after scan_dir is finished
    
}


