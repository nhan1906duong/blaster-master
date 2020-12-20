#pragma once
#include "SophiaStraightState.h"

class SophiaStraightRunningState: public SophiaStraightState
{
private:
	float acceleratorX;
public:
	SophiaStraightRunningState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
};

