#pragma once
#include "JasonState.h"

class JasonCrawlingState: public JasonState
{
private:
	float acceleratorX;
	bool isLeftOrRightPressed;
public:
	JasonCrawlingState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
};

