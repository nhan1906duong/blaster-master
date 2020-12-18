#include "JasonJumpingState.h"
#include "Player.h"

JasonJumpingState::JasonJumpingState(PlayerData* data): JasonState(data)
{
	data->player->SetVy(0.7f);
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

void JasonJumpingState::KeyState(BYTE* state)
{

}

void JasonJumpingState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	data->player->AddVy(0.03);
	if (data->player->GetVy() > 0.3)
	{
		data->player->SetVy(0.3);
	}
}