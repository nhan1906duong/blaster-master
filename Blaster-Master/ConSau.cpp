#include "ConSau.h"
#include "GameDefine.h"

void ConSau::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CONSAU_WIDTH;
	bottom = y - CONSAU_HEIGHT;
}

void ConSau::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vy += GameDefine::ACCELERATOR_GRAVITY * dt;


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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0)
		{
			vx = -vx;
			this->nx = nx;
		}
		if (ny != 0)
		{
			vy = 0;
			SetState(STATE_MOVE);
		}
		else
		{
			SetState(STATE_FALL);
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void ConSau::Render()
{
	int ani;
	if (state == STATE_MOVE)
	{
		ani = 1;
	}
	else
	{
		ani = 0;
	}
	animation_set->at(ani)->Render(x, y, 255, nx > 0);
}

ConSau::ConSau()
{
	SetState(STATE_FALL);
	vx = -MOVE_SPEED;
	nx = -1;
}