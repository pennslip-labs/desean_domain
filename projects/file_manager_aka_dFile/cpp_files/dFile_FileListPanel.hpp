// responsible for displaying direcotry contents,
// handling double click navigation, selection, 
// and methods of refreshing the list

/* class notes:
    theres no need to store the parent panel as wxWidgets handles that already.
    the constructor only recievees the parent pointer so that it can store it in
    wxPanel through the bass class constructor. 
    all panel ownership is handled by wxWidgets so theres nothing we should be
    holding in here other than metadata */

#ifndef DFILE_FILELISTPANEL_HPP
    #define DFILE_FILELISTPANEL_HPP

#include "wx/listctrl.h"
#include "wx/wx.h"
#include "dFile_DirectoryScanner.hpp" // using for file meta data

class dFile_FileListPanel : public wxPanel {
    private:
        wxListCtrl* listCtrl; // gives control over the list in the panel
        wxString currentPath; // will hold the current path being used
        std::vector<fMetaData> files; // current path files info

        // sorts based on values. 0 = name, 1 = type, 2 = date, 3 = size
        int currentSortColumn = 0;
        bool sortAscending = true; // false sorts by descending

        // internal helpers
        void PopulateListCtrl(); // populates list control object given current directory
        void ClearList(); // clears the list when needing to refresh

        // event handlers
        void OnItemActivated(wxListEvent& evt); // handling when an item is activated
        void OnItemSelected(wxListEvent& evt); // handling when an is selected (show preview)
        void OnColumnClicked(wxListEvent& evt); // not sure what to do with this yet. may rmv
        // TODO: figure out if i need OnColumnClicked or not

    public:
        /* creates the list control, adding columns to the list,
        setting up the layout, and binding events.*/
        dFile_FileListPanel(wxWindow* parent, wxWindowID id = wxID_ANY);

        // directory operations
        void LoadDirectory(const wxString& path); // uses the directory scanner in dFrame
        void RefreshList(); // refreshes the wxListCtrl contents as well as column width

        // sorting
        void SortByColumn(int columnIndex, bool ascending); // used to change sorting choice

        // selection
        bool HasSelection() const; // sees if a file is selected or not
        int GetSelectedIndex() const; // extracts the index of the file withen the vector
        fMetaData GetSelectedFile() const; // used to get the metadata of a selected file

        // accessors
        wxString GetCurrentPath() const { return currentPath; } // gets the current path from the dir scanner in dframe
};

#endif
