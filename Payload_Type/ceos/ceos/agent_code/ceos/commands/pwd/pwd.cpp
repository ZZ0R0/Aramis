#include "pwd.h"
#include <windows.h>
#include <string>

BOOL executePwd(PParser arguments)
{
    SIZE_T size = 0;
    PCHAR newDir = getString(arguments, &size);

    // Check if the directory exists before changing
    if (SetCurrentDirectoryA(newDir))
    {
        currentDirectory = newDir;  // Update global directory
        return TRUE;
    }
    else
    {
        _err("[CD] Directory change failed");
        return FALSE;
    }

    std::string getDirectory()
}