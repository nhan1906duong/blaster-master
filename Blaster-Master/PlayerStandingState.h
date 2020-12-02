#pragma once
#include "PlayerState.h"

class CPlayerStandingState: public CPlayerState
{
public:
	CPlayerStandingState(CPlayerData* playerData);
	~CPlayerStandingState();

	void KeyState(BYTE* states);

	State GetState();
	int GetCurrentAnimationId();
};

