#pragma once
#include "JasonState.h"

class JasonStandingState: public JasonState
{
public:
	JasonStandingState(PlayerData* data);
	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

