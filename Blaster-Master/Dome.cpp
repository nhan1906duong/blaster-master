#include "Dome.h"
#include "Bullet.h"

Dome::Dome(int initDirection)
{
	animation_set = CAnimationSets::GetInstance()->Get(11);
	blood = 4;

	this->initDirection = initDirection;

	switch (initDirection)
	{
		case 3:
			SetVx(-0.03f);
			break;
	}
}

void Dome::Render()
{
	animation_set->at(initDirection)->Render(x, y);
}

void Dome::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

		for (int i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				float left, top, right, bottom;
				brick->GetBoundingBox(left, top, right, bottom);


				if (e->nx == -1) // LeftToRight
				{
					initDirection = 2;
					SetVx(0.0f);
					SetVy(-0.03f);
				}
				else if (e->nx == 1) // RightToLeft
				{
					initDirection = 0;
					SetVx(0.0f);
					SetVy(0.03f);
				}

				if (e->ny == -1) // BottomToTop
				{
					initDirection = 1;
					SetVx(0.03);
					SetVy(0.0);
				}
				else if (e->ny == 1) // TopToBottom
				{
					initDirection = 3;
					SetVx(-0.03);
					SetVy(0.0);
				}

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