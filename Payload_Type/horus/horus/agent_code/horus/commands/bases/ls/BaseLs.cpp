#include "BaseLs.h"

BOOL baseLs(const char* path, char* result, size_t resultSize) {

    char previousCwd[MAX_PATH_SIZE];

    // Get the current working directory
    if (!GetCurrentDirectoryA(MAX_PATH_SIZE, previousCwd)) {
        return FALSE;
    }
   
    char completePath[MAX_PATH_SIZE];
   
    if (CustomPathIsRelativeA(path)) {
        // Build completePath = currentDirectory + "\\" + path

        // Initialize completePath with currentDirectory
        CustomStrCopy(completePath, currentDirectory, MAX_PATH_SIZE);

        // Append "\\"
        CustomStrCat(completePath, "\\", MAX_PATH_SIZE);

        // Append path
        CustomStrCat(completePath, path, MAX_PATH_SIZE);
    }
    else {
        // Copy path into completePath
        CustomStrCopy(completePath, path, MAX_PATH_SIZE);
    }

    // Set the current directory to the target path
    if (!SetCurrentDirectoryA(completePath)) {
        return FALSE;
    }

    // Initialize result
    result[0] = '\0';

    // Create a search handle
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA("*", &findFileData);

    // Check if the handle is valid
    if (hFind == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    // Loop through all files in the directory
    do {
        // Add the file name to the result
        CustomStrCat(result, findFileData.cFileName, resultSize);
        CustomStrCat(result, "\n", resultSize);
    } while (FindNextFileA(hFind, &findFileData) != 0);

    // Close the search handle
    FindClose(hFind);

    // Restore the previous working directory
    SetCurrentDirectoryA(previousCwd);

    return TRUE;
}