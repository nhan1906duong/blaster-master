#include "Floater.h"

#include "FloaterBullet.h"
#include "Player.h"
#include "GridManager.h"

Floater::Floater(int timeDelay)
{
	blood = 4;
	SetVx(-0.03f);
	SetVy(0.03f);
	animation_set = CAnimationSets::GetInstance()->Get(12);
	this->timeDelay = timeDelay;
	firstAppear = false;
}

void Floater::Render()
{
	int ani = 0;
	if (beenShot)
	{
		ani = 1;
	}
	animation_set->at(ani)->Render(x, y);
}

void Floater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (!firstAppear)
	{
		firstAppear = true;
		lastShoot = GetTickCount();
	}
	else
	{
		if (GetTickCount() - lastShoot > PERIOD_BEETWEEN_SHOOT + timeDelay)
		{
			lastShoot = GetTickCount();
			float pX, pY;
			CPlayer::GetInstance()->GetMidPosition(pX, pY);
			float midX, midY;
			GetMidPosition(midX, midY);

			float ratioX = midX - pX;
			float ratioY = midY - pY;

			if (!(ratioX == 0 && ratioY == 0))
			{
				FloaterBullet* bullet = new FloaterBullet(ratioX, ratioY);
				bullet->SetPosition(midX, midY);
				GridManager::GetInstance()->AddObject(bullet);
			}
		}
	}


	Enemy::Update(dt, coObjects);

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