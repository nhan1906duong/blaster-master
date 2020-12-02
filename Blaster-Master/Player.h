#pragma once
#include "GameObject.h"
#include "PlayerData.h"

#define MARIO_UNTOUCHABLE_TIME 5000


class CPlayer : public CGameObject
{
	CPlayerData* playerData;
	int currentAnimation = 0;
	int level;
	int untouchable;
	DWORD untouchable_start;

	// allow jump
	bool allowJump, allowLie;

	float start_x;			// initial position of Mario at scene
	float start_y;
	int IsKeyDown(int KeyCode);
public:
	CPlayer(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(CPlayerState* newState);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void KeyState(BYTE* states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};