#include "SophiaFallingState.h"

#include "Player.h"

#include "Utils.h"

SophiaFallingState::SophiaFallingState(PlayerData* data) : SophiaState(data)
{
	acceleratorX = 0.01f;
	isLeftOrRightPressed = false;
	DebugOut(L"SophiaFallingState\n");
}

int SophiaFallingState::CurrentAnimationId()
{
	return 12;
}

void SophiaFallingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - SOPHIA_FALLING_HEIGHT;
}

void SophiaFallingState::KeyState(BYTE* states)
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

void SophiaFallingState::OnKeyDown(int keyCode)
{

}