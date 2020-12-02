#pragma once
#include "PlayerState.h"
class CPlayerJumpingState: public CPlayerState
{
public:
	CPlayerJumpingState(CPlayerData* playerData);
	~CPlayerJumpingState();

	void KeyState(BYTE* states);
	void Update(DWORD dt);
	
	State GetState();
	int GetCurrentAnimationId();
private:
	const float MAX_SPEED_VX = 0.05;
	const float MAX_SPEED_JUMP = 0.06f;
	float acceleratorX;
	float acceleratorY;
};

