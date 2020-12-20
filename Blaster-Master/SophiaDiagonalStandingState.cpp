#include "SophiaDiagonalStandingState.h"

#include "SophiaJumpingState.h"
#include "SophiaRunningState.h"
#include "SophiaStandingState.h"
#include "SophiaStraightStandingState.h"

#include "Player.h"


SophiaDiagonalStandingState::SophiaDiagonalStandingState(PlayerData* data) : SophiaState(data)
{
	times = 0;
	data->player->SetVx(0);
}

int SophiaDiagonalStandingState::CurrentAnimationId()
{
	return 15;

}

void SophiaDiagonalStandingState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	times++;
}

void SophiaDiagonalStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - SOPHIA_DEFAULT_HEIGHT;
}

void SophiaDiagonalStandingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_X:
		data->player->SetState(new SophiaJumpingState(data));
		break;
	}
}

void SophiaDiagonalStandingState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			data->player->SetState(new SophiaStandingState(data));
			break;
	}
}

void SophiaDiagonalStandingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_LEFT))
	{
		data->player->SetNx(-1);
		data->player->SetState(new SophiaRunningState(data));
	}
	else if (IsKeyDown(states, DIK_RIGHT))
	{
		data->player->SetNx(1);
		data->player->SetState(new SophiaRunningState(data));
	}

	if (times == 8)
	{
		if (IsKeyDown(states, DIK_UP))
		{
			data->player->SetState(new SophiaStraightStandingState(data));
		}
		else
		{
			data->player->SetState(new SophiaStandingState(data));
		}
	}
}
