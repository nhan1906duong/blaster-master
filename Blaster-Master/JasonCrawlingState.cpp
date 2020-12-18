#include "JasonCrawlingState.h"

JasonCrawlingState::JasonCrawlingState(PlayerData* data) : JasonState(data)
{

}

int JasonCrawlingState::CurrentAnimationId()
{
	return 1;
}

void JasonCrawlingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void JasonCrawlingState::KeyState(BYTE* states)
{

}

void JasonCrawlingState::OnKeyDown(int keyCode)
{

}