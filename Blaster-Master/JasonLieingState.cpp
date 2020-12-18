#include "JasonLieingState.h"

#include "Player.h"
#include "JasonCrawlingState.h"
#include "JasonStandingState.h"

#include "Utils.h"

JasonLieingState::JasonLieingState(PlayerData* data) : JasonState(data)
{
	DebugOut(L"JasonLieingState\n");
	data->player->SetVx(0);
	data->player->SetVy(0);
}

int JasonLieingState::CurrentAnimationId()
{
	return 3;
}

void JasonLieingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + JASON_LIE_WIDTH;
	bottom = top - JASON_LIE_HEIGHT;
}

void JasonLieingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_LEFT))
	{
		data->player->SetNx(-1);
		data->player->SetState(new JasonCrawlingState(data));
	}
	else if (IsKeyDown(states, DIK_RIGHT))
	{
		data->player->SetNx(1);
		data->player->SetState(new JasonCrawlingState(data));
	}
}

void JasonLieingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			data->player->AddPosition(0, 8.5);
			data->player->SetState(new JasonStandingState(data));
			break;
	}
}