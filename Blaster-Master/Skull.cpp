#include "Skull.h"

#include "Player.h"
#include "Bomb.h"

Skull::Skull(int nx)
{
	SetState(STATE_NORMAL);
	blood = 4;
	vx = nx * SKULL_VX;
	this->nx = nx;
	animation_set = CAnimationSets::GetInstance()->Get(16);
	startNhaDan = 0;
}

void Skull::Render()
{
	int ani = 0;
	if (state == STATE_NHA_DAN)
	{
		ani = 2;
	}
	animation_set->at(beenShot ? ani + 1 : ani)->Render(x, y, 255, nx > 0);
}

void Skull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - startNhaDan > TIME_NHA_DAN && state == STATE_NHA_DAN)
	{
		SetState(STATE_NORMAL);
	}
	Enemy::Update(dt, coObjects);

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

		if (ny == -1)
		{
			vy = 0;
		}
	}

	float midX = CPlayer::GetInstance()->GetMidX();
	if (vx != 0 && ((nx < 0 && x >= midX - 24 && x <= midX) || (nx > 0 && x >= midX  && x <= midX + 24)))
	{
		SetState(STATE_NHA_DAN);
		startNhaDan = GetTickCount64();
		Bomb* bomb = new Bomb(-nx);
		bomb->SetPosition(x - 4 * nx, y + 8 * nx);
		GridManager::GetInstance()->AddObject(bomb);

		nx = -nx;
		vy = SKULL_VY;
		vx = 0;
	}
}

void Skull::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SKULL_WIDTH;
	bottom = y - SKULL_HEIGHT;
}