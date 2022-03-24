#include "PlayerPaddle.h"

#include "RemotePaddle.h"

#include "Graphics.h"
#include "Server.h"
#include "Input.h"

void PlayerUpdate(Entity_t* ent){
    if(KeyDown(SDL_SCANCODE_UP)){
        ent->pos.y -= 5;
    }
    if(KeyDown(SDL_SCANCODE_DOWN)){
        ent->pos.y += 5;
    }

    if(ent->pos.y < 0){
        ent->pos.y = 0;
    }
    if(ent->pos.y + ent->bounds.y > GRAPHICS->height){
        ent->pos.y = GRAPHICS->height - ent->bounds.y;
    }

}

void PlayerDraw(Entity_t* ent){
    SDL_SetRenderDrawColor(
        GRAPHICS->renderer,
        0xff, 0xff, 0xff, 0xff
    );

    SDL_FRect dst = {
        .x = ent->pos.x,
        .y = ent->pos.y,
        .w = ent->bounds.x,
        .h = ent->bounds.y
    };

    SDL_RenderFillRectF(GRAPHICS->renderer, &dst);
}

Entity_t* MakePlayer(Vec2_t pos){
    Entity_t* ent = MakeEntity(
        pos,
        (Vec2_t){ 16, 64 },
        true,
        TYPE_PLAYER,
        PlayerUpdate,
        PlayerDraw
    );
    ent->serialize = PlayerSerialize;
    return ent;
}

void PlayerSerialize(Entity_t* ent, PosMessage_t* message){
    message->type = TYPE_REMOTE;
    message->pos = ent->pos;
}