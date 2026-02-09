#include "dFile_DirectoryScanner.hpp"
#include <iostream>
#include "dFile_wxDataFormat.hpp"
#include "Symlink_Check.hpp"

using namespace std;

dFile_DirectoryScanner::dFile_DirectoryScanner(const wxString &path) {
    dFile_DirectoryScanner::set_dir_path(path);
}

// -- getters

wxString dFile_DirectoryScanner::get_file_dir() const {return dir_path;}
vector<wxString> dFile_DirectoryScanner::get_past_dir_vect() const {return past_dir_paths;}
vector<fMetaData> dFile_DirectoryScanner::get_file_vect() const {return file_vect;}
int dFile_DirectoryScanner::get_num_of_paths_in_history() const {return past_dir_paths.size();}
int dFile_DirectoryScanner::get_num_of_files_in_dir() const {return file_vect.size();}

// -- setters

void dFile_DirectoryScanner::set_dir_path(const wxString &new_path) {dir_path = new_path;}
void dFile_DirectoryScanner::reset_past_dir_paths() {past_dir_paths.clear();}

// -- other methods

void dFile_DirectoryScanner::add_path_to_history(const wxString &new_path) {past_dir_paths.push_back(new_path);}
bool dFile_DirectoryScanner::check_in_history(const wxString &path) {
    for (const wxString &x : past_dir_paths) {
        if (path == x) return true;
    }
    return false;
}
void dFile_DirectoryScanner::rmv_oldest_path_from_history() {
    if (!past_dir_paths.empty()) {
        past_dir_paths.erase(past_dir_paths.begin());
    }
}
bool dFile_DirectoryScanner::scan_dir() {
    // expand the path so everything can use it
    wxString expandedDir = expand_file_paths(dir_path);

    // if the current path is not already in the
    // history, add it
    if (!check_in_history(expandedDir)) {
        past_dir_paths.push_back(expandedDir);
    }
    // ensure that file_vect is clear for each scan
    file_vect.clear();

    cout << "attempting to open directory \"" + expandedDir.ToStdString() + "\"..." << endl;

    // attempt to open the current directory
    wxDir open_dir(expandedDir);
    if (!open_dir.IsOpened()) return false;
    else { // safe gaurding the rest of the code for sanity
        // canonical wxWidget pattern for iterating files. using GetFirst() and
        // GetNext() in tandem as a makeshift iterator from the documentation
        wxString wxTempStr; // temp wxString for file names
        // if anything exists in current directory, get the first file, no wildcard filters, and include files & dir (no hidden stuff)
        bool contin = open_dir.GetFirst(&wxTempStr, wxEmptyString, wxDIR_DEFAULT);
        while (contin) { // main loop for all files/folders in the directory
            // skip . and .. directory entries
            if (wxTempStr == "." || wxTempStr == "..") {
                contin = open_dir.GetNext(&wxTempStr);
                continue;
            }
            
            // using wxFileName to get the file name, extension, and type.
            // though it requires the full file path to acquire its metadata
            wxString full_path_to_file = expandedDir + wxFileName::GetPathSeparator() + wxTempStr;
            wxFileName fn(full_path_to_file);

            // if symlink is encountered, will be skipped
            if (IsSymlink(full_path_to_file.ToStdString())) {
                cout << "\"" + wxTempStr.ToStdString() + "\" was detected as a symlink. skipping..." << endl;
                contin = open_dir.GetNext(&wxTempStr);
                continue;
            }

            // ensuring that the correct time is being pulled
            wxDateTime modifTime = fn.GetModificationTime(); 
            time_t ts = 0;
            if (modifTime.IsValid()) ts = modifTime.GetTicks();

            // ensuring that file size can be retrieved safely as well
            uintmax_t file_size = 0;
            if (!fn.IsDir()) { // only grab the file size for files
                wxULongLong size = fn.GetSize();
                if (size != wxInvalidSize) file_size = size.GetValue();
                else cout << "Invalid size for \"" + wxTempStr.ToStdString() + "\", setting to 0" << endl;
            }

            // now building the fMetaData struct
            fMetaData tmpMD = {
                wxTempStr.ToStdString(),                // get the file name
                fn.GetExt().ToStdString(),              // grab the extension
                file_size,                              // get the file size (unitmax_t)
                ts,                                     // grab the modification time
                wxDir::Exists(full_path_to_file),       // check if it's a directory
                false                                   // check if it's a symlink
            };

            // push the new metadata into the meta vector
            file_vect.push_back(tmpMD);

            // try to get the next file/dir in the directory. if theres no more, 
            // then it will return false
            contin = open_dir.GetNext(&wxTempStr);
        }

        // if the file vector is empty, then it indicates that the current dir is empty as well
        if (file_vect.empty()) {
            // can return a pseudo file that says as the name that theres no files(?)
            // get the current time stamp
            std::time_t timeStamp; 
            std::time(&timeStamp);
            fMetaData tmpMD = { // pseudo file detailing thats theres nothing in the dir
                "current directory has nothing...",
                "foo",
                0,
                timeStamp,
                false,
                false
            };

            file_vect.push_back(tmpMD);
            return true;
        } 
    }
    return true;
}