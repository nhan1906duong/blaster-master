#pragma once
#include "PlayerState.h"

#define SOPHIA_DEFAULT_WIDTH	26
#define SOPHIA_DEFAULT_HEIGHT	18

#define SOPHIA_FALLING_HEIGHT	16

#define SOPHIA_JUMPING_HEIGHT	21

#define SOPHIA_UP_WIDTH		25
#define SOPHIA_UP_HEIGHT	26

#define MAX_SOPHIA_VX		0.07f
#define MAX_SOPHIA_VY		0.15f
#define MAX_HOLD_VY 0.18f

class SophiaState : public PlayerState
{
protected:
	SophiaState(PlayerData* data) : PlayerState(data) {};
};