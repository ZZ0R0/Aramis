#include "WrapPwd.h"
#include "BasePwd.h"
#include <string>

BOOL wrapPwd(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);


    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    PPackage output = newPackage(0, FALSE);
    
    std::string result;
    BOOL success = basePwd(result);

    if (!success)
    {
        char result[256];
        addString(output, "[PWD] Error getting current working directory !\n", FALSE);
        return FALSE;
    }
    
    addBytes(responseTask, (PBYTE)result.c_str(), result.length(), TRUE);

    Parser *ResponseParser = sendPackage(responseTask);

    return TRUE;
}