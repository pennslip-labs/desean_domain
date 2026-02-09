/**
 * @author Shamar Pennant
 * @date 08/02/26
 * 
 * main entry point to the program. processing cmd line 
 * arguments and loading the frame.
 */

#include "dFile_Frame.hpp"
#include <iostream>
#include <wx/cmdline.h>

using namespace std;

class dFile_Launcher : public wxApp {
    private:
        wxString starting_directory = "~/";

        // over riden wxWidgets function to allow parameters to be passed via the terminal
        void OnInitCmdLine(wxCmdLineParser& parser) {
            parser.AddParam("Directory to open", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
        } 
        
        // over riden wxWidgets funcition to define how to handle cmdline arguments
        bool OnCmdLineParsed(wxCmdLineParser& parser) {
            if (parser.GetParamCount() > 0) {
                starting_directory = parser.GetParam(0);
                cout << "Directory argument received: " << starting_directory << endl;
            } else {
                cout << "No directory argument provided, using default: " << starting_directory << endl;
            }
            return true;
        }   

        // over riden wxFunction to define how the appliction should start
        bool OnInit() {
            cout << "dFile Launcher Starting..." << endl;
            
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