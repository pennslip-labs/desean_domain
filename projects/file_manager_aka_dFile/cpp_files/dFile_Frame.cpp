#include "dFile_Frame.hpp"
#include "dFile_FileListPanel.hpp"

using namespace std;

// Default constructor
dFile_Frame::dFile_Frame() {
    current_directory = "~/"; // setting directory to home
    apk_name = "dFile"; // setting the app name 
    frame_name = apk_name + " - " + current_directory; // initializing the frame name
    main_frame = new wxFrame(nullptr, wxID_ANY, frame_name); // init the frame with proper wxString conversion

    // initializing the container panel for the frame
    container = new wxPanel(main_frame);
    
    //TODO: remove later
    std::cout << "just entered the frame constructor" << endl;

    // Create file list panel as a child of container
    dFile_FileListPanel* file_list_panel = new dFile_FileListPanel(container, wxID_ANY);
    file_list_panel->LoadDirectory(current_directory);
    file_list_panel->RefreshList(false);// Now refresh the list
    
    //TODO: remove later
    std::cout << "and now im exaclty here" << endl;

    // Create sizer for the container that will hold the file_list_panel
    container_sizer = new wxBoxSizer(wxVERTICAL);
    container_sizer->Add(file_list_panel, 1, wxEXPAND | wxALL, 0);
    container->SetSizer(container_sizer);  // Set the sizer on container
    
    // Create sizer for the main frame that will hold the container
    frame_sizer = new wxBoxSizer(wxVERTICAL);
    frame_sizer->Add(container, 1, wxEXPAND | wxALL, 0);
    main_frame->SetSizer(frame_sizer);  // Set the sizer on main_frame
    


}

// Constructor with directory parameter
dFile_Frame::dFile_Frame(const wxString &loaded_directory) {
    current_directory = loaded_directory; // setting directory to the loaded one
    apk_name = "dFile"; // setting the app name 
    frame_name = apk_name + " - " + current_directory; // initializing frame name
    main_frame = new wxFrame(nullptr, wxID_ANY, frame_name); // init the frame with proper wxString conversion

   // initializing the container panel for the frame
    container = new wxPanel(main_frame);
    
    //TODO: remove later
    std::cout << "just entered the frame constructor" << endl;

    // Create file list panel as a child of container
    dFile_FileListPanel* file_list_panel = new dFile_FileListPanel(container, wxID_ANY);
    file_list_panel->LoadDirectory(current_directory);
    file_list_panel->RefreshList(false);// Now refresh the list
    
    //TODO: remove later
    std::cout << "and now im exaclty here" << endl;

    // Create sizer for the container that will hold the file_list_panel
    container_sizer = new wxBoxSizer(wxVERTICAL);
    container_sizer->Add(file_list_panel, 1, wxEXPAND | wxALL, 0);
    container->SetSizer(container_sizer);  // Set the sizer on container
    
    // Create sizer for the main frame that will hold the container
    frame_sizer = new wxBoxSizer(wxVERTICAL);
    frame_sizer->Add(container, 1, wxEXPAND | wxALL, 0);
    main_frame->SetSizer(frame_sizer);  // Set the sizer on main_frame
}

// Getter functions
wxString dFile_Frame::get_frame_name() const { 
    return frame_name; 
}

wxString dFile_Frame::get_current_directory() const { 
    return current_directory; 
}

wxBoxSizer* dFile_Frame::get_frame_sizer() const { 
    return frame_sizer; 
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

void dFile_Frame::set_frame_sizer(wxBoxSizer* new_sizer) { 
    frame_sizer = new_sizer; 
}

void dFile_Frame::set_main_frame(wxFrame* new_frame) { 
    main_frame = new_frame; 
}