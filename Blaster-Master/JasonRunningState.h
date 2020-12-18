#pragma once
#include "JasonState.h"

class JasonRunningState: public JasonState
{
private:
	float acceleratorX;
public:
	JasonRunningState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

