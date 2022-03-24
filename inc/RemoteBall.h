#pragma once
#include "Entity.h"
#include "Ball.h"

#ifndef TYPE_BALL
#define TYPE_BALL (2)
#endif

void UpdateRemoteBall(Entity_t* ent);
void RemoteBallDraw(Entity_t* ent);
void SetRemoteBallPos(Entity_t* ent, Vec2_t pos);

Entity_t* MakeRemoteBall();