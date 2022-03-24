#include <stdlib.h>
#include "Entity.h"

Entity_t* MakeEntity(
    Vec2_t pos,
    Vec2_t bounds,
    bool serialized,
    u8 type,
    EntityUpdate update,
    EntityDraw draw
)
{
    Entity_t* entity = malloc(sizeof(Entity_t));
    entity->pos = pos;
    entity->bounds = bounds;
    entity->serialized = serialized;
    entity->type = type;
    entity->update = update;
    entity->draw = draw;

    entity->setPos = DefaultSetPos;
    entity->serialize = NULL;

    return entity;
}

void DefaultSetPos(Entity_t* ent, Vec2_t pos){
    ent->pos = pos;
}

