#pragma once
#include "SophiaState.h"

class SophiaFallingState: public SophiaState
{
private:
	float acceleratorX;
	bool isLeftOrRightPressed;
public:
	SophiaFallingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

