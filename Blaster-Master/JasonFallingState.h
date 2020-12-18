#pragma once
#include "JasonState.h"

class JasonFallingState: public JasonState
{
private:
	float acceleratorX;
	bool isLeftOrRightPressed;
public:
	JasonFallingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

