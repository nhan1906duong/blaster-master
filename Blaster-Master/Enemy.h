#pragma once
#include "GameObject.h"

#include "Bullet.h"

#define ENEMY_DIE_STATE -1

class Enemy : public CGameObject
{
protected:
	int blood;
public:
	void BeenShot(Bullet* bullet)
	{
		int power = bullet->GetPower();
		blood -= power;
		if (blood <= 0)
		{
			PrepareToRemove();
		}
	}
};