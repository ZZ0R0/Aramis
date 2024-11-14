#include "BaseCd.h"
#include <shlwapi.h>  // Include for PathIsRelativeA

BOOL baseCd(std::string newDir)
{
    std::string completePath;


    if (PathIsRelativeA(newDir.c_str()))
    {
        completePath = currentDirectory + "\\" + newDir;
    }
    else
    {
        completePath = newDir;
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