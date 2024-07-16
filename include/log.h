
#ifndef LOG_H
#define LOG_H

#include "stdint.h"
#define ENABLE_LOGGING

#define IS_LOG_LEVEL(x) (x > LOG_LEVEL_INFO && x < LOG_LEVEL_CRITICAL)

typedef void (*Log_PrintFunc)(char *data, uint32_t dataLength);

typedef enum
{
    LOG_STATUS_OK,
    LOG_STATUS_NOT_INITIALIZED,
    LOG_STATUS_DISABLED,
    LOG_STATUS_INCORRECT_LEVEL,
    LOG_STATUS_LEVEL_UNDER_THRESHOLD,
} Log_Status;

typedef enum
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_CRITICAL,
} Log_Level;

#ifdef ENABLE_LOGGING
Log_Status LOG_INIT(Log_PrintFunc printCallback, Log_Level logLevelThreshold);
Log_Status LOG_PRINT(Log_Level logLevelThreshold, char *format, ...);
Log_Status LOG_SET_LEVEL_THRESHOLD(Log_Level LogLevelThreshold);
Log_Level LOG_GET_LEVEL_THRESHOLD();
Log_Status LOG_SET_PRINT_CALLBACK(Log_PrintFunc printCallback);
char *LOG_LEVEL_TO_STRING(Log_Level logLevel);
Log_Status LOG_ENABLE();
Log_Status LOG_DISABLE();
#else
#define LOG_INIT(a, b) LOG_STATUS_DISABLED
#define LOG_PRINT(a, b) LOG_STATUS_DISABLED
#define LOG_SET_LEVEL_THRESHOLD(a) LOG_STATUS_DISABLED
#define LOG_GET_LEVEL_THRESHOLD() LOG_STATUS_DISABLED
#define LOG_SET_PRINT_CALLBACK(a) LOG_STATUS_DISABLED
#define LOG_LEVEL_TO_STRING(a) LOG_STATUS_DISABLED
#define LOG_ENABLE() LOG_STATUS_DISABLED
#define LOG_DISABLE() LOG_STATUS_DISABLED
#endif

#endif