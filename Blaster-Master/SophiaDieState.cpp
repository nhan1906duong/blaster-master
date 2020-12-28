#include "SophiaDieState.h"

SophiaDieState::SophiaDieState(PlayerData* data) : SophiaState(data)
{

}

int SophiaDieState::CurrentAnimationId()
{
	return 30;
}

void SophiaDieState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}