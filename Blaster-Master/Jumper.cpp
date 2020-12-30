#include "Jumper.h"

#include "Player.h"

#include "GameDefine.h"

Jumper::Jumper()
{
	SetState(STATE_FALLING);
	nx = 1;
	vx = VX;
	animation_set = CAnimationSets::GetInstance()->Get(13);
}

void Jumper::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx > 0);
}

void Jumper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_JUMPING)
	{
		AddVy(0.09);
		if (GetVy() > 0.15)
		{
			SetVy(0.15);
			SetState(STATE_FALLING);
		}
	}

	vy += GameDefine::ACCELERATOR_GRAVITY;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (state != STATE_FALLING &&
			state != STATE_JUMPING)
		{
			state = STATE_FALLING;
		}
	}
	else
	{
		float min_tx, min_ty, brickNx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, brickNx, ny, rdx, rdy);

		x += min_tx * dx + 0.01f * brickNx;
		y += min_ty * dy + 0.01f * ny;

		for (int i = 0; i < coEvents.size(); ++i)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (ny == 1)
				{
					currentBrick = dynamic_cast<CBrick*>(e->obj);
					break;
				}
			}
		}

		if (ny != 0) vy = 0;

		if (ny != 0)
		{
			vy = 0;
			if (ny == 1)
			{
				state = STATE_WALKING;
			}
			else if (ny == -1)
			{
				state = STATE_FALLING;
			}
		}

		if (brickNx != 0)
		{
			this->nx = -this->nx;
			vx = -vx;
		}
		else
		{
			if (currentBrick)
			{
				float bLeft, bTop, bRight, bBottom;
				currentBrick->GetBoundingBox(bLeft, bTop, bRight, bBottom);

				float jLeft, jTop, jRight, jBottom;
				GetBoundingBox(jLeft, jTop, jRight, jBottom);

				if (state == STATE_WALKING && x > bRight - (jRight - jLeft))
				{
					x = bRight - (jRight - jLeft);
					vx = -vx;
					nx = -nx;
				}
			}
		}

		if (CPlayer::GetInstance()->IsALiveAndTouchable())
		{

			int randomState = rand() % 100;
			if (randomState > 96)
			{
				SetState(STATE_JUMPING);
			}
		}
		else
		{
			state = STATE_WALKING;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Jumper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + JUMPER_WIDTH;
	bottom = y - JUMPER_HEIGHT;
}