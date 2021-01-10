#pragma once
#include "PlayerState.h"

#define JASON_STAIR_WIDTH		10
#define JASON_STANDING_WIDTH	8
#define JASON_STANDING_HEIGHT	16

#define JASON_LIE_WIDTH			16
#define JASON_LIE_HEIGHT		8

#define MAX_JASON_VX 0.12f
#define MAX_CRAWLING_VX 0.07f

class JasonState : public PlayerState
{
protected:
	JasonState(PlayerData* data) : PlayerState(data)
	{

	}
};
