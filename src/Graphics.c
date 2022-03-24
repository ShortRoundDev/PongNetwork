#include "Graphics.h"

GraphicsManager_t* GraphicsManagerInstance = null;

bool InitGraphics(u16 width, u16 height){
    SDL_Init(SDL_INIT_EVERYTHING);

    GraphicsManagerInstance = (GraphicsManager_t*)malloc(sizeof(GraphicsManager_t));
    GraphicsManagerInstance->width = width;
    GraphicsManagerInstance->height = height;

    SDL_CreateWindowAndRenderer(
        width,
        height,
        SDL_WINDOW_SHOWN,
        &GraphicsManagerInstance->window,
        &GraphicsManagerInstance->renderer
    );

    return true;
}