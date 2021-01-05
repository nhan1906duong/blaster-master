#pragma once
#include "PlayerState.h"
#include "Player.h"

#define MAX_V	0.1f
#define ACCLERATOR	0.02f

#define WIDTH	24
#define HEIGHT	32

class JasonOverworldState: public PlayerState
{
public:
	JasonOverworldState(PlayerData* data) : PlayerState(data) 
	{
		data->player->SetVx(0.0f);
		data->player->SetVy(0.0f);
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		data->player->GetPosition(left, top);
		right = left + WIDTH;
		bottom = top - 32;
		top = bottom + 8;
	}
};

