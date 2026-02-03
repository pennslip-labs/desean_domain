// the main window for the file manager.
// responsible for the ui, containers,
// menu & status bars, and binding events

// the central driver

#ifndef DFILE_FRAME_H
    #define DFILE_FRAME_H

#include <iostream>
#include <wx/wx.h>

class dFile_Frame {
    private: 
        wxString frame_name; 
        wxString current_directory;
        wxString apk_name;
        wxBoxSizer* main_sizer;
        wxFrame* main_frame;
    
    public: 
        dFile_Frame();
        dFile_Frame(const wxString &loaded_directory);

        wxString get_frame_name() const;
        wxString get_current_directory() const;
        wxBoxSizer* get_main_sizer() const;
        wxFrame* get_main_frame();

        void set_frame_name(const wxString &new_name);
        void set_current_directory(const wxString &new_directory);
        void set_main_sizer(wxBoxSizer* new_sizer);
        void set_main_frame(wxFrame* new_frame);
};

#endif