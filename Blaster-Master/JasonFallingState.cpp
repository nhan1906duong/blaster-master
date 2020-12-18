#include "JasonFallingState.h"
#include "Player.h"

JasonFallingState::JasonFallingState(PlayerData* data) : JasonState(data)
{

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

}

void JasonFallingState::OnKeyDown(int keyCode)
{

}