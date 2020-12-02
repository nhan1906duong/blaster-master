#pragma once
#include "PlayerState.h"

class JasonGoingStairState: public CPlayerState
{
private:
	const float MAX_SPEED_GO_STAIR = 0.04;
	float acceleratorY;
public:
	JasonGoingStairState(CPlayerData* playerData);
	~JasonGoingStairState();

	void KeyState(BYTE* states);

	State GetState();
	int GetCurrentAnimationId();
};

