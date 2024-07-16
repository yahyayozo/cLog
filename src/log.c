
#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "stdbool.h"

#ifdef ENABLE_LOGGING

struct
{
    Log_PrintFunc LogPrintCallback;
    Log_Level LogLevelThreshold;
    bool IsLogEnabled;
    bool IsInitialized;
} Log_ConfigData;

Log_Status LOG_INIT(Log_PrintFunc printCallback, Log_Level logLevelThreshold)
{
    if (!IS_LOG_LEVEL(logLevelThreshold))
        return LOG_STATUS_INCORRECT_LEVEL;

    memset(&Log_ConfigData, 0, sizeof(Log_ConfigData));
    Log_ConfigData.LogPrintCallback = printCallback;
    Log_ConfigData.IsLogEnabled = true;
    Log_ConfigData.IsInitialized = true;
    Log_ConfigData.LogLevelThreshold = logLevelThreshold;

    return LOG_STATUS_OK;
}

Log_Status LOG_PRINT(Log_Level logLevel, char *format, ...)
{

    if (!Log_ConfigData.IsInitialized)
        return LOG_STATUS_NOT_INITIALIZED;

    if (!Log_ConfigData.IsLogEnabled)
        return LOG_STATUS_DISABLED;

    if (!IS_LOG_LEVEL(logLevel))
        return LOG_STATUS_INCORRECT_LEVEL;

    if (logLevel < Log_ConfigData.LogLevelThreshold)
        return LOG_STATUS_LEVEL_UNDER_THRESHOLD;

    static char printMsg[50];
    memset(printMsg, 0, sizeof(printMsg));

    uint8_t writeIndex = snprintf(printMsg, sizeof(printMsg), "[ %s ] ", LOG_LEVEL_TO_STRING(logLevel));
    va_list args;
    va_start(args, format);
    vsprintf(&printMsg[writeIndex], format, args);
    va_end(args);

    Log_ConfigData.LogPrintCallback(printMsg, strlen(printMsg));

    return LOG_STATUS_OK;
}

Log_Status LOG_SET_LEVEL_THRESHOLD(Log_Level LogLevelThreshold)
{
    if (!Log_ConfigData.IsInitialized)
        return LOG_STATUS_NOT_INITIALIZED;

    Log_ConfigData.LogLevelThreshold = LogLevelThreshold;
}

Log_Level LOG_GET_LEVEL_THRESHOLD()
{
    return Log_ConfigData.LogLevelThreshold;
}

Log_Status LOG_SET_PRINT_CALLBACK(Log_PrintFunc printCallback)
{
    Log_ConfigData.LogPrintCallback = printCallback;
    return LOG_STATUS_OK;
}

char *LOG_LEVEL_TO_STRING(Log_Level logLevel)
{
    switch (logLevel)
    {
    case LOG_LEVEL_INFO:
        return "INFO";
    case LOG_LEVEL_ERROR:
        return "ERROR";
    case LOG_LEVEL_WARNING:
        return "WARNING";
    case LOG_LEVEL_CRITICAL:
        return "CRITICAL";
    default:
        break;
    }
}

Log_Status LOG_ENABLE()
{
    if (!Log_ConfigData.IsInitialized)
        return LOG_STATUS_NOT_INITIALIZED;

    Log_ConfigData.IsLogEnabled = true;
    return LOG_STATUS_OK;
}

Log_Status LOG_DISABLE()
{
    if (!Log_ConfigData.IsInitialized)
        return LOG_STATUS_NOT_INITIALIZED;

    Log_ConfigData.IsLogEnabled = false;
    return LOG_STATUS_OK;
}

#endif /* ENABLE_LOGGING */