// helper class that reads a direcotry 
// and resturns a vector of dFile_Info 

#include "wx/dir.h"
#include <vector>
#include <filesystem>
#include <string>
#include "wx/string.h"
#include "wx/filename.h"

#ifndef DFILE_DIRECTORYSCANNER_HPP
    #define DFILE_DIRECTORYSCANNER_HPP

struct fMetaData {         // used to contain file metadata within the file_map
    std::string name;      // file name
    std::string type;      // file type
    uintmax_t size;        // file size
    std::time_t modified;  // file modification date
    bool isDirectory;      // is a directory or not
    bool isLink;           // is a link or not
};

class dFile_DirectoryScanner {
    private:
        wxString dir_path;                    //holds the current directory
        std::vector<wxString> past_dir_paths; //contains prev directories for back navigation
        std::vector<fMetaData> file_vect;     //list of files/dirs in current directory

    public:
        // explicit consrtuctor to ensure unwanted conversions dont occur
        explicit dFile_DirectoryScanner(const wxString &path);

        // getters
        wxString get_file_dir() const;
        std::vector<wxString> get_past_dir_vect() const;
        std::vector<fMetaData> get_file_vect() const;
        int get_num_of_paths_in_history() const;
        int get_num_of_files_in_dir() const;

        // setters
        void set_dir_path(const wxString &new_path); // sets the current directory path
        void reset_past_dir_paths();                 // resets the history to be empty

        // other methods. helpers if you will
        void add_path_to_history(const wxString &new_path); // adds path to history
        bool check_in_history(const wxString &path);        // checks if path is in history, reutrns true on success
        void rmv_oldest_path_from_history();                // removes the oldest path in history
        /* the big boi scanner. given that this object has the current directory,
            scan it, and then pull file metadata and save it in the files
            vector. if nothing is found, then a pseudo file will be pushed
            into the vector with a name that  displays "current directory
            has nothing..." and returns false. returns true on success */
        bool scan_dir();                                    
};

#endif