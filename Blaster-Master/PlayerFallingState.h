#pragma once
#include "PlayerState.h"

class CPlayerFallingState: public CPlayerState
{
public:
	CPlayerFallingState(CPlayerData* playerData);
	~CPlayerFallingState();

	void KeyState(BYTE* states);
	void Update(DWORD dt);

	State GetState();
	int GetCurrentAnimationId();
private:
	const float MAX_SPEED_VX = 0.05;
	const float MIN_SPEED_JUMP = -0.06f;
	float acceleratorX;
	float acceleratorY;

	bool isLeftOrRightKeyPress;
};

