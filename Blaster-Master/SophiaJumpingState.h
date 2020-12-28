#pragma once
#include "SophiaState.h"

class SophiaJumpingState: public SophiaState
{
private:
	float acceleratorX, acceleratorY;
	bool isHoldJump, isLeftOrRightPressed;
public:
	SophiaJumpingState(PlayerData* data, bool reset = true);
	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void KeyState(BYTE* states);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void OnKeyDown(int keyCode);
};

