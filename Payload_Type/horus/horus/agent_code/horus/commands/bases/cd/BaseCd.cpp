#include "BaseCd.h"

BOOL baseCd(const char* path)
{
    char completePath[MAX_PATH_SIZE];

    if (CustomPathIsRelativeA(path))
    {
        // Initialize completePath with currentDirectory
        CustomStrCopy(completePath, currentDirectory, MAX_PATH_SIZE);

        // Append "\\"
        CustomStrCat(completePath, "\\", MAX_PATH_SIZE);

        // Append path
        CustomStrCat(completePath, path, MAX_PATH_SIZE);
    }
    else
    {
        // Copy path into completePath
        CustomStrCopy(completePath, path, MAX_PATH_SIZE);
    }

    if (SetCurrentDirectoryA(completePath))
    {
        // Update currentDirectory
        CustomStrCopy(currentDirectory, completePath, MAX_PATH_SIZE);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}