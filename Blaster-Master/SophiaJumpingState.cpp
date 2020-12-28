#include "SophiaJumpingState.h"

#include "SophiaStraightJumpingState.h"
#include "SophiaFallingState.h"
#include "Player.h"
#include "Utils.h"

#include "Area2Scene.h"

SophiaJumpingState::SophiaJumpingState(PlayerData* data, bool reset) : SophiaState(data)
{
	DebugOut(L"SophiaJumpingState\n");
	acceleratorX = 0.01f;
	if (reset)
	{
		data->player->SetVy(0.01f);
	}
	acceleratorY = 0.015f;
	isHoldJump = isLeftOrRightPressed = false;
}

int SophiaJumpingState::CurrentAnimationId()
{
	int ani;
	if (isLeftOrRightPressed)
	{
		ani = 15;
		if (data->player->IsUntouchable())
		{
			ani = 16;
		}
	}
	else
	{
		ani = 13;
		if (data->player->IsUntouchable())
		{
			ani = 14;
		}
	}
	return ani;
}

void SophiaJumpingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - SOPHIA_JUMPING_HEIGHT;
}

void SophiaJumpingState::KeyState(BYTE* states)
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
	if (IsKeyDown(states, DIK_X))
	{
		isHoldJump = true;
	}
	else
	{
		isHoldJump = false;
	}
}

void SophiaJumpingState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float max_vy;
	if (isHoldJump)
	{
		max_vy = MAX_HOLD_VY;
	}
	else
	{
		max_vy = MAX_VY;
	}
	data->player->AddVy(acceleratorY);
	if (data->player->GetVy() > max_vy)
	{
		data->player->SetVy(max_vy);
		data->player->SetState(new SophiaFallingState(data));
	}
}

void SophiaJumpingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
		{
			if (!((CArea2Scene*) CGame::GetInstance()->GetCurrentScene())->CanAddPosition(16.1))
			{
				break;
			}
			data->player->AddPosition(0, 16);
			data->player->SetState(new SophiaStraightJumpingState(data, false));
			break;
		}
	}
}