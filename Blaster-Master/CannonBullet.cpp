#include "CannonBullet.h"
#include "Player.h"
#include "Brick.h"
#include "Bomb.h"

CannonBullet::CannonBullet()
{
	animation_set = CAnimationSets::GetInstance()->Get(24);
}

void CannonBullet::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CannonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isVerState) {
		SetVx(0.0f);
		SetVy(VectorBullter);
	}
	else {
		SetVy(0.0f);
		SetVx(VectorBullter);
	}

	Bullet::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, brickNx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, brickNx, ny, rdx, rdy);

		x += min_tx * dx + 0.01f * brickNx;
		y += min_ty * dy + 0.01f * ny;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj) && e->nx != 0)
			{
				/*Bomb* bomb = new Bomb(-nx);
				bomb->SetPosition(x, y);
				GridManager::GetInstance()->AddObject(bomb);*/
			}
		
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CannonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SIZE;
	bottom = y - BULLET_SIZE;
}
