#include "BaseShell.h"

BOOL baseShell(const char* cmd, char* result, size_t resultSize) {
    CHAR psCommand[2048];
    snprintf(psCommand, sizeof(psCommand), "powershell -NoProfile -WindowStyle Hidden -Command \"%s\"", cmd);

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    HANDLE hStdOutRead, hStdOutWrite;
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
    {
        return FALSE;
    }
    if (!SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0))
    {
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        return FALSE;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = hStdOutWrite;
    si.hStdOutput = hStdOutWrite;
    si.dwFlags |= STARTF_USESTDHANDLES;

    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(
            NULL,                     // Application name
            psCommand,                // Command line
            NULL,                     // Process handle not inheritable
            NULL,                     // Thread handle not inheritable
            TRUE,                     // Set handle inheritance to TRUE for pipe
            CREATE_NO_WINDOW,         // Suppress console window
            NULL,                     // Use parent's environment block
            currentDirectory.c_str(), // Set current working directory
            &si,                      // Pointer to STARTUPINFO structure
            &pi))                     // Pointer to PROCESS_INFORMATION structure
    {
        CloseHandle(hStdOutWrite);
        CloseHandle(hStdOutRead);
        return FALSE;
    }
    CloseHandle(hStdOutWrite); // Close the write end of the pipe now that the process has started
    // Replace strncat and strlen with CustomStrCat and CustomStrLen
    CHAR buffer[4096];
    DWORD bytesRead;
    while (ReadFile(hStdOutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        CustomStrCat(result, buffer, resultSize);
    }
    CloseHandle(hStdOutRead);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return TRUE;
}