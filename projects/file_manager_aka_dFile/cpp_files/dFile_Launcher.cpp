// main entry point to the program. creating the frame,
// and setting global themes
#include "dFile_Frame.hpp"
#include <iostream>
#include <wx/cmdline.h>


using namespace std;

class dFile_Launcher : public wxApp {
    private:
        wxString starting_directory = "~/"; //default starting directory

        // setting up for cmd line args. setting the param's as strings and optional
        void OnInitCmdLine(wxCmdLineParser& parser) {
            parser.AddParam("Directory to open", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
        } 
        // parsing any cmd line args given
        bool OnCmdLineParsed(wxCmdLineParser& parser) {
            if (parser.GetParamCount() > 0) {
                starting_directory = parser.GetParam(0);
                cout << "Directory argument received: " << starting_directory << endl;
            } else {
                cout << "No directory argument provided, using default: " << starting_directory << endl;
            }
            return true;
        }   

        // wxWidgets "main" function. is initialized by the wxIMPLEMENT_APP macro
        bool OnInit() {
            cout << "dFile Launcher Starting..." << endl;
            
            // Call parent class OnInit to process command line arguments
            if (!wxApp::OnInit()) {
                return false;
            }
            
            cout << "Using directory: " << starting_directory << endl;

            dFile_Frame* main_app = new dFile_Frame(starting_directory);
            main_app->get_main_frame()->Layout();
            main_app->get_main_frame()->Show();

            cout << "dFile Launcher has in fact -- been launched." << endl;

            return true;
        }
};

wxIMPLEMENT_APP(dFile_Launcher);
