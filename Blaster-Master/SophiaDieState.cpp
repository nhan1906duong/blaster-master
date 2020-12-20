#include "SophiaDieState.h"

SophiaDieState::SophiaDieState(PlayerData* data) : SophiaState(data)
{

}

int SophiaDieState::CurrentAnimationId()
{
	return 14;
}

void SophiaDieState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}