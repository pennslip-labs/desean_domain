#include "dFile_Frame.hpp"
#include "dFile_FileListPanel.hpp"

using namespace std;

// Default constructor
dFile_Frame::dFile_Frame() {
    current_directory = "~/";
    apk_name = "dFile";
    frame_name = apk_name + " - " + current_directory;
    main_frame = new wxFrame(nullptr, wxID_ANY, frame_name);

    container = new wxPanel(main_frame);
    
    dFile_FileListPanel* file_list_panel = new dFile_FileListPanel(container, wxID_ANY, this);
    file_list_panel->LoadDirectory(current_directory);
    
    container_sizer = new wxBoxSizer(wxVERTICAL);
    container_sizer->Add(file_list_panel, 1, wxEXPAND | wxALL, 0);
    container->SetSizer(container_sizer);
    
    frame_sizer = new wxBoxSizer(wxVERTICAL);
    frame_sizer->Add(container, 1, wxEXPAND | wxALL, 0);
    main_frame->SetSizer(frame_sizer);
    
    file_list_panel->RefreshList(false);
}

// Constructor with directory parameter
dFile_Frame::dFile_Frame(const wxString &loaded_directory) {
    current_directory = loaded_directory;
    apk_name = "dFile";
    frame_name = apk_name + " - " + current_directory;
    main_frame = new wxFrame(nullptr, wxID_ANY, frame_name);

    container = new wxPanel(main_frame);
    
    dFile_FileListPanel* file_list_panel = new dFile_FileListPanel(container, wxID_ANY, this);
    file_list_panel->LoadDirectory(current_directory);
    
    container_sizer = new wxBoxSizer(wxVERTICAL);
    container_sizer->Add(file_list_panel, 1, wxEXPAND | wxALL, 0);
    container->SetSizer(container_sizer);
    
    frame_sizer = new wxBoxSizer(wxVERTICAL);
    frame_sizer->Add(container, 1, wxEXPAND | wxALL, 0);
    main_frame->SetSizer(frame_sizer);
    
    file_list_panel->RefreshList(false);
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
void dFile_Frame::set_frame_name() {
    frame_name = apk_name + " - " + current_directory; 
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

void dFile_Frame::update_title() {
    frame_name = apk_name + " - " + current_directory;
    main_frame->SetTitle(frame_name);
}