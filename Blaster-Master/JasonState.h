#pragma once
#include "PlayerState.h"

#define JASON_STANDING_WIDTH	8
#define JASON_STANDING_HEIGHT	16

class JasonState : public PlayerState
{
protected:
	JasonState(PlayerData* data) : PlayerState(data)
	{

	}
};
