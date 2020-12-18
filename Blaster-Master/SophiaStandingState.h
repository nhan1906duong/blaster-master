#pragma once
#include "SophiaState.h"


class SophiaStandingState: public SophiaState
{
private:
	int huong; // 0: nam ngang, 1: huong xeo, 2: huong
	DWORD temp;

public:
	SophiaStandingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState(BYTE* states);
};

