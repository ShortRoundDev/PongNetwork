#pragma once

#include "Types.h"
#include "Vec2.h"

struct PosMessage;
typedef struct PosMessage PosMessage_t;

struct Entity;
typedef struct Entity Entity_t;

typedef void (*EntityUpdate)(Entity_t*);
typedef void (*EntityDraw)(Entity_t*);

typedef void (*EntityPosUpdate)(Entity_t*, Vec2_t);
typedef void (*EntitySerialize)(Entity_t*, PosMessage_t* data);

struct Entity {
    Vec2_t pos;
    Vec2_t bounds;
    Vec2_t move;
    float t;

    bool serialized;

    u8 type;

    EntityUpdate update;
    EntityDraw draw;
    EntityPosUpdate setPos;
    EntitySerialize serialize;
};

Entity_t* MakeEntity(Vec2_t pos, Vec2_t bounds, bool serialized, u8 type, EntityUpdate update, EntityDraw draw);

void DefaultSetPos(Entity_t* ent, Vec2_t pos);