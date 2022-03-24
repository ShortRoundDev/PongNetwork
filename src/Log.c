#include "Log.h"

#include "Colors.h"

#include <stdlib.h>

Logger_t* LoggerInstance = null;

bool InitLogging(char* fileName){
    LoggerInstance = malloc(sizeof(Logger_t));
    LoggerInstance->info = LogInfo;
    LoggerInstance->err = LogErr;
    LoggerInstance->warn = LogWarn;

    if(fileName == null){
        LoggerInstance->fpInfo = stdout;
        LoggerInstance->fpErr = stderr;
        LoggerInstance->fpWarn = stdout;
    } else {
        FILE* fp = fopen(fileName, "a");
        LoggerInstance->fpInfo = fp;
        LoggerInstance->fpErr = fp;
        LoggerInstance->fpWarn = fp;
    }
    return true;
}

void LogErr(char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogPrint(LOG->fpErr, RED, fmt, args);
}

void LogInfo(char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogPrint(LOG->fpInfo, WHT, fmt, args);
}
void LogWarn(char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogPrint(LOG->fpWarn, YEL, fmt, args);
}

void LogPrint(FILE* fp, char* color, char* fmt, va_list args){
    fprintf(fp, color);
    vfprintf(fp, fmt, args);
    fprintf(fp, "\n"COLOR_RESET);
    fflush(fp);
}
