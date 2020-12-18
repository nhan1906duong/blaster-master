#pragma once
#include "PlayerState.h"

#define SOPHIA_DEFAULT_WIDTH	26
#define SOPHIA_DEFAULT_HEIGHT	18

#define SOPHIA_FALLING_HEIGHT	16

#define MAX_VX 0.3f

class SophiaState : public PlayerState
{
protected:
	SophiaState(PlayerData* data) : PlayerState(data) {};
};