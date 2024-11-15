#include "WrapExit.h"
#include "BaseExit.h"

BOOL wrapExit(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);

    // Create a response package
    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    // Execute the Exit command
    BOOL success = baseExit();

    // Send the response package
    sendPackage(responseTask);

    // Clean up
    LocalFree(taskUuid);
    return success;
}