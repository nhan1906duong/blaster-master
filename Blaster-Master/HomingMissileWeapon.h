#pragma once
#include "PlayerBullet.h"

#include "Enemy.h"

#define HomingMissile_VX 0.1f

class HomingMissileWeapon : public PlayerBullet
{
private:
	Enemy* enemy;
public:
	HomingMissileWeapon(Enemy* enemy);
	~HomingMissileWeapon();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

