#pragma once
#include "GameObject.h"

class EnemyBullet: public CGameObject
{
protected:
	int power;
public:
	int GetPower()
	{
		return power;
	}
};

