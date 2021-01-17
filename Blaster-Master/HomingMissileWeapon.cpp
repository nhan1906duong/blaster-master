#include "HomingMissileWeapon.h"

#include "Utils.h"
#include "Collision.h"
#include "Area2Scene.h"

#include "Mine.h"

HomingMissileWeapon::HomingMissileWeapon(Enemy* enemy)
{
	this->enemy = enemy;
	animation_set = CAnimationSets::GetInstance()->Get(32);
}

HomingMissileWeapon::~HomingMissileWeapon()
{
	if (enemy != NULL)
	{
		delete enemy;
	}
}

void HomingMissileWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

	CGameObject::Update(dt);

	x += dx;
	y += dy;

	float eMidX, eMidY;
	enemy->GetMidPosition(eMidX, eMidY);
	float midX, midY;
	GetMidPosition(midX, midY);

	float distanceX = (midX > eMidX) ? midX - eMidX : eMidX - midX;
	float distanceY = (midY > eMidY) ? midY - eMidY : eMidY - midY;

	if (distanceX > distanceY)
	{
		nx = eMidX > midX ? 1 : -1;
		vx = HomingMissile_VX * nx;
		vy = 0.0f;
	}
	else
	{
		vy = HomingMissile_VX * (eMidY > midY ? 1 : -1);
		vx = 0;
	}

	if (Collision::CheckContain(this, enemy))
	{
		PrepareToRemove();
		if (dynamic_cast<Mine*>(enemy))
		{
			dynamic_cast<Mine*>(enemy)->PrepareToRemove();
		}
		else
		{
			enemy->PrepareToRemove();
		}
		((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y);
	}
}

void HomingMissileWeapon::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx < 0);
}

void HomingMissileWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 9;
	bottom = y - 6;
}