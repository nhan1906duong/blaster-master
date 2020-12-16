#include "SophiaBullet.h"
#include "Game.h"
#include "Area2Scene.h"

/** direct	1	LeftToRight
*			2	RightToLeft
*			3	BottomToTop
*/
SophiaBullet::SophiaBullet(int direct)
{
	this->direct = direct;
	if (direct == 1)
	{
		vx = 0.03f;
	}
	else if (direct == 2)
	{
		vx = -0.03f;
	}
	else
	{
		vy = 0.03f;
	}
	animation_set = CAnimationSets::GetInstance()->Get(18);
}

void SophiaBullet::Render()
{
	int ani;
	if (direct == 3)
	{
		ani = 1;
	} 
	else
	{
		ani = 0;
	}
	animation_set->at(ani)->Render(x, y, 255, direct == 1);
}

void SophiaBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SOPHIA_BULLET_WIDTH;
	bottom = y - SOPHIA_BULLET_HEIGHT;
}

void SophiaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;
		vx = vy = 0;
		PrepareToRemove();
		float collision_x, collision_y;
		if (direct == 1)
		{
			collision_x = x + 12;
			collision_y = y;
		}
		else
		{
			collision_x = x - 12;
			collision_y = y;
		}
		((CArea2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(collision_x, collision_y);
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}