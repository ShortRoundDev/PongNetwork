#include "System.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

System_t* SystemInstance = null;

bool InitSystem(int argc, char** argv){
    SystemInstance = malloc(sizeof(System_t));
    SystemInstance->argc = argc;
    SystemInstance->argv = argv;

    SystemInstance->isServer = !HasArg("-client");
    if(!SystemInstance->isServer){
        SystemInstance->serverAddr = GetArg("-address");
        if(SystemInstance->serverAddr == null){
            printf("No server address provided!");
            return false;
        }
    }
    char* portName = GetArg("port");
    if(portName == null){
        SystemInstance->serverPort = 2000;
    } else {
        SystemInstance->serverPort = atoi(portName);
    }

    SystemInstance->logFile = GetArg("-logFile");

    return true;
}

bool HasArg(char* argName){
    for(int i = 0; i < SYS->argc; i++){
        if(!strcmp(argName, SYS->argv[i])){
            return true;
        }
    }
    return false;
}

char* GetArg(char* argName){
    for(int i = 0; i < SYS->argc; i++){
        if(!strncmp(argName, SYS->argv[i], strlen(argName))){
            return SYS->argv[i] + strlen(argName) + 1; // argName=value
        }
    }
    return null;
}