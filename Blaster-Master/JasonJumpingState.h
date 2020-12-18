#pragma once
#include "JasonState.h"

class JasonJumpingState: public JasonState
{
public:
	JasonJumpingState(PlayerData* data);
	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void KeyState(BYTE* states);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

