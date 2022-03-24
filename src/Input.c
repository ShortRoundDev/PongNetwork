#include "Input.h"

Input_t* InputInstance = null;

void InitInput(){
    InputInstance = malloc(sizeof(Input_t));
    memset(InputInstance->keys, 0, sizeof(InputInstance->keys));
}

bool UpdateInput(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch(e.type){
        case SDL_KEYDOWN: {
            SDL_Scancode code = e.key.keysym.scancode;
            if(code >= 0 && code <= SDL_NUM_SCANCODES){

                KEYS[e.key.keysym.scancode] = true;
            }
            break;
        }
        case SDL_KEYUP: {
            SDL_Scancode code = e.key.keysym.scancode;
            if(code >= 0 && code < SDL_NUM_SCANCODES){
                KEYS[e.key.keysym.scancode] = false;
            }
            break;
        }
        case SDL_QUIT:{
            return true;
        }
        }
    }
    return false;
}

bool KeyDown(SDL_Scancode scancode){
    if(scancode >= 0 && scancode < SDL_NUM_SCANCODES){
        return KEYS[scancode];
    }
    return false;
}

bool KeyUp(SDL_Scancode scancode){
    return !KeyDown(scancode);
}
