#include "BasePwd.h"
#include <windows.h>

BOOL basePwd(char* result, size_t resultSize)
{
    MessageBoxA(NULL, "basePwd function called", "Info", MB_OK);
    CustomStrCopy(result, currentDirectory, resultSize);
    return TRUE;
}