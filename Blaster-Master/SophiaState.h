#pragma once
#include "PlayerState.h"

class SophiaState : public PlayerState
{
protected:
	SophiaState(PlayerData* data) : PlayerState(data) {};
};