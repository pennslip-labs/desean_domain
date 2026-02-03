#include "dFile_Frame.h"

using namespace std;

// Default constructor
dFile_Frame::dFile_Frame() {
    current_directory = "~/"; // setting directory to home
    apk_name = "dFile"; // setting the app name 
    frame_name = apk_name + " - " + current_directory; // initializing the frame name
    main_frame = new wxFrame(nullptr, wxID_ANY, frame_name); // init the frame with proper wxString conversion
}

// Constructor with directory parameter
dFile_Frame::dFile_Frame(const wxString &loaded_directory) {
    current_directory = loaded_directory; // setting directory to the loaded one
    apk_name = "dFile"; // setting the app name 
    frame_name = apk_name + " - " + current_directory; // initializing frame name
    main_frame = new wxFrame(nullptr, wxID_ANY, frame_name); // init the frame with proper wxString conversion
}

// Getter functions
wxString dFile_Frame::get_frame_name() const { 
    return frame_name; 
}

wxString dFile_Frame::get_current_directory() const { 
    return current_directory; 
}

wxBoxSizer* dFile_Frame::get_main_sizer() const { 
    return main_sizer; 
}

wxFrame* dFile_Frame::get_main_frame() {  
    return main_frame; 
}

// Setter functions
void dFile_Frame::set_frame_name(const wxString &new_name) { 
    frame_name = new_name; 
}

void dFile_Frame::set_current_directory(const wxString &new_directory) { 
    current_directory = new_directory; 
}

void dFile_Frame::set_main_sizer(wxBoxSizer* new_sizer) { 
    main_sizer = new_sizer; 
}

void dFile_Frame::set_main_frame(wxFrame* new_frame) { 
    main_frame = new_frame; 
}