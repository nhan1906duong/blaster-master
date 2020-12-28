#include "SophiaStraightFallingState.h"


#include "Player.h"
#include "SophiaFallingState.h"

#include "Utils.h"

SophiaStraightFallingState::SophiaStraightFallingState(PlayerData* data) : SophiaStraightState(data)
{
	acceleratorX = 0.01f;
	isLeftOrRightPressed = false;
	DebugOut(L"SophiaStraightFallingState\n");
}

int SophiaStraightFallingState::CurrentAnimationId()
{
	int ani;
	if (isLeftOrRightPressed)
	{
		ani = 27;
		if (data->player->IsUntouchable())
		{
			ani = 28;
		}
	}
	else
	{
		ani = 25;
		if (data->player->IsUntouchable())
		{
			ani = 26;
		}
	}
	return ani;
}

void SophiaStraightFallingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - 34;
}

void SophiaStraightFallingState::KeyState(BYTE* states)
{

	if (IsKeyDown(states, DIK_LEFT))
	{
		isLeftOrRightPressed = true;
		data->player->SetNx(-1);
		if (data->player->GetVx() > 0)
		{
			data->player->SetVx(-acceleratorX);
		}
		else
		{
			data->player->AddVx(-acceleratorX);
			if (data->player->GetVx() < -MAX_VX)
			{
				data->player->SetVx(-MAX_VX);
			}
		}
	}
	else if (IsKeyDown(states, DIK_RIGHT))
	{
		isLeftOrRightPressed = true;
		data->player->SetNx(1);
		if (data->player->GetVx() < 0)
		{
			data->player->SetVx(acceleratorX);
		}
		else
		{
			data->player->AddVx(acceleratorX);
			if (data->player->GetVx() > MAX_VX)
			{
				data->player->SetVx(MAX_VX);
			}
		}
	}
	else
	{
		isLeftOrRightPressed = false;
	}
}

void SophiaStraightFallingState::OnKeyDown(int keyCode)
{

}

void SophiaStraightFallingState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			data->player->SetState(new SophiaFallingState(data));
			break;
	}
}