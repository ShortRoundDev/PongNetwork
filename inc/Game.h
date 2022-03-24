#pragma once

#include "Types.h"
#include "Entity.h"

#define GAME (GameInstance)

typedef enum GameState{
    SERVER_WAITING,
    CLIENT_NO_CONNECTION,

    SERVER_PLAYING,
    CLIENT_PLAYING
} GameState_t;

typedef struct Game {
    Entity_t** entities;
    int totalEntities;

    Entity_t* remotePlayer;
    Entity_t* ball;

    GameState_t state;
} Game_t;

extern Game_t* GameInstance;

bool InitGame();
bool InitText();

void AddEntity(Entity_t* entity);
void DeleteEntity(Entity_t* entity);

void UpdateGame();
void DrawGame();

// Game draw states
void DrawGamePlaying();

void DrawServerWaiting();
void DrawClientWaiting();