#include "SophiaStraightRunningState.h"


#include "SophiaStraightStandingState.h"
#include "SophiaStraightJumpingState.h"
#include "SophiaRunningState.h"
#include "Player.h"
#include "Utils.h"


SophiaStraightRunningState::SophiaStraightRunningState(PlayerData* data) : SophiaStraightState(data)
{
	DebugOut(L"SophiaStraightRunningState\n");
	acceleratorX = 0.02f;
}

int SophiaStraightRunningState::CurrentAnimationId()
{
	return 16;
}

void SophiaStraightRunningState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - 34;
}

void SophiaStraightRunningState::KeyState(BYTE* states)
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
	else
	{
		data->player->SetState(new SophiaStraightStandingState(data));
	}
}

void SophiaStraightRunningState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_X:
		data->player->SetState(new SophiaStraightJumpingState(data));
		break;
	}
}


void SophiaStraightRunningState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			data->player->AddPosition(0, -16);
			data->player->SetState(new SophiaRunningState(data));
			break;
	}
}