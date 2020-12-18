#include "SophiaJumpingState.h"


#include "SophiaFallingState.h"
#include "Player.h"

SophiaJumpingState::SophiaJumpingState(PlayerData* data) : SophiaState(data)
{
	acceleratorX = 0.01f;
	data->player->SetVy(0.7f);
}

int SophiaJumpingState::CurrentAnimationId()
{
	return 5;
}

void SophiaJumpingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - SOPHIA_DEFAULT_HEIGHT;
}

void SophiaJumpingState::KeyState(BYTE* states)
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
}

void SophiaJumpingState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	data->player->AddVy(0.03);
	if (data->player->GetVy() > 0.2)
	{
		data->player->SetVy(0.2);
		data->player->SetState(new SophiaFallingState(data));
	}
}