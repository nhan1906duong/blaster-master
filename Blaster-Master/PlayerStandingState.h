#pragma once
#include "PlayerState.h"

class CPlayerStandingState: public CPlayerState
{
private:
	float acceleratorY;
	const float MIN_SPEED_JUMP = -0.06f;
public:
	CPlayerStandingState(CPlayerData* playerData);
	~CPlayerStandingState();

	void KeyState(BYTE* states);
	void Update(DWORD dt);

	State GetState();
	int GetCurrentAnimationId();
};

