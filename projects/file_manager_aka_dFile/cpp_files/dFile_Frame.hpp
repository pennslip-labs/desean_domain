/**
 * @author Shamar Pennant
 * @date 08/02/26
 * 
 * the main window for the file manager. responsible for the 
 * ui, containers, menu & status bars
 */

// the main window for the file manager.
// responsible for the ui, containers,
// 

#ifndef DFILE_FRAME_HPP
    #define DFILE_FRAME_HPP

#include <iostream>
#include <wx/wx.h>

class dFile_Frame {
    private: 
        wxString frame_name;          // the final frame name being used. helps user understand their location in the directory
        wxString current_directory;   // the last saved current directory
        wxString apk_name;            // holds the application name 
        wxBoxSizer* frame_sizer;      // the main sizer used for the frame itself
        wxFrame* main_frame;          // the main frame holding everything
        wxPanel* container;           // the container used to position everything within the frame
        wxBoxSizer* container_sizer;  // personal sizer used for the container
    
    public: 
        dFile_Frame();// default constructor. initializes the file list panel and frame, sizers, and container using the home dirctory
        /** given a wxString loaded_directory, loads the file list panel with the given wxString
         * and initializes the frame, sizers and containers
         */
        dFile_Frame(const wxString &loaded_directory); 

        wxString get_frame_name() const;        // returns the entire frame name
        wxString get_current_directory() const; // returns the current directory that was last saved
        wxBoxSizer* get_frame_sizer() const;    // returns the frame sizer
        wxFrame* get_main_frame();              // returns the frame

        void set_frame_name();                                     // changes frame_name based based on the cat of apk and the last saved directory
        void set_current_directory(const wxString &new_directory); // changes the current directory path being used to wxString new_directory
        void set_frame_sizer(wxBoxSizer* new_sizer);               // sets a new sizer for the frame given wxBoxSizer new_sizer
        void set_main_frame(wxFrame* new_frame);                   // sets a new frame given wxFrame new_frame
        void update_title();                                       // updates the title of the window given the current frame_name
};

#endif