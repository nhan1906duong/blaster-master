#pragma once
#include "GameObject.h"

#include "Bullet.h"
#include "HPItem.h"
#include "GridManager.h"

#define BEEN_SHOT_TIME	1000

#define ENEMY_DIE_STATE -1

class Enemy : public CGameObject
{
private:
	bool isAppear = false;
protected:
	int blood = 4;
	int beenShot = 0;
	ULONGLONG beenShotTime = 0;

	void CheckShotTime()
	{
		if (beenShot)
		{
			ULONGLONG current = GetTickCount64();
			if (current - beenShotTime > BEEN_SHOT_TIME)
			{
				beenShotTime = 0;
				beenShot = 0;
			}
		}
	}
public:
	bool isLock = false;
	bool IsAppear()
	{
		return isAppear;
	}

	void SetAppear()
	{
		isAppear = true;
	}

	void BeenShot(Bullet* bullet)
	{
		beenShot = 1;
		beenShotTime = GetTickCount64();
		int power = bullet->GetPower();
		blood -= power;
		if (blood <= 0)
		{
			PrepareToRemove();
		}
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		CGameObject::Update(dt);
		CheckShotTime();
	}

	void PrepareToRemove()
	{
		int randomState = rand() % 100;
		if (randomState > 50)
		{
			HPItem* item = new HPItem();
			item->SetPosition(x, y);
			GridManager::GetInstance()->AddObject(item);
		}
		CGameObject::PrepareToRemove();
	}
};