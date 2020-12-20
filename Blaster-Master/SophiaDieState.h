#pragma once
#include "SophiaState.h"

class SophiaDieState: public SophiaState
{
public:
	SophiaDieState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
};

