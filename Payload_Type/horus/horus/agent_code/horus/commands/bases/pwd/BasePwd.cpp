#include "BasePwd.h"

BOOL basePwd(char* result, size_t resultSize)
{
    CustomStrCopy(result, currentDirectory, resultSize);
    return TRUE;
}