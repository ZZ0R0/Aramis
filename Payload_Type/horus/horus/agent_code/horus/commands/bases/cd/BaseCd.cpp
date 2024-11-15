#include "BaseCd.h"
#include <shlwapi.h>  // Include for PathIsRelativeA

BOOL baseCd(std::string path)
{
    std::string completePath;


    if (PathIsRelativeA(path.c_str()))
    {
        completePath = currentDirectory + "\\" + path;
    }
    else
    {
        completePath = path;
    }


    if (SetCurrentDirectoryA(completePath.c_str()))
    {
        currentDirectory = completePath;  // Update global directory
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}