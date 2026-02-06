#ifndef DFILE_WXDATAFORMAT_HPP
#define DFILE_WXDATAFORMAT_HPP

#include "wx/string.h"
#include <ctime>
#include <stdint.h>
#include <math.h>

/**
 * a helper file that will convert data formats to a wxString
 */

// takes a uintmax_t variable and formats it into a wxString object
inline wxString format_size_to_wxStr(uintmax_t size) {
    // constants used to data conversions and measurements
    const double KB = 1024.0;
    const double MB = pow(KB, 2);
    const double GB = pow(KB, 3);
    const double TB = pow(KB, 4);

    // size formatting
    if (size >= TB) return wxString::Format("%.2f TB", size / TB);
    else if (size >= GB) return wxString::Format("%.2f GB", size / GB);
    else if (size >= MB) return wxString::Format("%.2f MB", size / MB);
    else if (size >= KB) return wxString::Format("%.2f KB", size / KB);
    // just for some future proofing if the file is HUGE
    else return wxString::Format("%llu", size);
}

// takes a time_t variable and formates it into a wxString object 
inline wxString format_date_to_wxStr(time_t date) {
    // ensure no weird values are being passed
    if (date <= 0) return wxString("N/A");

    // grabbing the struct that contains all the pieces of the date
    struct tm *datetime = localtime(&date);

    // ensure that localtime didnt return null
    if (datetime == nullptr) return wxString("N/A");

    return wxString::Format("%d/%d/%d - %02d:%02d", 
        datetime -> tm_mday, 
        datetime -> tm_mon + 1, 
        datetime -> tm_year + 1900, 
        datetime -> tm_hour, 
        datetime -> tm_min);
}

// takes in a raw wxString file path and normalizes/expands it
inline wxString expand_file_paths(const wxString &raw_path) {
    wxFileName fn(raw_path); // create a wxFileName object
    // what normalizes and expands the raw file path
    fn.Normalize(wxPATH_NORM_DOTS |      // Remove . and ..
                 wxPATH_NORM_ABSOLUTE |  // Make path absolute
                 wxPATH_NORM_TILDE |     // Expand ~ to home directory
                 wxPATH_NORM_LONG |      // Use long path format (Windows)
                 wxPATH_NORM_CASE);      // Normalize case (Windows/macOS)

    return fn.GetFullPath();
}

#endif