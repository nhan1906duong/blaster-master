#pragma once
#include "GameObject.h"

class Bullet: public CGameObject
{
protected:
	int power;
public:
	int GetPower()
	{
		return power;
	}

	void ChangePower(int power)
	{
		this->power += power;
	}
};

