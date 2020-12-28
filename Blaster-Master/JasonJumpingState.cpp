#include "JasonJumpingState.h"

#include "JasonFallingState.h"
#include "Player.h"
#include "Utils.h"

JasonJumpingState::JasonJumpingState(PlayerData* data): JasonState(data)
{
	acceleratorX = 0.01f;
	data->player->SetVy(0.01f);
	DebugOut(L"JasonJumpingState\n");
}

int JasonJumpingState::CurrentAnimationId()
{
	return 2;
}

void JasonJumpingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_STANDING_WIDTH;
	bottom = top - JASON_STANDING_HEIGHT;
}

void JasonJumpingState::KeyState(BYTE* states)
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

void JasonJumpingState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (data->player->SwitchToSophia())
	{
		return;
	}
	data->player->AddVy(0.018);
	if (data->player->GetVy() > 0.2)
	{
		data->player->SetVy(0.2);
		data->player->SetState(new JasonFallingState(data));
	}
}