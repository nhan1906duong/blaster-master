#pragma once
#include "JasonState.h"

#define MAX_VX 0.05f

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

