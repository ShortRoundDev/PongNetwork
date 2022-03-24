#pragma once

#include <SDL2/SDL.h>

#include "Types.h"

#define INPUT (InputInstance)

#define KEYS (INPUT->keys)

typedef struct Input {
    bool keys[SDL_NUM_SCANCODES];
} Input_t;

extern Input_t* InputInstance;

void InitInput();
bool UpdateInput();
bool KeyDown(SDL_Scancode scancode);
bool KeyUp(SDL_Scancode scancode);