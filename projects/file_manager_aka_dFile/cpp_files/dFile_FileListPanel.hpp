/**
 * @author Shamar Pennant
 * @date 08/02/26
 * 
 * responsible for displaying direcotry contents, handling double 
 * click navigation, selection, and methods of loading and 
 * refreshing the list
 */

#ifndef DFILE_FILELISTPANEL_HPP
    #define DFILE_FILELISTPANEL_HPP

#include "wx/listctrl.h"
#include "wx/wx.h"
#include "dFile_DirectoryScanner.hpp" // using for file meta data

// Forward declaration
class dFile_Frame;

class dFile_FileListPanel : public wxPanel {
    private:
        wxListCtrl* listCtrl; // gives control over the list in the panel
        wxString currentPath; // will hold the current path being used
        std::vector<fMetaData> files; // current path files info
        dFile_Frame *df_frame; // used to help refresh the frame title

        int currentSortColumn = 0; // used to indicate the volumn being used for sorting
        bool sortAscending = true; // indicating the direction of the sort

        //--internal helpers
        /** given file data is processed with the directory scanner, it populates the
         * list ctrl object in the frame with enries representing files and directories
        */
        void PopulateListCtrl(); 
        void ClearList(); // clears list ctrl to help prime for new files

        // event handlers
        void OnItemActivated(wxListEvent& evt); // envent handler for when an item in the list is activated via double click or enter
        void OnItemSelected(wxListEvent& evt); // event handler for when an item in the list is selected
        void OnColumnClicked(wxListEvent& evt); // event handler for when a column is clicked

    public:
        /**constructory. takes in a parent object pointer, an assigned window id (left as default), 
         * and a pointer to the over all frame to allow communication when changing the window text
         * during directory changes
        */
        dFile_FileListPanel(wxWindow* parent, wxWindowID id = wxID_ANY, dFile_Frame *frame = nullptr);

        /**uses the directory scanner to load file meta within the currently saved file directory. 
         * takes in const wxString path to use for the scan
         */
        void LoadDirectory(const wxString& path);
        /**refreshes the list ctrl. uses bool load to indicate whether or not to load the directory
         * again
         */
        void RefreshList(bool load);

        // takes in the columnindex to sort by and the direction (ascedning or decending)
        void SortByColumn(int columnIndex, bool ascending);

        int GetSelectedIndex() const; // gets the selected index within list ctrl
        fMetaData GetSelectedFile() const; // retrieves the selected file meta data

        wxString GetCurrentPath() const { return currentPath; } // returns the path last saved

        void set_df_frame(dFile_Frame &dff); // links dFile_Frame dff to this object to allow communication among one another
};

#endif