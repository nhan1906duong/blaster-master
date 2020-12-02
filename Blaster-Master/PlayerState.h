#pragma once
#include <d3dx9.h>
#include "PlayerData.h"
#include "Game.h"

class CPlayerState
{
public:
	enum State
	{
		Standing,
		Walking,
		Jumping,
		Falling,
		Lieing,
		GoingStair
	};

	virtual void Update(DWORD dt) {};
	virtual void KeyState(BYTE* states) {};
	virtual State GetState() = 0;
	virtual int GetCurrentAnimationId() = 0;

protected:
	CPlayerState(CPlayerData* playerData) { this->playerData = playerData; };
	CPlayerState() {};

	int IsKeyDown(int KeyCode) { return CGame::GetInstance()->IsKeyDown(KeyCode); };
	CPlayerData* playerData;
};
