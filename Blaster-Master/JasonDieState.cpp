#include "JasonDieState.h"

JasonDieState::JasonDieState(PlayerData* data) : JasonState(data)
{

}

int JasonDieState::CurrentAnimationId()
{
	return 6;
}

void JasonDieState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}