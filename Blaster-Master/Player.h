#pragma once
#include "GameObject.h"
#include "PlayerData.h"
#include "SophiaState.h"

#define PLAYER_UNTOUCHABLE_TIME 1000

class CPlayer : public CGameObject
{
private:
	static CPlayer* __instance;
	CPlayer();
	bool isOverworld;

	int bloodSophia;
	int bloodJason;

	float sophia_x;
	float sophia_y;
	int sophia_nx;

	bool isSwitchState;

	int untouchable;
	ULONGLONG untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	void TruMang();
	
	PlayerData* playerData;

	bool isLeftOrRightPressed = false;
	bool isUpPressed = false;

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
	static CPlayer* GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void StartUntouchable();

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void KeyState(BYTE* states);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void SetState(PlayerState* state);

	bool SwitchToSophia();
	
	int GetBlood()
	{
		if (IsSophiaState())
		{
			return bloodSophia;
		}
		else
		{
			return bloodJason;
		}
	}

	bool IsALiveAndTouchable();

	bool IsUntouchable();

	void fire(int type);

	void SwitchToOverworldState();

	void BackFromOverworld();
	PlayerData* GetPlayerData() {
		return playerData;
	};

	bool IsDie();
};