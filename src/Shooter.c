#include <stdio.h>
#include <sys/time.h>

#include <SDL2/SDL.h>

#include "System.h"
#include "Graphics.h"
#include "Server.h"
#include "Input.h"
#include "Log.h"
#include "Game.h"

u64 timer;
u64 accumulator;
#define CLIENT_TICK_RATE (16666)

int Init(int argc, char** argv);
void Run();

int main(int argc, char** argv){
    timer = GetTime();
    int status = 0;
    if((status = Init(argc, argv))){
        return status;
    }
    Run();
}

int Init(int argc, char** argv){
    if(!InitSystem(argc, argv)){
        return 1;
    }
    if(!InitLogging(SYS->logFile)){
        return 2;
    }
    if(!InitGraphics(800, 600)){
        return 3;
    }
    InitInput();
    if(!InitGame()){
        return 4;
    }
    if(SYS->isServer){
        if(!CreateServer()){
            return 5;
        }
    }else if(!ConnectServer(SYS->serverAddr, SYS->serverPort)){
        return 6;
    }
    return 0;
}

void Run(){
    while(!UpdateInput()){
        u64 now = GetTime();
        u64 frametime = now - timer;

        if(frametime > 250000){
            frametime = 250000;
        }
        
        accumulator += frametime;
        while(accumulator > CLIENT_TICK_RATE){
            accumulator -= CLIENT_TICK_RATE;
            UpdateGame();
            DrawGame();
        }
        timer = now;
    }
}
