#pragma once
#include "GameObject.h"
#include "PlayerData.h"
#include "SophiaState.h"

#define PLAYER_UNTOUCHABLE_TIME 500

class CPlayer : public CGameObject
{
private:
	bool isOverworld;

	int bloodSophia;
	int bloodJason;

	float sophia_x;
	float sophia_y;
	int sophia_nx;

	bool isSwitchState;

	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	bool isSwitch = false;

	void TruMang();
	
	PlayerData* playerData;

	bool isLeftOrRightPressed = false;


	int IsKeyDown(BYTE* states, int keyCode)
	{
		return (states[keyCode] & 0x80) > 0;
	}

	bool IsSophiaState()
	{
		return dynamic_cast<SophiaState*>(playerData->playerState);
	}

	void Switch();

public:
	CPlayer(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void SetState(PlayerState* state);

	bool SwitchToSophia();

	LPGAMEOBJECT fire();
};