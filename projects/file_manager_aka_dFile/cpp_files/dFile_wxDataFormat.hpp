/**
 * @author Shamar Pennant
 * @date 08/02/26
 * 
 * This is a helper file to help format the different data types
 * as one would expect when viewing files such as data size,
 * dates, and also expanding file paths.
 */

#ifndef DFILE_WXDATAFORMAT_HPP
#define DFILE_WXDATAFORMAT_HPP

#include "wx/string.h"
#include <ctime>
#include <stdint.h>
#include <math.h>
#include "wx/filename.h"

/**
 * a helper file that will convert data formats to a wxString
 */

// takes a uintmax_t variable and formats it into a wxString object
inline wxString format_size_to_wxStr(uintmax_t size) {
    const double KB = 1024.0;
    const double MB = pow(KB, 2);
    const double GB = pow(KB, 3);
    const double TB = pow(KB, 4);

    if (size >= TB) return wxString::Format("%.2f TB", size / TB);
    else if (size >= GB) return wxString::Format("%.2f GB", size / GB);
    else if (size >= MB) return wxString::Format("%.2f MB", size / MB);
    else if (size >= KB) return wxString::Format("%.2f KB", size / KB);
    else return wxString::Format("%llu", size);
}

// takes a time_t variable and formats it into a wxString object 
inline wxString format_date_to_wxStr(time_t date) {
    if (date <= 0) return wxString("N/A");

    struct tm *datetime = localtime(&date);
    if (datetime == NULL) return wxString("N/A");

    return wxString::Format("%d/%d/%d - %02d:%02d", 
        datetime->tm_mday, 
        datetime->tm_mon + 1, 
        datetime->tm_year + 1900, 
        datetime->tm_hour, 
        datetime->tm_min);
}

// takes in a raw wxString file path and normalizes/expands it
inline wxString expand_file_paths(const wxString &raw_path) {
    wxFileName fn(raw_path);
    fn.Normalize(wxPATH_NORM_DOTS |      
                 wxPATH_NORM_ABSOLUTE |  
                 wxPATH_NORM_TILDE |     
                 wxPATH_NORM_LONG |      
                 wxPATH_NORM_CASE);      

    return fn.GetFullPath();
}

#endif