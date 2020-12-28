#include "SophiaFallingState.h"

#include "Player.h"
#include "SophiaStraightFallingState.h"

#include "Utils.h"
#include "Area2Scene.h"

SophiaFallingState::SophiaFallingState(PlayerData* data) : SophiaState(data)
{
	acceleratorX = 0.01f;
	isLeftOrRightPressed = false;
	DebugOut(L"SophiaFallingState\n");
}

int SophiaFallingState::CurrentAnimationId()
{
	int ani;
	if (isLeftOrRightPressed)
	{
		ani = 19;
		if (data->player->IsUntouchable())
		{
			ani = 20;
		}
	}
	else
	{
		ani = 17;
		if (data->player->IsUntouchable())
		{
			ani = 18;
		}
	}
	return ani;
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
	switch (keyCode)
	{
		case DIK_UP:
		{
			if (!((CArea2Scene*)CGame::GetInstance()->GetCurrentScene())->CanAddPosition(-18.1))
			{
				break;
			}
			data->player->SetState(new SophiaStraightFallingState(data));
			break;
		}

	}
}