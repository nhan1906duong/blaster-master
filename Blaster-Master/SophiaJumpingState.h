#pragma once
#include "SophiaState.h"

class SophiaJumpingState: public SophiaState
{
private:
	float acceleratorX, acceleratorY;
	bool isHoldJump;
public:
	SophiaJumpingState(PlayerData* data);
	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void KeyState(BYTE* states);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

