// helper class that reads a direcotry 
// and resturns a vector of dFile_Info 

#include "wx/dir.h"
#include <vector>

#ifndef DFILE_DIRECTORYSCANNER_H
    #define DFILE_DIRECTORYSCANNER_H

using namespace std;

class dFile_DirectoryScanner : public wxDir {
    private:
        wxString dir_path; //holds the current directory
        vector<wxString> past_dir_paths; //contains prev directories for back navigation
        vector<wxString> file_list; //list of files/dirs in current directory

    public:
        dFile_DirectoryScanner(const wxString &path);

        // getters
        wxString get_file_dir() const;
        vector<wxString> get_past_dir_vect() const;
        vector<wxString> get_file_vect() const;
        int get_num_of_paths_in_history() const;
        int get_num_of_files_in_dir() const;

        // setters
        void set_dir_path(const wxString &new_path); // sets the current directory path
        void reset_past_dir_paths(); // resets the history to be empty

        // other methods. helpers if you will
        void add_path_to_history(const wxString &new_path); // adds path to history
        bool check_in_history(const wxString &path); // checks if path is in history
        void rmv_path_from_history(const wxString &path); // removes path from history
        void rmv_oldest_path_from_history(); // removes the oldest path in history
};

#endif;