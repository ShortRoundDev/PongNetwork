#include "Ball.h"

#include "Log.h"
#include "Game.h"
#include "Server.h"
#include "Graphics.h"

void BallUpdate(Entity_t* ent){
    ent->pos = AddVec(ent->pos, ent->move);
    if(ent->pos.x > GRAPHICS->width || ent->pos.x < 0){
        ent->move.x *= -1;
    }
    if(ent->pos.y > GRAPHICS->height || ent->pos.y < 0){
        ent->move.y *= -1;
    }

    for(int i = 0; i < GAME->totalEntities; i++){
        Entity_t* other = GAME->entities[i];
        if(other == ent){
            continue;
        }

        SDL_Rect a = {
            .x = (int)ent->pos.x + ent->move.x,
            .y = (int)ent->pos.y + ent->move.y,
            .w = (int)ent->bounds.x,
            .h = (int)ent->bounds.y
        };

        SDL_Rect b = {
            .x = (int)other->pos.x,
            .y = (int)other->pos.y,
            .w = (int)other->bounds.x,
            .h = (int)other->bounds.y
        };

        if(SDL_HasIntersection(&a, &b)){
            ent->move.x *= -1;
            LOG->info("Bounce");
            break;
        }
    }
}

void BallDraw(Entity_t* ent){
    SDL_Renderer* renderer = GRAPHICS->renderer;
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_FRect dst = {
        ent->pos.x, ent->pos.y,
        ent->bounds.x, ent->bounds.y
    };
    SDL_RenderFillRectF(renderer, &dst);
}

Entity_t* MakeBall(){
    Entity_t* ent = MakeEntity(
        (Vec2_t){ .x = GRAPHICS->width/2, .y = GRAPHICS->height/2 },
        (Vec2_t){ .x = 16, .y = 16 },
        true,
        TYPE_BALL,
        BallUpdate,
        BallDraw
    );
    ent->move =  (Vec2_t){ .x = 2, .y = 2 };
    ent->serialize = BallSerialize;
    return ent;
}

void BallSerialize(Entity_t* ent, PosMessage_t* message){
    message->type = TYPE_BALL;
    message->pos = ent->pos;
}