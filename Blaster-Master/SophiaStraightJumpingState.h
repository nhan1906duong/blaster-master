#pragma once
#include "SophiaStraightState.h"

class SophiaStraightJumpingState: public SophiaStraightState
{
private:
	float acceleratorX, acceleratorY;
	bool isHoldJump;
public:
	SophiaStraightJumpingState(PlayerData* data, bool reset = true);
	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void KeyState(BYTE* states);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void OnKeyUp(int keyCode);
};

