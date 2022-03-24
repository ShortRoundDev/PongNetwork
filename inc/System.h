#pragma once

#include "Types.h"
#define SYS (SystemInstance)

typedef struct System {
    bool isServer;
    char* serverAddr;
    i32 serverPort;

    char* logFile;

    i32 argc;
    char** argv;
} System_t;
extern System_t* SystemInstance;

bool InitSystem(int argc, char** argv);

bool HasArg(char* argName);

char* GetArg(char* argName);