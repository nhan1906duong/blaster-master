#pragma once
#include "GameObject.h"

#define PLAYER_UNTOUCHABLE_TIME 5000


#define PLAYER_STATE_IDLE			0
#define PLAYER_STATE_WALKING_RIGHT	100
#define PLAYER_STATE_WALKING_LEFT	200
#define PLAYER_STATE_JUMP			300
#define PLAYER_STATE_DIE			400

class CPlayer : public CGameObject
{
private:
	bool isSophia;
	bool isOverworld;

	int bloodSophia;
	int bloodJason;

	float sophia_x;
	float sophia_y;

	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	CPlayer(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void KeyState(BYTE* states);
};