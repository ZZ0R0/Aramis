#include "WrapPwd.h"
#include "BasePwd.h"
#include <string>

BOOL wrapPwd(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);
    UINT32 nbArg = getInt32(arguments);
    SIZE_T size = 0;
    PCHAR cmd = getString(arguments, &size);

    cmd = (PCHAR)LocalReAlloc(cmd, size + 1, LMEM_MOVEABLE | LMEM_ZEROINIT);


    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    PPackage output = newPackage(0, FALSE);
    
    std::string result;
    BOOL success = basePwd(result);

    if (!success)
    {
        char result[256];
        snprintf(result, sizeof(result), "[CD] Error executing command => %s !\n", cmd);
        addString(output, result, FALSE);
        return FALSE;
    }
    
    addBytes(responseTask, (PBYTE)result.c_str(), result.length(), TRUE);

    Parser *ResponseParser = sendPackage(responseTask);

    return TRUE;
}