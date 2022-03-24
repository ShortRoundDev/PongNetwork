#pragma once

#include "Entity.h"
#include "PlayerPaddle.h"

#define TYPE_REMOTE (1)

void RemoteUpdate(Entity_t* ent);

Entity_t* MakeRemote(Vec2_t pos);

void RemotePaddleDraw();
void SetRemotePaddlePos(Entity_t* ent, Vec2_t pos);