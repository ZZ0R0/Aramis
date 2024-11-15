#include "BaseCd.h"

BOOL baseCd(const char* path)
{
    char completePath[MAX_PATH];

    if (CustomPathIsRelativeA(path))
    {
        // Initialize completePath with currentDirectory
        CustomStrCopy(completePath, currentDirectory, MAX_PATH);

        // Append "\\"
        CustomStrCat(completePath, "\\", MAX_PATH);

        // Append path
        CustomStrCat(completePath, path, MAX_PATH);
    }
    else
    {
        // Copy path into completePath
        CustomStrCopy(completePath, path, MAX_PATH);
    }

    if (SetCurrentDirectoryA(completePath))
    {
        // Update currentDirectory
        CustomStrCopy(currentDirectory, completePath, MAX_PATH);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}