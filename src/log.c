
#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"

#ifdef ENABLE_LOGGING

struct
{
    Log_PrintFunc LogPrintCallback;
    Log_Level LogLevelThreshold;
} Log_ConfigData;

void LOG_INIT(Log_PrintFunc printCallback, Log_Level logLevelThreshold)
{

    Log_ConfigData.LogPrintCallback = printCallback;
    Log_ConfigData.LogLevelThreshold = logLevelThreshold;
}

void LOG_PRINT(Log_Level logLevel, char *format, ...)
{
    static char printMsg[50];
    memset(printMsg, 0, sizeof(printMsg));

    if (logLevel < Log_ConfigData.LogLevelThreshold)
        return;
    uint8_t writeIndex = snprintf(printMsg, sizeof(printMsg), "[ %s ] ", LOG_LEVEL_TO_STRING(logLevel));
    va_list args;
    va_start(args, format);
    vsprintf(&printMsg[writeIndex], format, args);
    va_end(args);

    Log_ConfigData.LogPrintCallback(printMsg, strlen(printMsg));
}

void LOG_SET_LEVEL_THRESHOLD(Log_Level LogLevelThreshold)
{
    Log_ConfigData.LogLevelThreshold = LogLevelThreshold;
}

void LOG_SET_PRINT_CALLBACK(Log_PrintFunc printCallback)
{
    Log_ConfigData.LogPrintCallback = printCallback;
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

#endif /* ENABLE_LOGGING */