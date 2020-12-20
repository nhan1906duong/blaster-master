#pragma once
#include "SophiaStraightState.h"

class SophiaStraightFallingState: public SophiaStraightState
{
private:
	float acceleratorX;
	bool isLeftOrRightPressed;
public:
	SophiaStraightFallingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
};

