#pragma once
#include "JasonState.h"

class JasonDieState: public JasonState
{
public:
	JasonDieState(PlayerData* data);

	int CurrentAnimationId();
	void GetBoundingBox(float&, float&, float&, float&);
};

