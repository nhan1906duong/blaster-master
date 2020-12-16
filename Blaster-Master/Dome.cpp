#include "Dome.h"
#include "Bullet.h"

Dome::Dome()
{

}

void Dome::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Dome::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	//vy += GameDefine::ACCELERATOR_GRAVITY * dt;


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

		if (nx != 0)
		{
			vx = -vx;
		}
		if (ny != 0)
		{
			vy = 0;
		}

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Bullet*>(e->obj))
			{
				shouldRemove = true;
			}
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Dome::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOME_WIDTH;
	bottom = y - DOME_HEIGHT;
}