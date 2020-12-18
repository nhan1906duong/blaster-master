#include "JasonFallingState.h"
#include "Player.h"

#include "Utils.h"

JasonFallingState::JasonFallingState(PlayerData* data) : JasonState(data)
{
	acceleratorX = 0.01f;
	isLeftOrRightPressed = false;
	DebugOut(L"JasonFallingState\n");
}

int JasonFallingState::CurrentAnimationId()
{
	return 2;
}

void JasonFallingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_STANDING_WIDTH;
	bottom = top - JASON_STANDING_HEIGHT;
}

void JasonFallingState::KeyState(BYTE* states)
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

void JasonFallingState::OnKeyDown(int keyCode)
{

}