#include "BaseLs.h"
#include <windows.h>
#include <shlwapi.h>  // Include for PathIsRelativeA
#include <string>

BOOL baseLs(std::string path, std::string &output){

    char previousCwd[MAX_PATH];

    // Get the current working directory
    if (!GetCurrentDirectoryA(MAX_PATH, previousCwd)) {
        return FALSE;
    }
   
    // Get the current working directory
    std::string completePath;


    if (PathIsRelativeA(path.c_str()))
    {
        completePath = currentDirectory + "\\" + path;
    }
    else
    {
        completePath = path;
    }

   // Change the current directory to the specified path
    if (!SetCurrentDirectoryA(path.c_str())) {
        return FALSE;
    }

    // Create a search handle
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA("*", &findFileData);

    // Check if the handle is valid
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    // Loop through all files in the directory
    do
    {
        // Add the file name to the output
        output += findFileData.cFileName;
        output += "\n";
    } while (FindNextFileA(hFind, &findFileData) != 0);

    // Close the search handle
    FindClose(hFind);

    SetCurrentDirectoryA(previousCwd);

    return TRUE;
}