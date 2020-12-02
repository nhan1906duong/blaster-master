#pragma once
#include "PlayerState.h"

class JasonLieingState: public CPlayerState
{
private:
	const float MAX_SPEED_VX = 0.05;
	float acceleratorX;
public:
	JasonLieingState(CPlayerData* playerData);
	~JasonLieingState();

	void Update(DWORD dt);
	void KeyState(BYTE* states);

	State GetState();
	int GetCurrentAnimationId();
};

