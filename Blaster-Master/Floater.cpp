#include "Floater.h"

Floater::Floater()
{
	SetVx(-0.03f);
	SetVy(0.03f);
	animation_set = CAnimationSets::GetInstance()->Get(12);
}

void Floater::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Floater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

		if (nx == -1) // LeftToRight
		{
			SetVx(-0.03f);
		}
		else if (nx == 1) // RightToLeft
		{
			SetVx(0.03f);
		}

		if (ny == -1) // BottomToTop
		{
			SetVy(-0.03f);
		}
		else if (ny == 1) //TopToBottom
		{
			SetVy(0.03f);
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Floater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOATER_WIDTH;
	bottom = y - FLOATER_HEIGHT;
}