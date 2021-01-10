#include "SophiaRunningState.h"

#include "SophiaStandingState.h"
#include "SophiaStraightRunningState.h"
#include "SophiaJumpingState.h"
#include "Player.h"
#include "Utils.h"

#include "Area2Scene.h"

SophiaRunningState::SophiaRunningState(PlayerData* data) : SophiaState(data)
{
	DebugOut(L"SophaRunningState\n");
	acceleratorX = 0.02f;
}

int SophiaRunningState::CurrentAnimationId()
{
	int ani = 11;
	if (data->player->IsUntouchable())
	{
		ani = 12;
	}
	return ani;
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
			if (data->player->GetVx() < -MAX_SOPHIA_VX)
			{
				data->player->SetVx(-MAX_SOPHIA_VX);
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
			if (data->player->GetVx() > MAX_SOPHIA_VX)
			{
				data->player->SetVx(MAX_SOPHIA_VX);
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
		case DIK_UP:
		{
			if (!((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->CanAddPosition(16.2f))
			{
				break;
			}
			data->player->AddPosition(0, 16.1f);
			data->player->SetState(new SophiaStraightRunningState(data));
			break;
		}
		case DIK_X:
		{
			if (!((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->CanAddPosition(3.2f))
			{
				break;
			}
			data->player->AddPosition(0, 3.1f);
			data->player->SetState(new SophiaJumpingState(data));
			break;
		}
	}
}