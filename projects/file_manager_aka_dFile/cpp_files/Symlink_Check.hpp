/**
 * @author Copilot
 * @date 08/02/26
 * 
 * helper that was sourced from Copilot 2026 > https://copilot.microsoft.com/shares/WESpw9pQiDC3vxDcsage5
 * I had difficulties with my installation of wxWidgets as it seemed I 
 * didn't have any method of detecting symlinks included in the package.
 * which lead to segfaults within my code as it couldn't parse the 
 * data correctly. So i opted to use this to try and skip symlinks 
 * all together.
*/

#ifndef SYMLINK_CHECK_HPP
#define SYMLINK_CHECK_HPP

#include <string>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <sys/stat.h>
    #include <unistd.h>
#endif

bool IsSymlink(const std::string& path)
{
    #if defined (_WIN32)
        // Convert UTF-8 → UTF-16
        int wlen = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, nullptr, 0);
        if (wlen == 0) return false;

        std::wstring wpath(wlen, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, &wpath[0], wlen);

        DWORD attrs = GetFileAttributesW(wpath.c_str());
        if (attrs == INVALID_FILE_ATTRIBUTES)
            return false;

        // Symlinks and junctions are reparse points
        return (attrs & FILE_ATTRIBUTE_REPARSE_POINT) != 0;

    #else
        struct stat info;
        if (lstat(path.c_str(), &info) != 0)
            return false;

        return S_ISLNK(info.st_mode);
    #endif
}

#endif
