#pragma once
#include "GameObject.h"

#include "Bullet.h"

#define BEEN_SHOT_TIME	1000

#define ENEMY_DIE_STATE -1

class Enemy : public CGameObject
{
protected:
	int blood;
	int beenShot = 0;
	DWORD beenShotTime;

	void CheckShotTime()
	{
		if (beenShot)
		{
			DWORD current = GetTickCount();
			if (current - beenShotTime > BEEN_SHOT_TIME)
			{
				beenShotTime = 0;
				beenShot = 0;
			}
		}
	}
public:
	void BeenShot(Bullet* bullet)
	{
		beenShot = 1;
		beenShotTime = GetTickCount();
		int power = bullet->GetPower();
		blood -= power;
		if (blood <= 0)
		{
			PrepareToRemove();
		}
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		CheckShotTime();
	}
};