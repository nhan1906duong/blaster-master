#pragma once
#include "PlayerState.h"

class CPlayerWalkingState: public CPlayerState
{
private:
	const float MAX_SPEED_VX = 0.05;
	float acceleratorX;
public:
	CPlayerWalkingState(CPlayerData* playerData);
	~CPlayerWalkingState();

	void Update(DWORD dt);
	void KeyState(BYTE* states);

	State GetState();
	int GetCurrentAnimationId();
};

