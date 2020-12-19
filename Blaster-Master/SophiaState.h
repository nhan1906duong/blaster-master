#pragma once
#include "PlayerState.h"

#define SOPHIA_DEFAULT_WIDTH	26
#define SOPHIA_DEFAULT_HEIGHT	18

#define SOPHIA_FALLING_HEIGHT	16

#define MAX_VX		0.1f
#define MAX_VY		0.15f
#define MAX_HOLD_VY 0.2f

class SophiaState : public PlayerState
{
protected:
	SophiaState(PlayerData* data) : PlayerState(data) {};
};