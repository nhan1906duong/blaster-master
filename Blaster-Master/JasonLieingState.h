#pragma once
#include "JasonState.h"

class JasonLieingState : public JasonState
{
public:
	JasonLieingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

