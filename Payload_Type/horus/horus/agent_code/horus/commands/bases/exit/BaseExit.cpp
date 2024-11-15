#include "BaseExit.h"

BOOL baseExit()
{
    // Perform any necessary cleanup here

    // Terminate the process
    ExitProcess(0);
    return TRUE; // This line will never be reached
}