#include "JasonCrawlingState.h"

#include "Player.h"
#include "JasonLieingState.h"

#include "JasonStandingState.h"
#include "JasonRunningState.h"

JasonCrawlingState::JasonCrawlingState(PlayerData* data) : JasonState(data)
{
	acceleratorX = 0.01f;

	isLeftOrRightPressed = false;
}

int JasonCrawlingState::CurrentAnimationId()
{
	return 4;
}

void JasonCrawlingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_LIE_WIDTH;
	bottom = top - JASON_LIE_HEIGHT;
}

void JasonCrawlingState::KeyState(BYTE* states)
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
			if (data->player->GetVx() < -MAX_CRAWLING_VX)
			{
				data->player->SetVx(-MAX_CRAWLING_VX);
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
			if (data->player->GetVx() > MAX_CRAWLING_VX)
			{
				data->player->SetVx(MAX_CRAWLING_VX);
			}
		}
	}
	else
	{
		isLeftOrRightPressed = false;
		data->player->SetState(new JasonLieingState(data));
	}
}

void JasonCrawlingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			data->player->AddPosition(0, 8.5);
			if (isLeftOrRightPressed)
			{
				data->player->SetState(new JasonRunningState(data));
			}
			else 
				data->player->SetState(new JasonStandingState(data));
			break;
	}
}