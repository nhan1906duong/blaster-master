#include "JasonRunningState.h"

#include "JasonStandingState.h"
#include "JasonJumpingState.h"
#include "Player.h"


JasonRunningState::JasonRunningState(PlayerData* data) : JasonState(data)
{
	acceleratorX = 0.02f;
}

int JasonRunningState::CurrentAnimationId()
{
	return 1;
}

void JasonRunningState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_STANDING_WIDTH;
	bottom = top - JASON_STANDING_HEIGHT;
}

void JasonRunningState::KeyState(BYTE* states)
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
		data->player->SetState(new JasonStandingState(data));
	}
}

void JasonRunningState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_X:
		data->player->SetState(new JasonJumpingState(data));
		break;
	}
}