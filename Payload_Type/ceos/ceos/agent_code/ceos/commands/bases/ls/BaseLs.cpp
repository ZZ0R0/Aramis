#include "BaseLs.h"

BOOL baseLs(std::string &output){
   
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

    return TRUE;
}