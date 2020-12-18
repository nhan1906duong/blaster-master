#pragma once
#include "JasonState.h"

class JasonJumpingState: public JasonState
{
private:
	float acceleratorX;
public:
	JasonJumpingState(PlayerData* data);
	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void KeyState(BYTE* states);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

