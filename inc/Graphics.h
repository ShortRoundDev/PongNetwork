#pragma once
#include <SDL2/SDL.h>
#include "Types.h"

#define GRAPHICS (GraphicsManagerInstance)

typedef struct GraphicsManager {
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    u16 width;
    u16 height;
} GraphicsManager_t;

extern GraphicsManager_t* GraphicsManagerInstance;

bool InitGraphics(u16 width, u16 height);