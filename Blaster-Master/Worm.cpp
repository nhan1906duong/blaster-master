#include "Worm.h"
#include "GameDefine.h"

#include "Utils.h"
#include "ChongNhon.h"
#include "Bullet.h"

#include "Player.h"

Worm::Worm()
{
	animation_set = CAnimationSets::GetInstance()->Get(10);
	SetState(STATE_FALLING);
	vx = -MOVE_SPEED;
	nx = -1;
	blood = 4;
}

void Worm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CONSAU_WIDTH;
	bottom = y - CONSAU_HEIGHT;
}

void Worm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == STATE_JUMPING)
	{
		AddVy(0.02);
		if (GetVy() > 0.2)
		{
			SetVy(0.2);
			SetState(STATE_FALLING);
		}
	}

	vy += GameDefine::ACCELERATOR_GRAVITY;

	Enemy::Update(dt, coObjects);

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


		CPlayer* player = CPlayer::GetInstance();

		if (ny != 0)
		{
			vy = 0;
			if (ny == 1)
			{
				state = STATE_MOVE;
			}
			else if (ny == -1)
			{
				state = STATE_FALLING;
			}
		}

		if (brickNx != 0)
		{
			if (!player->IsALiveAndTouchable())
			{
				this->nx = -this->nx;
				vx = -vx;
			}
			else
			{
				if (state == STATE_MOVE)
				{
					SetVy(0.01);
					SetState(STATE_JUMPING);
				}
			}
		}

		if (player->IsALiveAndTouchable())
		{
			float left, top, right, bottom;
			player->GetBoundingBox(left, top, right, bottom);
			if (x < left + 5)
			{
				this->nx = 1;
				SetVx(MOVE_SPEED);
			}
			else if (x > right + 5)
			{
				this->nx = -1;
				SetVx(-MOVE_SPEED);
			}
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Worm::Render()
{
	int ani;
	if (state == STATE_MOVE)
	{
		ani = 2;
	}
	else
	{
		ani = 0;
	}
	animation_set->at(beenShot ? ani + 1 : ani)->Render(x, y, 255, nx > 0);
	//RenderBoundingBox();
}

void Worm::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_FALLING:
		vy = 0.0f;
		break;
	case STATE_JUMPING:
		vy = 0.1f;
		break;
	}
}