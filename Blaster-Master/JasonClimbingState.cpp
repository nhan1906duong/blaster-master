#include "JasonClimbingState.h"

#include "Player.h"
#include "Utils.h"

#include "JasonFallingState.h"

JasonClimbingState::JasonClimbingState(PlayerData* data, float l, float t, float r, float b, float jumpPoint) : JasonState(data)
{
	this->l = l;
	this->t = t;
	this->r = r;
	this->b = b;
	this->jumpPoint = jumpPoint;

	data->player->SetPosition((l + r) / 2 - JASON_STAIR_WIDTH / 2, b + 0.1 + JASON_STANDING_HEIGHT);
	data->player->SetVx(0);
	DebugOut(L"JasonClimbingState\n");
	acceleratorY = 0.02f;
}

int JasonClimbingState::CurrentAnimationId()
{
	int ani = 5;
	if (data->player->GetVy() == 0)
	{
		ani = 31;
	}
	return ani;
}

void JasonClimbingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_STAIR_WIDTH;
	bottom = top - JASON_STANDING_HEIGHT;
}

void JasonClimbingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_DOWN))
	{
		if (data->player->GetVy() > 0)
		{
			data->player->SetVy(-acceleratorY);
		}
		else
		{
			data->player->AddVy(-acceleratorY);
			if (data->player->GetVy() < -MAX_VX)
			{
				data->player->SetVy(-MAX_VX);
			}
		}
	}
	else if (IsKeyDown(states, DIK_UP))
	{
		if (data->player->GetVy() < 0)
		{
			data->player->SetVy(acceleratorY);
		}
		else
		{
			data->player->AddVy(acceleratorY);
			if (data->player->GetVy() > MAX_VX)
			{
				data->player->SetVy(MAX_VX);
			}
		}
	}
	else
	{
		data->player->SetVy(0);
	}
}

int JasonClimbingState::GetTop()
{
	return t;
}

void JasonClimbingState::OnKeyDown(int keyCode)
{
	float l, t, r, b = 0;
	data->player->GetBoundingBox(l, t, r, b);
	switch (keyCode)
	{
		case DIK_LEFT:
			if (b >= jumpPoint)
			{
				data->player->AddPosition(-4, 4);
				data->player->SetState(new JasonFallingState(data));
			}
			break;
		case DIK_RIGHT:
			if (b >= jumpPoint)
			{
				data->player->AddPosition(4, 4);
				data->player->SetState(new JasonFallingState(data));
			}
			break;
	}
}