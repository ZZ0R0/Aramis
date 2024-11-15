#include "BasePwd.h"

BOOL basePwd(char* output, size_t outputSize)
{
    CustomStrCopy(output, currentDirectory, outputSize);
    return TRUE;
}