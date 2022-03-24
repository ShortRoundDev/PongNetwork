#include "RemoteBall.h"

#include "Log.h"
#include "Graphics.h"

void RemoteBallUpdate(Entity_t* ent){
}

void RemoteBallDraw(Entity_t* ent){
    Vec2_t diff = (Vec2_t){
        .x = ent->pos.x - ent->move.x,
        .y = ent->pos.y - ent->move.y
    };

    Vec2_t interpolated = (Vec2_t){
        .x = ent->pos.x + (diff.x * ent->t),
        .y = ent->pos.y + (diff.y * ent->t),
    };

    SDL_Renderer* renderer = GRAPHICS->renderer;
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_FRect dst = {
        interpolated.x, interpolated.y,
        ent->bounds.x, ent->bounds.y
    };
    SDL_RenderFillRectF(renderer, &dst);
    ent->t += (1.0f/6.0f);
}

Entity_t* MakeRemoteBall(){
    Entity_t* ent = MakeEntity(
        (Vec2_t){ .x = GRAPHICS->width/2, .y = GRAPHICS->height/2 },
        (Vec2_t){ .x = 16, .y = 16 },
        false,
        TYPE_BALL,
        RemoteBallUpdate,
        RemoteBallDraw
    );
    ent->setPos = SetRemoteBallPos;

    return ent;
}

void SetRemoteBallPos(Entity_t* ent, Vec2_t pos){
    ent->move = ent->pos;
    ent->pos = pos;
    ent->t = 0.0f;
}