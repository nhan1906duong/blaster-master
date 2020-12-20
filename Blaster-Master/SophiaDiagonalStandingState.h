#pragma once
#include "SophiaState.h"

class SophiaDiagonalStandingState: public SophiaState
{
private:
	int times;
public:
	SophiaDiagonalStandingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState(BYTE* states);
};

