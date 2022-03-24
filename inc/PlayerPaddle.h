#pragma once

#include "Entity.h"

#define TYPE_PLAYER (0)

void PlayerUpdate(Entity_t* ent);
void PlayerDraw(Entity_t* ent);

Entity_t* MakePlayer(Vec2_t pos);
void PlayerSerialize(Entity_t* ent, PosMessage_t* message);