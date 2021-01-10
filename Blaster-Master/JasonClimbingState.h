#pragma once
#include "JasonState.h"

class JasonClimbingState: public JasonState
{
private:
	float acceleratorY;
	float l, t, r, b;
	float jumpPoint;
public:
	JasonClimbingState(PlayerData* data, float l, float t, float r, float b, float jumpPoint, bool isDown = false);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
	float GetTop();
};

