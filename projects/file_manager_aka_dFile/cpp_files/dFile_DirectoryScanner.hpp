/**
 * @author Shamar Pennant
 * @date 08/02/26
 * 
 * responsible for reading files within a directory, processing
 * their meta data, and saving them in a vector to be used 
 * across the file manager to allow file representation.
 */

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
        /* explicit consrtuctor to ensure unwanted conversions dont occur. 
        takes in a const wxString object as a path to initialize*/
        explicit dFile_DirectoryScanner(const wxString &path);

        // getters
        wxString get_file_dir() const; // retrieve the file directory being used by the directory scanner
        std::vector<wxString> get_past_dir_vect() const; // gets the vector of previous directories
        std::vector<fMetaData> get_file_vect() const; // gets the file meta data vector from within the last processed directory
        int get_num_of_paths_in_history() const; // returns the number of paths in history vector
        int get_num_of_files_in_dir() const; // gets the number of files in the last processed directory

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