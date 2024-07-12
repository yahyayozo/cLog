
#ifndef LOG_H
#define LOG_H

#include "stdint.h"
#define ENABLE_LOGGING

typedef void (*Log_PrintFunc)(char *data, uint32_t dataLength);

typedef enum
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_CRITICAL,
} Log_Level;

#ifdef ENABLE_LOGGING
void LOG_INIT(Log_PrintFunc printCallback, Log_Level logLevelThreshold);
void LOG_PRINT(Log_Level logLevelThreshold, char *format, ...);
void LOG_SET_LEVEL_THRESHOLD(Log_Level LogLevelThreshold);
void LOG_SET_PRINT_CALLBACK(Log_PrintFunc printCallback);
char *LOG_LEVEL_TO_STRING(Log_Level logLevel);
#else
#define LOG_INIT(a,b)
#define LOG_PRINT(a,b)  do{} while(0)
#define LOG_SET_LEVEL_THRESHOLD(a)
#define LOG_SET_PRINT_CALLBACK(a)
#define LOG_LEVEL_TO_STRING(a)
#endif

#endif