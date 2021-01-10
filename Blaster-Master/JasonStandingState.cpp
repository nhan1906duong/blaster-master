#include "JasonStandingState.h"

#include "JasonRunningState.h"
#include "JasonJumpingState.h"
#include "JasonLieingState.h"
#include "JasonClimbingState.h"

#include "Player.h"
#include "Utils.h"

#include "Stair.h"
#include "Area2Scene.h"

JasonStandingState::JasonStandingState(PlayerData* data) : JasonState(data)
{
	DebugOut(L"JasonStandingState\n");
	data->player->SetVx(0);
	data->player->SetVy(0);
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
		case DIK_UP:
			{
				float l, t, r, b, jumpPoint;
				if (((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->HasStairNearBy(l, t, r, b, jumpPoint))
				{
					data->player->SetState(new JasonClimbingState(data, l, t, r, b, jumpPoint));
				}
				break;
			}
		case DIK_X:
			{
				data->player->SetState(new JasonJumpingState(data));
				break;
			}
		case DIK_DOWN:
			{
				float l, t, r, b, jumpPoint;
				if (((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->HasStairNearBy(l, t, r, b, jumpPoint))
				{
					data->player->SetState(new JasonClimbingState(data, l, t, r, b, jumpPoint, true));
				}
				else
				{
					data->player->AddPosition(0, -7.9);
					data->player->SetState(new JasonLieingState(data));
				}
				break;
			}
	}
}