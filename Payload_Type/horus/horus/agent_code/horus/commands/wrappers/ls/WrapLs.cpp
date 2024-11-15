#include "WrapCd.h"
#include "BaseCd.h"

// Function to handle the 'cd' command
BOOL wrapCd(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);
    UINT32 nbArg = getInt32(arguments);
    SIZE_T size = 0;
    PCHAR newDir = getString(arguments, &size);

    // Reallocate memory for newDir without using C/C++ standard libraries
    newDir = (PCHAR)LocalReAlloc(newDir, size + 1, LMEM_MOVEABLE | LMEM_ZEROINIT);

    // Create a response package
    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    // Create an output package
    PPackage output = newPackage(0, FALSE);

    // Execute the CD command
    BOOL success = baseCd(newDir);
    if (!success)
    {
        // Define a result buffer without using C/C++ standard libraries
        char result[256];
        result[0] = '\0'; // Initialize the result string

        // Add an error message to the result
        CustomStrCopy(result, "Failed to change directory.\n", sizeof(result));

        // Add the result to the output package
        addString(output, result, FALSE);
    }
    else
    {
        // Define a success message
        char successMsg[256];
        successMsg[0] = '\0';
        CustomStrCopy(successMsg, "Directory changed successfully.\n", sizeof(successMsg));

        // Add the success message to the output package
        addString(output, successMsg, FALSE);
    }

    // Send the output package
    sendPackage(responseTask);

    // Clean up
    LocalFree(newDir);

    return success;
}