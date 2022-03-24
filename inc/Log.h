#pragma once

#include <stdio.h>
#include <stdarg.h>

#include "Types.h"

#define LOG (LoggerInstance)

typedef struct Logger {
    void (*err)(char*, ...);
    void (*info)(char*, ...);
    void (*warn)(char*, ...);

    FILE* fpInfo;
    FILE* fpErr;
    FILE* fpWarn;
} Logger_t;

extern Logger_t* LoggerInstance;

bool InitLogging(char* fileName);

void LogErr(char* fmt, ...);
void LogInfo(char* fmt, ...);
void LogWarn(char* fmt, ...);

void LogPrint(FILE* fp, char* color, char* fmt, va_list args);