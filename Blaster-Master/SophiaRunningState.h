#pragma once
#include "SophiaState.h"
class SophiaRunningState: public SophiaState
{
private:
	float acceleratorX;
public:
	SophiaRunningState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

