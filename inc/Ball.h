#pragma once

#include "Entity.h"

#ifndef TYPE_BALL
#define TYPE_BALL (2)
#endif

void BallUpdate(Entity_t* ent);
void BallDraw(Entity_t* ent);

Entity_t* MakeBall();
void BallSerialize(Entity_t* ent, PosMessage_t* message);