#include "RemotePaddle.h"

#define sign(a) ((a) > 0 ? 1 : ((a) == 0 ? 0 : -1))

#include "Log.h"
#include "Graphics.h"
#include "Game.h"

void RemoteUpdate(Entity_t* ent){
    // maybe have an event queue or something?
}

Entity_t* MakeRemote(Vec2_t pos){
    Entity_t* ent = MakeEntity(pos,
        (Vec2_t){ .x = 16, .y = 64 },
        false,
        TYPE_REMOTE,
        RemoteUpdate,
        RemotePaddleDraw
    );

    GAME->remotePlayer = ent;
    ent->setPos = SetRemotePaddlePos;

    return ent;
}

void SetRemotePaddlePos(Entity_t* ent, Vec2_t pos){
    ent->move = ent->pos;
    ent->pos = pos;

    ent->t = 0.0f;
}

void RemotePaddleDraw(Entity_t* ent){
    Vec2_t diff = (Vec2_t){
        .x = ent->pos.x - ent->move.x,
        .y = ent->pos.y - ent->move.y
    };

    Vec2_t interpolated = (Vec2_t){
        .x = ent->move.x + (diff.x * ent->t),
        .y = ent->move.y + (diff.y * ent->t),
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