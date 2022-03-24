#include "Game.h"

#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Log.h"
#include "System.h"
#include "Graphics.h"
#include "PlayerPaddle.h"
#include "RemotePaddle.h"
#include "Ball.h"
#include "RemoteBall.h"

Game_t* GameInstance = null;

SDL_Rect waitingSize = { .x = 0, .y = 0, .w = 0, .h = 0 };
SDL_Texture* serverWaiting = null;

bool InitGame(){

    TTF_Init();

    GameInstance = malloc(sizeof(Game_t));
    GameInstance->totalEntities = 0;
    GameInstance->entities = malloc(sizeof(Entity_t*) * 6); // 6 by default, we probably only need 3

    if(SYS->isServer){
        // Player on left
        GameInstance->entities[GameInstance->totalEntities++] = MakePlayer(
            (Vec2_t){.x = 16, .y = GRAPHICS->height/2 - 32}
        );

        GameInstance->entities[GameInstance->totalEntities++] = MakeRemote(
            (Vec2_t){.x = GRAPHICS->width - 32, .y = GRAPHICS->height/2 - 32}
        );

        GameInstance->entities[GameInstance->totalEntities++] = MakeBall();
        GAME->state = SERVER_WAITING;

        InitText("Waiting for client...");
    } else {
        GameInstance->entities[GameInstance->totalEntities++] = MakeRemote(
            (Vec2_t){.x = 16, .y = GRAPHICS->height/2 - 32}
        );

        GameInstance->entities[GameInstance->totalEntities++] = MakePlayer(
            (Vec2_t){.x = GRAPHICS->width - 32, .y = GRAPHICS->height/2 - 32}
        );

        GameInstance->entities[GameInstance->totalEntities++] = MakeRemoteBall();
        GAME->state = CLIENT_NO_CONNECTION;
        InitText("Connecting to server...");
    }

    return true;
}

bool InitText(const char* text){
    TTF_Font* font = TTF_OpenFont("NotoSans-Bold.ttf", 48);
    if(!font){
        char buff[1024];
        SDL_GetErrorMsg(buff, sizeof(buff));
        LOG->err("Couldn't load font... %s", buff);
        return false;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text, (SDL_Color){ 0xff, 0xff, 0xff, 0xff });
    serverWaiting = SDL_CreateTextureFromSurface(GRAPHICS->renderer, surface);
    waitingSize = (SDL_Rect){
        .x = 0,
        .y = 0,
        .w = surface->w,
        .h = surface->h
    };
    return true;
}

void UpdateGame() {
    if(GAME->state == CLIENT_NO_CONNECTION || SERVER_WAITING)
        return;
    for(int i = 0; i < GAME->totalEntities; i++){
        Entity_t* ent = GAME->entities[i];
        ent->update(ent);
    }
}

void DrawGame() {
    SDL_SetRenderDrawColor(GRAPHICS->renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(GRAPHICS->renderer);
    switch(GAME->state){
        case SERVER_PLAYING:
        case CLIENT_PLAYING:
            DrawGamePlaying();
            break;
        case SERVER_WAITING:
        case CLIENT_NO_CONNECTION:
            DrawServerWaiting();
            break;
    }
    
    SDL_RenderPresent(GRAPHICS->renderer);
}

void DrawGamePlaying(){
    for(int i = 0; i < GAME->totalEntities; i++){
        Entity_t* ent = GAME->entities[i];
        ent->draw(ent);
    }
}

void DrawServerWaiting(){
    static float size = 0.0f;
    size += 0.01f;
    
    SDL_Point p = (SDL_Point){
        .x = waitingSize.w/2,
        .y = waitingSize.h/2
    };

    float sizeModifier = ((sin(size) + 2.0f)/2.0f);

    SDL_Rect dst = {
        GRAPHICS->width/2 - (waitingSize.w * sizeModifier) / 2,
        GRAPHICS->height/2 - (waitingSize.h * sizeModifier) / 2,
        (waitingSize.w * sizeModifier),
        (waitingSize.h * sizeModifier)
    };

    SDL_RenderCopyEx(GRAPHICS->renderer,
        serverWaiting,
        &waitingSize,
        &dst,
        cosf(size * 2.3f) * 15,
        &p,
        SDL_FLIP_NONE
    );
}

void DrawClientWaiting(){
    static float size = 0.0f;
    size += 0.01f;
    
    SDL_Point p = (SDL_Point){
        .x = waitingSize.w/2,
        .y = waitingSize.h/2
    };

    float sizeModifier = ((sin(size) + 2.0f)/2.0f);

    SDL_Rect dst = {
        GRAPHICS->width/2 - (waitingSize.w * sizeModifier) / 2,
        GRAPHICS->height/2 - (waitingSize.h * sizeModifier) / 2,
        (waitingSize.w * sizeModifier),
        (waitingSize.h * sizeModifier)
    };

    SDL_RenderCopyEx(GRAPHICS->renderer,
        serverWaiting,
        &waitingSize,
        &dst,
        cosf(size * 2.3f) * 15,
        &p,
        SDL_FLIP_NONE
    );
}