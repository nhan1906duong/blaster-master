#include "SophiaRunningState.h"

#include "SophiaStandingState.h"
#include "SophiaJumpingState.h"
#include "Player.h"
#include "Utils.h"


SophiaRunningState::SophiaRunningState(PlayerData* data) : SophiaState(data)
{
	DebugOut(L"SophaRunningState\n");
	acceleratorX = 0.02f;
}

int SophiaRunningState::CurrentAnimationId()
{
	return 9;
}

void SophiaRunningState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - SOPHIA_DEFAULT_HEIGHT;
}

void SophiaRunningState::KeyState(BYTE* states)
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
		data->player->SetState(new SophiaStandingState(data));
	}
}

void SophiaRunningState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_X:
		data->player->SetState(new SophiaJumpingState(data));
		break;
	}
}