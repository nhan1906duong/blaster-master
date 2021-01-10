#include "JasonClimbingState.h"

#include "Player.h"
#include "Utils.h"

#include "JasonFallingState.h"

JasonClimbingState::JasonClimbingState(PlayerData* data, float l, float t, float r, float b, float jumpPoint, bool isDown) : JasonState(data)
{
	this->l = l;
	this->t = t;
	this->r = r;
	this->b = b;
	this->jumpPoint = jumpPoint;
	float px, py;
	CPlayer::GetInstance()->GetPosition(px, py);
	if (isDown)
	{
		data->player->SetPosition((l + r) / 2 - JASON_STAIR_WIDTH / 2, py);
	}
	else
	{
		data->player->SetPosition((l + r) / 2 - JASON_STAIR_WIDTH / 2, py + 4);
	}
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
			if (data->player->GetVy() < -MAX_JASON_VX)
			{
				data->player->SetVy(-MAX_JASON_VX);
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
			if (data->player->GetVy() > MAX_JASON_VX)
			{
				data->player->SetVy(MAX_JASON_VX);
			}
		}
	}
	else
	{
		data->player->SetVy(0);
	}
}

float JasonClimbingState::GetTop()
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
			if (b >= jumpPoint - 4)
			{
				data->player->AddPosition(-4, 8);
				data->player->SetState(new JasonFallingState(data));
			}
			break;
		case DIK_RIGHT:
			if (b >= jumpPoint - 4)
			{
				data->player->AddPosition(4, 8);
				data->player->SetState(new JasonFallingState(data));
			}
			break;
	}
}