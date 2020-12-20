#include "SophiaStraightJumpingState.h"

#include "SophiaStraightFallingState.h"
#include "SophiaJumpingState.h"
#include "Player.h"

#include "Utils.h"

SophiaStraightJumpingState::SophiaStraightJumpingState(PlayerData* data, bool reset) : SophiaStraightState(data)
{
	DebugOut(L"SophiaStraightJumpingState\n");
	acceleratorX = 0.01f;
	if (reset)
	{
		data->player->SetVy(0.01f);
	}
	acceleratorY = 0.015f;
	isHoldJump = false;
}

int SophiaStraightJumpingState::CurrentAnimationId()
{
	return 16;
}

void SophiaStraightJumpingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - 34;
}

void SophiaStraightJumpingState::KeyState(BYTE* states)
{

	if (IsKeyDown(states, DIK_LEFT))
	{
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
	if (IsKeyDown(states, DIK_X))
	{
		isHoldJump = true;
	}
	else
	{
		isHoldJump = false;
	}
}

void SophiaStraightJumpingState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		data->player->SetState(new SophiaStraightFallingState(data));
	}
}

void SophiaStraightJumpingState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		data->player->SetState(new SophiaJumpingState(data, false));
		break;
	}
}