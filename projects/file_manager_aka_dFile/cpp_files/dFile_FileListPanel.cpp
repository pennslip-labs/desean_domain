// TODO: implement header file and class def. get to a point where file list is visible and interactable

#include "dFile_FileListPanel.hpp"
#include "dFile_DefSize.hpp"
#include "dFile_wxDataFormat.hpp"
#include <stdio.h>

using namespace std;

dFile_FileListPanel::dFile_FileListPanel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id) {
    listCtrl = new wxListCtrl( // initializing the listctrl with def settings
        this, 
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

    // adding the list control to the sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 0);
    SetSizer(sizer);
}   

void dFile_FileListPanel::PopulateListCtrl() {
    //TODO: remove later
    std::cout << "DEBUG: LoadDirectory completed, files count: " << files.size() << std::endl;

    // wxListCtrl lets me associate a long value with each row using SetItemData().
    // I use this long value to store the index of the corresponding fMetaData
    // entry inside file_vect. This creates a direct link between the UI row and
    // the backend metadata.
    //
    // When the user selects or activates a row, I can call GetItemData(row) to
    // retrieve the stored index, then use that index to access the correct
    // fMetaData object in file_vect. This keeps the UI and backend cleanly
    // connected without duplicating data or storing metadata inside wxListItem.

    // TLDR: wxListCtrl is used for the rows and file_vect for the index

    int i = 0; // used for indexing the vector
    for (const fMetaData &fmd : files) { // iterating through the vector
        // this helps to tie the listctrl row to vector index for consistency (row and i are 1:1).
        // connecting the backend to the UI
        int row = listCtrl->InsertItem(i, fmd.isDirectory ? wxString::FromUTF8(fmd.name + " >") : wxString::FromUTF8(fmd.name)); // place the data item in listctrl
        
        // editing the columns of said item based on the metadata
        listCtrl -> SetItem(row, 1,  wxString::FromUTF8(fmd.type));
        listCtrl -> SetItem(row, 2, format_size_to_wxStr(fmd.size));
        listCtrl -> SetItem(row, 3, format_date_to_wxStr(fmd.modified));

        listCtrl -> SetItemData(row, i); // the final knot that connect the vector index and litctrl row

        i++; // increasing the index
    } // when needing the index of an item in fMeteData, can use long GetItemData(selectedRow) 

    //TODO: remove later
    std::cout << "DEBUG: Finished PopulateListCtrl" << std::endl;
}

void dFile_FileListPanel::ClearList() {listCtrl->DeleteAllItems();}

// TODO: implement event triggers and how the UI should respond
void dFile_FileListPanel::OnItemActivated(wxListEvent &evt) {

}

void dFile_FileListPanel::OnItemSelected(wxListEvent &evt) {

}

void dFile_FileListPanel::OnColumnClicked(wxListEvent &evt) {

}

void dFile_FileListPanel::LoadDirectory(const wxString &path) {
    // update local saved directory
    currentPath = path;
    // clear the old files vector to avoid duplicates
    files.clear();
    // create a local directory scanner object initialized with the given path
    dFile_DirectoryScanner dir_scanner(path);
    // use it to pull all the file metadata within the directory
    if (!dir_scanner.scan_dir()) cout << "error in loading directory..." << endl;
    // pull the meta data vector from dir_sanner and save it
    copy(dir_scanner.get_file_vect().begin(), dir_scanner.get_file_vect().end(), back_insert_iterator(files));
}

void dFile_FileListPanel::RefreshList(bool load_dir) {
    listCtrl -> DeleteAllItems();
    if (load_dir) LoadDirectory(currentPath);
    PopulateListCtrl();
}

void dFile_FileListPanel::SortByColumn(int columnIndex, bool ascending) {
    // will use lambda functions to define the sorting given we only need them once.
    // sorting with wxString given the UI is based on that, and then 
    // the date and size will be sorted based on their raw data (not formatted)

    switch (columnIndex) {
        case 0: // sort by name
            std::sort(files.begin(), files.end(), 
            [] (const fMetaData &a, const fMetaData &b) {
                // place directories first
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;

                // otherwise can sort by case sensitive names
                return wxString::FromUTF8(a.name).Cmp(wxString::FromUTF8(b.name)) > 0;
            });
            break;
        case 1: // sort by type
            std::sort(files.begin(), files.end(),
            [] (const fMetaData &a, const fMetaData &b) {
                // placing directories first again
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;

                // otherwise sort by type as normal
                return wxString::FromUTF8(a.type).Cmp(wxString::FromUTF8(b.type)) > 0;
            });
            break;
        case 2: // sort by size 
            std::sort(files.begin(), files.end(), 
            [] (const fMetaData &a, const fMetaData &b) {
                // placing the directory first in the list
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;

                // if not directory, sort as follows
                return a.size > b.size;
            });
            break;
        case 3: // sorting by date
            std::sort(files.begin(), files.end(),
            [] (const fMetaData &a, const fMetaData &b) {
                // place directories first
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;

                // sorting normal files
                return a.modified > b.modified;
            });
            break;
    }

    // refresh the list for it to take affect (ensuring we don't 
    // reload the directory and over write the sorting we did)
    RefreshList(false);
}

// TODO: finishing implementation. not sure if I need it
bool dFile_FileListPanel::HasSelection() const {
    return false;
}
