#include "JasonStandingState.h"

#include "JasonRunningState.h"
#include "JasonJumpingState.h"

#include "Player.h"

JasonStandingState::JasonStandingState(PlayerData* data) : JasonState(data)
{
	data->player->SetVx(0);
}

int JasonStandingState::CurrentAnimationId()
{
	return 0;
}

void JasonStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_STANDING_WIDTH;
	bottom = top - JASON_STANDING_HEIGHT;
}

void JasonStandingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_LEFT))
	{
		data->player->SetNx(-1);
		data->player->SetState(new JasonRunningState(data));
	}
	else if (IsKeyDown(states, DIK_RIGHT))
	{
		data->player->SetNx(1);
		data->player->SetState(new JasonRunningState(data));
	}
}

void JasonStandingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		case DIK_X:
			data->player->SetState(new JasonJumpingState(data));
			break;
	}
}