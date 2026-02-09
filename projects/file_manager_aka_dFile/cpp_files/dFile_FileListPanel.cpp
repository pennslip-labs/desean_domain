// TODO: implement header file and class def. get to a point where file list is visible and interactable

#include "dFile_FileListPanel.hpp"
#include "dFile_DefSize.hpp"
#include "dFile_wxDataFormat.hpp"
#include <stdio.h>
#include "dFile_Frame.hpp"

using namespace std;

dFile_FileListPanel::dFile_FileListPanel(wxWindow* parent, wxWindowID id, dFile_Frame *frame) 
    : wxPanel(parent, id), df_frame(frame) 
{
    listCtrl = new wxListCtrl(
        this, 
        id,
        def_position,
        def_size,
        wxLC_REPORT | wxLC_SINGLE_SEL
    );

    listCtrl->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    listCtrl->InsertColumn(1, "TYPE", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    listCtrl->InsertColumn(2, "SIZE", wxLIST_FORMAT_RIGHT, wxLIST_AUTOSIZE);
    listCtrl->InsertColumn(3, "DATE", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);

    // binding events 
    listCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, &dFile_FileListPanel::OnItemActivated, this);
    listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &dFile_FileListPanel::OnItemSelected, this);
    listCtrl->Bind(wxEVT_LIST_COL_CLICK, &dFile_FileListPanel::OnColumnClicked, this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 0);
    SetSizer(sizer);
}   

void dFile_FileListPanel::PopulateListCtrl() {
    int i = 0;
    for (const fMetaData &fmd : files) {
        int row = listCtrl->InsertItem(i, fmd.isDirectory ? wxString::FromUTF8(fmd.name + " >") : wxString::FromUTF8(fmd.name));
        
        listCtrl->SetItem(row, 1, wxString::FromUTF8(fmd.type));
        listCtrl->SetItem(row, 2, format_size_to_wxStr(fmd.size));
        listCtrl->SetItem(row, 3, format_date_to_wxStr(fmd.modified));

        listCtrl->SetItemData(row, i);
        i++;
    }
}

void dFile_FileListPanel::ClearList() {
    listCtrl->DeleteAllItems();
}

void dFile_FileListPanel::OnItemActivated(wxListEvent &evt) {
    long listItemIndex = evt.GetIndex();
    
    if (listItemIndex == -1) {
        //TODO: REMOVE
        cout << "DEBUG: No item selected!" << endl;
        return;
    }
    
    long mfdIndex = listCtrl->GetItemData(listItemIndex);
    
    if (mfdIndex >= 0 && mfdIndex < (long)files.size()) {
        const fMetaData &file = files[mfdIndex];
        
        if (file.isDirectory) {
            // Handle special case for "current directory has nothing..."
            if (file.name == "current directory has nothing...") {
                //TODO: REMOVE
                cout << "DEBUG: Empty directory placeholder clicked" << endl;
                return;
            }
            
            // Build the new path
            wxString new_path = currentPath;
            
            // Ensure path ends with separator
            if (!new_path.EndsWith(wxFileName::GetPathSeparator())) {
                new_path += wxFileName::GetPathSeparator();
            }
            
            // Append directory name
            new_path += wxString::FromUTF8(file.name);
            
            // Ensure directory path ends with separator for display
            if (!new_path.EndsWith(wxFileName::GetPathSeparator())) {
                new_path += wxFileName::GetPathSeparator();
            }
            
            //TODO: REMOVE
            cout << "DEBUG: Navigating to directory: " << new_path.ToStdString() << endl;
            
            // Navigate to the new directory
            LoadDirectory(new_path);
            RefreshList(false);
            
            // Update frame title
            if (df_frame) {
                df_frame->set_current_directory(new_path);
                df_frame->update_title();
            }
        } else {
            // Handle file click (you might want to open the file)
            // TODO: REMOVE
            cout << "DEBUG: File clicked: " << file.name << endl;
            // TODO: Add file opening logic here
        }
    }
}

void dFile_FileListPanel::OnItemSelected(wxListEvent &evt) {
    // TODO: Implement if needed
}

void dFile_FileListPanel::OnColumnClicked(wxListEvent &evt) {
    // TODO: Implement if needed
}

void dFile_FileListPanel::LoadDirectory(const wxString &path) {
    currentPath = path;
    files.clear();
    
    dFile_DirectoryScanner dir_scanner(path);
    if (!dir_scanner.scan_dir()) {
        cout << "error in loading directory..." << endl;
    }
    
    files = dir_scanner.get_file_vect();
}

void dFile_FileListPanel::RefreshList(bool load_dir) {
    ClearList();
    if (load_dir) LoadDirectory(currentPath);
    PopulateListCtrl();

    // Auto-size columns
    for (int i = 0; i < 4; i++) {
        listCtrl->SetColumnWidth(i, wxLIST_AUTOSIZE);
    }
}

void dFile_FileListPanel::SortByColumn(int columnIndex, bool ascending) {
    switch (columnIndex) {
        case 0:
            std::sort(files.begin(), files.end(), 
            [] (const fMetaData &a, const fMetaData &b) {
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;
                return wxString::FromUTF8(a.name).Cmp(wxString::FromUTF8(b.name)) > 0;
            });
            break;
        case 1:
            std::sort(files.begin(), files.end(),
            [] (const fMetaData &a, const fMetaData &b) {
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;
                return wxString::FromUTF8(a.type).Cmp(wxString::FromUTF8(b.type)) > 0;
            });
            break;
        case 2:
            std::sort(files.begin(), files.end(), 
            [] (const fMetaData &a, const fMetaData &b) {
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;
                return a.size > b.size;
            });
            break;
        case 3:
            std::sort(files.begin(), files.end(),
            [] (const fMetaData &a, const fMetaData &b) {
                if (a.isDirectory && !b.isDirectory) return a.isDirectory > b.isDirectory;
                return a.modified > b.modified;
            });
            break;
    }

    RefreshList(false);
}

int dFile_FileListPanel::GetSelectedIndex() const {
    long selected = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected == -1) {
        return -1;
    }
    return listCtrl->GetItemData(selected);
}

fMetaData dFile_FileListPanel::GetSelectedFile() const {
    int index = GetSelectedIndex();
    if (index >= 0 && index < files.size()) {
        return files[index];
    }
    return fMetaData{"", "", 0, 0, false, false};
}

void dFile_FileListPanel::set_df_frame(dFile_Frame &dff) {
    df_frame = &dff;
}