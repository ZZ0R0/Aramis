#pragma once
#ifndef HORUS_H
#define HORUS_H

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601 // Windows 7
#endif // _WIN32_WINNT

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

} CONFIG_HORUS, *PCONFIG_HORUS;

extern PCONFIG_HORUS horusConfig;

VOID setUUID(PCHAR newUUID);
VOID horusMain();

#endif // HORUS_H
